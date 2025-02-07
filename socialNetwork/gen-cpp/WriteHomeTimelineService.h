/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef WriteHomeTimelineService_H
#define WriteHomeTimelineService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "social_network_types.h"

namespace social_network {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class WriteHomeTimelineServiceIf {
 public:
  virtual ~WriteHomeTimelineServiceIf() {}
  virtual bool MakeVisible(const int64_t object_id, const std::map<std::string, std::string> & carrier) = 0;
};

class WriteHomeTimelineServiceIfFactory {
 public:
  typedef WriteHomeTimelineServiceIf Handler;

  virtual ~WriteHomeTimelineServiceIfFactory() {}

  virtual WriteHomeTimelineServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(WriteHomeTimelineServiceIf* /* handler */) = 0;
};

class WriteHomeTimelineServiceIfSingletonFactory : virtual public WriteHomeTimelineServiceIfFactory {
 public:
  WriteHomeTimelineServiceIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<WriteHomeTimelineServiceIf>& iface) : iface_(iface) {}
  virtual ~WriteHomeTimelineServiceIfSingletonFactory() {}

  virtual WriteHomeTimelineServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(WriteHomeTimelineServiceIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<WriteHomeTimelineServiceIf> iface_;
};

class WriteHomeTimelineServiceNull : virtual public WriteHomeTimelineServiceIf {
 public:
  virtual ~WriteHomeTimelineServiceNull() {}
  bool MakeVisible(const int64_t /* object_id */, const std::map<std::string, std::string> & /* carrier */) {
    bool _return = false;
    return _return;
  }
};

typedef struct _WriteHomeTimelineService_MakeVisible_args__isset {
  _WriteHomeTimelineService_MakeVisible_args__isset() : object_id(false), carrier(false) {}
  bool object_id :1;
  bool carrier :1;
} _WriteHomeTimelineService_MakeVisible_args__isset;

class WriteHomeTimelineService_MakeVisible_args {
 public:

  WriteHomeTimelineService_MakeVisible_args(const WriteHomeTimelineService_MakeVisible_args&);
  WriteHomeTimelineService_MakeVisible_args& operator=(const WriteHomeTimelineService_MakeVisible_args&);
  WriteHomeTimelineService_MakeVisible_args() : object_id(0) {
  }

  virtual ~WriteHomeTimelineService_MakeVisible_args() throw();
  int64_t object_id;
  std::map<std::string, std::string>  carrier;

  _WriteHomeTimelineService_MakeVisible_args__isset __isset;

  void __set_object_id(const int64_t val);

  void __set_carrier(const std::map<std::string, std::string> & val);

  bool operator == (const WriteHomeTimelineService_MakeVisible_args & rhs) const
  {
    if (!(object_id == rhs.object_id))
      return false;
    if (!(carrier == rhs.carrier))
      return false;
    return true;
  }
  bool operator != (const WriteHomeTimelineService_MakeVisible_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const WriteHomeTimelineService_MakeVisible_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class WriteHomeTimelineService_MakeVisible_pargs {
 public:


  virtual ~WriteHomeTimelineService_MakeVisible_pargs() throw();
  const int64_t* object_id;
  const std::map<std::string, std::string> * carrier;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _WriteHomeTimelineService_MakeVisible_result__isset {
  _WriteHomeTimelineService_MakeVisible_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _WriteHomeTimelineService_MakeVisible_result__isset;

class WriteHomeTimelineService_MakeVisible_result {
 public:

  WriteHomeTimelineService_MakeVisible_result(const WriteHomeTimelineService_MakeVisible_result&);
  WriteHomeTimelineService_MakeVisible_result& operator=(const WriteHomeTimelineService_MakeVisible_result&);
  WriteHomeTimelineService_MakeVisible_result() : success(0) {
  }

  virtual ~WriteHomeTimelineService_MakeVisible_result() throw();
  bool success;
  ServiceException se;

  _WriteHomeTimelineService_MakeVisible_result__isset __isset;

  void __set_success(const bool val);

  void __set_se(const ServiceException& val);

  bool operator == (const WriteHomeTimelineService_MakeVisible_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const WriteHomeTimelineService_MakeVisible_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const WriteHomeTimelineService_MakeVisible_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _WriteHomeTimelineService_MakeVisible_presult__isset {
  _WriteHomeTimelineService_MakeVisible_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _WriteHomeTimelineService_MakeVisible_presult__isset;

class WriteHomeTimelineService_MakeVisible_presult {
 public:


  virtual ~WriteHomeTimelineService_MakeVisible_presult() throw();
  bool* success;
  ServiceException se;

  _WriteHomeTimelineService_MakeVisible_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class WriteHomeTimelineServiceClient : virtual public WriteHomeTimelineServiceIf {
 public:
  WriteHomeTimelineServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  WriteHomeTimelineServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool MakeVisible(const int64_t object_id, const std::map<std::string, std::string> & carrier);
  void send_MakeVisible(const int64_t object_id, const std::map<std::string, std::string> & carrier);
  bool recv_MakeVisible();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class WriteHomeTimelineServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<WriteHomeTimelineServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (WriteHomeTimelineServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_MakeVisible(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  WriteHomeTimelineServiceProcessor(::apache::thrift::stdcxx::shared_ptr<WriteHomeTimelineServiceIf> iface) :
    iface_(iface) {
    processMap_["MakeVisible"] = &WriteHomeTimelineServiceProcessor::process_MakeVisible;
  }

  virtual ~WriteHomeTimelineServiceProcessor() {}
};

class WriteHomeTimelineServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  WriteHomeTimelineServiceProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< WriteHomeTimelineServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< WriteHomeTimelineServiceIfFactory > handlerFactory_;
};

class WriteHomeTimelineServiceMultiface : virtual public WriteHomeTimelineServiceIf {
 public:
  WriteHomeTimelineServiceMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<WriteHomeTimelineServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~WriteHomeTimelineServiceMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<WriteHomeTimelineServiceIf> > ifaces_;
  WriteHomeTimelineServiceMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<WriteHomeTimelineServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  bool MakeVisible(const int64_t object_id, const std::map<std::string, std::string> & carrier) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->MakeVisible(object_id, carrier);
    }
    return ifaces_[i]->MakeVisible(object_id, carrier);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class WriteHomeTimelineServiceConcurrentClient : virtual public WriteHomeTimelineServiceIf {
 public:
  WriteHomeTimelineServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  WriteHomeTimelineServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool MakeVisible(const int64_t object_id, const std::map<std::string, std::string> & carrier);
  int32_t send_MakeVisible(const int64_t object_id, const std::map<std::string, std::string> & carrier);
  bool recv_MakeVisible(const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

} // namespace

#endif
