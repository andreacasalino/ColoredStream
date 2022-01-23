#include <ColoredStream/ColoredStream.hpp>
#include <fstream>
using namespace colored_stream;

int main() {
  std::cout << ClassicColoredStream{RED, "This should be ", "RED"} << " done"
            << std::endl;

  std::cout << ClassicColoredStream{GREEN, "This should be ", "GREEN"}
            << " done" << std::endl;

  std::cout << ClassicColoredStream{YELLOW, "This should be ", "YELLOW"}
            << " done" << std::endl;

  std::cout << ClassicColoredStream{BLUE, "This should be ", "BLUE"} << " done"
            << std::endl;

  std::cout << ClassicColoredStream{MAGENTA, "This should be ", "MAGENTA"}
            << " done" << std::endl;

  std::cout << ClassicColoredStream{CYAN, "This should be ", "CYAN"} << " done"
            << std::endl;

  std::cout << ClassicColoredStream{WHITE, "This should be ", "WHITE"}
            << " done" << std::endl;

  {
    std::ofstream stream("temp.txt");
    stream << ClassicColoredStream{RED, "This should contain only plain text"}
           << " done" << std::endl;
  }

  return EXIT_SUCCESS;
}