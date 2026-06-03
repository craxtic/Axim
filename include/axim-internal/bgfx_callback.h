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

#include <bgfx/bgfx.h>

#define UNUSED(x) (void)(true ? (void)0 : ((void)(x)))


inline struct SilentCallback : public bgfx::CallbackI {
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
    UNUSED(_format);
    
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