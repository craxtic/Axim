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
#include <axim/engine/mobjects/vmobject.h>

namespace axm {

class AXIM_ENGINE_API Rect : public VMobject {

public:
  Rect() = default;

  Rect(vec2f p1, vec2f p2, Color fill_color = Color::White);

  /// TODO: implement a full version of copy
  [[nodiscard]] Mobject *copy(bool should_clone) const override;
};

} // namespace axm