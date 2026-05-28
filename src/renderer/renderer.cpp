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

#include "axim/renderer/shader.h"
#include <axim/renderer/renderer.h>
#include <axim/renderer/vertex.h>
#include <bgfx/bgfx.h>
#include <bgfx/defines.h>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

#include <axim-internal/renderer_cloud.h>
#include <axim-internal/shader_prog_def.h>
#include <axim-internal/bgfx_callback.h>


static const bgfx::VertexLayout vertex_layout =
    bgfx::VertexLayout()
        .begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
        // .add(bgfx::Attrib::TexCoord0, 1, bgfx::AttribType::Float);
        // .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);



#define BGFX_RESET_OPTIONS (BGFX_RESET_VSYNC)

namespace axm {

Renderer::Renderer(u32 backbuffer_width, u32 backbuffer_height, void *nwh, void *ndt) {

  bgfx::Init init;

  #if defined (__linux)
    init.type = bgfx::RendererType::Vulkan;
  #elif defined (_WIN32)
    init.type = bgfx::RendererType::Direct3D11;
  #elif defined (__APPLE__)
    init.type = bgfx::RendererType::Metal;
  #endif
  
  init.platformData.ndt = ndt;
  init.platformData.nwh = nwh;

  init.resolution.width = backbuffer_width;
  init.resolution.height = backbuffer_height;
  init.resolution.reset = BGFX_RESET_OPTIONS;

  init.callback = &silent_callback;
  bgfx::init(init);

  reset(backbuffer_width, backbuffer_height);

  this->shader = r_storage::construct<Shader>();
  this->shader->load_builtin_shaders();
}

void Renderer::clear(Color color) {
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, color, 1.0f, 0);
  bgfx::touch(0);
}

void Renderer::reset(u32 width, u32 height) {
  bgfx::reset(width, height, BGFX_RESET_OPTIONS);
  bgfx::setViewRect(0, 0, 0, width, height);
}

void Renderer::submit(const std::vector<Vertex> &vertices,
                      const std::vector<u16> &indices) {
  if (vertices.empty())
    return;

  size_t vertices_count = vertices.size();
  size_t indices_count = indices.size();

  bgfx::TransientVertexBuffer tvb;
  bgfx::TransientIndexBuffer tib;

  bgfx::allocTransientVertexBuffer(&tvb, vertices_count, vertex_layout);
  bgfx::allocTransientIndexBuffer(&tib, indices_count);

  memcpy(tvb.data, vertices.data(), vertices_count * sizeof(Vertex));
  memcpy(tib.data, indices.data(), indices_count * sizeof(u16));

  bgfx::setVertexBuffer(0, &tvb);
  bgfx::setIndexBuffer(&tib);
  bgfx::setState(BGFX_STATE_BLEND_ALPHA |  BGFX_STATE_DEFAULT & ~BGFX_STATE_CULL_MASK);
  bgfx::submit(0, shader->programs->curve);
  return;
}


void Renderer::present() { bgfx::frame(); }

} // namespace axm