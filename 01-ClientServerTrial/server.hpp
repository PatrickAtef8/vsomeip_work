#ifndef SERVER_HPP
#define SERVER_HPP

#include <vsomeip/vsomeip.hpp>
#include <memory>

class server {
private:
    std::shared_ptr<vsomeip::application> app = nullptr;

public:
    bool init();
    void start();
    void stop();
};

#endif // SERVER_HPP