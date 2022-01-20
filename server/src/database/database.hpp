#pragma once

#include "config.hpp"
#include "database/task.hpp"
#include "tasks.pb.h"
#include <mutex>
#include <optional>
#include <vector>

namespace Database {
class API {
public:
  API(Config::Config const &config);
  std::optional<mkdocs::tasks::Task> get_task();
  /**
   * @brief Get the tasks for a list
   * @details if the list does not exist, return the null option. if the list
   * exists, return the vector of tasks.
   * @param list_name the name of the list
   *
   * @return std::optional<mkdocs::tasks::TaskList>
   *
   */
  std::optional<Task> get_tasks(std::string const &list_name);

  bool ensure_task_list_exists(std::string const &list_name);
};
}; // namespace Database