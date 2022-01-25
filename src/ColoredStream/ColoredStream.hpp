#pragma once

#include <iostream>
#include <map>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>

namespace colored_stream {
/// context:
/// https://en.wikipedia.org/wiki/ANSI_escape_code

enum ClassicColor { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

struct Uint8Color {
  std::uint8_t code;
};

struct Uint24Color {
  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;
};

using Color = std::variant<ClassicColor, Uint8Color, Uint24Color>;

class ColoredStream : public std::stringstream {
public:
  ColoredStream(const Color &text_color) : text(text_color){};

  template <typename T, typename... Args>
  ColoredStream(const Color &text_color, const T &element, const Args &...arsg)
      : ColoredStream(text_color) {
    this->add(element, arsg...);
  }

  void setBackground(const Color &color) { background.emplace(color); };

  void print(std::ostream &stream) const {
    if (static_cast<const std::ostream *>(&std::cout) == &stream) {
      this->toStream(stream);
      return;
    }
    stream << this->str();
  };

  std::string col_str() const {
    std::stringstream result;
    this->toStream(result);
    return result.str();
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
  void toStream(std::ostream &stream) const {
    this->addColorText(stream);
    this->addColorBackground(stream);
    stream << this->str();
    stream << RESETTER;
  }

  void addColorText(std::ostream &stream) const {
    struct ColorVisitor {
      std::ostream &stream;

      void operator()(const ClassicColor &color) {
        auto table_it = CLASSIC_COLORS_TABLE.find(color);
        if (table_it == CLASSIC_COLORS_TABLE.end()) {
          throw std::runtime_error{"Invalid color"};
        }
        stream << table_it->second;
      }
      void operator()(const Uint8Color &color) {
        stream << "\u001b[38;5;" << std::to_string(color.code) << 'm';
      }
      void operator()(const Uint24Color &color) {
        stream << "\u001b[38;2;" << std::to_string(color.red) << ';'
               << std::to_string(color.green) << ';'
               << std::to_string(color.blue) << 'm';
      }
    };
    std::visit(ColorVisitor{stream}, this->text);
  };

  void addColorBackground(std::ostream &stream) const {
    if (std::nullopt == this->background) {
      return;
    }
    struct ColorVisitor {
      std::ostream &stream;

      void operator()(const ClassicColor &color) {
        throw std::runtime_error{"Invalid color"};
      }
      void operator()(const Uint8Color &color) {
        stream << "\u001b[48;5;" << std::to_string(color.code) << 'm';
      }
      void operator()(const Uint24Color &color) {
        stream << "\u001b[48;2;" << std::to_string(color.red) << ';'
               << std::to_string(color.green) << ';'
               << std::to_string(color.blue) << 'm';
      }
    };
    std::visit(ColorVisitor{stream}, *this->background);
  };

  const Color text;
  std::optional<const Color> background;
};

const std::string ColoredStream::RESETTER = "\u001b[0m";

const std::map<ClassicColor, std::string> ColoredStream::CLASSIC_COLORS_TABLE =
    {
        {RED, "\u001b[31;1m"},     {GREEN, "\u001b[32;1m"},
        {YELLOW, "\u001b[33;1m"},  {BLUE, "\u001b[34;1m"},
        {MAGENTA, "\u001b[35;1m"}, {CYAN, "\u001b[36;1m"},
        {WHITE, "\u001b[37;1m"},
};

std::ostream &operator<<(std::ostream &stream, const ColoredStream &subject) {
  subject.print(stream);
  return stream;
}

} // namespace colored_stream
