#pragma once
#include <cstdint>
#include <string>

namespace Config {
struct Config {
  /**
   * @brief Path to the database file. defaults to $(pwd)/db.sqlite
   *
   */
  std::string path = "db.sqlite";
  std::string listen_address = "0.0.0.0";
  uint16_t listen_port = 8345;
};
}; // namespace Config