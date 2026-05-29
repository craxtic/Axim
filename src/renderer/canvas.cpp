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


Canvas::Canvas(u32 width, u32 height, Color fill)  : width(width), height(height), bg_color(fill)
  {}


void Canvas::reset(u32 width, u32 height){
  this->width = width;
  this->height = height;
}

void Canvas::clear() {
  this->vertices.clear();
  this->indices.clear();
}

void Canvas::draw_quadratic_bezier_stroke(vec2f p0, vec2f p1, vec2f p2, float thickness, Color color) {

  // {-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}
  // vertices.push_back({p0, color});
  vec2f points[] = {
    {600, 200},
    {800, 200},
    {800, 400},
    {800, 400},
    {800, 600},
    {600, 600},
    // {400, 600},
    // {400, 400},
    // {400, 200},
    // {600, 200},
  };


  // 3, 5, 7, 8, 9, 11, ...
  // number of points = 2n + 1, n is the number of curves.
  // 0, 1, 2,  2, 3, 4,  4, 5, 6,  6, 7, 8,  8, 9, 10
  // % 3
  // 0, 1, 2,  2, 1, 0,  0, 1, 2,  0, 1, 2,  0, 1, 2

  // 1, 2, 3,  3, 4, 5,  5, 6, 7,  7, 8, 9,  9, 10, 11
  // 0, 1, 2,  0, 1, 2,  0, 1, 2,  0, 1, 2,  0, 1, 2

  // vec2f uvs[] = {
  //   {0.0, 0.0},
  //   {0.5, 0.0},
  //   {0.1, 0.1},
  //   {0.0, 0.0},
  //   {0.5, 0.0},
  // };

  // index = gl_vertexID & 4; 


  for(vec2f p : points){
    vertices.push_back({p, color, 1});
  }
  
  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);

  indices.push_back(3);
  indices.push_back(4);
  indices.push_back(5);

  // for(int i = 0; i < sizeof(points)/sizeof(vec2f) / 2 + 1; i += 2){
    
  //   indices.push_back(0 + i);
  //   indices.push_back(1 + i);
  //   indices.push_back(2 + i);
    
  //   std::cout << 0 + i << std::endl;
  //   std::cout << 1 + i << std::endl;
  //   std::cout << 2 + i << std::endl;
  
  // }

}

void Canvas::draw_path(const BezierPath &path, const Brush &brush) const {}

void Canvas::draw_path(const BezierPath &path, const Pen &pen) const {}

} // namespace axm
