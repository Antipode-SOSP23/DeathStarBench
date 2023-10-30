#include "../include/monitor.h"

using namespace rendezvous;

DatastoreMonitor::DatastoreMonitor(std::unique_ptr<DatastoreMonitorMongodb> shim, std::string service, 
    std::string tag, std::string region, std::string addr, int port) : 
    _shim(std::move(shim)), _region(region), _service(service), _tag(tag), _running(true) {

        auto channel = grpc::CreateChannel(addr + ":" + std::to_string(port), grpc::InsecureChannelCredentials());
        _server = rendezvous::ClientService::NewStub(channel);

        _consistency_checks = rendezvous::is_consistency_checks_enabled();
}

void DatastoreMonitor::_handle_grpc_error(grpc::Status status) {
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

void DatastoreMonitor::stop() {
  _running = false;
  for (auto& thread: _threads) {
    thread.join();
  }
}

// -----------------
// MongoDB specific
// -----------------

void DatastoreMonitor::monitor_branches_change_stream() {
  _threads.emplace_back(std::thread ([this]() {
    _shim->monitor_branches_change_stream();
  }));
}

// -----------------
// Publish Subscribe
// -----------------

void DatastoreMonitor::monitor_branches() {
    _threads.emplace_back(std::thread ([this]() {
        _subscribe_branches();
    }));

    if (_consistency_checks) {
        LOG(info) << "Starting close branches with consistency checks enabled...";
        _threads.emplace_back(std::thread ([this]() {
            _close_branches();
        }));
    }
    else {
        LOG(info) << "Starting close branches without consistency checks enabled...";
        _threads.emplace_back(std::thread ([this]() {
            _close_branches_no_consistency_checks();
        }));
    }
}

void DatastoreMonitor::_subscribe_branches() {
    SubscribeMessage request;
    SubscribeResponse response;
    request.set_service(_service);
    request.set_region(_region);
    
    while (_running) {
        grpc::ClientContext context;
        std::unique_ptr<grpc::ClientReader<SubscribeResponse>> reader(_server->Subscribe(&context, request));

        LOG(info) << "Going to subscribe... ";

        while (reader->Read(&response)) {
            const std::string& bid = response.bid();
            //LOG(debug) << "Received subscribed branch with bid = " << bid;
            _mutex.lock();
            _bids.push_front(bid);
            _cond.notify_all();
            _mutex.unlock();
        }
        LOG(error) << "Broken subscription stream! Retrying in 5 seconds...";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    // notify to join second thread at the end
    _bids.clear();
    _cond.notify_all();
}

void DatastoreMonitor::_close_branches() {
    grpc::Status status;
    rendezvous::Empty response;
    rendezvous::CloseBranchMessage request;
    request.set_region(_region);

    while (_running) {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_bids.size() == 0 && _running) {
            _cond.wait(lock);
        }
        for (auto bid_it = _bids.begin(); bid_it != _bids.end(); ) {
            //LOG(debug) << "Going to find bid = " << (*bid_it);
            if (_shim->find_metadata(*bid_it)) {
                request.set_bid(*bid_it);
                grpc::ClientContext context;
                //LOG(debug) << "Closing subscribed branch with bid = " << (*bid_it);
                status = _server->CloseBranch(&context, request, &response);
                if (status.ok()) {
                    bid_it = _bids.erase(bid_it);
                }
                else {
                    _handle_grpc_error(status);
                    ++bid_it;
                }
            }
            else {
                //LOG(debug) << "Going to find bid = " << (*bid_it);
                ++bid_it;
            }
        }
    }
}

void DatastoreMonitor::_close_branches_no_consistency_checks() {
    grpc::Status status;
    rendezvous::Empty response;
    rendezvous::CloseBranchMessage request;
    request.set_region(_region);

    while (_running) {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_bids.size() == 0 && _running) {
            _cond.wait(lock);
        }
        for (auto bid_it = _bids.begin(); bid_it != _bids.end(); ) {
            request.set_bid(*bid_it);
            grpc::ClientContext context;
            status = _server->CloseBranch(&context, request, &response);
            if (status.ok()) {
                bid_it = _bids.erase(bid_it);
            }
            else {
                _handle_grpc_error(status);
                ++bid_it;
            }
        }
    }
}