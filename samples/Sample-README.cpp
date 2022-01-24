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

  {
    ColoredStream stream{RED, "Hello World"};
    stream.setBackground(Uint8Color{11});
    std::cout << stream << std::endl;
  }

  return EXIT_SUCCESS;
}