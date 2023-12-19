#include <ColoredStream/ColoredStream.h>
#include <iostream>
#include <stdexcept>

namespace colored_stream {
const std::string ColoredText::RESETTER = "\u001b[0m";

const std::string ColoredText::TEXT_UINT8_PREABLE = "\u001b[38;5;";
const std::string ColoredText::BCKGRND_UINT8_PREABLE = "\u001b[48;5;";

const std::string ColoredText::TEXT_UINT24_PREABLE = "\u001b[38;2;";
const std::string ColoredText::BCKGRND_UINT24_PREABLE = "\u001b[48;2;";

const char ColoredText::SEPARATOR = ';';
const char ColoredText::M_LETTER = 'm';

const std::unordered_map<ClassicColor, std::string>
    ColoredText::CLASSIC_COLORS_TABLE = {
        {ClassicColor::RED, "\u001b[31;1m"},
        {ClassicColor::GREEN, "\u001b[32;1m"},
        {ClassicColor::YELLOW, "\u001b[33;1m"},
        {ClassicColor::BLUE, "\u001b[34;1m"},
        {ClassicColor::MAGENTA, "\u001b[35;1m"},
        {ClassicColor::CYAN, "\u001b[36;1m"},
        {ClassicColor::WHITE, "\u001b[37;1m"},
};

ColoredText::ColoredText(const Settings &settings)
    : text(settings.text_), background{settings.background_} {};

void ColoredText::print(std::ostream &stream) const {
  if (static_cast<const std::ostream *>(&std::cout) == &stream) {
    this->toStream(stream);
    return;
  }
  stream << this->str();
};

std::string ColoredText::col_str() const {
  std::stringstream result;
  this->toStream(result);
  return result.str();
};

void ColoredText::toStream(std::ostream &stream) const {
  this->addColorText(stream);
  this->addColorBackground(stream);
  stream << this->str();
  stream << RESETTER;
}

void ColoredText::addColorText(std::ostream &stream) const {
  struct ColorVisitor {
    std::ostream &stream;

    void operator()(const Null &) {}
    void operator()(const ClassicColor &color) {
      auto table_it = CLASSIC_COLORS_TABLE.find(color);
      if (table_it == CLASSIC_COLORS_TABLE.end()) {
        throw std::runtime_error{"Invalid color"};
      }
      stream << table_it->second;
    }
    void operator()(const Uint8Color &color) {
      stream << TEXT_UINT8_PREABLE << std::to_string(color.code) << M_LETTER;
    }
    void operator()(const Uint24Color &color) {
      stream << TEXT_UINT24_PREABLE << std::to_string(color.red) << SEPARATOR
             << std::to_string(color.green) << SEPARATOR
             << std::to_string(color.blue) << M_LETTER;
    }
  };
  std::visit(ColorVisitor{stream}, this->text);
};

void ColoredText::addColorBackground(std::ostream &stream) const {
  struct ColorVisitor {
    std::ostream &stream;

    void operator()(const Null &) {}
    void operator()(const Uint8Color &color) {
      stream << BCKGRND_UINT8_PREABLE << std::to_string(color.code) << M_LETTER;
    }
    void operator()(const Uint24Color &color) {
      stream << BCKGRND_UINT24_PREABLE << std::to_string(color.red) << SEPARATOR
             << std::to_string(color.green) << SEPARATOR
             << std::to_string(color.blue) << M_LETTER;
    }
  };
  std::visit(ColorVisitor{stream}, this->background);
};

std::ostream &operator<<(std::ostream &stream, const ColoredText &subject) {
  subject.print(stream);
  return stream;
}
} // namespace colored_stream
