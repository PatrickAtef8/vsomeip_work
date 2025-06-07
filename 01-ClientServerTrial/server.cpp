#include "server.hpp"
#include <iostream>

constexpr vsomeip::service_t service_id = 0x4111;
constexpr vsomeip::instance_t instance_id = 0x3111;
constexpr vsomeip::method_t method_id = 0x6000;

void on_service_availability(vsomeip::service_t _service_id, vsomeip::instance_t _instance_id, bool _isAvailable) {
    // Log only for debugging purposes
    std::cout << "Service [" << std::hex << _service_id << "." << _instance_id << "] is "
              << (_isAvailable ? "available." : "NOT available.") << std::endl;
}

void on_message_handler(const std::shared_ptr<vsomeip::message> &_request) {
    std::cout << "Server received a request from client." << std::endl;

    auto app = vsomeip::runtime::get()->get_application("server");
    auto response = vsomeip::runtime::get()->create_response(_request);
    response->set_return_code(vsomeip::return_code_e::E_OK);
    app->send(response);
}

bool server::init() {
    app = vsomeip::runtime::get()->create_application("server");

    app->register_availability_handler(service_id, instance_id, on_service_availability);
    app->register_message_handler(service_id, instance_id, method_id, on_message_handler);

    if (!app->init()) {
        std::cerr << "Server app initialization failed!" << std::endl;
        return false;
    }

    app->offer_service(service_id, instance_id);
    return true;
}

void server::start() {
    app->start();
}

void server::stop() {
    app->unregister_availability_handler(service_id, instance_id);
    app->unregister_message_handler(service_id, instance_id, method_id);
    app->stop();
}

int main() {
    server _server;
    if (_server.init()) {
        _server.start();
    }
    return 0;
}