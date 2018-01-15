
#include "HelloTriangleApp.hpp"

//#include <range/v3/algorithm.hpp>
//#include <range/v3/core.hpp>

#include <iostream>
using namespace std;

int main() {
  try {
    HelloTriangleApp app;
    app.run();
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
