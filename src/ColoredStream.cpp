#include <ColoredStream/ColoredStream.h>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

namespace colored_stream {
namespace {
static const std::string TEXT_UINT8_PREABLE = "\u001b[38;5;";
static const std::string BCKGRND_UINT8_PREABLE = "\u001b[48;5;";

static const std::string TEXT_UINT24_PREABLE = "\u001b[38;2;";
static const std::string BCKGRND_UINT24_PREABLE = "\u001b[48;2;";

static const char SEPARATOR = ';';
static const char M_LETTER = 'm';

static const std::unordered_map<ClassicColor, std::string>
    CLASSIC_COLORS_TABLE = {
        {ClassicColor::RED, "\u001b[31;1m"},
        {ClassicColor::GREEN, "\u001b[32;1m"},
        {ClassicColor::YELLOW, "\u001b[33;1m"},
        {ClassicColor::BLUE, "\u001b[34;1m"},
        {ClassicColor::MAGENTA, "\u001b[35;1m"},
        {ClassicColor::CYAN, "\u001b[36;1m"},
        {ClassicColor::WHITE, "\u001b[37;1m"},
};

void addColorText(std::ostream &stream, const ColorText &color) {
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
  std::visit(ColorVisitor{stream}, color);
};

void addColorBackground(std::ostream &stream, const ColorBackground &color) {
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
  std::visit(ColorVisitor{stream}, color);
};
} // namespace

std::ostream &operator<<(std::ostream &stream, const Colors &subject) {
  addColorText(stream, subject.text);
  addColorBackground(stream, subject.background);
  return stream;
}

ColoredText::ColoredText(const Settings &settings) : colors{settings.colors} {};

namespace {
static const std::unordered_set<const std::ostream *>
    STREAMS_SUPPORTING_COLORS = std::unordered_set<const std::ostream *>{
        static_cast<const std::ostream *>(&std::cout),
        static_cast<const std::ostream *>(&std::cerr)};
}

void ColoredText::print(std::ostream &stream) const {
  if (STREAMS_SUPPORTING_COLORS.find(&stream) !=
      STREAMS_SUPPORTING_COLORS.end()) {
    stream << colors;
    stream << this->str();
    stream << RESETTER;
    return;
  }
  stream << this->str();
};

std::ostream &operator<<(std::ostream &stream, const ColoredText &subject) {
  subject.print(stream);
  return stream;
}

ColoredStream::ColoredStream(const Settings &settings, std::ostream &recipient)
    : wrapped_{recipient}, supportsColor{STREAMS_SUPPORTING_COLORS.find(
                                             &recipient) !=
                                         STREAMS_SUPPORTING_COLORS.end()},
      colors{settings.colors} {}

ColoredStream::ColoredStream(const ColorText &color, std::ostream &recipient)
    : ColoredStream{Settings{}.text(color), recipient} {}

#ifdef _WIN32
ColoredStream &ColoredStream::operator<<(
    std::ostream&(*__pf)(std::ostream&)) {
  __pf(wrapped_);
  return *this;
}

ColoredStream &ColoredStream::operator<<(
    std::ostream::_Myios&(*__pf)(std::ostream::_Myios&)) {
  __pf(wrapped_);
  return *this;
}
#else
ColoredStream& ColoredStream::operator<<(
    std::ostream::__ostream_type& (*__pf)(std::ostream::__ostream_type&)) {
    __pf(wrapped_);
    return *this;
}

ColoredStream& ColoredStream::operator<<(
    std::ostream::__ios_type& (*__pf)(std::ostream::__ios_type&)) {
    __pf(wrapped_);
    return *this;
}
#endif

ColoredStream &ColoredStream::operator<<(
    std::ostream::ios_base &(*__pf)(std::ostream::ios_base &)) {
  __pf(wrapped_);
  return *this;
}

} // namespace colored_stream
