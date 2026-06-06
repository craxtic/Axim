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


#include "axim/renderer/canvas.h"
#include "axim/renderer/renderer.h"
#include "axim/renderer/shader.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_platform.h>
#include <SDL3/SDL_properties.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <cassert>

// #include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>

#include <axim/presenter/window.h>
#include <axim/core/types/color.h>
#include <axim/utils/errors.h>
#include <iostream>


#include <axim-internal/p_storage.h>


// #include <iostream>

namespace axm {

  
PreviewPresenter::PreviewPresenter(u32 width, u32 height, Color bg_color){

  SDL_Init(SDL_INIT_VIDEO);

  SDL_PropertiesID props = SDL_CreateProperties();
  SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Axim");
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);

  
  this->window = SDL_CreateWindowWithProperties(props);
  assert(this->window);
  SDL_DestroyProperties(props);

  props = SDL_GetWindowProperties(window);
  void *ndt, *nwh;

  #if defined (SDL_PLATFORM_LINUX)

    const char* driver = SDL_GetCurrentVideoDriver();
    if(SDL_strcmp(driver, "x11") == 0){
      ndt = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, NULL);
      nwh = (void*)(uintptr_t)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
    }else
    if(SDL_strcmp(driver, "wayland") == 0){
      ndt = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, NULL);
      nwh = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, NULL);
    }
  
  #elif defined (SDL_PLATFORM_WINDOWS)
    nwh = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
    ndt = nullptr;
  #elif defined(SDL_PLATFORM_APPLE)
    nwh = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, NULL);
    ndt = nullptr;
  #endif

  // SDL_PumpEvents();
  SDL_SyncWindow(window);

  int w, h;
  SDL_GetWindowSizeInPixels(window, &w, &h);
  std::cout << width << "*" << height << std::endl;
  std::cout << w << "x" << h << std::endl;
  this->renderer = p_storage::construct<Renderer>(w, h, nwh, ndt);
  this->canvas = p_storage::construct<Canvas>(w, h, bg_color);

  return;
}

void PreviewPresenter::clear() {
  this->canvas->clear();
  this->renderer->clear(canvas->bg_color);
};


void PreviewPresenter::present() const {
  this->renderer->submit(canvas->get_vertices(), canvas->get_indices(), ShaderType::Curve);
  this->renderer->submit(canvas->get_interior_vert(), canvas->get_interior_indi(), ShaderType::Triangle);
  this->renderer->present();
}
  
PreviewPresenter::~PreviewPresenter(){
  renderer->destroy();
  SDL_DestroyWindow(window);
}
 
Canvas* PreviewPresenter::get_canvas(){
  return this->canvas;
}

/// TODO: handle the event with a proper window id
void PreviewPresenter::idle(int duration, bool *running) const {

  
  while(true){

    SDL_Event event;
    SDL_WaitEvent(&event);
    
    switch (event.type) {
      
      case SDL_EVENT_QUIT: if(running) *running = false; return;
      break;
      case SDL_EVENT_KEY_DOWN:
        if(event.key.key == SDLK_R) return;
      break;
      case SDL_EVENT_WINDOW_RESIZED:
        std::cout << "get resized" << std::endl;
        int w, h;
        SDL_GetWindowSizeInPixels(this->window, &w, &h);
        canvas->reset_size(w, h);
        renderer->reset(w, h);
        // renderer->clear(canvas->bg_color);
        this->present();
      break;
    }
  
  }
      

  return;
}

}
  
