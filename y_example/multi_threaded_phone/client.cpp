#include <gflags/gflags.h>
#include <bthread/bthread.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include <brpc/channel.h>
#include "phone.pb.h"
#include <bvar/bvar.h>

DEFINE_int32(thread_num, 50, "Number of threads to send requests");
DEFINE_bool(use_bthread, false, "Use bthread to send requests");
DEFINE_int32(attachment_size, 0, "Carry so many byte attachment along with requests");
DEFINE_int32(request_size, 16, "Bytes of each request");
DEFINE_string(protocol, "baidu_std", "Protocol type. Defined in src/brpc/options.proto");
DEFINE_string(connection_type, "", "Connection type. Available values: single, pooled, short");
DEFINE_string(server, "0.0.0.0:8002", "IP Address of server");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_int32(timeout_ms, 100, "RPC timeout in milliseconds");
DEFINE_int32(max_retry, 3, "Max retries(not including the first RPC)"); 
DEFINE_bool(dont_fail, false, "Print fatal when some call failed");
DEFINE_bool(enable_ssl, false, "Use SSL connection");
DEFINE_int32(dummy_port, -1, "Launch dummy server at this port");

std::string g_request;
std::string g_attachment;
bvar::LatencyRecorder g_latency_recorder("client");
bvar::Adder<int>g_error_count("g_error_count");

static void* sender(void* arg) {
    phonepackage::PhoneService_Stub stub(static_cast<google::protobuf::RpcChannel*>(arg));
    int log_id = 0;
    while(!brpc::IsAskedToQuit()) {
        phonepackage::PhoneRequest request;
        phonepackage::PhoneResponse response;
        brpc::Controller cntl;
        request.set_first_name(g_request);
        cntl.set_log_id(log_id++); 
        cntl.request_attachment().append(g_attachment);
        stub.Phone(&cntl, &request, &response, NULL);

        if (!cntl.Failed()) {
            g_latency_recorder << cntl.latency_us();

        } else {
            g_error_count << 1;
            CHECK(brpc::IsAskedToQuit() || FLAGS_dont_fail) 
                << "error " << cntl.ErrorText() << "latency " << cntl.latency_us();
            bthread_usleep(50000);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);
    brpc::Channel channel;
    brpc::ChannelOptions options;
    if (FLAGS_enable_ssl) {
        options.mutable_ssl_options();
    }
    options.protocol = FLAGS_protocol;
    options.connection_type = FLAGS_connection_type;
    options.connect_timeout_ms = std::min(FLAGS_timeout_ms / 2, 100);
    options.timeout_ms = FLAGS_timeout_ms;
    options.max_retry = FLAGS_max_retry;

    if (channel.Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &options) != 0){
        LOG(ERROR) << "Failed to init channel. ";
        return -1;
    }
    if (FLAGS_attachment_size > 0) {
        g_attachment.resize(FLAGS_attachment_size, 'a');
    }
    if (FLAGS_request_size <= 0) {
        LOG(ERROR) << "Bad request size is " << FLAGS_request_size;
    }
    g_request.resize(FLAGS_request_size, 'r');
    if (FLAGS_dummy_port >= 0) {
        brpc::StartDummyServerAt(FLAGS_dummy_port);   
    }

    std::vector<bthread_t> bids;
    std::vector<pthread_t> pids;
    if (!FLAGS_use_bthread) {
        pids.resize(FLAGS_thread_num);
        for (int i = 0; i < FLAGS_thread_num; i++) {
            if (pthread_create(&pids[i], NULL, sender, &channel) != 0) {
                LOG(ERROR) << "create pthread failed. ";
                return -1;
            }
        }

    } else {
        bids.resize(FLAGS_thread_num);
        for (int i = 0; i < FLAGS_thread_num; ++i) {
            if (bthread_start_background(
                    &bids[i], NULL, sender, &channel) != 0) {
                LOG(ERROR) << "create bthread failed. ";
                return -1;        
            }
        }
    }
    while(!brpc::IsAskedToQuit()) {
        sleep(1);
        LOG(INFO) << "Send PhoneRequest at qps = " << g_latency_recorder.qps(1)
                  << "Latency is " << g_latency_recorder.latency(1);
    }

    LOG(INFO) << "request is going to quit. ";
    for (int i = 0; i < FLAGS_thread_num; i++) {
        if (!FLAGS_use_bthread) {
            pthread_join(pids[i], NULL);
        } else {
            bthread_join(bids[i], NULL);
        }
    }
    return 0;

}
