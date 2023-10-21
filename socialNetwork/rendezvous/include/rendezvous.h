#ifndef RENDEVOUS_H
#define RENDEVOUS_H

#include <string>
#include <vector>
#include <thread>
#include <google/protobuf/util/json_util.h>
#include <grpcpp/grpcpp.h>
#include "../../gen-protos/rendezvous.grpc.pb.h"
#include "../utils/logger.h"

namespace rendezvous {

  typedef unsigned char byte;

  const std::string ROOT_ASYNC_ZONE = "";

  inline bool is_rendezvous_enabled() {
    return atoi(std::getenv("RENDEZVOUS")) != 0;
  }

  inline bool is_consistency_checks_enabled() {
    return atoi(std::getenv("CONSISTENCY_CHECKS")) != 0;
  }

  inline std::string next_async_zone(const std::string& current_async_zone, int curr_num_async_zones) {
    return current_async_zone + ":" + std::to_string(curr_num_async_zones);
  }

  inline std::string next_async_zone(int curr_num_async_zones) {
    return ROOT_ASYNC_ZONE + ":" + std::to_string(curr_num_async_zones);
  }

  inline std::vector<std::string> next_async_zones(const std::string& current_async_zone, int num, int curr_num_async_zones) {
    std::vector<std::string> zones = std::vector<std::string>();
    for (int i = 0; i < num; i++) {
      std::string core_id = std::to_string(curr_num_async_zones + i);
      zones.emplace_back(current_async_zone + ":" + core_id);
    }
    return zones;
  }

  inline std::vector<std::string> next_async_zones(int num, int curr_num_async_zones) {
    std::vector<std::string> zones = std::vector<std::string>();
    for (int i = 0; i < num; i++) {
      std::string core_id = std::to_string(curr_num_async_zones + i);
      zones.emplace_back(ROOT_ASYNC_ZONE + ":" + core_id);
    }
    return zones;
  }

  typedef struct AsyncRequestHelperStruct {
    int nrpcs = 0;
    grpc::CompletionQueue queue;
    std::vector<std::unique_ptr<grpc::Status>> statuses;
    std::vector<std::unique_ptr<grpc::ClientContext>> contexts;
    std::vector<std::unique_ptr<rendezvous::RegisterBranchResponse>> responses;
    std::vector<std::unique_ptr<grpc::ClientAsyncResponseReader<rendezvous::RegisterBranchResponse>>> rpcs;
    std::mutex mutex;
} AsyncRequestHelper;

  inline void saveAsyncCall(AsyncRequestHelper * rh, grpc::ClientContext * context, grpc::Status * status, rendezvous::RegisterBranchResponse * response) {
    rh->contexts.emplace_back(context);
    rh->statuses.emplace_back(status);
    rh->responses.emplace_back(response);
    rh->rpcs[rh->nrpcs]->Finish(response, status, (void*)1);
    rh->nrpcs++;
  }

  inline bool CompleteAsyncCalls(AsyncRequestHelper * rh) {
    bool ok = true;
    //LOG(debug) << "GOING TO WAIT ASYNC CALLS #" << rh->nrpcs;
    for(int i = 0; i < rh->nrpcs; i++) {
        void * tagPtr;
        bool ok = false;

        rh->queue.Next(&tagPtr, &ok);
        const size_t tag = size_t(tagPtr);
        const grpc::Status & status = *(rh->statuses[tag-1].get());

        if (!status.ok()) {
          LOG(warning) << "[RENDEZVOUS] Received NOT OK async call #" << i << " with code " << status.error_code() << ": " << status.error_message();
          ok = false;
        }
    }
    delete rh;
    return ok;
  }

  inline std::string compute_bid(const std::string& unique_prefix, const std::string& rid, int curr_num_branches) {
    std::string core_bid = std::to_string(curr_num_branches);
    return unique_prefix + '_' + core_bid + ":" + rid;
  }

  inline std::vector<std::string> compute_bids(const std::string& unique_prefix, const std::string& rid, int num, int curr_num_branches) {
    std::vector<std::string> bids = std::vector<std::string>();
    for (int i = 0; i < num; i++) {
      std::string core_bid = std::to_string(curr_num_branches + i);
      bids.emplace_back(unique_prefix + '_' + core_bid + ":" + rid);
    }
    return bids;
  }

  /* inline google::protobuf::util::Status context_msg_to_json(const rendezvous::RequestContext& msg, std::string * output) {
    // reset string since the protobuf method appends the output to the end
    output->clear();
    return google::protobuf::util::MessageToJsonString(msg, output);
  }

  inline google::protobuf::util::Status context_json_to_msg(google::protobuf::StringPiece input, rendezvous::RequestContext * msg) {
    return google::protobuf::util::JsonStringToMessage(input, msg);
  }

  inline std::string context_msg_to_string(const rendezvous::RequestContext& context) {
    return context.SerializeAsString();
  }

  inline rendezvous::RequestContext context_string_to_msg(const std::string& context_str) {
    RequestContext context;
    context.ParseFromString(context_str);
    return context;
  } */
}


#endif