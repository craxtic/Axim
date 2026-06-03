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

#include <axim/config.h>
#include <axim/core/types/vector3.h>

namespace axm {

class AXIM_CORE_API ConicSegment {

public:
  vec3f p0;
  vec3f p1;
  vec3f p2; 
  float w1;


  /**
  * @brief Represents a Conic Segment (Rational Quadratic Bézier Curve).
  * 
  * A conic segment defined by three control points and one weight factor.
  * The weight value determines the geometric shape of the resulting curve.
  *
  * @param[in] p0 The start point.
  * @param[in] p1 The control point.
  * @param[in] p2 The end point.
  * @param[in] w1 The weight of the control point p1.
  *
  * Shape classification based on the weight parameter (w1):
  * - w1 -> 0 : Degenerates into a straight line segment.
  * - 0 < w1 < 1  : Forms an elliptical or circular arc.
  * - w1 = 1  : Form a parabolic arc.
  * - w1 > 1  : Forms a hyperbolic arc.
  *
  * @note the end point weight w0 & w2 are fixed to 1.
  */ 
  ConicSegment(const vec3f& p0, const vec3f& p1, const vec3f& p2, float w1):
    p0(p0),
    p1(p1),
    p2(p2), 
    w1(w1)
  {}


};

}