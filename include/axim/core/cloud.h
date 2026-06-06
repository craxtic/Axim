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

#include "axim/config.h"
#include <axim/core/allocator.h>
#include <new>
#include <utility>

namespace axm {


class AXIM_CORE_API Cloud {

public:
  Allocator allocator;
  Cloud *next = nullptr;

  /**
   * @brief Construct a new Cloud object
   * 
   * @param capacity 
   */
  Cloud(
    size_t capacity
  ): 
    allocator(Allocator(capacity))
  {}
  
  ~Cloud();


  /**
   * @brief allocate n bytes memory of the cloud
   * 
   * @param n number of bytes
   * @param alignment memory alignment
   * @return void* 
   */
  void* 
  allocate(
    size_t n, 
    size_t alignment = alignof(max_align_t)
  );



  /**
   * @brief allocate an array of any data type T
   * 
   * @tparam T any data type
   * @param count number of elements
   * @return T* 
   */
  template<typename T> inline T* 
  allocate(size_t count){
    return reinterpret_cast<T*>(allocate(sizeof(T) * count, alignof(T)));
  }
  

  /**
   * @brief appends a new element to the end by constructing in-place direcly.
   * 
   * @tparam T any data type
   * @tparam Args 
   * @param args 
   * @return T* 
   */
  template<typename T, typename...Args> inline T* 
  construct(Args&&...args){
    T* memory = allocate<T>(1);
    return new(memory) T(std::forward<Args>(args)...);
  } 


};



}