/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#جيڪڏهن_وصف_نه_ٿيل SDL_video_c_h_
#وصف_ڪريو SDL_video_c_h_

#ضمن "SDL_internal.h"

بنية SDL_VideoDevice;

/**
 * Initialize the video subsystem, optionally specifying a video driver.
 *
 * This function initializes the video subsystem, setting up a connection to
 * the window manager, etc, and determines the available display modes and
 * pixel formats, but does not initialize a window or graphics mode.
 *
 * If you use this function and you haven't used the SDL_INIT_VIDEO flag with
 * either SDL_Init() or SDL_InitSubSystem(), you should call SDL_QuitVideo()
 * before calling SDL_Quit().
 *
 * It is safe to call this function multiple times. SDL_InitVideo() will call
 * SDL_QuitVideo() itself if the video subsystem has already been initialized.
 *
 * You can use SDL_GetNumVideoDrivers() and SDL_GetVideoDriver() to find a
 * specific `driver_name`.
 *
 * \param driver_name the name of a video driver to initialize, or NULL for
 *                    the default driver
 * \returns true on success or false on failure; call
 *          SDL_GetError() for more information.
 */
خارجي bool SDL_InitVideo(ثابت حرف *driver_name);

/**
 * Shut down the video subsystem, if initialized with SDL_InitVideo().
 *
 * This function closes all windows, and restores the original video mode.
 */
خارجي فراغ SDL_QuitVideo(فراغ);

خارجي bool SDL_سيٽ_دري_Texture_VSync(بنية SDL_VideoDevice *_this, SDL_دري *دري, صحيح vsync);

#إذا defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ثابت حرف *SDL_GetCSSCursorName(SDL_SystemCursor id, ثابت حرف **fallback_name);
#جيڪڏهن_پورو

خارجي bool SDL_جوڙيو_دري_Renderer(SDL_دري *دري, SDL_Renderer *renderer);
خارجي فراغ SDL_Remove_دري_Renderer(SDL_دري *دري, SDL_Renderer *renderer);

#جيڪڏهن_پورو // SDL_video_c_h_
