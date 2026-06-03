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
#include <filesystem>

#ifndef AXIM_SHADERS_DIR
#define AXIM_SHADERS_DIR ""
#endif


namespace axm {

struct ShaderPrograms;

struct ShaderType {
  enum Enum{
    Triangle,
    Curve,
  };
};


class AXIM_RENDERER_API Shader {

public:

  /**
   * @brief Construct a new Shader object
   * 
   */
  Shader();

  /**
   * @brief Load all builtin shader programs
   * 
   */
  void 
  load_builtin_shaders();
  
  /**
   * @brief Destroy all shader programs
   * 
   */
  void destroy();


  /**
   * @brief Get the programs object
   * 
   * @return ShaderPrograms* 
   *
   * @note ShaderPrograms is a struct of bgfx::ProgramHandler
   */
  ShaderPrograms* 
  get_programs(){
    return programs;
  }

private:
  ShaderPrograms *programs; 
};

} // namespace axm