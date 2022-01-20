#include "config.hpp"
#include "server.hpp"
#include "tasks.pb.h"

int main(int argc, char *argv[]) {

  Config::Config config;
  server::start(config);

  return 0;
}