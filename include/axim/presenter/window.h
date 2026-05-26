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

#include "axim/core/types/color.h"
#include <axim/presenter/presenter.h>

#include <SDL3/SDL_video.h>


namespace axm {

  
class AXIM_PRESENTER_API PreviewPresenter : public PresenterInterface {
  SDL_Window *window;
  Renderer *renderer;

public:
  PreviewPresenter(u32 width, u32 height);

  void present(const Canvas& canvas) const override;

  void clear(Color color) override;
  

  /// keep window alive and wait for window close event
  void idle(int duration, bool *running) const override;

  ~PreviewPresenter();
   
};


}