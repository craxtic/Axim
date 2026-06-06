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

#include <axim/engine/mobjects/mobject.h>

namespace axm {

class Animation {

public:

  /**
   * @brief Construct a new Animation object
   * 
   * @param target target mobject to animate
   * @param run_time_s the time of animation in second
   */
  Animation(
    Mobject &target, 
    float run_time_s
  ): 
    mobject(target), 
    run_time(run_time_s), 
    begin_state(*(target.copy(true))) 
  {}

  /**
   * @brief interpolate the all points of the mobjects
   * 
   * @param alpha 
   */
  virtual constexpr void interpolate(float alpha) = 0;



  /**
   * @brief Get the run time object
   * 
   * @return float 
   */
  [[nodiscard]] inline float get_run_time(){
    return run_time;
  }


  /**
   * @brief Get the mobject object
   * 
   * @return Mobject& 
   */
  [[nodiscard]] inline Mobject &get_mobject(){
    return mobject;
  }

  
protected:
  Mobject &mobject;
  float run_time;
  const Mobject &begin_state;

};

} // namespace axm