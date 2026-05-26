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
#include <axim/core/types/vector2.h>

namespace axm {

class AXIM_CORE_API QuadraticBezier {

public:
  vec2f p0;
  vec2f p1_minus_p0; // p1 - p0
  vec2f p2_minus_2p1_plus_p0; // p2 - 2*p1 + p0

  QuadraticBezier(vec2f p0, vec2f p1, vec2f p2):
    p0(p0),
    p1_minus_p0(p1 - p0),
    p2_minus_2p1_plus_p0(p2 - 2.0f*p1 + p0)
  {}

  inline constexpr vec2f evaluate(float t) const {
    float tt = t*t;
    return (p0) + (2 * t * p1_minus_p0) + (tt * p2_minus_2p1_plus_p0);
  }


};

}