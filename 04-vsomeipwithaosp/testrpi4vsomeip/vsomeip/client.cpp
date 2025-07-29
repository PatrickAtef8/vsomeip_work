#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

constexpr vsomeip::service_t service_id = 0x4111;
constexpr vsomeip::instance_t instance_id = 0x3111;
constexpr vsomeip::method_t method_id = 0x6000;

class client {
private:
    std::shared_ptr<vsomeip::application> app;

public:
    bool init() {
        app = vsomeip::runtime::get()->create_application("client");

        app->register_availability_handler(service_id, instance_id,
            [this](vsomeip::service_t, vsomeip::instance_t, bool is_available) {
                if (is_available) {
                    std::cout << "[Client] Server is available. Sending message..." << std::endl;

                    std::string msg = "Knock knock... AOSP 15 calling Yocto!";
                    auto payload = vsomeip::runtime::get()->create_payload();
                    std::vector<vsomeip::byte_t> data(msg.begin(), msg.end());
                    payload->set_data(data);

                    auto request = vsomeip::runtime::get()->create_request();
                    request->set_service(service_id);
                    request->set_instance(instance_id);
                    request->set_method(method_id);
                    request->set_payload(payload);

                    app->send(request);
                }
            });

        app->register_message_handler(service_id, instance_id, method_id,
            [](const std::shared_ptr<vsomeip::message> &response) {
                std::string received(reinterpret_cast<const char*>(response->get_payload()->get_data()),
                                     response->get_payload()->get_length());
                std::cout << "[Client] Received response from server: " << received << std::endl;
            });

        if (!app->init()) {
            std::cerr << "Client init failed!" << std::endl;
            return false;
        }

        app->request_service(service_id, instance_id);
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
    client cli;
    if (cli.init())
        cli.start();
    return 0;
}

