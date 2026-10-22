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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_vivantevideo_h_
#define SDL_vivantevideo_h_

#અન્તર્ભાવ "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#અન્તર્ભાવ <SDL3/SDL_egl.h>

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
#અન્તર્ભાવ <gc_vdk.h>
#નહીંતર
#અન્તર્ભાવ <EGL/egl.h>
#endif

સંરચના SDL_VideoData
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#નહીંતર
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(શૂન્ય *context);
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplayByIndex)(પૂર્ણાંક DisplayIndex);
    શૂન્ય(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, પૂર્ણાંક *Width, પૂર્ણાંક *Height);
    શૂન્ય(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, પૂર્ણાંક *Width, પૂર્ણાંક *Height, unsigned long *Physical, પૂર્ણાંક *Stride, પૂર્ણાંક *bits_per_pixel);
    શૂન્ય(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, પૂર્ણાંક X, પૂર્ણાંક Y, પૂર્ણાંક Width, પૂર્ણાંક Height);
    શૂન્ય(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, પૂર્ણાંક *X, પૂર્ણાંક *Y, પૂર્ણાંક *Width, પૂર્ણાંક *Height);
    શૂન્ય(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, પૂર્ણાંક *X, પૂર્ણાંક *Y, પૂર્ણાંક *Width, પૂર્ણાંક *Height, પૂર્ણાંક *bits_per_pixel, unsigned પૂર્ણાંક *Offset);
    શૂન્ય(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#endif
};

સંરચના SDL_DisplayData
{
    EGLNativeDisplayType native_display;
};

સંરચના SDL_WindowData
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
શૂન્ય VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
શૂન્ય VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
શૂન્ય VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
શૂન્ય VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
શૂન્ય VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
શૂન્ય VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
શૂન્ય VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vivantevideo_h_
