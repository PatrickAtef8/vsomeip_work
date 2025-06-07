#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vsomeip/vsomeip.hpp>
#include <memory>

class client {
private:
    std::shared_ptr<vsomeip::application> app = nullptr;

public:
    bool init();
    void start();
    void stop();
};

#endif // CLIENT_HPP