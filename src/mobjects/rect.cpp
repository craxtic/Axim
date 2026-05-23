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

#include <axim/mobjects/rect.h>
#include <axim/mobjects/mobcloud.h>


namespace axm {

Rect::Rect(vec2f p1, vec2f p2, Color fill_color) : VMobject(fill_color) {
  this->set_pocount(16);

  this->push_cubic_points(
    {p1.x, p1.y, 0},
    {p1.x, p1.y, 0},
    {p2.x, p1.y, 0},
    {p2.x, p1.y, 0}
  );
  this->push_cubic_points(
    {p2.x, p1.y, 0},
    {p2.x, p1.y, 0},
    {p2.x, p2.y, 0},
    {p2.x, p2.y, 0}
  );
  this->push_cubic_points(
    {p2.x, p2.y, 0},
    {p2.x, p2.y, 0},
    {p1.x, p2.y, 0},
    {p1.x, p2.y, 0}
  );
  // this->push_cubic_points(
  //   {p1.x, p2.y, 0},
  //   {p1.x, p2.y, 0},
  //   {p1.x, p1.y, 0},
  //   {p1.x, p1.y, 0}
  // );
  this->push_cubic_points(
    {p1.x, p2.y, 0},
    {p1.x, p2.y, 0},
    {p1.x, p1.y, 0},
    {p1.x, p1.y, 0}
  );

  return;
}

[[nodiscard]] Mobject *Rect::copy(bool should_clone) const {
    Rect *_Rect = new Rect();

    if(!should_clone){
      _Rect->poindex = this->get_poindex();
      _Rect->pocount = this->get_pocount();
      _Rect->paindex = this->get_paindex();
      return _Rect;
    }

    _Rect->pocount = this->get_pocount();
    _Rect->poindex = mobcloud::new_poindex();
    _Rect->paindex = mobcloud::push_paint(this->get_paint());

    for(int i = 0; i < _Rect->get_pocount(); i++)
      _Rect->push_point((*this)[i]);

    return _Rect;
  }

} // namespace axm