#ifndef MONGODB_SHIM_H
#define MONGODB_SHIM_H

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
#include "../utils/logger.h"

using json = nlohmann::json;

namespace rendezvous {

  class StorageMongodb {

    private:
      mongoc_client_t * _client;
      const std::string _db_name;
      mongoc_client_session_t * _session;

      mongoc_collection_t * _rendezvous_collection;
      bson_t * _rendezvous_doc;

    public:
      StorageMongodb(mongoc_client_t * client, std::string db_name);

      static bool create_index(mongoc_client_t * client);
      static bool write(mongoc_collection_t * collection, bson_t * doc, std::string metadata,
        const bson_t * opts, bson_t * reply, bson_error_t * err);

      // --------------------------------
      // OLD IMPLEMENTATION: transactions
      // --------------------------------
      static bool create_index(mongoc_client_t * client, std::string db_name);
      bool init_write(const mongoc_session_opt_t *session_opts = nullptr, const mongoc_transaction_opt_t *tx_opts = nullptr);
      bool finish_write(const std::string& bid);
      bool abort_write();
      bool write_metadata(mongoc_client_t * client, const std::string& bid, const std::string& db_name);
      void free();

  };
}


#endif