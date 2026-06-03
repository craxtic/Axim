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

#include "axim/core/types/color.h"
#include "axim/core/types/ctype.h"
#include "axim/core/types/vector2.h"
#include "axim/core/types/vector3.h"
#include <array>
#include <axim/core/conicsegment.h>
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
  this->interior_vert.clear();
  this->interior_indi.clear();
}


void Canvas::draw(const std::span<const ConicSegment>& segments, const Brush& brush) {


  if(segments.size() == 0) return;


  for(int i = 0; i < segments.size(); ++i){
    size_t base_i = vertices.size();
    vertices.push_back({segments[i].p0, Color::White, 1, 0});
    vertices.push_back({segments[i].p1, Color::White, segments[i].w1, 1});
    vertices.push_back({segments[i].p2, Color::White, 1, 2});

    indices.push_back(base_i + 0);
    indices.push_back(base_i + 1);
    indices.push_back(base_i + 2);
  } 

  for(int i = 0; i < segments.size() / 2; ++i){
    size_t base_i = interior_vert.size();
    interior_vert.push_back({segments[0].p0, Color::White, 1, 0});
    interior_vert.push_back({segments[i].p2, Color::White, 1, 1});
    interior_vert.push_back({segments[i+1].p2, Color::White, 1, 2});

    interior_indi.push_back(base_i + 0);
    interior_indi.push_back(base_i + 1);
    interior_indi.push_back(base_i + 2);
  } 

  // std::cout << "s1: " << vertices.size() << std::endl;

}

void Canvas::draw(const std::span<const ConicSegment>& segments, const Pen &pen) const {}

} // namespace axm
