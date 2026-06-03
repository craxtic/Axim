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

#include "axim/core/types/vector3.h"
#include <axim/renderer/path.h>


namespace axm {



void ConicPathBuilder::move_to(const vec3f& dest_pos){
  this->cpos = dest_pos;
}

void ConicPathBuilder::line_to(const vec3f& dest_pos){
  if(!advanceable()) return;

  advance_idx();
  vec3f start_pos = get_last_pos();
  this->segments[cidx].p0 = start_pos;
  this->segments[cidx].p1 = 0.5f * (start_pos + dest_pos);
  this->segments[cidx].p2 = dest_pos;
  this->segments[cidx].w1 = 0.0f;

  finish();
}




void ConicPathBuilder::close(){

  vec3f path_starting_pos = this->segments[0].p0;
  this->line_to(path_starting_pos);

  return;
}

void ConicPathBuilder::reset(){
  for (auto segement : segments) {
    segement.p0.to_zero();
    segement.p1.to_zero();
    segement.p2.to_zero();
    segement.w1 = 0;
  }
}


}
