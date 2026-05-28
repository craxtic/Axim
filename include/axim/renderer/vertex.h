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

#include <axim/core/types/ctype.h>
#include <axim/core/types/color.h>
#include <axim/core/types/vector2.h>
#include <axim/core/types/vector3.h>
#include <vector>

namespace axm {

struct Vertex {
  vec3f pos;
  Color color;

  Vertex(vec2f pos2d, Color color):
    pos(pos2d.x, pos2d.y, 0),
    color(color)
  {}

  Vertex(const vec3f& pos, Color color):
    pos(pos),
    color(color)
  {}
 
};


}