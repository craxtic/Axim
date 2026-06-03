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

// #include "bindings/animations.hh"
#include <axim/engine/animations/shift.h>
#include "axim/core/types/vector3.h"
#include "binding.hh"

using namespace axm;

extern "C" {

AXIM_API_EXPORT Animation* axm_Shift(Mobject *target, vec2f delta, float run_time){
  return storage::construct<Shift>(*target, vec3f(delta.x, delta.y, 0), run_time);
}

}
