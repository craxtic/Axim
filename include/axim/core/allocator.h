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
#include <cstddef>
#include <cstring>

namespace axm {

using byte = unsigned char;

class AXIM_CORE_API Allocator {
  byte *begin;
  byte *current;
  byte *end;

public:

  /**
   * @brief Construct a new Allocator object
   * 
   */
  Allocator() = default;

  /**
   * @brief Construct a new Allocator object
   * 
   * @param capacity 
   */
  explicit Allocator(
    size_t capacity
  );

  ~Allocator();

  /**
   * @brief allocate n bytes from the region
   * 
   * @param n number of bytes
   * @param alignment memory aligment
   * @return void* 
   */
  [[nodiscard]] void*
  allocate(
    size_t n, 
    size_t alignment = alignof(max_align_t)
  );



  /**
   * @brief 
   * 
   * @tparam T any data type 
   * @param count the array count
   * @return T* 
   */
  template<typename T> inline T*
  allocate(size_t count){
    return reinterpret_cast<T*>(allocate(sizeof(T) * count, alignof(T)));
  }


  /**
   * @brief reset the region back to the first starting address
   * 
   */
  inline void 
  reset(){
    current = begin;
  };


  /**
   * @brief set all bytes in the region to zero
   * 
   */
  inline void 
  clean(){
    std::memset(begin, 0, capacity());
  };


  /**
   * @brief returns the total capcity of the region
   * 
   * @return size_t 
   */
  [[nodiscard]] inline size_t 
  capacity(){
    return (end - begin);
  }

  /**
   * @brief returns the used size of the regions
   * 
   * @return size_t 
   */
  [[nodiscard]] inline size_t 
  size(){
    return (current - begin);
  }

};



}
