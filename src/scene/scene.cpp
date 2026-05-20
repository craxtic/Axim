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

#include <axim/presenters/presenter.h>
#include <axim/utils/utils.h>
#include <axim/mobjects/mobject.h>
#include <axim/mobjects/vmobject.h>
#include <axim/scene/scene.h>
#include <axim/utils/errors.h>


#include <chrono>

namespace axm {

Scene::Scene(u8 frame_rate, const Color &bg_color, PresenterInterface* presenter)
    : presenter(presenter), frame_rate(frame_rate), bg_color(bg_color){

  
  this->mobjects.reserve(MOBJECT_COUNT_PER_SCENE_PROBABLY);
  
  if(presenter == nullptr) return;
  presenter->make_current();
  this->canvas = presenter->get_canvas();

}

void Scene::render_frame() const {
  this->canvas->clear(this->bg_color);
  
  for (const Mobject *mobject : this->mobjects) {
    this->canvas->drawPath(mobject->get_path(), mobject->get_paint());
  }
  
  this->presenter->present();
  return;
}

void Scene::set_presenter(PresenterInterface *presenter) {
  if (presenter == nullptr) 
    return;

  presenter->make_current();
  this->canvas = presenter->get_canvas();
  this->presenter = presenter;
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