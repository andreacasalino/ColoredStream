#include <ColoredStream/ColoredStream.hpp>
#include <fstream>
using namespace colored_stream;

int main() {
  std::cout << CustomColoredStream{'F', "Hello world ", 'F'} << " done"
            << std::endl;

  return EXIT_SUCCESS;
}