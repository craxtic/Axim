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

#include "axim/config.h"
#include <axim/renderer/canvas.h>
#include <axim/core/types/color.h>

namespace axm {

class AXIM_PRESENTER_API PresenterInterface {

public:
  virtual ~PresenterInterface() = default;

  virtual void clear(Color color) = 0;

  /// display the drawn buffer to the output
  virtual void present(const Canvas& canvas) const = 0;

  /// pause
  /// TODO: introduce a new param to accept the idling duration
  virtual void idle(int duration, bool *running) const = 0;
};

} // namespace axm
