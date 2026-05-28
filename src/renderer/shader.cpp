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

#include "axim-internal/renderer_cloud.h"
#include <axim/renderer/shader.h>

#include <fstream>
#include <bgfx/bgfx.h>

#include <axim-internal/shader_prog_def.h>

namespace axm {


#define REGISTER_SHADER_PROGRAM(name) 


static bgfx::ShaderHandle create_shader_handle_from(const std::filesystem::path &path);



Shader::Shader(){
  this->programs = r_storage::construct<ShaderPrograms>();
}


void Shader::load_builtin_shaders(){
  bgfx::ShaderHandle vsh;
  bgfx::ShaderHandle fsh;
  
  vsh = create_shader_handle_from(AXIM_SHADERS_DIR "/triangle.vert.bin");
  fsh = create_shader_handle_from(AXIM_SHADERS_DIR "/triangle.frag.bin");
  programs->triangle = bgfx::createProgram(vsh, fsh, true);
  
  vsh = create_shader_handle_from(AXIM_SHADERS_DIR "/curve.vert.bin");
  fsh = create_shader_handle_from(AXIM_SHADERS_DIR "/curve.frag.bin");
  programs->curve = bgfx::createProgram(vsh, fsh, true);
}

void Shader::destroy(){
  bgfx::destroy(programs->triangle);
  bgfx::destroy(programs->curve);
}



static bgfx::ShaderHandle create_shader_handle_from(const std::filesystem::path &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    std::perror(path.c_str());
    return BGFX_INVALID_HANDLE;
  }

  std::streamsize size = file.tellg();

  const bgfx::Memory *memory = bgfx::alloc(size);
  file.seekg(0, std::ios::beg);

  file.read(reinterpret_cast<char *>(memory->data), size);

  return bgfx::createShader(memory);
}




}