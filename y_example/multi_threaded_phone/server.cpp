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
DEFINE_int32(max_concurrency, 0, "Limit of request processing in parallel");
DEFINE_int32(internal_port, -1, "Only allow builtin services at this port");

namespace phonepackage{
class PhoneServiceImpl : public PhoneService {
 public:
  PhoneServiceImpl() {};
  ~PhoneServiceImpl() {};
  void Phone(google::protobuf::RpcController* base_controller,
                    const ::phonepackage::PhoneRequest* request,
                    ::phonepackage::PhoneResponse* response,
                    ::google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);
        brpc::Controller* cntl = static_cast<brpc::Controller*>(base_controller);
        std::string name = request->first_name() + "number";
        response->set_phone_number(name);
        if (FLAGS_phone_attachment) {
            cntl->response_attachment().append(cntl->request_attachment());
        }
  }
};

}
DEFINE_bool(h, false, "print help information ");

int main(int argc, char* argv[]) {
    std::string help_str = " dummpy_help_information. ";
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_h) {
        fprintf(stderr, "%s\n%s\n%s ", help_str.c_str(),help_str.c_str(), help_str.c_str());
        return 0; 
    }
    brpc::Server server;
    phonepackage::PhoneServiceImpl phone_service_impl;
    if (server.AddService(&phone_service_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "add phone_service_impl failed. ";
        return 0;
    }
    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    options.max_concurrency = FLAGS_max_concurrency;
    options.internal_port = FLAGS_internal_port;
    options.mutable_ssl_options()->default_cert.certificate = "cert.pem";
    options.mutable_ssl_options()->default_cert.private_key = "key.pem";
    if (server.Start(FLAGS_port, &options) != 0) {
        LOG(ERROR) << "server start failed. ";
        return -1;
    }
    server.RunUntilAskedToQuit();
    return 0;

}
