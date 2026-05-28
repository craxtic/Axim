/*     _          _
 *    / \   __  _(_)_ __ ___
 *   / _ \  \ \/ / | '_ ` _ \
 *  / ___ \  >  <| | | | | | |
 * /_/   \_\/_/\_\_|_| |_| |_|
 *
 * Copyright (c) 2026 The Axim Team
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org.
 */

#pragma once

#include <axim/core/types/ctype.h>

#include <ostream>

namespace axm {

// template <typename T>
struct Color {

  // union {
  union {
    u32 rgba;
    struct {
      u8 r, g, b, a;
    };
  };

  constexpr Color() = default;

  constexpr Color(u8 r, u8 g, u8 b, u8 a = 255);

  constexpr explicit Color(u32 hex);

  // [[nodiscard]] constexpr u8 &operator[](int i) { return data[i]; }
  // [[nodiscard]] constexpr const u8 &operator[](int i) const { return data[i];
  // }

  [[nodiscard]] constexpr operator u32() const { return rgba; }

  static const Color Black;       // Black predefined color
  static const Color White;       // White predefined color
  static const Color Red;         // Red predefined color
  static const Color Green;       // Green predefined color
  static const Color Blue;        // Blue predefined color
  static const Color Yellow;      // Yellow predefined color
  static const Color Magenta;     // Magenta predefined color
  static const Color Cyan;        // Cyan predefined color
  static const Color Transparent; // Transparent (black) predefined color
};

constexpr Color::Color(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}

constexpr Color::Color(u32 hex)
    : r(static_cast<u8>((hex & 0xff000000) >> 24)),
      g(static_cast<u8>((hex & 0x00ff0000) >> 16)),
      b(static_cast<u8>((hex & 0x0000ff00) >> 8)),
      a(static_cast<u8>((hex & 0x000000ff) >> 0)) {}

/* Color() + Color() */
[[nodiscard]] constexpr Color operator+(const Color &x, const Color &y) {

  const auto clamped_add = [](u8 a, u8 b) {
    const int result = int{a} + int{b};
    return static_cast<u8>(result < 255 ? result : 255);
  };

  return Color(clamped_add(x.r, y.r), clamped_add(x.g, y.g),
               clamped_add(x.b, y.b), clamped_add(x.a, y.a));
}

/* Color() - Color() */
[[nodiscard]] constexpr Color operator-(const Color &x, const Color &y) {

  const auto clamped_substract = [](u8 a, u8 b) {
    const int result = int{a} - int{b};
    return static_cast<u8>(result > 0 ? result : 0);
  };

  return Color(clamped_substract(x.r, y.r), clamped_substract(x.g, y.g),
               clamped_substract(x.b, y.b), clamped_substract(x.a, y.a));
}

/* Color() * Color() */
[[nodiscard]] constexpr Color operator*(const Color &x, const Color &y) {

  const auto scaled_multiply = [](u8 a, u8 b) {
    const auto result = static_cast<u8>(u16{a} * u16{b});
    return static_cast<std::uint8_t>(result / 255u);
  };

  return Color(scaled_multiply(x.r, y.r), scaled_multiply(x.g, y.g),
               scaled_multiply(x.b, y.b), scaled_multiply(x.a, y.a));
}

/* Color() == Color() */
[[nodiscard]] constexpr bool operator==(const Color &x, const Color &y) {
  return (x.r == y.r) && (x.g == y.g) && (x.b == y.b) && (x.a == y.a);
}

/* Color() != Color() */
[[nodiscard]] constexpr bool operator!=(const Color &x, const Color &y) {
  return !(x == y);
}

/* Color() += Color() */
constexpr Color &operator+=(Color &x, const Color &y) { return x = x + y; }

/* Color() -= Color() */
constexpr Color &operator-=(Color &x, const Color &y) { return x = x - y; }

/* Color() *= Color() */
constexpr Color &operator*=(Color &x, const Color &y) { return x = x * y; }

/* format into "(r,g,b,a)" */
inline std::ostream &operator<<(std::ostream &stream, const Color &c) {
  return stream << '(' << c.r << ',' << c.g << ',' << c.b << ',' << c.a << ')';
}

inline constexpr Color Color::Black(0, 0, 0);
inline constexpr Color Color::White(255, 255, 255);
inline constexpr Color Color::Red(255, 0, 0);
inline constexpr Color Color::Green(0, 255, 0);
inline constexpr Color Color::Blue(0, 0, 255);
inline constexpr Color Color::Yellow(255, 255, 0);
inline constexpr Color Color::Magenta(255, 0, 255);
inline constexpr Color Color::Cyan(0, 255, 255);
inline constexpr Color Color::Transparent(0, 0, 0, 0);

} // namespace axm
