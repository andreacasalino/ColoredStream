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

  return EXIT_SUCCESS;
}