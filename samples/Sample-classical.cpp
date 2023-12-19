#include <ColoredStream/ColoredStream.h>
#include <fstream>
#include <iostream>
using namespace colored_stream;

int main() {
  std::cout << ColoredText{ClassicColor::RED, "This should be ", "RED"}
            << " back to default color" << std::endl;

  std::cout << ColoredText{ClassicColor::GREEN, "This should be ", "GREEN"}
            << " back to default color" << std::endl;

  std::cout << ColoredText{ClassicColor::YELLOW, "This should be ", "YELLOW"}
            << " back to default color" << std::endl;

  std::cout << ColoredText{ClassicColor::BLUE, "This should be ", "BLUE"}
            << " back to default color" << std::endl;

  std::cout << ColoredText{ClassicColor::MAGENTA, "This should be ", "MAGENTA"}
            << " back to default color" << std::endl;

  std::cout << ColoredText{ClassicColor::CYAN, "This should be ", "CYAN"}
            << " back to default color" << std::endl;

  std::cout << ColoredText{ClassicColor::WHITE, "This should be ", "WHITE"}
            << " back to default color" << std::endl;

  {
    std::ofstream stream("temp.txt");
    stream << ColoredText{ClassicColor::RED,
                          "This should contain only plain text"}
           << " back to default color" << std::endl;
  }

  return EXIT_SUCCESS;
}