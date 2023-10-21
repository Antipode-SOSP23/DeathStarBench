#include "../include/monitor_mongodb.h"

using namespace rendezvous;

DatastoreMonitorMongodb::DatastoreMonitorMongodb(mongoc_client_pool_t * mongodb_client_pool, 
    std::string database_name, std::string collection_name) : 
    _client_pool(mongodb_client_pool), _database_name(database_name), _collection_name(collection_name) {
        _init_connections();
}

// mongodb change streams
DatastoreMonitorMongodb::DatastoreMonitorMongodb(mongoc_client_pool_t * mongodb_client_pool, 
    std::string database_name, std::string collection_name, 
    std::string service, std::string tag, std::string region, std::string addr, int port) : 
    _client_pool(mongodb_client_pool), _database_name(database_name), _collection_name(collection_name), 
    _region(region), _service(service), _tag(tag) {
        _init_connections();
        auto channel = grpc::CreateChannel(addr + ":" + std::to_string(port), grpc::InsecureChannelCredentials());
        _server = rendezvous::ClientService::NewStub(channel);
}


DatastoreMonitorMongodb::~DatastoreMonitorMongodb() {
    if (_collection) {
        mongoc_collection_destroy(_collection);
    }
    if (_client) {
        mongoc_client_pool_push(_client_pool, _client);
    }
}

// -------
// Helpers
// -------
void DatastoreMonitorMongodb::_init_connections() {
    if (!_client) {
        _client = mongoc_client_pool_pop(_client_pool);
        if (!_client) {
            exit(EXIT_FAILURE);
        }
        LOG(info) << "[INIT CONNECTIONS] initialized client";

        if (!_collection) {
            _collection = mongoc_client_get_collection(_client, _database_name.c_str(), _collection_name.c_str());
            if (!_collection) {
                exit(EXIT_FAILURE);
            }
            LOG(info) << "[INIT CONNECTIONS] initialized collection";
        }
    }
}

// -------------------------
// Rendezvous Implementation
// -------------------------
bool DatastoreMonitorMongodb::find_metadata(const std::string& bid) {
    bson_error_t error;
    bson_t reply;

    bson_t * filter = bson_new();
    BSON_APPEND_UTF8(filter, "rv_bid", bid.c_str());
    
    //LOG(debug) << "[FIND METADATA] searching for bid = " << bid;

    mongoc_cursor_t * cursor;

    cursor = mongoc_collection_find_with_opts(_collection, filter, nullptr, nullptr);

    const bson_t * doc;
    bool found = mongoc_cursor_next(cursor, &doc);
    if (found) {
        char * json_char = bson_as_json(doc, nullptr);
        json json = json::parse(json_char);
        std::cout << json.dump() << std::endl;

        bson_free(json_char);
        bson_destroy(filter);
        mongoc_cursor_destroy(cursor);
        return true;
    }

    if (mongoc_cursor_error(cursor, &error)) {
        bson_destroy(filter);
        mongoc_cursor_destroy(cursor);
        LOG(error) << "[FIND METADATA] Error reading cursor while finding metadata";
        return false;
    }
    
    bson_destroy(filter);
    mongoc_cursor_destroy(cursor);
    //LOG(debug) << "[FIND METADATA] Branch with bid " << bid << " not found!";
    return false;
}

// ---------------------
// MongoDB Change Stream
// ---------------------
void DatastoreMonitorMongodb::monitor_branches_change_stream() {
    _init_connections();
    grpc::Status status;
    rendezvous::CloseBranchMessage request;
    request.set_region(_region);

    bson_t * pipeline = bson_new();

    bson_t match, op;
    BSON_APPEND_DOCUMENT_BEGIN(pipeline, "0", &match);
    BSON_APPEND_DOCUMENT_BEGIN(&match, "$match", &op);
    BSON_APPEND_UTF8(&op, "operationType", "insert");
    bson_append_document_end(&match, &op);
    bson_append_document_end(pipeline, &match);

    bson_t * ops = bson_new();
    BSON_APPEND_INT64(ops, "maxAwaitTimeMS", CHANGE_STREAM_TIMEOUT_MS);
    
    //LOG(debug) << "[MONGODB WATCHES] Initializing stream...";
    mongoc_change_stream_t * stream = mongoc_collection_watch(_collection, pipeline, ops);

    const bson_t * doc;
    while (mongoc_change_stream_next(stream, &doc)) {
        char * doc_json_char = bson_as_json(doc, nullptr);
        json doc_json = json::parse(doc_json_char);
        //LOG(debug) << "[MONGODB WATCHES] Received change: " << doc_json_char;
        const std::string& bid = doc_json["bid"];

        grpc::ClientContext context;
        rendezvous::Empty response;
        request.set_bid(bid);
        //LOG(debug) << "[MONGODB WATCHES] Closing branch with bid = " << bid;
        status = _server->CloseBranch(&context, request, &response);

        if (status.ok()) {
            std::cout << "[MONGODB WATCHES] Closed branch for bid = " << doc_json["bid"] << std::endl;
        } else {
            _handle_grpc_error(status);
        }

        bson_free(doc_json_char);
    }
    mongoc_change_stream_destroy(stream);
    bson_free(ops);
    bson_free(pipeline);
}

void DatastoreMonitorMongodb::_handle_grpc_error(grpc::Status status) {
    switch (status.error_code()) {
        case grpc::StatusCode::UNAVAILABLE:
            LOG(error) << "Rendezvous server is unavailable. Retrying in 5 seconds...";
            std::this_thread::sleep_for(std::chrono::seconds(5));
            break;

        case grpc::StatusCode::INVALID_ARGUMENT:
        case grpc::StatusCode::NOT_FOUND:
        case grpc::StatusCode::ALREADY_EXISTS:
            LOG(error) << "Rendezvous grpc exception caught: (error " << status.error_code() << ") " << status.error_message();
            break;

        default:
            LOG(fatal) << "Unexpected rendezvous grpc exception caught: (error " << status.error_code() << ") " << status.error_message();
            exit(EXIT_FAILURE);
    }
}