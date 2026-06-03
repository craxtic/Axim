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

#include <axim/config.h>
#include <axim/core/conicsegment.h>
#include <axim/core/types/vector3.h>
#include <axim/renderer/renderer.h>
#include <span>

namespace axm {
  


class AXIM_RENDERER_API ConicPathBuilder {

public:


  /**
   * @brief Construct a new Conic Path Builder object
   * 
   * @param[in] segments 
   */
  ConicPathBuilder(
    std::span<ConicSegment> segments
  ):
    segments(segments), 
    cidx(-1)
  {}


  /**
   * @brief 
   * 
   * @param[in] start_pos 
   */
  void 
  move_to(
    const vec3f& start_pos
  );


  /**
   * @brief constructs a new conic segment of the path 
   * 
   * @note The last point of the path is used as p0
   * @param[in] p1 The control point
   * @param[in] p2 The end point
   * @param[in] w1 The weight of p1
   */
  void 
  conic_to(
    const vec3f& p1, 
    const vec3f& p2, 
    float w1
  );
  

  /**
   * @brief constructs a new straight line
   * 
   * @param[in] dest_pos
   */
  void 
  line_to(
    const vec3f& dest_pos
  );


  /**
   * @brief connect the last point to the start point with a straight line
   * 
   */
  void 
  close();


  /**
   * @brief reset all points of all segments to zero
   * 
   */
  void 
  reset();


  /**
   * @brief Get the segments object
   * 
   * @return std::span<ConicSegment> 
   */
  inline std::span<ConicSegment> 
  get_segments(){
    return this->segments;
  }

private:
  std::span<ConicSegment> segments;
  vec3f cpos; /// current position
  i32 cidx; /// current index;

  inline void advance_idx(){
    ++cidx;
  }

  inline vec3f get_last_pos(){
    return cpos;
  }

  inline bool advanceable(){
    return cidx <= int(segments.size() - 1);
  }

  inline void finish(){
    cpos = segments[cidx].p2;
  }

};

}