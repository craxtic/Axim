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

#include "axim/core/conicsegment.h"
#include "axim/core/types/ctype.h"
#include "axim/renderer/paint.h"
#include <axim/config.h>
#include <axim/core/types/vector2.h>
#include <axim/renderer/vertex.h>
#include <vector>


namespace axm {



class AXIM_RENDERER_API Canvas {

public:
  std::vector<Vertex> vertices;
  std::vector<u16> indices;

  std::vector<Vertex> interior_vert;
  std::vector<u16> interior_indi;

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
  void draw(const std::span<const ConicSegment>& segments, const Brush& brush);
  void draw(const std::span<const ConicSegment>& segments, const Pen& pen) const;


};


}