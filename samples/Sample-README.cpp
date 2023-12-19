#include <ColoredStream/ColoredStream.h>
#include <iostream>
using namespace colored_stream;

int main() {
  std::cout << ColoredText{ClassicColor::RED, "Hello world"} << std::endl;

  {
    ColoredText colored_content(ClassicColor::RED);
    colored_content << "Hello ";
    colored_content << "World ";
    colored_content << " :-)";

    std::cout << colored_content << std::endl;
  }

  std::cout << ColoredText{ClassicColor::BLUE, "Hello ", "World ", " :-)"}
            << std::endl;

  {
    ColoredText stream{
        Settings{}.text(ClassicColor::RED).background(Uint8Color{11}),
        "Hello World"};
    std::cout << stream << std::endl;
  }

  {
    ColoredStream stream{ClassicColor::MAGENTA, std::cerr};
    stream << "All this line was "
           << "passed to the same "
           << " ColoredStream";

    stream << " ... also this from another line of code" << std::endl;
  }

  return EXIT_SUCCESS;
}