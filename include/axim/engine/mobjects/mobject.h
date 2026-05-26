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
#include <axim/core/types/color.h>
#include <axim/core/types/vector3.h>
#include <axim/engine/mobjects/mobcloud.h>
#include <axim/renderer/path.h>

namespace axm {

/// Mathematical Object Class
class AXIM_ENGINE_API Mobject {


public:
  float z_index;

  Mobject() = default;

  Mobject(Color color, float z_index = 0);

  virtual ~Mobject();

  /// fetch the path of the mobject, (this can be raster version)
  [[nodiscard]] virtual BezierPath get_path() const = 0;

  /// copy the id and move to a new object
  /// reacllocate and clone the raw data if should_clone is true.
  [[nodiscard]] virtual constexpr Mobject *copy(bool should_clone) const = 0;

  /// return the point at a givel local index
  [[nodiscard]] inline vec3f &operator[](u32 index) const {
    return mobcloud::get_point_at(poindex + index);
  }

  /// return the reference to the corresponding fillstyle object of this mobject
  [[nodiscard]] inline const Brush &get_brush() const {
    return mobcloud::get_brush_at(paindex);
  }

  /// return the global starting index to the points of this mobject
  [[nodiscard]] inline constexpr u32 get_poindex() const {
    return poindex;
  }

  /// return the point count of this mobject
  [[nodiscard]] inline constexpr u16 get_pocount() const {
    return pocount;
  }

  /// return the global index to the corresponding paint object
  [[nodiscard]] inline constexpr u16 get_paindex() const {
    return paindex;
  }

protected:
  u32 poindex;
  u16 pocount;
  u16 paindex;

  /// push a new point to the cloud
  /// this should be called in constructor of any Mobject
  inline void push_point(const vec3f &point) { mobcloud::push_point(point); }

  inline void push_cubic_points(const vec3f &p1, const vec3f &p2, const vec3f &p3, const vec3f &p4){
    push_point(p1);
    push_point(p2);
    push_point(p3);
    push_point(p4);
  }

  /// set the point count of this mobject
  inline constexpr void set_pocount(u16 pocount) {
    this->pocount = pocount;
  }
};



} // namespace axm
