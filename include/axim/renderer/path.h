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

#include "axim/renderer/renderer.h"
#include <axim/config.h>
#include <vector>

namespace axm {
  

struct Brush {
  Color color;
};

struct Pen {
  Color color;
  float stroke_width;
};


class AXIM_RENDERER_API BezierPath {

public:
  std::vector<vec2f> points;

  BezierPath();

  void move_to(vec2f p);
  void line_to(vec2f p);
  void cubic_to(vec2f c1, vec2f c2, vec2f p);
  void curve_to(vec2f p);

  void close();
  void reset();

};

}