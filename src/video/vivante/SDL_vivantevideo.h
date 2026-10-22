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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_vivantevideo_h_
#define SDL_vivantevideo_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_egl.h>

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
#ಅನ್ತರ್ಭಾವ <gc_vdk.h>
#ಅನ್ಯಥಾ
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#endif

ಸಂರಚನಾ SDL_VideoData
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#ಅನ್ಯಥಾ
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(ಶೂನ್ಯ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplayByIndex)(ಪೂರ್ಣಾಙ್ಕ DisplayIndex);
    ಶೂನ್ಯ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, ಪೂರ್ಣಾಙ್ಕ *Width, ಪೂರ್ಣಾಙ್ಕ *Height);
    ಶೂನ್ಯ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, ಪೂರ್ಣಾಙ್ಕ *Width, ಪೂರ್ಣಾಙ್ಕ *Height, unsigned long *Physical, ಪೂರ್ಣಾಙ್ಕ *Stride, ಪೂರ್ಣಾಙ್ಕ *bits_per_pixel);
    ಶೂನ್ಯ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, ಪೂರ್ಣಾಙ್ಕ X, ಪೂರ್ಣಾಙ್ಕ Y, ಪೂರ್ಣಾಙ್ಕ Width, ಪೂರ್ಣಾಙ್ಕ Height);
    ಶೂನ್ಯ(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, ಪೂರ್ಣಾಙ್ಕ *X, ಪೂರ್ಣಾಙ್ಕ *Y, ಪೂರ್ಣಾಙ್ಕ *Width, ಪೂರ್ಣಾಙ್ಕ *Height);
    ಶೂನ್ಯ(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, ಪೂರ್ಣಾಙ್ಕ *X, ಪೂರ್ಣಾಙ್ಕ *Y, ಪೂರ್ಣಾಙ್ಕ *Width, ಪೂರ್ಣಾಙ್ಕ *Height, ಪೂರ್ಣಾಙ್ಕ *bits_per_pixel, unsigned ಪೂರ್ಣಾಙ್ಕ *Offset);
    ಶೂನ್ಯ(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#endif
};

ಸಂರಚನಾ SDL_DisplayData
{
    EGLNativeDisplayType native_display;
};

ಸಂರಚನಾ SDL_WindowData
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
ಶೂನ್ಯ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ಶೂನ್ಯ VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ಶೂನ್ಯ VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ಶೂನ್ಯ VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಶೂನ್ಯ VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಶೂನ್ಯ VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
ಶೂನ್ಯ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vivantevideo_h_
