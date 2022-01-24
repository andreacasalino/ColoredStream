#pragma once

#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>

namespace colored_stream {
/// context:
/// https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html

enum ClassicColor { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

struct ASCIIColorCode {
  char code;
};

using Color = std::variant<ClassicColor, ASCIIColorCode>;

class ColoredStream : public std::stringstream {
public:
  ColoredStream(const Color &color) : color(color){};

  template <typename T, typename... Args>
  ColoredStream(const Color &color, const T &element, const Args &...arsg)
      : ColoredStream(color) {
    this->add(element, arsg...);
  }

  void print(std::ostream &stream) const {
    if (static_cast<const std::ostream *>(&std::cout) == &stream) {
      struct ColorVisitor {
        std::ostream &stream;

        void operator()(const ClassicColor &color) {
          auto table_it = CLASSIC_COLORS_TABLE.find(color);
          if (table_it == CLASSIC_COLORS_TABLE.end()) {
            throw std::runtime_error{"Invalid color"};
          }
          stream << table_it->second;
        }
        void operator()(const ASCIIColorCode &color) {
          stream << CUSTOM_COLOR_PREAMBLE << color.code << 'm';
        }
      };
      std::visit(ColorVisitor{stream}, this->color);

      stream << this->str();
      stream << RESETTER;
      return;
    }
    stream << this->str();
  };

protected:
  static const std::string RESETTER;

  static const std::map<ClassicColor, std::string> CLASSIC_COLORS_TABLE;

  static const std::string CUSTOM_COLOR_PREAMBLE;

  template <typename T, typename... Args>
  void add(const T &element, const Args &...args) {
    this->add(element);
    this->add(args...);
  };
  template <typename T> void add(const T &element) { *this << element; };

private:
  const Color color;
};

const std::string ColoredStream::RESETTER = "\u001b[0m";

const std::map<ClassicColor, std::string> ColoredStream::CLASSIC_COLORS_TABLE =
    {
        {RED, "\u001b[31;1m"},     {GREEN, "\u001b[32;1m"},
        {YELLOW, "\u001b[33;1m"},  {BLUE, "\u001b[34;1m"},
        {MAGENTA, "\u001b[35;1m"}, {CYAN, "\u001b[36;1m"},
        {WHITE, "\u001b[37;1m"},
};

const std::string ColoredStream::CUSTOM_COLOR_PREAMBLE = "\u001b[38;5;";

std::ostream &operator<<(std::ostream &stream, const ColoredStream &subject) {
  subject.print(stream);
  return stream;
}

} // namespace colored_stream
