#pragma once
#include "config.hpp"
#include "database/task.hpp"
#include <optional>
#include <vector>

namespace Database::detail {
/**
 * @brief Initialize sqlite_orm storage
 *
 * @param config
 */
void create_storage(Config::Config const &config);

/**
 * @brief Get the tasks for a list
 * @details if the list does not exist, return the null option. if the list
 * exists, return the vector of tasks.
 * @param list_name the name of the list
 *
 * @return std::optional<std::vector<mkdocs::tasks::Task>>
 *
 */

std::optional<Task> get_tasks(std::string const &);

bool create_or_update_task_list(std::string const &list_name);
}; // namespace Database::detail