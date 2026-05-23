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

#include <axim/mobjects/mobcloud.h>
#include <axim/mobjects/mobject.h>
#include <include/core/SkPaint.h>

namespace axm {

Mobject::Mobject(Color color, float z_index)
    : poindex(mobcloud::new_poindex()), z_index(z_index) {
  
  this->paindex = mobcloud::init_new_paint();
  SkPaint &paint = mobcloud::get_paint_at(this->paindex);
  paint.setColor(color);
  paint.setAntiAlias(true);
  // paint.setStroke(true);

  /// TODO: handle z_index initialization
}

Mobject::~Mobject() {
  
}

} // namespace axm