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
#include <axim/core/types/vector3.h>
#include <axim/core/types/ctype.h>
#include <axim/renderer/path.h>

namespace axm::mobcloud {

class MobjectCloud {

public:
  std::vector<vec3f> points;
  std::vector<Brush> brushes;
  std::vector<Pen> pens;

  MobjectCloud() = default;

  MobjectCloud(size_t init_mobcount, size_t std_pocount);

  

  
 
};


extern MobjectCloud *const mobject_cloud;

inline u32 new_poindex(){
  return mobject_cloud->points.size();
}

inline u16 init_new_brush(){
  mobject_cloud->brushes.emplace_back();
  return mobject_cloud->brushes.size() - 1;
} 

inline Brush &get_brush_at(u16 paindex){
  return mobject_cloud->brushes[paindex];
}

inline vec3f &get_point_at(u32 poindex){
  return mobject_cloud->points[poindex];
}

inline void push_point(const vec3f &point) {
  mobject_cloud->points.emplace_back(point.x, point.y, point.z);
} 


inline u16 push_paint(const Brush &fill) {
  mobject_cloud->brushes.emplace_back(fill);
  return mobject_cloud->brushes.size() - 1;
}

} // namespace axm