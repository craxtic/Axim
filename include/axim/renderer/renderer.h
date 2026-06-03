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

#include <axim/config.h>
#include <axim/renderer/shader.h>
#include <axim/core/types/ctype.h>
#include <axim/renderer/vertex.h>


#include <cstdint>
#include <vector>
#include <array>
#include <filesystem>



namespace axm {



class AXIM_RENDERER_API Renderer {


public:

  /**
   * @brief Construct a new Renderer object
   * 
   * @param[in] backbuffer_width 
   * @param[in] backbuffer_height 
   * @param[in] nwh Native Window Handler
   * @param[in] ndt Native Display Type
   *
   * @note Shader profile for each platform:
   * - linux : Vulkan
   * - windows : Direct3D 11
   * - macos : Metal
   */
  Renderer(
    u32 backbuffer_width, 
    u32 backbuffer_height, 
    void* nwh, 
    void* ndt
  );
    

  /**
   * @brief reset the view clear with a color
   * 
   * @param[in] color 
   */
  void 
  clear(
    Color color
  );


  /**
   * @brief swap the double frame buffers
   *
   * simply call bgfx::frame();
   */
  void 
  present();
  

  /**
   * @brief reset the rendering resolution
   *   
   * @note It recaculate the orthographic projection matrix implicitly .
   *
   * @param[in] backbuffer_width 
   * @param[in] backbuffer_height 
   */
  void 
  reset(
    u32 backbuffer_width, 
    u32 backbuffer_height
  );
  

  /**
   * @brief submit a vertex and an index buffer 
   * 
   * @param[in] vertices 
   * @param[in] indices 
   * @param[in] sh_type Shader program type used to render
   * 
   * @sa ShaderType 
   */
  void 
  submit(
    const std::vector<Vertex>& vertices, 
    const std::vector<u16>& indices, 
    const ShaderType::Enum sh_type
  );

private:
  Shader *shader;

};

}
