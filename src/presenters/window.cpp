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


#include <SDL3/SDL_video.h>
#include <include/core/SkColor.h>
#include <include/core/SkColorSpace.h>
#include <include/core/SkSurface.h>
#include <include/core/SkCanvas.h>

#include <include/gpu/ganesh/GrDirectContext.h>
#include <include/gpu/ganesh/GrBackendSurface.h>
#include <include/gpu/ganesh/SkSurfaceGanesh.h>
#include <include/gpu/ganesh/gl/GrGLDirectContext.h>
#include <include/gpu/ganesh/gl/GrGLBackendSurface.h>
#include <include/gpu/ganesh/GrDirectContext.h>
#include <include/gpu/ganesh/gl/GrGLDirectContext.h>
#include <include/gpu/ganesh/gl/GrGLInterface.h>

// #include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>
#include <GL/gl.h>

#include <axim/presenters/window.h>
#include <axim/core/types/color.h>
#include <axim/utils/errors.h>
#include <iostream>



// #include <iostream>

namespace axm {

  
PreviewPresenter::PreviewPresenter(){

  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


  window = SDL_CreateWindow(
    "axim Preview", 
    800, 600,
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
  );
  check_null_unlikely(window, "CreateWindow");

  this->gl_context = SDL_GL_CreateContext(this->window);
  this->make_current();

  sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
  this->context = GrDirectContexts::MakeGL(interface);
  check_null_unlikely(context, "Context::MakeGL");


  return;
}

void PreviewPresenter::make_current() {
  SDL_GL_MakeCurrent(this->window, this->gl_context);  
};



SkCanvas *PreviewPresenter::get_canvas(){
  std::cout << "canvas" << std::endl;
  SDL_GL_SwapWindow(window);
  SDL_PumpEvents();
  int width, height;
  SDL_GetWindowSizeInPixels(window, &width, &height);
  
  this->surface = _create_sk_surface(width, height);
  check_null_unlikely(surface, "_create_sk_surface");
  return this->surface->getCanvas();
}

void PreviewPresenter::present() const {
  this->context->flush(this->surface.get());
  this->context->submit();
  SDL_GL_SwapWindow(window);
}
  
PreviewPresenter::~PreviewPresenter() {
  if (surface) surface->unref();
  context->unref();
  SDL_GL_DestroyContext(gl_context);
  SDL_DestroyWindow(window);
}
  
sk_sp<SkSurface>  PreviewPresenter::_create_sk_surface(int w, int h){

  GrGLFramebufferInfo gl_info;
  gl_info.fFBOID = 0;
  gl_info.fFormat = GL_RGBA8;
  GrBackendRenderTarget backend_rt = GrBackendRenderTargets::MakeGL(w, h, 1, 8, gl_info);


  // SkColorSpace color_space;
  SkSurfaceProps props(0, kUnknown_SkPixelGeometry);
  sk_sp<SkSurface> surface = SkSurfaces::WrapBackendRenderTarget(
    context.get(),
    backend_rt,
    kBottomLeft_GrSurfaceOrigin,
    kRGBA_8888_SkColorType,
    nullptr,
    &props
  );
  return surface;
}


/// TODO: handle the event with a proper window id
void PreviewPresenter::idle(int duration, bool *running) const {

  
  while(true){

    SDL_Event event;
    SDL_WaitEvent(&event);
    
    switch (event.type) {
      
      case SDL_EVENT_QUIT: if(running) *running = false; return;
      case SDL_EVENT_KEY_DOWN:
        if(event.key.key == SDLK_R) return;
      break;
    }
  
  }
      

  return;
}

}
  
