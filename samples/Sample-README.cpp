#include <ColoredStream/ColoredStream.hpp>
using namespace colored_stream;

int main() {
  std::cout << ClassicColoredStream{RED, "Hello world"} << std::endl;

  {
    ClassicColoredStream colored_content(RED);
    colored_content << "Hello ";
    colored_content << "World ";
    colored_content << " :-)";

    std::cout << colored_content << std::endl;
  }

  std::cout << ClassicColoredStream{BLUE, "Hello ", "World ", " :-)"}
            << std::endl;

  return EXIT_SUCCESS;
}