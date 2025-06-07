#include "client.hpp"
#include <iostream>

constexpr vsomeip::service_t service_id = 0x4111; // Match server’s service ID
constexpr vsomeip::instance_t instance_id = 0x3111; // Match server’s instance ID
constexpr vsomeip::method_t method_id = 0x6000;

void on_service_availability(vsomeip::service_t _service_id, vsomeip::instance_t _instance_id, bool _isAvailable) {
    std::cout << "Service [" << std::hex << _service_id << "." << _instance_id << "] is "
              << (_isAvailable ? "available." : "NOT available.") << std::endl;
    if (_service_id == service_id && _instance_id == instance_id && _isAvailable) {
        std::cout << "The Client service is available, sending request..." << std::endl;
        auto app = vsomeip::runtime::get()->get_application("client");
        auto request = vsomeip::runtime::get()->create_request();
        request->set_service(service_id);
        request->set_instance(instance_id);
        request->set_method(method_id);
        app->send(request);
    }
}

void on_message_handler(const std::shared_ptr<vsomeip::message> &_response) {
    vsomeip::return_code_e returnCode = _response->get_return_code();
    std::cout << "Client received response. Return code: " << static_cast<int>(returnCode)
              << " (" << (returnCode == vsomeip::return_code_e::E_OK ? "E_OK" : "Error") << ")" << std::endl;
}

bool client::init() {
    app = vsomeip::runtime::get()->create_application("client");

    app->register_availability_handler(service_id, instance_id, on_service_availability);
    app->register_message_handler(service_id, instance_id, method_id, on_message_handler);

    if (!app->init()) {
        std::cerr << "Client app initialization failed!" << std::endl;
        return false;
    }

    app->request_service(service_id, instance_id);
    return true;
}

void client::start() {
    app->start();
}

void client::stop() {
    app->unregister_availability_handler(service_id, instance_id);
    app->unregister_message_handler(service_id, instance_id, method_id);
    app->stop();
}

int main() {
    client _client;
    if (_client.init()) {
        _client.start();
    }
    return 0;
}