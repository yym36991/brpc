#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include "phone.pb.h"

DEFINE_bool(phone_attachment, true, "Echo attachment as well");
DEFINE_int32(port, 8000, "TCP Port of this server");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no "
             "read/write operations during the last `idle_timeout_s'");
DEFINE_int32(logoff_ms, 2000, "Maximum duration of server's LOGOFF state "
             "(waiting for client to close connection before server stops)");

namespace phonepackage {
class PhoneServiceImpl : public PhoneService {
 public:
  PhoneServiceImpl() {};
  virtual ~PhoneServiceImpl() {};
  virtual void Phone(google::protobuf::RpcController* controller,
                       const ::phonepackage::PhoneRequest* request,
                       ::phonepackage::PhoneResponse* response,
                       ::google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);
        brpc::Controller* cntl = static_cast<brpc::Controller*>(controller);
        LOG(INFO) << "received request id is " << cntl->log_id()
                  << " form " << cntl->remote_side()
                  << " to " << cntl->local_side()
                  << " : " << request->first_name()
                  << " (attachment " << cntl->request_attachment() << " ) ";
        std::string phone_number = request->first_name() + " number. ";          
        response->set_phone_number(phone_number);

        if (FLAGS_phone_attachment) {
            // Set attachment which is wired to network directly instead of
            // being serialized into protobuf messages.
            cntl->response_attachment().append(cntl->request_attachment());
        }
    }
};
}

int main(int argc, char* argv[]) {
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);

    brpc::Server server;
    phonepackage::PhoneServiceImpl phone_service_impl;
    if (server.AddService(&phone_service_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "add service failed ";
        return -1;

    }
    
    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    if (server.Start(FLAGS_port, &options) != 0) {
        LOG(ERROR) << "server start failed ";
        return -1;
    }

    server.RunUntilAskedToQuit();
    return 0;

}
