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
#ضمن "SDL_internal.h"

#ifndef SDL_vivantevideo_h_
#define SDL_vivantevideo_h_

#ضمن "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ضمن <SDL3/SDL_egl.h>

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
#ضمن <gc_vdk.h>
#אחרת
#ضمن <EGL/egl.h>
#endif

بنية SDL_VideoData
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#אחרת
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(فراغ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplayByIndex)(صحيح DisplayIndex);
    فراغ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, صحيح *Width, صحيح *Height);
    فراغ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, صحيح *Width, صحيح *Height, unsigned long *Physical, صحيح *Stride, صحيح *bits_per_pixel);
    فراغ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, صحيح X, صحيح Y, صحيح Width, صحيح Height);
    فراغ(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, صحيح *X, صحيح *Y, صحيح *Width, صحيح *Height);
    فراغ(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, صحيح *X, صحيح *Y, صحيح *Width, صحيح *Height, صحيح *bits_per_pixel, unsigned صحيح *Offset);
    فراغ(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#endif
};

بنية SDL_DisplayData
{
    EGLNativeDisplayType native_display;
};

بنية SDL_WindowData
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
فراغ VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
فراغ VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
فراغ VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
فراغ VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
فراغ VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vivantevideo_h_
