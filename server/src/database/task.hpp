#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace Database {
/**
 * @brief Manage Task Objects
 * @details A task is an object that can be marked as completed or not. The
 * representation of tasks can be thought of as a directed graph, where the root
 * is a task that has no parent. The description of the root corresponds to the
 * page.
 */

struct Task {
  int32_t id;
  std::optional<int32_t> parent_id;
  bool completed;
  std::string description;
  std::string modification;
};
} // namespace Database