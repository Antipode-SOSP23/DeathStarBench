/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "HomeTimelineService.h"

namespace social_network {


HomeTimelineService_ReadHomeTimeline_args::~HomeTimelineService_ReadHomeTimeline_args() throw() {
}


uint32_t HomeTimelineService_ReadHomeTimeline_args::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->req_id);
          this->__isset.req_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->user_id);
          this->__isset.user_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->start);
          this->__isset.start = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->stop);
          this->__isset.stop = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->carrier.clear();
            uint32_t _size249;
            ::apache::thrift::protocol::TType _ktype250;
            ::apache::thrift::protocol::TType _vtype251;
            xfer += iprot->readMapBegin(_ktype250, _vtype251, _size249);
            uint32_t _i253;
            for (_i253 = 0; _i253 < _size249; ++_i253)
            {
              std::string _key254;
              xfer += iprot->readString(_key254);
              std::string& _val255 = this->carrier[_key254];
              xfer += iprot->readString(_val255);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.carrier = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t HomeTimelineService_ReadHomeTimeline_args::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("HomeTimelineService_ReadHomeTimeline_args");

  xfer += oprot->writeFieldBegin("req_id", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->req_id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("user_id", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->user_id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("start", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->start);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("stop", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->stop);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("carrier", ::apache::thrift::protocol::T_MAP, 5);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->carrier.size()));
    std::map<std::string, std::string> ::const_iterator _iter256;
    for (_iter256 = this->carrier.begin(); _iter256 != this->carrier.end(); ++_iter256)
    {
      xfer += oprot->writeString(_iter256->first);
      xfer += oprot->writeString(_iter256->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}


HomeTimelineService_ReadHomeTimeline_pargs::~HomeTimelineService_ReadHomeTimeline_pargs() throw() {
}


uint32_t HomeTimelineService_ReadHomeTimeline_pargs::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("HomeTimelineService_ReadHomeTimeline_pargs");

  xfer += oprot->writeFieldBegin("req_id", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64((*(this->req_id)));
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("user_id", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64((*(this->user_id)));
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("start", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32((*(this->start)));
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("stop", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32((*(this->stop)));
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("carrier", ::apache::thrift::protocol::T_MAP, 5);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>((*(this->carrier)).size()));
    std::map<std::string, std::string> ::const_iterator _iter257;
    for (_iter257 = (*(this->carrier)).begin(); _iter257 != (*(this->carrier)).end(); ++_iter257)
    {
      xfer += oprot->writeString(_iter257->first);
      xfer += oprot->writeString(_iter257->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}


HomeTimelineService_ReadHomeTimeline_result::~HomeTimelineService_ReadHomeTimeline_result() throw() {
}


uint32_t HomeTimelineService_ReadHomeTimeline_result::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 0:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->success.read(iprot);
          this->__isset.success = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->se.read(iprot);
          this->__isset.se = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t HomeTimelineService_ReadHomeTimeline_result::write(::apache::thrift::protocol::TProtocol* oprot) const {

  uint32_t xfer = 0;

  xfer += oprot->writeStructBegin("HomeTimelineService_ReadHomeTimeline_result");

  if (this->__isset.success) {
    xfer += oprot->writeFieldBegin("success", ::apache::thrift::protocol::T_STRUCT, 0);
    xfer += this->success.write(oprot);
    xfer += oprot->writeFieldEnd();
  } else if (this->__isset.se) {
    xfer += oprot->writeFieldBegin("se", ::apache::thrift::protocol::T_STRUCT, 1);
    xfer += this->se.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}


HomeTimelineService_ReadHomeTimeline_presult::~HomeTimelineService_ReadHomeTimeline_presult() throw() {
}


uint32_t HomeTimelineService_ReadHomeTimeline_presult::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 0:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += (*(this->success)).read(iprot);
          this->__isset.success = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->se.read(iprot);
          this->__isset.se = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

void HomeTimelineServiceClient::ReadHomeTimeline(PostListRpcResponse& _return, const int64_t req_id, const int64_t user_id, const int32_t start, const int32_t stop, const std::map<std::string, std::string> & carrier)
{
  send_ReadHomeTimeline(req_id, user_id, start, stop, carrier);
  recv_ReadHomeTimeline(_return);
}

void HomeTimelineServiceClient::send_ReadHomeTimeline(const int64_t req_id, const int64_t user_id, const int32_t start, const int32_t stop, const std::map<std::string, std::string> & carrier)
{
  int32_t cseqid = 0;
  oprot_->writeMessageBegin("ReadHomeTimeline", ::apache::thrift::protocol::T_CALL, cseqid);

  HomeTimelineService_ReadHomeTimeline_pargs args;
  args.req_id = &req_id;
  args.user_id = &user_id;
  args.start = &start;
  args.stop = &stop;
  args.carrier = &carrier;
  args.write(oprot_);

  oprot_->writeMessageEnd();
  oprot_->getTransport()->writeEnd();
  oprot_->getTransport()->flush();
}

void HomeTimelineServiceClient::recv_ReadHomeTimeline(PostListRpcResponse& _return)
{

  int32_t rseqid = 0;
  std::string fname;
  ::apache::thrift::protocol::TMessageType mtype;

  iprot_->readMessageBegin(fname, mtype, rseqid);
  if (mtype == ::apache::thrift::protocol::T_EXCEPTION) {
    ::apache::thrift::TApplicationException x;
    x.read(iprot_);
    iprot_->readMessageEnd();
    iprot_->getTransport()->readEnd();
    throw x;
  }
  if (mtype != ::apache::thrift::protocol::T_REPLY) {
    iprot_->skip(::apache::thrift::protocol::T_STRUCT);
    iprot_->readMessageEnd();
    iprot_->getTransport()->readEnd();
  }
  if (fname.compare("ReadHomeTimeline") != 0) {
    iprot_->skip(::apache::thrift::protocol::T_STRUCT);
    iprot_->readMessageEnd();
    iprot_->getTransport()->readEnd();
  }
  HomeTimelineService_ReadHomeTimeline_presult result;
  result.success = &_return;
  result.read(iprot_);
  iprot_->readMessageEnd();
  iprot_->getTransport()->readEnd();

  if (result.__isset.success) {
    // _return pointer has now been filled
    return;
  }
  if (result.__isset.se) {
    throw result.se;
  }
  throw ::apache::thrift::TApplicationException(::apache::thrift::TApplicationException::MISSING_RESULT, "ReadHomeTimeline failed: unknown result");
}

bool HomeTimelineServiceProcessor::dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext) {
  ProcessMap::iterator pfn;
  pfn = processMap_.find(fname);
  if (pfn == processMap_.end()) {
    iprot->skip(::apache::thrift::protocol::T_STRUCT);
    iprot->readMessageEnd();
    iprot->getTransport()->readEnd();
    ::apache::thrift::TApplicationException x(::apache::thrift::TApplicationException::UNKNOWN_METHOD, "Invalid method name: '"+fname+"'");
    oprot->writeMessageBegin(fname, ::apache::thrift::protocol::T_EXCEPTION, seqid);
    x.write(oprot);
    oprot->writeMessageEnd();
    oprot->getTransport()->writeEnd();
    oprot->getTransport()->flush();
    return true;
  }
  (this->*(pfn->second))(seqid, iprot, oprot, callContext);
  return true;
}

void HomeTimelineServiceProcessor::process_ReadHomeTimeline(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext)
{
  void* ctx = NULL;
  if (this->eventHandler_.get() != NULL) {
    ctx = this->eventHandler_->getContext("HomeTimelineService.ReadHomeTimeline", callContext);
  }
  ::apache::thrift::TProcessorContextFreer freer(this->eventHandler_.get(), ctx, "HomeTimelineService.ReadHomeTimeline");

  if (this->eventHandler_.get() != NULL) {
    this->eventHandler_->preRead(ctx, "HomeTimelineService.ReadHomeTimeline");
  }

  HomeTimelineService_ReadHomeTimeline_args args;
  args.read(iprot);
  iprot->readMessageEnd();
  uint32_t bytes = iprot->getTransport()->readEnd();

  if (this->eventHandler_.get() != NULL) {
    this->eventHandler_->postRead(ctx, "HomeTimelineService.ReadHomeTimeline", bytes);
  }

  HomeTimelineService_ReadHomeTimeline_result result;
  try {
    iface_->ReadHomeTimeline(result.success, args.req_id, args.user_id, args.start, args.stop, args.carrier);
    result.__isset.success = true;
  } catch (ServiceException &se) {
    result.se = se;
    result.__isset.se = true;
  } catch (const std::exception& e) {
    if (this->eventHandler_.get() != NULL) {
      this->eventHandler_->handlerError(ctx, "HomeTimelineService.ReadHomeTimeline");
    }

    ::apache::thrift::TApplicationException x(e.what());
    oprot->writeMessageBegin("ReadHomeTimeline", ::apache::thrift::protocol::T_EXCEPTION, seqid);
    x.write(oprot);
    oprot->writeMessageEnd();
    oprot->getTransport()->writeEnd();
    oprot->getTransport()->flush();
    return;
  }

  if (this->eventHandler_.get() != NULL) {
    this->eventHandler_->preWrite(ctx, "HomeTimelineService.ReadHomeTimeline");
  }

  oprot->writeMessageBegin("ReadHomeTimeline", ::apache::thrift::protocol::T_REPLY, seqid);
  result.write(oprot);
  oprot->writeMessageEnd();
  bytes = oprot->getTransport()->writeEnd();
  oprot->getTransport()->flush();

  if (this->eventHandler_.get() != NULL) {
    this->eventHandler_->postWrite(ctx, "HomeTimelineService.ReadHomeTimeline", bytes);
  }
}

::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > HomeTimelineServiceProcessorFactory::getProcessor(const ::apache::thrift::TConnectionInfo& connInfo) {
  ::apache::thrift::ReleaseHandler< HomeTimelineServiceIfFactory > cleanup(handlerFactory_);
  ::apache::thrift::stdcxx::shared_ptr< HomeTimelineServiceIf > handler(handlerFactory_->getHandler(connInfo), cleanup);
  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > processor(new HomeTimelineServiceProcessor(handler));
  return processor;
}

void HomeTimelineServiceConcurrentClient::ReadHomeTimeline(PostListRpcResponse& _return, const int64_t req_id, const int64_t user_id, const int32_t start, const int32_t stop, const std::map<std::string, std::string> & carrier)
{
  int32_t seqid = send_ReadHomeTimeline(req_id, user_id, start, stop, carrier);
  recv_ReadHomeTimeline(_return, seqid);
}

int32_t HomeTimelineServiceConcurrentClient::send_ReadHomeTimeline(const int64_t req_id, const int64_t user_id, const int32_t start, const int32_t stop, const std::map<std::string, std::string> & carrier)
{
  int32_t cseqid = this->sync_.generateSeqId();
  ::apache::thrift::async::TConcurrentSendSentry sentry(&this->sync_);
  oprot_->writeMessageBegin("ReadHomeTimeline", ::apache::thrift::protocol::T_CALL, cseqid);

  HomeTimelineService_ReadHomeTimeline_pargs args;
  args.req_id = &req_id;
  args.user_id = &user_id;
  args.start = &start;
  args.stop = &stop;
  args.carrier = &carrier;
  args.write(oprot_);

  oprot_->writeMessageEnd();
  oprot_->getTransport()->writeEnd();
  oprot_->getTransport()->flush();

  sentry.commit();
  return cseqid;
}

void HomeTimelineServiceConcurrentClient::recv_ReadHomeTimeline(PostListRpcResponse& _return, const int32_t seqid)
{

  int32_t rseqid = 0;
  std::string fname;
  ::apache::thrift::protocol::TMessageType mtype;

  // the read mutex gets dropped and reacquired as part of waitForWork()
  // The destructor of this sentry wakes up other clients
  ::apache::thrift::async::TConcurrentRecvSentry sentry(&this->sync_, seqid);

  while(true) {
    if(!this->sync_.getPending(fname, mtype, rseqid)) {
      iprot_->readMessageBegin(fname, mtype, rseqid);
    }
    if(seqid == rseqid) {
      if (mtype == ::apache::thrift::protocol::T_EXCEPTION) {
        ::apache::thrift::TApplicationException x;
        x.read(iprot_);
        iprot_->readMessageEnd();
        iprot_->getTransport()->readEnd();
        sentry.commit();
        throw x;
      }
      if (mtype != ::apache::thrift::protocol::T_REPLY) {
        iprot_->skip(::apache::thrift::protocol::T_STRUCT);
        iprot_->readMessageEnd();
        iprot_->getTransport()->readEnd();
      }
      if (fname.compare("ReadHomeTimeline") != 0) {
        iprot_->skip(::apache::thrift::protocol::T_STRUCT);
        iprot_->readMessageEnd();
        iprot_->getTransport()->readEnd();

        // in a bad state, don't commit
        using ::apache::thrift::protocol::TProtocolException;
        throw TProtocolException(TProtocolException::INVALID_DATA);
      }
      HomeTimelineService_ReadHomeTimeline_presult result;
      result.success = &_return;
      result.read(iprot_);
      iprot_->readMessageEnd();
      iprot_->getTransport()->readEnd();

      if (result.__isset.success) {
        // _return pointer has now been filled
        sentry.commit();
        return;
      }
      if (result.__isset.se) {
        sentry.commit();
        throw result.se;
      }
      // in a bad state, don't commit
      throw ::apache::thrift::TApplicationException(::apache::thrift::TApplicationException::MISSING_RESULT, "ReadHomeTimeline failed: unknown result");
    }
    // seqid != rseqid
    this->sync_.updatePending(fname, mtype, rseqid);

    // this will temporarily unlock the readMutex, and let other clients get work done
    this->sync_.waitForWork(seqid);
  } // end while(true)
}

} // namespace

