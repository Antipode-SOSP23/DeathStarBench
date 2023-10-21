#ifndef MONITOR_H
#define MONITOR_H

#include <grpcpp/grpcpp.h>
#include "../../gen-protos/rendezvous.grpc.pb.h"
#include "monitor_mongodb.h"
#include "rendezvous.h"
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <chrono>
#include <ctime>
#include <iostream>
#include "../utils/logger.h"

namespace rendezvous {

  class DatastoreMonitor {

    private:
      std::shared_ptr<rendezvous::ClientService::Stub> _server;
      std::unique_ptr<DatastoreMonitorMongodb> _shim;

      /* parameters to close branches */
      std::string _region;
      std::string _service;
      std::string _tag;

      /* management of subscriber threads */
      std::atomic<bool> _running;
      std::vector<std::thread> _threads;
      std::mutex _mutex;
      std::condition_variable _cond;
      std::list<std::string> _bids;

      bool _consistency_checks;
      

    public:
      DatastoreMonitor(std::unique_ptr<DatastoreMonitorMongodb> shim, 
        std::string service, std::string tag, std::string region, 
        std::string rendezvous_addr, int rendezvous_port);


      // -------
      // Helpers
      // -------
      void _handle_grpc_error(grpc::Status status);
      void stop();

      // -----------------
      // MongoDB specific
      // -----------------
      void monitor_branches_change_stream();

      // ----------------------------
      // Rendezvous Publish Subscribe
      // ----------------------------
      void monitor_branches();
      void _subscribe_branches();
      void _close_branches();
      void _close_branches_no_consistency_checks();

  };
}


#endif