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


  Vertex(const vec3f& pos, Color color, u8 w, u8 local_index):
    pos(pos),
    color(
      color.r,
      color.g,
      (color.b & 0b11111100) | w,
      (color.a & 0b11111100) | local_index
    )
  {
    // we sacrifice
    //  2 bit of color.b for flag w
    //  2 bits of color.a for local_index
  }
 
};


}