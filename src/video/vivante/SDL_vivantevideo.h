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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_vivantevideo_h_
#define SDL_vivantevideo_h_

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_egl.h>

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
#ଅନ୍ତର୍ଭାଵ <gc_vdk.h>
#ଅନ୍ୟଥା
#ଅନ୍ତର୍ଭାଵ <EGL/egl.h>
#endif

ସଂରଚନା SDL_VideoData
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#ଅନ୍ୟଥା
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(ଶୂନ୍ୟ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplayByIndex)(ପୂର୍ଣ୍ଣସଂଖ୍ୟା DisplayIndex);
    ଶୂନ୍ୟ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Height);
    ଶୂନ୍ୟ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Height, unsigned long *Physical, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Stride, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *bits_per_pixel);
    ଶୂନ୍ୟ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, ପୂର୍ଣ୍ଣସଂଖ୍ୟା X, ପୂର୍ଣ୍ଣସଂଖ୍ୟା Y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା Width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା Height);
    ଶୂନ୍ୟ(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *X, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Height);
    ଶୂନ୍ୟ(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *X, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Height, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *bits_per_pixel, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *Offset);
    ଶୂନ୍ୟ(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#endif
};

ସଂରଚନା SDL_DisplayData
{
    EGLNativeDisplayType native_display;
};

ସଂରଚନା SDL_WindowData
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
ଶୂନ୍ୟ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ଶୂନ୍ୟ VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ଶୂନ୍ୟ VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ଶୂନ୍ୟ VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ଶୂନ୍ୟ VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ଶୂନ୍ୟ VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
ଶୂନ୍ୟ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vivantevideo_h_
