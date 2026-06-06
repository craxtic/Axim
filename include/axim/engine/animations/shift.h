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

#include <axim/core/types/vector2.h>
#include <axim/engine/animations/animation.h>

namespace axm {

class AXIM_ENGINE_API Shift : public Animation {

public:

  /**
   * @brief Construct a new Shift object
   * 
   * @param target mobject to animate
   * @param delta delta position to move
   * @param run_time_s run time in second
   */
  Shift(
    Mobject &target, 
    vec3f delta, 
    float run_time_s = 1.f
  );


  /**
   * @brief interpolate the shifting animation
   * 
   * @param alpha 
   */
  constexpr void interpolate(float alpha) override;

  
private:
  vec3f delta;

};

} // namespace axm