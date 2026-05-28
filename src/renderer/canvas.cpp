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

#include "axim/core/types/vector2.h"
#include <axim/core/beziercurve.h>
#include <axim/renderer/canvas.h>
#include <cmath>
#include <iostream>
#include <iterator>

namespace axm {

void Canvas::clear() {
  this->vertices.clear();
  this->indices.clear();
}

void Canvas::draw_quadratic_bezier_stroke(vec2f p0, vec2f p1, vec2f p2, float thickness, Color color) {

  // {-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}
  // vertices.push_back({p0, color});
  vec2f p[] = {
    { 0.6f,  0.5f},
    { -0.6f, 0.3f},
    { 0.0f, -0.8f},
  };

  vertices.push_back( {p[0], color});
  vertices.push_back({p[1],  color});
  vertices.push_back({p[2],  color});
  

  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  
  // indices.push_back(0);
  // indices.push_back(3);
  // indices.push_back(2);

}

void Canvas::draw_path(const BezierPath &path, const Brush &brush) const {}

void Canvas::draw_path(const BezierPath &path, const Pen &pen) const {}

} // namespace axm
