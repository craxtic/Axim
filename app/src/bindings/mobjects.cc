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

#include <axim/engine/mobjects/rect.h>

#include "axim/core/types/vector3.h"
#include "binding.hh"
// #include "bindings/mobjects.hh"

using namespace axm;

extern "C" {

AXIM_API_EXPORT Mobject* axm_Rect(vec2f a, vec2f b){  
  vec3f m = {a.x, a.y, 0};
  vec3f n = {b.x, b.y, 0};
  return storage::construct<axm::Rect>(m, n);
}

}
