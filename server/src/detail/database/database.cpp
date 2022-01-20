#include "config.hpp"
#include "database/task.hpp"
#include <iostream>
#include <memory>
#include <mutex>
#include <sqlite_orm/sqlite_orm.h>
using namespace sqlite_orm;

namespace Database::detail {

static auto create_storage_impl(Config::Config const &config) {
  auto storage = make_storage(
      config.path,
      make_unique_index(
          "idx_contacts_email",
          indexed_column(&Task::parent_id).collate("BINARY").desc(),
          indexed_column(&Task::description).collate("BINARY").desc()),
      make_table("TASKS",
                 make_column("ID", &Task::id, primary_key(), autoincrement()),
                 make_column("PARENT_ID", &Task::parent_id),
                 make_column("DESCRIPTION", &Task::description),
                 make_column("STATUS", &Task::completed),
                 make_column("MODIFICATION", &Task::modification)));
  storage.sync_schema();
  return storage;
}

using storage_t = decltype(create_storage_impl(Config::Config()));
static std::unique_ptr<storage_t> storage = nullptr;

/**
 * @brief mutex to ensure that only one caller can read/write to the database
 */
static std::mutex m_lock;

void create_storage(Config::Config const &config) {
  if (!storage) {
    std::lock_guard guard(m_lock);
    if (!storage) {
      detail::storage =
          std::make_unique<storage_t>(create_storage_impl(config));
    }
  }
}
/**
 * WITH    q AS
        (
        SELECT  *
        FROM   TASKS
        WHERE   PARENT_ID = 6
        UNION ALL
        SELECT  m.*
        FROM    TASKS m
        JOIN    q
        ON      m.PARENT_ID = q.ID
        )
SELECT  *
FROM    q
ORDER by  q.PARENT_ID, q.ID **/
/**
 * @brief Get the current time from the database;
 *
 * @return std::string
 */
std::string get_database_now() {
  return storage->select(strftime("%Y-%m-%d %H:%M:%S", "now")).front();
}

Task get_task(uint64_t id) { return detail::storage->get<Task>(id); }

std::optional<Task> get_tasks(std::string const &list_name) {
  std::lock_guard guard(m_lock);
  // sqlite_orm::join;
  return std::nullopt;
}

bool create_or_update_task_list(std::string const &list_name) {
  std::lock_guard guard(m_lock);
  if (auto tasks = storage->get_all<Task>(where(
          is_null(&Task::parent_id) and (c(&Task::description) == list_name)));
      tasks.size() > 0) {
    return true;
  }

  // need to create it since it was not in the database
  auto now = get_database_now();
  Task task{-1, std::nullopt, false, list_name, now};
  try {
    storage->insert<Task>(task);
  } catch (std::system_error &e) {
    std::cerr << e.what() << std::endl;
  }
  return true;
}

} // namespace Database::detail