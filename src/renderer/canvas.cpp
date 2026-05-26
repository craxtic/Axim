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

namespace axm {

void Canvas::clear() {
  this->vertices.clear();
  this->indices.clear();
}

void Canvas::draw_cubic_stroke(vec2f p1, vec2f p2, vec2f p3, vec2f p4,
                               float thickness, Color color) {


  vec2f a = p1, b = p2;
  vec2f v = b - a;
  vec2f n = v.unit().normal();

  vec2f r = (thickness / 2.0f) * n;

  size_t baseindex = vertices.size();

  vertices.push_back({a + r, color});
  vertices.push_back({a - r, color});
  vertices.push_back({b - r, color});
  vertices.push_back({b + r, color});

  indices.push_back(baseindex + 0);
  indices.push_back(baseindex + 1);
  indices.push_back(baseindex + 2);

  indices.push_back(baseindex + 0);
  indices.push_back(baseindex + 2);
  indices.push_back(baseindex + 3);
}

void Canvas::draw_path(const BezierPath &path, const Brush &brush) const {}

void Canvas::draw_path(const BezierPath &path, const Pen &pen) const {}

} // namespace axm
