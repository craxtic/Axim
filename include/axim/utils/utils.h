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

#include <cstddef>
#include <source_location>
#include <string_view>
#include <utility>
#include <chrono>
#include <iostream>

// /// unrolling helper function
// template <std::size_t N, typename F>
// constexpr void static_loop_unroll(F &&op_func) noexcept {

//   [&]<std::size_t... Is>(std::index_sequence<Is...>){
//     (std::forward<F>(op_func)(Is), ...);
//   }(std::make_index_sequence<N>{});

//   return;
// }

namespace axm {

  
class Stopwatch {

public: 
  std::chrono::steady_clock::time_point begin;
  std::source_location scope_location;

  Stopwatch(std::source_location scope_location = std::source_location::current()): 
    begin(std::chrono::steady_clock::now()),
    scope_location(scope_location)
  {}


  void lap(std::source_location lap_location = std::source_location::current()){

    auto end = std::chrono::steady_clock::now();
    std::cout << scope_location.file_name() << ":"  
    << scope_location.line() << "-"
    << lap_location.line() << ":"
    << end - begin  << "\n";

  }

  void* operator new(std::size_t) = delete;
  void* operator new[](std::size_t) = delete;

};

}