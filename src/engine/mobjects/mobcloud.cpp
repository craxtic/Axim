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

#include <axim/engine/mobjects/mobcloud.h>
#include <axim/core/types/color.h>

namespace axm::mobcloud {

MobjectCloud::MobjectCloud(size_t init_mobcount, size_t std_pocount) {

  this->points.reserve(init_mobcount * std_pocount);
  this->brushes.reserve(init_mobcount);

}

} // namespace axm