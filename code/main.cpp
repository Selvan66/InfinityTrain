/** @file main.cpp */
#include <exception>
#include <iostream>

#include "App/Application.h"
#include "Utils/Utility.h"

int main() {
  try {
    Utility::setupLogger();

    Application app;
    app.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
