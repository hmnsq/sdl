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

#నిర్వచితం_కాకపోతే SDL_video_c_h_
#నిర్వచించు SDL_video_c_h_

#అన్తర్భావ "SDL_internal.h"

నిర్మాణం SDL_VideoDevice;

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
బాహ్య bool SDL_InitVideo(స్థిరరాశి అక్షరం *driver_name);

/**
 * Shut down the video subsystem, if initialized with SDL_InitVideo().
 *
 * This function closes all windows, and restores the original video mode.
 */
బాహ్య శూన్య SDL_QuitVideo(శూన్య);

బాహ్య bool SDL_సమితి_కిటికీ_Texture_VSync(నిర్మాణం SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం vsync);

#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
స్థిరరాశి అక్షరం *SDL_GetCSSCursorName(SDL_SystemCursor id, స్థిరరాశి అక్షరం **fallback_name);
#అయితే_ముగింపు

బాహ్య bool SDL_కూడు_కిటికీ_Renderer(SDL_కిటికీ *కిటికీ, SDL_Renderer *renderer);
బాహ్య శూన్య SDL_Remove_కిటికీ_Renderer(SDL_కిటికీ *కిటికీ, SDL_Renderer *renderer);

#అయితే_ముగింపు // SDL_video_c_h_
