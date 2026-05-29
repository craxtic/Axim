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

#include "axim/core/types/vector2.h"
#include <axim/config.h>
#include <axim/presenter/presenter.h>
#include <cstdio>




namespace axm {


class AXIM_PRESENTER_API ExportPresenter : public PresenterInterface {

  FILE* ffmpeg;
  vec2i dimensions;

public:

  ExportPresenter(vec2i dimensions, std::string_view output_filename);
  ~ExportPresenter();

  virtual void clear() override;


  /// display the drawn buffer to the output
  virtual void present() const override;

  virtual Canvas* get_canvas() override;

  /// pause
  /// TODO: introduce a new param to accept the idling duration
  virtual void idle(int duration, bool *running) const override;

};


}