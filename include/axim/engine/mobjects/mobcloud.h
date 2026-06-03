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

#include <vector>

#include <axim/config.h>
#include <axim/core/conicsegment.h>
#include <axim/core/types/vector3.h>
#include <axim/core/types/ctype.h>
#include <axim/renderer/paint.h>

namespace axm::mobcloud {

class MobjectCloud {

public:
  std::vector<ConicSegment> conics;
  std::vector<Brush> brushes;
  std::vector<Pen> pens;

  MobjectCloud() = default;

  MobjectCloud(size_t init_mobcount, size_t std_pocount);


};


extern MobjectCloud *const mobject_cloud;

inline u32 new_conindex(){
  return mobject_cloud->conics.size();
}

inline u16 init_new_brush(){
  mobject_cloud->brushes.emplace_back();
  return mobject_cloud->brushes.size() - 1;
} 

inline Brush &get_brush_at(u16 paindex){
  return mobject_cloud->brushes[paindex];
}

inline ConicSegment &get_conic_at(u32 conindex){
  return mobject_cloud->conics[conindex];
}

inline void push_conic(const vec3f &p0, const vec3f& p1, const vec3f& p2, float w1) {
  mobject_cloud->conics.emplace_back(p0, p1, p2, w1);
} 


inline u16 push_paint(const Brush &fill) {
  mobject_cloud->brushes.emplace_back(fill);
  return mobject_cloud->brushes.size() - 1;
}

} // namespace axm