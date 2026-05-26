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

#include <axim/config.h>
#include <axim/engine/mobjects/mobcloud.h>


namespace axm::mobcloud {

/// these objects are created to last the entire life time of the program
/// no free is required, the memory leak is harmless
/// a clean up function may be implemented later

MobjectCloud *const mobject_cloud =
    new MobjectCloud(MOBJECT_COUNT_PER_SCENE_PROBABLY, 10);
// PreviewPresenter *const preview_presenter = new PreviewPresenter();

static class _init {

public:
  _init() {  }

} init;

} // namespace axm