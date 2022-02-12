#pragma once

#include <map>
#include <optional>
#include <ostream>
#include <sstream>
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
  ColoredStream(const Color &text_color);

  template <typename T, typename... Args>
  ColoredStream(const Color &text_color, const T &element, const Args &...arsg)
      : ColoredStream(text_color) {
    this->add(element, arsg...);
  }

  void setBackground(const Color &color);

  void print(std::ostream &stream) const;

  std::string col_str() const;

protected:
  static const std::string RESETTER;
  static const std::string TEXT_UINT8_PREABLE;
  static const std::string BCKGRND_UINT8_PREABLE;
  static const std::string TEXT_UINT24_PREABLE;
  static const std::string BCKGRND_UINT24_PREABLE;
  static const char SEPARATOR;
  static const char M_LETTER;

  static const std::map<ClassicColor, std::string> CLASSIC_COLORS_TABLE;

  static const std::string CUSTOM_COLOR_PREAMBLE;

  template <typename T, typename... Args>
  void add(const T &element, const Args &...args) {
    this->add(element);
    this->add(args...);
  };
  template <typename T> void add(const T &element) { *this << element; };

private:
  void toStream(std::ostream &stream) const;

  void addColorText(std::ostream &stream) const;

  void addColorBackground(std::ostream &stream) const;

  const Color text;
  std::optional<const Color> background;
};

std::ostream &operator<<(std::ostream &stream, const ColoredStream &subject);
} // namespace colored_stream
