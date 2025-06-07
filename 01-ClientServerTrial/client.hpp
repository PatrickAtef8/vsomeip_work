#include <vsomeip/vsomeip.hpp>
#include <memory>
#include <iostream>

constexpr vsomeip::service_t service_id = 0x4666;
constexpr vsomeip::instance_t instance_id = 0x3000;
constexpr vsomeip::method_t method_id = 0x6000;

struct payload {
    std::string p2;
};

void on_service_availability(vsomeip::service_t _service_id, vsomeip::instance_t _instance_id, bool _isAvailable)
{
    if(service_id == _service_id && _instance_id == instance_id && _isAvailable)
    {
        std::cout<< "The Client service is available request method " << std::endl;
        auto app = vsomeip::runtime::get()->get_application("client");
        auto request = vsomeip::runtime::get()->create_request();
        request->set_service(service_id);
        request->set_instance(instance_id);
        request->set_method(method_id);
        app->send(request);
    }

}

void on_message_handler(const std::shared_ptr< vsomeip::message > & _response)
{
    int returnCode = static_cast<int>(_response->get_return_code());

    std::cout<< "The Client Return code is : " << returnCode << std::endl;
}

class client {
private:
    std::shared_ptr<vsomeip::application> app = nullptr;
public:
    bool init(void) {
        app = vsomeip::runtime::get()->create_application("client");
        app->register_availability_handler(
            service_id,
             instance_id,
              on_service_availability);

      app->register_message_handler(service_id,
         instance_id,
          method_id,
           on_message_handler);

        app->init();

        app->request_service(service_id, instance_id);

        return true;
    }

    void start()
    {
        app->start();
    }

    void stop()
    {
        app->unregister_availability_handler(service_id, instance_id);
        app->unregister_message_handler(service_id,instance_id, method_id);
        app->stop();
    }

};