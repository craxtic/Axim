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

#include "axim/core/types/ctype.h"
#include "axim/renderer/path.h"
#include <axim/config.h>
#include <axim/core/types/vector2.h>
#include <axim/renderer/vertex.h>


namespace axm {



class AXIM_RENDERER_API Canvas {

  std::vector<Vertex> vertices;
  std::vector<u16> indices;

public:
  u32 width, height;
  Color bg_color;

  Canvas(u32 width, u32 height, Color fill);

  void reset(u32 width, u32 height);
  
  [[nodiscard]] inline const std::vector<Vertex>& get_vertices() const {
    return vertices;
  }
  
  [[nodiscard]] inline const std::vector<u16>& get_indices() const {
    return indices;
  }
  
  void clear();
  void draw_quadratic_bezier_stroke(vec2f p0, vec2f p1, vec2f p2, float thickness, Color color);
  void draw_path(const BezierPath& path, const Brush& brush) const;
  void draw_path(const BezierPath& path, const Pen& pen) const;


};


}