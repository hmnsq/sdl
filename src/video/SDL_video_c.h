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

#ifndef SDL_video_c_h_
#define SDL_video_c_h_

#अन्तर्भाव "SDL_internal.h"

संरचना SDL_VideoDevice;

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
बाह्य bool SDL_InitVideo(अचर वर्ण *driver_name);

/**
 * Shut down the video subsystem, if initialized with SDL_InitVideo().
 *
 * This function closes all windows, and restores the original video mode.
 */
बाह्य शून्य SDL_QuitVideo(शून्य);

बाह्य bool SDL_SetWindowTextureVSync(संरचना SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क vsync);

#यदि defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
अचर वर्ण *SDL_GetCSSCursorName(SDL_SystemCursor id, अचर वर्ण **fallback_name);
#endif

बाह्य bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer);
बाह्य शून्य SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer);

#endif // SDL_video_c_h_
