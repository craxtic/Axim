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
#include <axim/core/cloud.h>
#include <axim/mobjects/mobject.h>


namespace storage {

inline axm::Cloud cloud{8192};


template<typename T, typename...Args>
inline T* construct(Args&&...args){
  return cloud.construct<T>(std::forward<Args>(args)...);
}

};
  

