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


#define AXIM_VERSION_MAJOR 0
#define AXIM_VERSION_MINOR 0
#define AXIM_VERSION_PATCH 1


#if defined (_WIN32)

#define AXIM_API_EXPORT __declspec(dllexport)
#define AXIM_API_IMPORT __declspec(dllimport)

#else  /* Linux, FreeBSD, macOS */

#define AXIM_API_EXPORT __attribute__((__visibility__("default")))
#define AXIM_API_IMPORT __attribute__((__visibility__("default")))

#endif


#if defined (AXIM_CORE_EXPORTS)

#define AXIM_CORE_API AXIM_API_EXPORT

#else

#define AXIM_CORE_API AXIM_API_IMPORT

#endif

#if defined (AXIM_RENDERER_EXPORTS)

#define AXIM_RENDERER_API AXIM_API_EXPORT

#else

#define AXIM_RENDERER_API AXIM_API_IMPORT

#endif



#if defined (AXIM_ENGINE_EXPORTS)

#define AXIM_ENGINE_API AXIM_API_EXPORT

#else

#define AXIM_ENGINE_API AXIM_API_IMPORT

#endif



#if defined (AXIM_PRESENTER_EXPORTS)

#define AXIM_PRESENTER_API AXIM_API_EXPORT

#else

#define AXIM_PRESENTER_API AXIM_API_IMPORT

#endif




#define MOBJECT_COUNT_PER_SCENE_PROBABLY 100
