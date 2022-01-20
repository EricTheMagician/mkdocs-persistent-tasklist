#pragma once
#include "config.hpp"
#include <functional>
#include <httplib.h>
namespace server {

using service_t =
    std::function<void(httplib::Server &server, Config::Config const &config)>;

void start(Config::Config const &config);

} // namespace server