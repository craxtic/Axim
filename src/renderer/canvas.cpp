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

#include "axim/core/types/ctype.h"
#include "axim/core/types/vector2.h"
#include "axim/core/types/vector3.h"
#include <axim/core/beziercurve.h>
#include <axim/renderer/canvas.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

namespace axm {

Canvas::Canvas(u32 width, u32 height, Color fill)
    : width(width), height(height), bg_color(fill) {}

void Canvas::reset(u32 width, u32 height) {
  this->width = width;
  this->height = height;
}

void Canvas::clear() {
  this->vertices.clear();
  this->indices.clear();
}


void Canvas::draw_path(const BezierPath &path, const Brush &brush) {

  const std::vector<vec3f> &points = path.points;
  size_t len = path.points.size();
  Color color = brush.color;

  for(int i = 0; i < len/2 + 3; i += 2){
    vertices.push_back({points[0+i], color, 1, 0});
    vertices.push_back({points[1+i], color, 1, 1});
    vertices.push_back({points[2+i], color, 1, 2});
  } 

  for(int i = 0; i < len / 2; i += 2){
    vertices.push_back({points[0], color, 0, 0});
    vertices.push_back({points[2+i], color, 0, 1});
    vertices.push_back({points[4+i], color, 0, 2});
  }

  for(int i = 0; i < vertices.size(); i++){
    indices.push_back(i);
  }

}

void Canvas::draw_path(const BezierPath &path, const Pen &pen) const {}

} // namespace axm
