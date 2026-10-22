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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_vivantevideo_h_
#define SDL_vivantevideo_h_

#अन्तर्भाव "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#अन्तर्भाव <SDL3/SDL_egl.h>

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
#अन्तर्भाव <gc_vdk.h>
#अन्यथा
#अन्तर्भाव <EGL/egl.h>
#endif

संरचना SDL_VideoData
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#अन्यथा
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(शून्य *context);
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplayByIndex)(पूर्णांक DisplayIndex);
    शून्य(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, पूर्णांक *Width, पूर्णांक *Height);
    शून्य(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, पूर्णांक *Width, पूर्णांक *Height, अचिन्हित दीर्घ *Physical, पूर्णांक *Stride, पूर्णांक *bits_per_pixel);
    शून्य(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, पूर्णांक X, पूर्णांक Y, पूर्णांक Width, पूर्णांक Height);
    शून्य(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, पूर्णांक *X, पूर्णांक *Y, पूर्णांक *Width, पूर्णांक *Height);
    शून्य(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, पूर्णांक *X, पूर्णांक *Y, पूर्णांक *Width, पूर्णांक *Height, पूर्णांक *bits_per_pixel, अचिन्हित पूर्णांक *Offset);
    शून्य(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#endif
};

संरचना SDL_DisplayData
{
    EGLNativeDisplayType native_display;
};

संरचना SDL_WindowData
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
शून्य VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
शून्य VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
शून्य VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
शून्य VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
शून्य VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
शून्य VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
शून्य VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vivantevideo_h_
