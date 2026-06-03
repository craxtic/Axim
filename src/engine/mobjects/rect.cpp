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

#include "axim/renderer/path.h"
#include <axim/core/conicsegment.h>
#include <axim/engine/mobjects/rect.h>
#include <axim/engine/mobjects/mobcloud.h>
#include <iostream>


namespace axm {

Rect::Rect(vec3f p1, vec3f p2, Color fill_color) : VMobject(fill_color) {
  
  this->init_conic_segments(4);  
  ConicPathBuilder path(get_conic_segments());

  for(auto seg : path.get_segments()){
    std::cout << seg.p0 << std::endl;
    std::cout << seg.p1 << std::endl;
    std::cout << seg.p2 << std::endl;
  }

  std::cout << "---\n";
  
  path.move_to(p1);
  path.line_to({p2.x, p1.y, 0});
  path.line_to({p2.x, p2.y, 0});
  path.line_to({p1.x, p2.y, 0});
  // path.line_to({p1.x, p1.y, 0});
  path.close();

  for(auto seg : path.get_segments()){
    std::cout << seg.p0 << std::endl;
    std::cout << seg.p1 << std::endl;
    std::cout << seg.p2 << std::endl;
  }

  return;
}

[[nodiscard]] Mobject *Rect::copy(bool should_clone) const {
    Rect *_Rect = new Rect();

    if(!should_clone){
      _Rect->conindex = this->get_conindex();
      _Rect->concount = this->get_concount();
      _Rect->paindex = this->get_paindex();
      return _Rect;
    }

    _Rect->concount = this->get_concount();
    _Rect->conindex = mobcloud::new_conindex();
    _Rect->paindex = mobcloud::push_paint(this->get_brush());

    for(int i = 0; i < _Rect->get_concount(); i++) {
      const ConicSegment& conic = (*this)[i];
      mobcloud::push_conic(conic.p0, conic.p1, conic.p2, conic.w1);
    }  
    return _Rect;
  }

} // namespace axm