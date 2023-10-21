#ifndef MONITOR_MONGODB_H
#define MONITOR_MONGODB_H

#include <string>
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <chrono>
#include <bson/bson.h>
#include <chrono>
#include <mongoc.h>
#include <nlohmann/json.hpp>
#include <mutex>
#include <grpcpp/grpcpp.h>
#include "../../gen-protos/rendezvous.grpc.pb.h"
#include "../utils/logger.h"

using json = nlohmann::json;

namespace rendezvous {

  const static int CHANGE_STREAM_TIMEOUT_MS = 1000 * 120; // 2 minutes

  class DatastoreMonitorMongodb {

    private:
      mongoc_client_t * _client;
      mongoc_collection_t * _collection;
      mongoc_client_pool_t * _client_pool;

      const std::string _database_name;
      const std::string _collection_name;

      // mongob change stream requires rendezvous connections
      std::shared_ptr<rendezvous::ClientService::Stub> _server;
      std::string _region;
      std::string _service;
      std::string _tag;

    public:
      DatastoreMonitorMongodb(mongoc_client_pool_t * mongodb_client_pool, 
        std::string database_name, std::string collection_name);
      // mongodb change stream requires rendezvous connections
      DatastoreMonitorMongodb(mongoc_client_pool_t * mongodb_client_pool, 
        std::string database_name, std::string collection_name,
        std::string service, std::string tag, std::string region, std::string addr, int port);
     ~DatastoreMonitorMongodb();

      // -------
      // Helpers
      // -------
      void _init_connections();

      // -------------------------
      // Rendezvous Implementation
      // -------------------------
      bool find_metadata(const std::string& rid);

      // ----------------------
      // MongoDB Change Stream
      // ---------------------
      void monitor_branches_change_stream();
      void _handle_grpc_error(grpc::Status status);
  };
}


#endif