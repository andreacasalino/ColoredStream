#include <ColoredStream/ColoredStream.h>
#include <iostream>
#include <limits>
#include <vector>
using namespace colored_stream;

int main() {
  std::vector<uint8_t> range;
  for (std::uint8_t code = 0; code < std::numeric_limits<std::uint8_t>::max();
       code += 25) {
    range.push_back(code);
  }

  for (auto text_code : range) {
    for (auto backgrnd_code : range) {
      std::cout << ColoredText{Settings{}
                                   .text(Uint8Color{text_code})
                                   .background(Uint8Color{backgrnd_code}),
                               "Hello World"}
                << " text uint8 code: " << std::to_string(text_code)
                << " background uint8 code: " << std::to_string(backgrnd_code)
                << std::endl;
    }
  }

  return EXIT_SUCCESS;
}