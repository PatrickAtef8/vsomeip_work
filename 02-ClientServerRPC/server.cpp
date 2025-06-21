#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>
#include <string>

constexpr vsomeip::service_t service_id = 0x4111;
constexpr vsomeip::instance_t instance_id = 0x3111;
constexpr vsomeip::method_t method_id = 0x6000;

class server {
private:
    std::shared_ptr<vsomeip::application> app;

public:
    bool init() {
        app = vsomeip::runtime::get()->create_application("server");

        app->register_message_handler(service_id, instance_id, method_id,
            [this](const std::shared_ptr<vsomeip::message> &req) {
                std::string received((char*)req->get_payload()->get_data(), req->get_payload()->get_length());
                std::cout << "[Server] Hello from PC! Received message from client: " << received << std::endl;

                std::string reply = "Hello from PC!";
                auto response_payload = vsomeip::runtime::get()->create_payload();
                std::vector<vsomeip::byte_t> data(reply.begin(), reply.end());
                response_payload->set_data(data);

                auto response = vsomeip::runtime::get()->create_response(req);
                response->set_payload(response_payload);
                response->set_return_code(vsomeip::return_code_e::E_OK);
                app->send(response);
            });

        if (!app->init()) {
            std::cerr << "Server init failed!" << std::endl;
            return false;
        }

        app->offer_service(service_id, instance_id);
        return true;
    }

    void start() {
        app->start();
    }

    void stop() {
        app->stop();
    }
};

int main() {
    server srv;
    if (srv.init())
        srv.start();
    return 0;
}
