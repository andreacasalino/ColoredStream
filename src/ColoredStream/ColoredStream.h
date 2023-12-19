#pragma once

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <variant>

namespace colored_stream {
/// context:
/// https://en.wikipedia.org/wiki/ANSI_escape_code

static const std::string RESETTER = "\u001b[0m";

enum class ClassicColor { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

struct Uint8Color {
  std::uint8_t code;
};

struct Uint24Color {
  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;
};

struct Null {};

using ColorText = std::variant<Null, ClassicColor, Uint8Color, Uint24Color>;
using ColorBackground = std::variant<Null, Uint8Color, Uint24Color>;

struct Colors {
  ColorText text = Null{};
  ColorBackground background = Null{};
};

std::ostream &operator<<(std::ostream &stream, const Colors &subject);

struct Settings {
  Settings() = default;

  Settings &text(const ColorText &col) {
    colors.text = col;
    return *this;
  }
  Settings &background(const ColorBackground &col) {
    colors.background = col;
    return *this;
  }

  Colors colors;
};

class ColoredText : public std::stringstream {
public:
  ColoredText(const Settings &settings);

  template <typename T, typename... Args>
  ColoredText(const Settings &settings, const T &element, const Args &...arsg)
      : ColoredText(settings) {
    this->add(element, arsg...);
  }

  // background color assumed to Null
  template <typename... Args>
  ColoredText(const ColorText &color, const Args &...arsg)
      : ColoredText(Settings{}.text(color), arsg...) {}

  void print(std::ostream &stream) const;

protected:
  template <typename T, typename... Args>
  void add(const T &element, const Args &...args) {
    this->add(element);
    this->add(args...);
  };
  template <typename T> void add(const T &element) { *this << element; };

private:
  const Colors colors;
};

std::ostream &operator<<(std::ostream &stream, const ColoredText &subject);

// Wraps a concrete ostream so that every time something
// is passed to this stream, the prefix, the content and the postfix needed to
// render the content are actually propagated to the wrapped stream
class ColoredStream {
public:
  ColoredStream(const Settings &settings, std::ostream &recipient = std::cout);

  // background color assumed to Null
  ColoredStream(const ColorText &color, std::ostream &recipient = std::cout);

  template <typename T> ColoredStream &operator<<(T w) {
    if (supportsColor) {
      wrapped_ << colors;
      wrapped_ << w;
      wrapped_ << RESETTER;
    } else {
      wrapped_ << w;
    }
    return *this;
  }

#ifdef _WIN32
  ColoredStream &operator<<(
      std::ostream&(*__pf)(std::ostream&));
  ColoredStream &
  operator<<(std::ostream::_Myios&(*__pf)(std::ostream::_Myios&));
#else
  ColoredStream& operator<<(
      std::ostream::__ostream_type& (*__pf)(std::ostream::__ostream_type&));
  ColoredStream&
      operator<<(std::ostream::__ios_type& (*__pf)(std::ostream::__ios_type&));
#endif
  ColoredStream &
  operator<<(std::ostream::ios_base &(*__pf)(std::ostream::ios_base &));

private:
  std::ostream &wrapped_;
  bool supportsColor;
  const Colors colors;
};
} // namespace colored_stream
