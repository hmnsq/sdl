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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_vivantevideo_h_
#define SDL_vivantevideo_h_

#അന്തര്ഭാവ "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#അന്തര്ഭാവ <SDL3/SDL_egl.h>

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
#അന്തര്ഭാവ <gc_vdk.h>
#അല്ലെങ്കിൽ
#അന്തര്ഭാവ <EGL/egl.h>
#endif

ഘടന SDL_VideoData
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#അല്ലെങ്കിൽ
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(ശൂന്യം *context);
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplayByIndex)(പൂർണ്ണസംഖ്യ DisplayIndex);
    ശൂന്യം(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, പൂർണ്ണസംഖ്യ *Width, പൂർണ്ണസംഖ്യ *Height);
    ശൂന്യം(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, പൂർണ്ണസംഖ്യ *Width, പൂർണ്ണസംഖ്യ *Height, unsigned long *Physical, പൂർണ്ണസംഖ്യ *Stride, പൂർണ്ണസംഖ്യ *bits_per_pixel);
    ശൂന്യം(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, പൂർണ്ണസംഖ്യ X, പൂർണ്ണസംഖ്യ Y, പൂർണ്ണസംഖ്യ Width, പൂർണ്ണസംഖ്യ Height);
    ശൂന്യം(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, പൂർണ്ണസംഖ്യ *X, പൂർണ്ണസംഖ്യ *Y, പൂർണ്ണസംഖ്യ *Width, പൂർണ്ണസംഖ്യ *Height);
    ശൂന്യം(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, പൂർണ്ണസംഖ്യ *X, പൂർണ്ണസംഖ്യ *Y, പൂർണ്ണസംഖ്യ *Width, പൂർണ്ണസംഖ്യ *Height, പൂർണ്ണസംഖ്യ *bits_per_pixel, unsigned പൂർണ്ണസംഖ്യ *Offset);
    ശൂന്യം(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#endif
};

ഘടന SDL_DisplayData
{
    EGLNativeDisplayType native_display;
};

ഘടന SDL_WindowData
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
ശൂന്യം VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ശൂന്യം VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ശൂന്യം VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ശൂന്യം VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ശൂന്യം VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ശൂന്യം VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
ശൂന്യം VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vivantevideo_h_
