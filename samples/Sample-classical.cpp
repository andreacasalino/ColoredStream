#include <ColoredStream/ColoredStream.hpp>
#include <fstream>
using namespace colored_stream;

int main() {
  std::cout << ClassicColoredStream{RED, "This should be ", "RED"}
            << " back to default color" << std::endl;

  std::cout << ClassicColoredStream{GREEN, "This should be ", "GREEN"}
            << " back to default color" << std::endl;

  std::cout << ClassicColoredStream{YELLOW, "This should be ", "YELLOW"}
            << " back to default color" << std::endl;

  std::cout << ClassicColoredStream{BLUE, "This should be ", "BLUE"}
            << " back to default color" << std::endl;

  std::cout << ClassicColoredStream{MAGENTA, "This should be ", "MAGENTA"}
            << " back to default color" << std::endl;

  std::cout << ClassicColoredStream{CYAN, "This should be ", "CYAN"}
            << " back to default color" << std::endl;

  std::cout << ClassicColoredStream{WHITE, "This should be ", "WHITE"}
            << " back to default color" << std::endl;

  {
    std::ofstream stream("temp.txt");
    stream << ClassicColoredStream{RED, "This should contain only plain text"}
           << " back to default color" << std::endl;
  }

  return EXIT_SUCCESS;
}