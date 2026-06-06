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

#include <axim/core/types/color.h>
#include <axim/core/types/ctype.h>
#include <axim/core/conicsegment.h>
#include <axim/renderer/canvas.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <print>
#include <vector>
#include <limits>

namespace axm {

Canvas::Canvas(u32 width, u32 height, Color fill): 
  width(width), 
  height(height), 
  bg_color(fill) 
{

  this->vertices.reserve(UINT16_MAX);
  this->indices.reserve(UINT16_MAX);
  this->interior_vert.reserve(UINT16_MAX);
  this->interior_vert.reserve(UINT16_MAX);

}


void Canvas::clear() {
  this->vertices.clear();
  this->indices.clear();
  this->interior_vert.clear();
  this->interior_indi.clear();
  return;
}



void Canvas::draw(
  const std::span<const ConicSegment>& segments, 
  const Brush& brush
){

  if(segments.size() == 0) return;

  for(size_t i = 0; i < segments.size(); ++i){
    if(segments[i].w1 == 0) continue;
    size_t base_i = vertices.size();
    vertices.emplace_back(segments[i].p0, brush.color, 1, 0);
    vertices.emplace_back(segments[i].p1, brush.color, segments[i].w1, 1);
    vertices.emplace_back(segments[i].p2, brush.color, 1, 2);

    indices.emplace_back(base_i + 0);
    indices.emplace_back(base_i + 1);
    indices.emplace_back(base_i + 2);
  } 

  for(size_t i = 0; i < segments.size() / 2; ++i){
    size_t base_i = interior_vert.size();
    interior_vert.emplace_back(segments[0].p0, brush.color, 1, 0);
    interior_vert.emplace_back(segments[i].p2, brush.color, 1, 1);
    interior_vert.emplace_back(segments[i+1].p2, brush.color, 1, 2);

    interior_indi.emplace_back(base_i + 0);
    interior_indi.emplace_back(base_i + 1);
    interior_indi.emplace_back(base_i + 2);
  } 

  std::printf("size: v(%ld), i(%ld)\n", vertices.size(), interior_vert.size());

  return;
}

void Canvas::draw(
  const std::span<const ConicSegment>& segments, 
  const Pen &pen
){

  (void) (segments);
  (void) (pen);

  return;
}

} // namespace axm
