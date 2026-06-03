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
#include <axim/core/conicsegment.h>
#include <axim/core/types/ctype.h>
#include <axim/renderer/paint.h>
#include <axim/core/types/vector2.h>
#include <axim/renderer/vertex.h>

#include <vector>


namespace axm {

class AXIM_RENDERER_API Canvas {

public: 
  u32 width, height;
  Color bg_color;  /**< background color of the canvas */

  /**
   * @brief Construct a new Canvas object
   * 
   * @param[in] width 
   * @param[in] height 
   * @param[in] bg_color Background color 
   */
  Canvas(
    u32 width, 
    u32 height, 
    Color bg_color
  );

  /**
   * @brief clear all vertex and index buffers
   * 
   */
  void 
  clear();


  /**
   * @brief draw a span of conic segments on the canvas with a brush (fill) 
   * 
   * @param segments 
   * @param brush 
   *
   * @sa Brush
   */
  void 
  draw(
    const std::span<const ConicSegment>& segments, 
    const Brush& brush
  );


  /**
   * @brief draw a span of conic segments on the canvas with a pen (strokes) 
   * 
   * @param segments 
   * @param pen 
   * 
   * @sa Pen
   */
  void 
  draw(
    const std::span<const ConicSegment>& segments, 
    const Pen& pen
  );


  /**
   * @brief reset the size of the canvas 
   * 
   * @param width 
   * @param height 
   */
  inline void 
  reset_size(
    u32 width, 
    u32 height
  ){
    this->width = width;
    this->height = height;
  }
  

  /**
   * @brief Get the vertices object
   * 
   * @return const std::vector<Vertex>& 
   */
  [[nodiscard]] inline const std::vector<Vertex>& 
  get_vertices() const {
    return vertices;
  }
  

  /**
   * @brief Get the indices object
   * 
   * @return const std::vector<u16>& 
   */
  [[nodiscard]] inline const std::vector<u16>& 
  get_indices() const {
    return indices;
  }


  /**
   * @brief Get the interior_vert object
   * 
   * @return const std::vector<Vertex>& 
   */
  [[nodiscard]] inline const std::vector<Vertex>& 
  get_interior_vert() const {
    return interior_vert;
  }
  

  /**
   * @brief Get the interior_indi object
   * 
   * @return const std::vector<u16>& 
   */
  [[nodiscard]] inline const std::vector<u16>& 
  get_interior_indi() const {
    return interior_indi;
  }
  
private:
  std::vector<Vertex> vertices;       /**< The vertex buffer for curves. */
  std::vector<u16> indices;           /**< The index buffer for curves. */
  std::vector<Vertex> interior_vert;  /**< The vertex buffer for solid interiors. */
  std::vector<u16> interior_indi;     /**< The index buffer for slid interiors. */

};


}