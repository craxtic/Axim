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
#include <axim/config.h>
#include <axim/scene/scene.h>

#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>

namespace fs = std::filesystem;

#ifndef AXIM_LUA_DIR

  #if defined(_WIN32)
    #define AXIM_LUA_DIR "C:/ProgramData/axim/lua" 
  #else
    #define AXIM_LUA_DIR "/usr/share/axim/lua"
  #endif

#endif



static fs::path resolve_lua_dir();



void init_luajit_ffi_module(lua_State *lstate){

  fs::path lua_dir = resolve_lua_dir();
  lua_dir /= "?.lua";


  std::string load_script = std::format(R"(
    package.path = "{};" .. package.path
    require("axim.init")
  )",lua_dir.generic_string());

  if(luaL_dostring(lstate, load_script.c_str())){
    std::cerr << "error: " << lua_tostring(lstate, -1) << std::endl;
  }

}

static fs::path resolve_lua_dir(){
  
  const char* env_path = std::getenv("AXIM_LUA_DIR");
  if(env_path != NULL){
    return fs::path(env_path);
  }
  return fs::path(AXIM_LUA_DIR);
}
