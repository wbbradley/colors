#pragma once

#include <ostream>
#include <sstream>
#include <unistd.h>

namespace colors {

template<typename T, int fgcolor>
struct Color {
  Color(const T &val) : val(val) {}

  const T &val;
};
}

namespace std {
template <typename T, int fgcolor> string to_string(const colors::Color<T, fgcolor> &c) {
  std::stringstream ss;
  if (isatty(0) && isatty(1)) {
    ss << "\e[0;3" << fgcolor << "m" << c.val << "\e[0m";
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

} // namespace colors
