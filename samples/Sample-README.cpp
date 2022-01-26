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
    ColoredStream stream_red{RED, "Hello World"};
    stream_red.setBackground(Uint8Color{11});

    ColoredStream stream_green{Uint24Color{0, 0, 0}, "Hello World"};
    stream_green.setBackground(Uint24Color{247, 148, 244});

    std::cout << stream_red << " , " << stream_green << " back to normal"
              << std::endl;
  }

  return EXIT_SUCCESS;
}