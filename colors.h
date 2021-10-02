#pragma once

#include <ostream>
#include <sstream>
#include <unistd.h>
#include <string.h>

namespace colors {

template <typename T, int fgcolor> struct Color {
  Color(const T &val) : val(val) {
  }

  const T &val;
};
template <typename T, int r, int g, int b> struct RGB {
  RGB(const T &val) : val(val) {
  }

  const T &val;
};
} // namespace colors

namespace std {
template <typename T, int fgcolor> string to_string(const colors::Color<T, fgcolor> &c) {
  static bool tty = isatty(0) && isatty(1) && strcmp(getenv("NOCOLOR") ? getenv("NOCOLOR") : "", "1") != 0;
  std::stringstream ss;
  if (tty) {
    ss << "\e[0;3" << fgcolor << "m" << c.val << "\e[0m";
    return ss.str();
  } else {
    ss << c.val;
    return ss.str();
  }
}
template <typename T, int r, int g, int b> string to_string(const colors::RGB<T, r, g, b> &c) {
  static bool tty = isatty(0) && isatty(1) && strcmp(getenv("NOCOLOR") ? getenv("NOCOLOR") : "", "1") == -1;
  std::stringstream ss;
  if (tty) {
    ss << "\e[38;2;" << r << ";" << g << ";" << b << "m" << c.val << "\e[0m";
    return ss.str();
  } else {
    ss << c.val;
    return ss.str();
  }
}
} // namespace std

namespace colors {

template <typename T, int fgcolor>
std::ostream &operator<<(std::ostream &os, const Color<T, fgcolor> &c) {
  return os << std::to_string(c);
}
template <typename T, int r, int g, int b>
std::ostream &operator<<(std::ostream &os, const RGB<T, r, g, b> &c) {
  return os << std::to_string(c);
}

template <typename U> Color<U, 0> black(const U &val) {
  return Color<U, 0>(val);
}
template <typename U> Color<U, 1> red(const U &val) {
  return Color<U, 1>(val);
}
template <typename U> Color<U, 2> green(const U &val) {
  return Color<U, 2>(val);
}
template <typename U> Color<U, 3> yellow(const U &val) {
  return Color<U, 3>(val);
}
template <typename U> Color<U, 4> blue(const U &val) {
  return Color<U, 4>(val);
}
template <typename U> Color<U, 5> magenta(const U &val) {
  return Color<U, 5>(val);
}
template <typename U> Color<U, 6> cyan(const U &val) {
  return Color<U, 6>(val);
}
template <typename U> RGB<U, 255, 140, 0> darkorange(const U &val) {
  return RGB<U, 255, 140, 0>(val);
}

} // namespace colors
