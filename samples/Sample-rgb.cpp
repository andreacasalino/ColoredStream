#include <ColoredStream/ColoredStream.hpp>
#include <vector>
using namespace colored_stream;

int main() {

  std::vector<uint8_t> range = {0, 10, 20, 50, 100, 150, 200, 255};

  for (const auto &red : range) {
    for (const auto &green : range) {
      for (const auto &blue : range) {
        std::cout << ColoredStream{Uint24Color{red, green, blue}, "Hello World"}
                  << " red uint8 code: " << std::to_string(red)
                  << " green uint8 code: " << std::to_string(green)
                  << " blue uint8 code: " << std::to_string(blue) << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}