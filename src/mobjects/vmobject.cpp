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


#include <include/core/SkPath.h>
#include <include/core/SkPathBuilder.h>

#include <axim/core/types/color.h>
#include <axim/core/types/vector3.h>
#include <axim/mobjects/vmobject.h>
#include <include/private/base/SkPoint_impl.h>
#include <iostream>

namespace axm {

VMobject::VMobject(Color fill_color) : Mobject(fill_color) {}

[[nodiscard]] SkPath VMobject::get_path() const {

  static SkPathBuilder builder;
  // builder.reset();

  if (this->get_pocount() == 0)
    return builder.detach();

  builder.moveTo({(*this)[0].x, (*this)[0].y});
  SkPoint a{(*this)[1].x, (*this)[1].y};
  SkPoint b{(*this)[2].x, (*this)[2].y};
  SkPoint c{(*this)[3].x, (*this)[3].y};

  // builder.cubicTo(a, b, c);

  // for (int i = 4; i < this->get_pocount(); i += 4) {
  //   vec2f p1 = (*this)[i]; 
  //   vec2f p2 = (*this)[i+1];
  //   vec2f p3 = (*this)[i+2];
  //   vec2f p4 = (*this)[i+3];
  //   builder.lineTo(p1);
  //   builder.cubicTo(p2, p3, p4);
  // }
  builder.addCircle(c, 100);

  builder.close();

  return builder.detach();
};

} // namespace axm