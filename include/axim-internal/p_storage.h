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

#include <axim/core/cloud.h>

namespace axm::p_storage {


inline static Cloud p_cloud{1024};

template<typename T, typename...Args>
inline T* construct(Args&&...args){
  return p_cloud.construct<T>(std::forward<Args>(args)...);
}

}