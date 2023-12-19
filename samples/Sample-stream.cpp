#include <ColoredStream/ColoredStream.h>
#include <stdexcept>
using namespace colored_stream;

struct Error {
  std::string msg;
};

std::ostream &operator<<(std::ostream &recipient, const Error &err) {
  recipient << err.msg;
  return recipient;
}

int main() {
  ColoredStream outStream{ClassicColor::GREEN, std::cout};
  ColoredStream errStream{ClassicColor::RED, std::cerr};

  outStream << "Normal behaviour" << std::endl;

  std::string msg = "some detailed message explaining the error";
  errStream << "Ops, an error occurred: " << msg << std::endl;

  outStream << "Ok "
            << "recovered" << std::endl;

  errStream << "Auch no, another error: "
            << Error{"This would be the msg contained in a printable object"}
            << std::endl;

  return EXIT_SUCCESS;
}