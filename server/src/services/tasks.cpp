#include "database/database.hpp"
#include "server.hpp"

void initialize_task_services(httplib::Server &server,
                              Config::Config const &config) {

  server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
  });
  server.Get(R"(/task/(\d+))",
             [config](const httplib::Request &req, httplib::Response &res) {
               auto numbers = req.matches[1];
               res.set_content(numbers, "text/plain");
             });

  // Get the available tasks for a list
  server.Get(R"(/task_list/(.+))",
             [config](const httplib::Request &req, httplib::Response &res) {
               auto task_list = req.matches[1];
               res.set_content(task_list, "text/plain");
             });

  server.Post("/task_list", [config](const httplib::Request &req,
                                     httplib::Response &res) {
    auto list_name = req.get_param_value("name");
    if (list_name.size() == 0) {
      res.set_content("Parameter name missing", "text/plain");
      res.status = 400; // bad request
      return;
    }
    bool success = Database::API(config).ensure_task_list_exists(list_name);
    if (!success) {
      res.status = 400;
    }
    res.set_content(list_name, "text/plain");
  });
}
