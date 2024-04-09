/** @file main.cpp */
#include <exception>
#include <iostream>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include "App/Application.h"

int main() {
  try {
    spdlog::info("TEST");
    std::shared_ptr<spdlog::logger> logger =
      spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
    Application app;
    logger->info("TEST");
    app.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
