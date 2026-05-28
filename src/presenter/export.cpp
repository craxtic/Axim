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

#include <axim/presenter/export.h>
#include <cstdio>
#include <format>
#include <string_view>


#ifdef _WIN32

#define POPEN _popen
#define PCLOSE _pclose

#else

#define POPEN popen
#define PCLOSE pclose

#endif


namespace axm {

ExportPresenter::ExportPresenter(vec2i dimensions, std::string_view output_filename): dimensions(dimensions){




  /*
  
  ffmpeg -y -f rawvideo -pixel_format rgba -video_size 1920x1080 -i - \
-c:v libx264 -preset slower -crf 18 -pix_fmt yuv420p output.mp4

  
  */
  std::string command = std::format(
    "ffmpeg -y -f rawvideo -framerate 60 -pixel_format bgra -video_size {}x{} -i - -c:v libx264 -preset slower -crf 18 -pix_fmt yuv420p {}", 
    dimensions.x, dimensions.y, output_filename
  );

  this->ffmpeg = POPEN(command.c_str(), "w");

}

void ExportPresenter::clear(Color color){
  
}


/// display the drawn buffer to the output
void ExportPresenter::present(const Canvas& canvas) const {
  
}

/// pause
void ExportPresenter::idle(int duration, bool *running) const {
  
  return;
}

ExportPresenter::~ExportPresenter() {
  // this->surface->unref();
  PCLOSE(this->ffmpeg);
}



}