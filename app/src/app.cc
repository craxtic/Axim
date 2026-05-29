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

#include "app.hh"
#include "axim/utils/utils.h"



#include <axim/axim.h>
#include <axim/presenter/presenter.h>
#include <axim/presenter/window.h>
#include <axim/presenter/export.h>
#include <axim/core/cloud.h>

#include <iostream>


axm::Scene* scene = nullptr;

static axm::PresenterInterface *get_presenter(Settings &setting){
  
  
  switch (setting.active_mode) {
    case Mode::Preview:
      return new axm::PreviewPresenter(setting.preview.dimensions.x, setting.preview.dimensions.y, setting.background_color);
    case Mode::Export:
      return new axm::ExportPresenter(setting.output.resolution, "output.mp4");
  }

}


int run_app(const char* script_filepath, Settings &setting){

  axm::PresenterInterface *presenter = get_presenter(setting);

  scene = new axm::Scene(60, presenter);

  lua_State *lstate = luaL_newstate();
  luaL_openlibs(lstate);

  init_luajit_ffi_module(lstate);

  bool previewing = true;
  while(previewing){
    
    std::cout << "reload" << std::endl;
    
    axm::Stopwatch stopwatch;
    if(luaL_dofile(lstate, script_filepath)){
      std::cerr << "Error: " << lua_tostring(lstate, -1) << std::endl;
    }
    stopwatch.lap();
    
    scene->idle(-1, &previewing);
    
    scene->clear();
  }
  
  lua_close(lstate);

  return 0;
}