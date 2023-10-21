#include "../include/storage_mongodb.h"

using namespace rendezvous;

StorageMongodb::StorageMongodb(mongoc_client_t * client, std::string db_name) 
    : _client(client), _db_name(db_name) { }

bool StorageMongodb::create_index(mongoc_client_t * client, std::string db_name) {
    mongoc_database_t * database = mongoc_client_get_database(client, db_name.c_str());
    bson_error_t error;

    if (!database) {
        LOG(error) << "Failure creating index: database does not exist";
        return false;
    }

    bson_t keys;
    bson_init (&keys);
    BSON_APPEND_INT32 (&keys, "rv_bid", 1);
    char * index_name = mongoc_collection_keys_to_index_string (&keys);
    bson_t reply;

    bson_t * create_indexes = BCON_NEW (
        "createIndexes", BCON_UTF8 (db_name.c_str()),
        "indexes", 
            "[", "{",
                "key", BCON_DOCUMENT(&keys),
                "name", BCON_UTF8(index_name),
                "unique", BCON_BOOL(false),
            "}", "]"
        );

    bool r = mongoc_database_write_command_with_opts (database, create_indexes, nullptr, &reply, &error);
    if (!r) {
        bson_free(index_name);
        bson_destroy(&reply);
        bson_destroy(create_indexes);
        mongoc_database_destroy(database);
        LOG(error) << "Failure creating index for rendezvous collection";
        return false;
    }

    LOG(info) << "Created index for rendezvous collection";
    bson_free(index_name);
    bson_destroy(&reply);
    bson_destroy(create_indexes);
    mongoc_database_destroy(database);
    return true;
}

bool StorageMongodb::write(mongoc_collection_t * collection, bson_t * doc, std::string metadata,
    const bson_t * opts, bson_t * reply, bson_error_t * err) {

        BSON_APPEND_UTF8(doc, "rv_bid", metadata.c_str());
        return mongoc_collection_insert_one(collection, doc, opts, reply, err);
}

// --------------------------------
// OLD IMPLEMENTATION: transactions
// --------------------------------
bool StorageMongodb::create_index(mongoc_client_t * client) {
    mongoc_database_t * database = mongoc_client_get_database(client, "rendezvous");
    bson_error_t error;

    if (!database) {
        LOG(error) << "Failure creating index: database does not exist";
        return false;
    }

    bson_t keys;
    bson_init (&keys);
    BSON_APPEND_INT32 (&keys, "ts", 1);
    char * index_name = mongoc_collection_keys_to_index_string (&keys);
    bson_t reply;

    bson_t * create_indexes = BCON_NEW (
        "createIndexes",
        BCON_UTF8 ("rendezvous"),
        "indexes", 
            "[", "{",
                "key", BCON_DOCUMENT(&keys),
                "name", BCON_UTF8(index_name),
                "expireAfterSeconds", BCON_INT32(1800), // expire after 30 minutes
            "}", "]"
        );

    bool r = mongoc_database_write_command_with_opts (database, create_indexes, nullptr, &reply, &error);
    if (!r) {
        bson_free(index_name);
        bson_destroy(&reply);
        bson_destroy(create_indexes);
        mongoc_database_destroy(database);
        LOG(error) << "Failure creating index for rendezvous collection";
        return false;
    }

    LOG(info) << "Created index for rendezvous collection";
    bson_free(index_name);
    bson_destroy(&reply);
    bson_destroy(create_indexes);
    mongoc_database_destroy(database);
    return true;
}


bool StorageMongodb::init_write(const mongoc_session_opt_t *session_opts, const mongoc_transaction_opt_t *tx_opts) {
    bson_error_t error;
    _session = mongoc_client_start_session(_client, session_opts, &error);

    if (!_session) {
        std::cout << "Error starting session: " << error.message << std::endl;
        return false;
    }

    bool started = mongoc_client_session_start_transaction(_session, tx_opts, &error);
    if (!started) {
        std::cout << "Error starting transaction: " << error.message << std::endl;
        mongoc_client_session_destroy(_session);
        return false;
    }

    return true;
}

bool StorageMongodb::abort_write() {
    bson_error_t error;
    bool aborted = mongoc_client_session_abort_transaction(_session, &error);

    if (!aborted) {
        std::cout << "Error aborting transaction: " << error.message << std::endl;
    }

    mongoc_client_session_destroy(_session);
    return aborted;
}

bool StorageMongodb::finish_write(const std::string& bid) {
    bson_error_t error;
    bson_t reply;

    mongoc_collection_t * rendezvous_collection = mongoc_client_get_collection(_client, _db_name.c_str(), "rendezvous");
    if (!rendezvous_collection) {
        std::cout << "Could not find rendezvous collection" << std::endl;
        mongoc_client_session_destroy(_session);
        return false;
    }

    bson_t * rendezvous_doc = bson_new();
    BSON_APPEND_UTF8(rendezvous_doc, "bid", bid.c_str());
    BSON_APPEND_TIME_T(rendezvous_doc, "ts", std::time(nullptr));
    bool inserted = mongoc_collection_insert_one(rendezvous_collection, rendezvous_doc, nullptr, nullptr, &error);

    if (!inserted) {
        std::cout << "Error inserting rendezvous metadata: " << error.message << std::endl;
        bson_free(rendezvous_doc);
        mongoc_collection_destroy(rendezvous_collection);
        mongoc_client_session_destroy(_session);
        return false;
    }

    bool committed = mongoc_client_session_commit_transaction(_session, &reply, &error);

    if (!committed) {
        std::cout << "Error during commit: " << error.message << std::endl;
    }

    bson_free(rendezvous_doc);
    mongoc_collection_destroy(rendezvous_collection);
    mongoc_client_session_destroy(_session);
    return committed;
}

bool StorageMongodb::write_metadata(mongoc_client_t * client, const std::string& bid, const std::string& db_name) {
    bson_error_t error;
    bson_t reply;

    _rendezvous_collection = mongoc_client_get_collection(client, db_name.c_str(), "rendezvous");
    if (!_rendezvous_collection) {
        std::cout << "Could not find rendezvous collection" << std::endl;
        return false;
    }

    bson_t * _rendezvous_doc = bson_new();
    BSON_APPEND_UTF8(_rendezvous_doc, "bid", bid.c_str());
    BSON_APPEND_TIME_T(_rendezvous_doc, "ts", std::time(nullptr));
    bool inserted = mongoc_collection_insert_one(_rendezvous_collection, _rendezvous_doc, nullptr, nullptr, &error);

    if (!inserted) {
        std::cout << "Error inserting rendezvous metadata: " << error.message << std::endl;
        return false;
    }

    return true;
}

void StorageMongodb::free() {
    bson_free(_rendezvous_doc);
    mongoc_collection_destroy(_rendezvous_collection);
}