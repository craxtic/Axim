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

#include <axim/core/conicsegment.h>
#include <axim/core/conicsegment.h>
#include <axim/presenter/window.h>
#include <axim/renderer/canvas.h>
#include <axim/presenter/presenter.h>
#include <axim/utils/utils.h>
#include <axim/engine/mobjects/mobject.h>
#include <axim/engine/mobjects/vmobject.h>
#include <axim/engine/scene/scene.h>
#include <axim/utils/errors.h>


#include <chrono>
#include <iostream>
#include <span>

namespace axm {

Scene::Scene(u8 frame_rate, PresenterInterface* presenter)
    : presenter(presenter), frame_rate(frame_rate){

  
  this->mobjects.reserve(MOBJECT_COUNT_PER_SCENE_PROBABLY);
  
  if(presenter == nullptr) 
    this->presenter = new PreviewPresenter(1000, 800, Color::Black);
  this->canvas = this->presenter->get_canvas();
  this->presenter->clear();
  this->presenter->present();
}

void Scene::render_frame() const {
  this->presenter->clear();
  
  for (const Mobject* mobject : this->mobjects) {
    canvas->draw(std::span<ConicSegment>(&(*mobject)[0], mobject->get_concount()), mobject->get_brush());
  }

  this->presenter->present();
  return;
}

void Scene::set_presenter(PresenterInterface *presenter) {
  if (presenter == nullptr) 
    return;

  this->presenter = presenter;
  this->canvas = presenter->get_canvas();
  return;
}

void Scene::add(Mobject &mobject) {
  this->push(&mobject);
  this->render_frame();
  return;
}

void Scene::add(const Mobject &&mobject) {
  Mobject *mob = mobject.copy(false);
  this->rvalue_mobjects.emplace_back(mob);
  this->push(mob);
  this->render_frame();
}

void Scene::play(Animation &animation) {

  this->push(&animation.get_mobject());
  
  float run_time = animation.get_run_time();
  float elapsed_time = 0.0f;
  auto start_time = std::chrono::steady_clock::now();


  while (elapsed_time < run_time) {
    auto current_time = std::chrono::steady_clock::now();
    
    std::chrono::duration<float> duration = current_time - start_time;
    elapsed_time = duration.count();

    float alpha = elapsed_time / run_time;
    if (alpha > 1.0f) alpha = 1.0f;

    animation.interpolate(alpha);

    this->render_frame();
  }

}


void Scene::idle(float duration, bool *running) const {
  this->presenter->idle(duration, running);
  return;
};

Scene::~Scene() {

  for (Mobject *mob : this->rvalue_mobjects)
    delete mob;
  this->rvalue_mobjects.clear();

}

} // namespace axm