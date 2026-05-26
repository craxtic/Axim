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

#include "axim/core/types/vector2.h"
#include <lua.hpp>

#include <axim/engine/scene/scene.h>


extern axm::Scene* scene;

enum class Mode {
  Preview, 
  Export,
};

struct Settings {
  Mode active_mode;
  axm::vec2i unitsize;
  axm::vec2i framesize;
  axm::Color background_color;
  struct {
    int framerate;
    axm::vec2i dimensions;  
    bool reload_on_save;
  } preview;
  struct {
    int framerate;
    axm::vec2i resolution;
  } output;
};



int run_app(const char* script_filepath, Settings &setting);

void init_luajit_ffi_module(lua_State* lstate);

