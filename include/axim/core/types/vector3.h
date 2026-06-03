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

#include "axim/core/types/vector2.h"
#include <ostream>
#include <cmath>

#include <axim/core/types/vector2.h>

namespace axm {

template <typename T> struct vec3 {

  T x{0}, y{0}, z{0};
  
  constexpr vec3() = default;
  
  constexpr vec3(T x, T y, T z): x(x), y(y), z(z){ }


  /// \brief norm of vector |v|
  [[nodiscard]] constexpr T norm() const {
    return sqrt(x * x + y * y + z * z);
  }

  /// square of vector's norm 
  /// General property of Euclidean vector:  vector v^2 = norm |v|^2
  [[nodiscard]] constexpr T squared() const{
    return x * x + y * y + z * z;
  }

  /// return a unit vector of this*
  [[nodiscard]] constexpr vec3<T> unit() const{
    T norm = this->norm();
    return  vec3<T>(x/norm, y/norm, z/norm);
  }


  /**
   * @brief set all x, y, z components to 0
   * 
   */
  constexpr void to_zero(){
    x = 0;
    y = 0;
    z = 0;
  }

  [[nodiscard]] constexpr operator vec2f() const {
    return vec2f(x, y);
  }


};



/* nagate each component of the vector*/
template <typename T>
[[nodiscard]] constexpr vec3<T> operator-(const vec3<T> &v) {
  return vec3<T>(-v.x, -v.y, -v.z);
}


/* add two vectors, and return a new instance*/
template <typename T>
[[nodiscard]] constexpr vec3<T> operator+(const vec3<T> &a, const vec3<T> b) {
  return vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}


/* substract two vectors, and return a new instance*/
template <typename T>
[[nodiscard]] constexpr vec3<T> operator-(const vec3<T> &a, const vec3<T> b) {
  return vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

/* multiply a vector with a constant, and return a new vector*/
template <typename T>
[[nodiscard]] constexpr vec3<T> operator*(const vec3<T> &a, const T k) {
  return vec3<T>(a.x * k, a.y * k, a.z * k);
}


/* multiply a constant with a vector, and return a new vector*/
template <typename T>
[[nodiscard]] constexpr vec3<T> operator*(const T k, const vec3<T> &a) {
  return vec3<T>(k * a.x, k * a.y, k* a.z);
}


/* divide a vector by a constant, and return a new vector*/
template <typename T>
[[nodiscard]] constexpr vec3<T> operator/(const vec3<T> &a, const T k) {
  return vec3<T>(a.x / k, a.y / k, a.z / k);
}


/* dot product of two vectors */
template <typename T>
[[nodiscard]] constexpr T operator*(const vec3<T> &a, const vec3<T> &b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/* cross product of two vectors*/
template <typename T>
[[nodiscard]] constexpr vec3<T> operator^(const vec3<T> &a, const vec3<T> &b) {
  return vec3<T>(
    (a.y * b.z - b.y * a.z), 
    (b.x * a.z - a.x * b.z), 
    (a.x * b.y - b.x * a.y)
  );
}

/* return true if two vectors are equal */
template <typename T>
[[nodiscard]] constexpr bool operator==(const vec3<T> &a, const vec3<T> &b) {
  return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}


/* return true if two vectors are not equal */
template <typename T>
[[nodiscard]] constexpr bool operator!=(const vec3<T> &a, const vec3<T> &b) {
  return !(a == b);
}


/* add a new vector to itself */
template <typename T>
constexpr vec3<T> operator+=(vec3<T> &a, const vec3<T> &b){
  return a = a + b;
}


/* subtract a new vector from itself */
template <typename T>
constexpr vec3<T> operator-=(vec3<T> &a, const vec3<T> &b){
  return a = a - b;
}


/* multiply itself with a constant */
template <typename T>
constexpr vec3<T> operator*=(vec3<T> &a, const T k){
  return a = a * k;
}


/* divide itself by a constant */
template <typename T>
constexpr vec3<T> operator/=(vec3<T> &a, const T k){
  return a = a / k;
}


/* perform itself cross product with a vector */
template <typename T>
constexpr vec3<T> operator^=(vec3<T> &a, const vec3<T> &b){
  return a = a ^ b;
}


template <typename T>
constexpr std::ostream& operator<<(std::ostream &stream, const vec3<T> &a){
  return stream << '(' << a.x << ',' << a.y << ',' << a.z << ')';
}


/* pre-defined vec3 with some primitive types */
using vec3i = vec3<int>;
using vec3f = vec3<float>;


} 
