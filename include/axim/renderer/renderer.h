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
#include "axim/renderer/shader.h"
#include <axim/core/types/color.h>
#include <axim/config.h>
#include <axim/core/types/ctype.h>
#include <axim/core/types/vector3.h>
#include <axim/renderer/vertex.h>


#include <cstdint>
#include <vector>
#include <array>
#include <filesystem>



namespace axm {




class AXIM_RENDERER_API Renderer {

  Shader *shader;

public:

  Renderer(u32 backbuffer_width, u32 backbuffer_height, void* nwh, void* ndt);
    
  
  void clear(Color color);
  void reset(u32 backbuffer_width, u32 backbuffer_height);
  void submit(const std::vector<Vertex>& vertices, const std::vector<u16>& indices);
  void present();


};

}
