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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_vivantevideo_h_
#define SDL_vivantevideo_h_

#অন্তর্ভাব "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#অন্তর্ভাব <SDL3/SDL_egl.h>

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
#অন্তর্ভাব <gc_vdk.h>
#অন্যথা
#অন্তর্ভাব <EGL/egl.h>
#endif

সংরচনা SDL_VideoData
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#অন্যথা
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(শূন্য *context);
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplayByIndex)(পূর্ণাঙ্ক DisplayIndex);
    শূন্য(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, পূর্ণাঙ্ক *Width, পূর্ণাঙ্ক *Height);
    শূন্য(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, পূর্ণাঙ্ক *Width, পূর্ণাঙ্ক *Height, unsigned long *Physical, পূর্ণাঙ্ক *Stride, পূর্ণাঙ্ক *bits_per_pixel);
    শূন্য(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, পূর্ণাঙ্ক X, পূর্ণাঙ্ক Y, পূর্ণাঙ্ক Width, পূর্ণাঙ্ক Height);
    শূন্য(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, পূর্ণাঙ্ক *X, পূর্ণাঙ্ক *Y, পূর্ণাঙ্ক *Width, পূর্ণাঙ্ক *Height);
    শূন্য(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, পূর্ণাঙ্ক *X, পূর্ণাঙ্ক *Y, পূর্ণাঙ্ক *Width, পূর্ণাঙ্ক *Height, পূর্ণাঙ্ক *bits_per_pixel, unsigned পূর্ণাঙ্ক *Offset);
    শূন্য(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#endif
};

সংরচনা SDL_DisplayData
{
    EGLNativeDisplayType native_display;
};

সংরচনা SDL_WindowData
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
শূন্য VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
শূন্য VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
শূন্য VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
শূন্য VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
শূন্য VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
শূন্য VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
শূন্য VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vivantevideo_h_
