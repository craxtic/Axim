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

#include <include/core/SkPoint.h>
#include <ostream>
#include <cmath>

namespace axm {

template <typename T> struct vec2 {

  T x{0}, y{0};

  
  constexpr vec2() = default;
  
  constexpr vec2(T x, T y): x(x), y(y) {}

  // /// vec[i]
  // [[nodiscard]] constexpr T& operator[](int i) { return data[i]; }
  // [[nodiscard]] constexpr const T& operator[](int i) const { return data[i]; }


  /* \brief norm of vector |v| */
  [[nodiscard]] constexpr T norm() const {
    return sqrt(x * x + y * y);
  }

  /// square of vector's norm 
  /// General property of Euclidean vector:  vector v^2 = norm |v|^2
  [[nodiscard]] constexpr T squared() const{
    return x * x + y * y;
  }


  /// return a normal (perpendicular) vector of this*
  [[nodiscard]] constexpr vec2 normal() const{
    return vec2(-y, x);
  }

  /// return a unit vector of this*
  [[nodiscard]] constexpr vec2 unit() const{
    T norm = this->norm();
    return  vec2(x/norm, y/norm);
  }


  [[nodiscard]] constexpr operator SkPoint(){
    return SkPoint(x, y);
  }


};


/* nagate each component of the vector*/
template <typename T>
[[nodiscard]] constexpr vec2<T> operator-(const vec2<T> &v) {
  return vec2<T>(-v.x, -v.y);
}


/* add two vectors, and return a new instance*/
template <typename T>
[[nodiscard]] constexpr vec2<T> operator+(const vec2<T> &a, const vec2<T> b) {
  return vec2<T>(a.x + b.x, a.y + b.y);
}


/* substract two vectors, and return a new instance*/
template <typename T>
[[nodiscard]] constexpr vec2<T> operator-(const vec2<T> &a, const vec2<T> b) {
  return vec2<T>(a.x - b.x, a.y - b.y);
}

/* multiply a vector with a constant, and return a new vector*/
template <typename T>
[[nodiscard]] constexpr vec2<T> operator*(const vec2<T> &a, const T k) {
  return vec2<T>(a.x * k, a.y * k);
}


/* multiply a constant with a vector, and return a new vector*/
template <typename T>
[[nodiscard]] constexpr vec2<T> operator*(const T k, const vec2<T> &a) {
  return vec2<T>(k * a.x, k * a.y);
}


/* divide a vector by a constant, and return a new vector*/
template <typename T>
[[nodiscard]] constexpr vec2<T> operator/(const vec2<T> &a, const T k) {
  return vec2<T>(a.x / k, a.y / k);
}


/* dot product of two vector */
template <typename T>
[[nodiscard]] constexpr T operator*(const vec2<T> &a, const vec2<T> &b) {
  return (a.x * b.x) + (a.y * b.y);
}


/* return true if two vectors are equal */
template <typename T>
[[nodiscard]] constexpr bool operator==(const vec2<T> &a, const vec2<T> &b) {
  return (a.x == b.x) && (a.y == b.y);
}


/* return true if two vectors are not equal */
template <typename T>
[[nodiscard]] constexpr bool operator!=(const vec2<T> &a, const vec2<T> &b) {
  return !(a == b);
}


/* add a new vector to itself */
template <typename T>
constexpr vec2<T> operator+=(vec2<T> &a, const vec2<T> &b){
  return a = a + b;
}


/* subtract a new vector from itself */
template <typename T>
constexpr vec2<T> operator-=(vec2<T> &a, const vec2<T> &b){
  return a = a - b;
}


/* multiply itself with a constant */
template <typename T>
constexpr vec2<T> operator*=(vec2<T> &a, const T k){
  return a = a * k;
}


/* divide itself by a constant */
template <typename T>
constexpr vec2<T> operator/=(vec2<T> &a, const T k){
  return a = a / k;
}


template <typename T>
constexpr std::ostream& operator<<(std::ostream &stream, const vec2<T> &a){
  return stream << '(' << a.x << ',' << a.y << ')';
}


/* pre-defined vec2 with some primitive types. */
using vec2i = vec2<int>;
using vec2u = vec2<unsigned int>;
using vec2f = vec2<float>;

} 
