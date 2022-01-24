#include <ColoredStream/ColoredStream.hpp>
using namespace colored_stream;

int main() {
  std::cout << ColoredStream{RED, "Hello world"} << std::endl;

  {
    ColoredStream colored_content(RED);
    colored_content << "Hello ";
    colored_content << "World ";
    colored_content << " :-)";

    std::cout << colored_content << std::endl;
  }

  std::cout << ColoredStream{BLUE, "Hello ", "World ", " :-)"} << std::endl;

  return EXIT_SUCCESS;
}