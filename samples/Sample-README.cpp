#include <ColoredStream/ColoredStream.h>
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
    ColoredStream stream1{RED, "Hello World"};
    stream1.setBackground(Uint8Color{11});

    ColoredStream stream2{Uint24Color{0, 0, 0}, "Hello World"};
    stream2.setBackground(Uint24Color{247, 148, 244});

    std::cout << stream1 << " , " << stream2 << " back to normal" << std::endl;
  }

  return EXIT_SUCCESS;
}