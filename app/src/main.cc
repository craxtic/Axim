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
 

#include "app.hh"

#include <axim/core/types/color.h>
#include <iostream>


int main(int argc, char *argv[]) {

  if (argc != 2)
    return 1;

  Settings setting;
  setting.background_color = axm::Color(0xff303030);
  setting.framesize.x = 1200;
  setting.framesize.y = 800; 

  char opt;
  std::cout << "demo code, \n1.preview\n2.export\nchoose: ";
  std::cin >> opt;

  if (opt == '1') {
    setting.active_mode = Mode::Preview;
    setting.preview.framerate = 60;
    setting.preview.dimensions = setting.framesize;

  } else if (opt == '2') {
    setting.active_mode = Mode::Export;
  } else
    return 0;



  return run_app(argv[1], setting);
}
