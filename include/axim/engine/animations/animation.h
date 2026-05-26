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

protected:
  Mobject &mobject;
  float run_time;
  const Mobject &begin_state;
public:
  Animation(Mobject &target, float run_time)
      : mobject(target), run_time(run_time), begin_state(*(target.copy(true))) {}

  virtual constexpr void interpolate(float alpha) = 0;

  [[nodiscard]] inline float get_run_time(){
    return run_time;
  }

  [[nodiscard]] inline Mobject &get_mobject(){
    return mobject;
  }

};

} // namespace axm