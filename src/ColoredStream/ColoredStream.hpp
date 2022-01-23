#pragma once

#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace colored_stream {
/// context:
/// https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html

class ColoredStream : public std::stringstream {
public:
  void print(std::ostream &stream) const {
    if (static_cast<const std::ostream *>(&std::cout) == &stream) {
      this->addColored(stream);
      return;
    }
    stream << this->str();
  };

protected:
  ColoredStream() = default;

  virtual void addColored(std::ostream &stream) const = 0;

  static const std::string RESETTER;

  template <typename T, typename... Args>
  void add(const T &element, const Args &...args) {
    this->add(element);
    this->add(args...);
  };
  template <typename T> void add(const T &element) { *this << element; };
};

const std::string ColoredStream::RESETTER = "\u001b[0m";

std::ostream &operator<<(std::ostream &stream, const ColoredStream &subject) {
  subject.print(stream);
  return stream;
}

enum ClassicColor { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

class ClassicColoredStream : public ColoredStream {
public:
  ClassicColoredStream(const ClassicColor &color)
      : color(CLASSIC_COLORS_TABLE.find(color)) {
    if (this->color == CLASSIC_COLORS_TABLE.end()) {
      throw std::runtime_error{"Invalid color"};
    }
  };

  template <typename T, typename... Args>
  ClassicColoredStream(const ClassicColor &color, const T &element,
                       const Args &...arsg)
      : ClassicColoredStream(color) {
    this->add(element, arsg...);
  }

protected:
  void addColored(std::ostream &stream) const override {
    stream << color->second << this->str() << RESETTER;
  };

private:
  const std::map<ClassicColor, std::string>::const_iterator color;

  static const std::map<ClassicColor, std::string> CLASSIC_COLORS_TABLE;
};

const std::map<ClassicColor, std::string>
    ClassicColoredStream::CLASSIC_COLORS_TABLE = {
        {RED, "\u001b[31;1m"},     {GREEN, "\u001b[32;1m"},
        {YELLOW, "\u001b[33;1m"},  {BLUE, "\u001b[34;1m"},
        {MAGENTA, "\u001b[35;1m"}, {CYAN, "\u001b[36;1m"},
        {WHITE, "\u001b[37;1m"},
};

class CustomColoredStream : public ColoredStream {
public:
  CustomColoredStream(char color_code) : color_code(color_code){};

  template <typename T, typename... Args>
  CustomColoredStream(char color_code, const T &element, const Args &...arsg)
      : CustomColoredStream(color_code) {
    this->add(element, arsg...);
  }

protected:
  void addColored(std::ostream &stream) const override {
    stream << CUSTOM_COLOR_PREAMBLE << color_code << 'm' << this->str()
           << RESETTER;
  };

private:
  const char color_code;

  static const std::string CUSTOM_COLOR_PREAMBLE;
};

const std::string CustomColoredStream::CUSTOM_COLOR_PREAMBLE = "\u001b[38;5;";

} // namespace colored_stream
