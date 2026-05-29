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

#include <axim/engine/animations/animation.h>
#include <axim/config.h>
#include <axim/core/types/color.h>
#include <axim/core/types/vector2.h>
#include <axim/engine/mobjects/mobject.h>
#include <axim/presenter/presenter.h>

#include <axim/renderer/canvas.h>


#include <vector>

namespace axm {

// enum class RenderMode { Preview, Export };

class AXIM_ENGINE_API Scene final {

  PresenterInterface *presenter;
  Canvas *canvas;

  std::vector<Mobject *> mobjects; /// z_index of 0
  std::vector<Mobject *> rvalue_mobjects;
  
  u8 frame_rate;


public:
  Scene(u8 frame_rate, PresenterInterface *presenter);

  ~Scene();

  /// set the framerate (fps) of the scene
  inline void set_framerate(u8 frame_rate) { this->frame_rate = frame_rate; }

  /// set the background color of the scene
  inline void set_canvas(Canvas* canvas) { this->canvas = canvas; }

  /// add an mobject to the mobject rendering list
  inline void push(Mobject *mobject) { mobjects.emplace_back(mobject); }

  void remove(const Mobject &mobject);

  /// clear all mobjects from the scene
  inline void clear(){
    this->mobjects.clear();
    this->render_frame();
  }


  /// set the render mode to preview or export
  void set_presenter(PresenterInterface *presenter);

  /// render the current frame using the mobject list
  void render_frame() const;

  /// add an mobject to the scene and render
  void add(Mobject &mobject);
  void add(const Mobject &&mobject);

  /// play an animation
  void play(Animation &animatoin);

  void idle(float duration, bool *running = nullptr) const;
};

} // namespace axm