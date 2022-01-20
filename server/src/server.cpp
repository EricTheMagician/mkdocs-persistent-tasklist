#define FILE_SERVER_CPP
#include "server.hpp"
#include "database/database.hpp"
#include "services/available.hpp"

#include <vector>
namespace {
static std::vector<server::service_t> services;
} // namespace

namespace server {

void start(Config::Config const &config) {
  httplib::Server the_server;
  initialize_task_services(the_server, config);
  the_server.listen(config.listen_address.c_str(), config.listen_port);
}
} // namespace server
