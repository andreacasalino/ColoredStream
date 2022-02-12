#include <ColoredStream/ColoredStream.h>
#include <fstream>
#include <iostream>
using namespace colored_stream;

int main() {
  std::cout << ColoredStream{RED, "This should be ", "RED"}
            << " back to default color" << std::endl;

  std::cout << ColoredStream{GREEN, "This should be ", "GREEN"}
            << " back to default color" << std::endl;

  std::cout << ColoredStream{YELLOW, "This should be ", "YELLOW"}
            << " back to default color" << std::endl;

  std::cout << ColoredStream{BLUE, "This should be ", "BLUE"}
            << " back to default color" << std::endl;

  std::cout << ColoredStream{MAGENTA, "This should be ", "MAGENTA"}
            << " back to default color" << std::endl;

  std::cout << ColoredStream{CYAN, "This should be ", "CYAN"}
            << " back to default color" << std::endl;

  std::cout << ColoredStream{WHITE, "This should be ", "WHITE"}
            << " back to default color" << std::endl;

  {
    std::ofstream stream("temp.txt");
    stream << ColoredStream{RED, "This should contain only plain text"}
           << " back to default color" << std::endl;
  }

  return EXIT_SUCCESS;
}