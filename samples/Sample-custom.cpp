#include <ColoredStream/ColoredStream.hpp>
#include <limits>
using namespace colored_stream;

int main() {
  for (std::uint8_t text_code = 0;
       text_code < std::numeric_limits<std::uint8_t>::max(); ++text_code) {
    for (std::uint8_t backgrnd_code = 0;
         backgrnd_code < std::numeric_limits<std::uint8_t>::max();
         ++backgrnd_code) {
      ColoredStream stream(Uint8Color{text_code}, "Hello World");
      stream.setBackground(Uint8Color{backgrnd_code});
      std::cout << stream << " text uint8 code: " << std::to_string(text_code)
                << " background uint8 code: " << std::to_string(backgrnd_code)
                << std::endl;
    }
  }

  return EXIT_SUCCESS;
}