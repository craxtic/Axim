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

#define UNUSED(x) (void)(true ? (void)0 : ((void)(x)))

struct SilentCallback : public bgfx::CallbackI {
  virtual ~SilentCallback() {}

  virtual void traceVargs(const char *_filePath, uint16_t _line,
                          const char *_format, va_list _argList) override {
    UNUSED(_filePath);
    UNUSED(_line);
    UNUSED(_format);
    UNUSED(_argList);
  }

  virtual void fatal(const char *_filePath, uint16_t _line,
                     bgfx::Fatal::Enum _code, const char *_str) override {
    UNUSED(_filePath);
    UNUSED(_line);
    UNUSED(_code);
    UNUSED(_str);
    abort();
  }
  virtual bool cacheRead(uint64_t _id, void *_data, uint32_t _size) override {
    // BX_UNUSED(_id);
    UNUSED(_id);
    UNUSED(_data);
    UNUSED(_size);
    return false;
  }

  virtual void cacheWrite(uint64_t _id, const void *_data,
                          uint32_t _size) override {
    UNUSED(_id);
    UNUSED(_data);
    UNUSED(_size);
  }
  virtual void screenShot(const char *_filePath, uint32_t _width,
                          uint32_t _height, uint32_t _pitch,
                          bgfx::TextureFormat::Enum _format, const void *_data,
                          uint32_t _size, bool _yflip) override {
    UNUSED(_filePath);
    UNUSED(_width);
    UNUSED(_height);
    UNUSED(_pitch);
    UNUSED(_data);
    UNUSED(_size);
    UNUSED(_yflip);
  }
  virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch,
                            bgfx::TextureFormat::Enum _format,
                            bool _yflip) override {
    UNUSED(_width);
    UNUSED(_height);
    UNUSED(_pitch);
    UNUSED(_format);
    UNUSED(_yflip);
  }
  virtual void captureEnd() override {}
  virtual void captureFrame(const void *_data, uint32_t _size) override {
    UNUSED(_data);
    UNUSED(_size);
  }
  virtual uint32_t cacheReadSize(uint64_t _id) override {
    UNUSED(_id);
    return 0;
  }
  virtual void profilerEnd() override {}
  virtual void profilerBeginLiteral(const char *_name, uint32_t _abgr,
                                    const char *_filePath,
                                    uint16_t _line) override {

    UNUSED(_name);
    UNUSED(_abgr);
    UNUSED(_filePath);
    UNUSED(_line);
  }
  virtual void profilerBegin(const char *_name, uint32_t _abgr,
                             const char *_filePath, uint16_t _line) override {
    UNUSED(_name);
    UNUSED(_abgr);
    UNUSED(_filePath);
    UNUSED(_line);
  }

} silent_callback;

static const bgfx::VertexLayout layout =
    bgfx::VertexLayout()
        .begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);

#define BGFX_RESET_OPTIONS (BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4)

namespace axm {

Renderer::Renderer(u32 backbuffer_width, u32 backbuffer_height, void *nwh, void *ndt) {

  bgfx::Init init;

  #if defined (__linux)
    init.type = bgfx::RendererType::Vulkan;
  #elif defined (_WIN32)
    init.type = bgfx::RendererType::Direct3D11;
  #elif define (__APPLE__)
    init.type = bgfx::RendererType::Metal;
  #endif
  
  init.platformData.ndt = ndt;
  init.platformData.nwh = nwh;

  init.resolution.width = backbuffer_width;
  init.resolution.height = backbuffer_height;
  init.resolution.reset = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4;

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

  bgfx::allocTransientVertexBuffer(&tvb, vertices_count, layout);
  bgfx::allocTransientIndexBuffer(&tib, indices_count);

  memcpy(tvb.data, vertices.data(), vertices_count * sizeof(Vertex));
  memcpy(tib.data, indices.data(), indices_count * sizeof(u16));

  bgfx::setVertexBuffer(0, &tvb);
  bgfx::setIndexBuffer(&tib);
  bgfx::setState(BGFX_STATE_DEFAULT & ~BGFX_STATE_CULL_MASK);
  bgfx::submit(0, shader->programs->triangle);
  return;
}

void Renderer::present() { bgfx::frame(); }

} // namespace axm