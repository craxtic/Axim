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

// #include "bindings/scene.hh"
#include <axim/config.h>
#include <axim/scene/scene.h>

using namespace axm;

extern axm::Scene* scene;

extern "C" {

  
AXIM_API_EXPORT void axm_scene_add(axm::Mobject* mobject){
  scene->add(*mobject);
}
  
AXIM_API_EXPORT void axm_scene_play(axm::Animation* animation){
  scene->play(*animation);
}

}
