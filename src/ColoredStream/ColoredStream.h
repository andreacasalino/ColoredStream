#pragma once

#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>

namespace colored_stream {
/// context:
/// https://en.wikipedia.org/wiki/ANSI_escape_code

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

struct Settings {
  Settings() = default;

  Settings &text(const ColorText &col) {
    text_ = col;
    return *this;
  }
  Settings &background(const ColorBackground &col) {
    background_ = col;
    return *this;
  }

  ColorText text_ = Null{};
  ColorBackground background_ = Null{};
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

  std::string col_str() const;

protected:
  static const std::string RESETTER;
  static const std::string TEXT_UINT8_PREABLE;
  static const std::string BCKGRND_UINT8_PREABLE;
  static const std::string TEXT_UINT24_PREABLE;
  static const std::string BCKGRND_UINT24_PREABLE;
  static const char SEPARATOR;
  static const char M_LETTER;

  static const std::unordered_map<ClassicColor, std::string>
      CLASSIC_COLORS_TABLE;

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

  const ColorText text;
  const ColorBackground background;
};

std::ostream &operator<<(std::ostream &stream, const ColoredText &subject);
} // namespace colored_stream
