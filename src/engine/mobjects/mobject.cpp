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

#include <axim/engine/mobjects/mobcloud.h>
#include <axim/engine/mobjects/mobject.h>
#include <axim/renderer/paint.h>

namespace axm {

Mobject::Mobject(Color color, float z_index)
    : conindex(mobcloud::new_conindex()), z_index(z_index) {
  
  this->paindex = mobcloud::init_new_brush();
  Brush &brush = mobcloud::get_brush_at(this->paindex);
  brush.color = color;

  /// TODO: handle z_index initialization
}

void Mobject::init_conic_segments(u16 concount){

  this->concount = concount;

  vec3f zero(0, 0, 0);
  for(int i = 0; i < concount; ++i){
    mobcloud::push_conic(zero, zero, zero, 0);
  }
}


Mobject::~Mobject() {
  
}

} // namespace axm