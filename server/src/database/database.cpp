#include "database/database.hpp"
#include "detail/database/database.hpp"

namespace Database {

API::API(Config::Config const &config) { detail::create_storage(config); }
std::optional<Task> API::get_tasks(std::string const &list_name) {
  return std::nullopt;
}

bool API::ensure_task_list_exists(std::string const &list_name) {
  return detail::create_or_update_task_list(list_name);
}
}; // namespace Database