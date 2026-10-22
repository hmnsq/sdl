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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_vivantevideo_h_
#घोषणा SDL_vivantevideo_h_

#समावेश "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#समावेश <SDL3/SDL_egl.h>

#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
#समावेश <gc_vdk.h>
#अन्यथा
#समावेश <EGL/egl.h>
#पूर्ण_अगर

काष्ठा SDL_Video_तथ्य
{
#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdkPrivate vdk_private;
#अन्यथा
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(व्योम *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_सूचकांक)(पूर्णांक Display_सूचकांक);
    व्योम(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, पूर्णांक *Width, पूर्णांक *Height);
    व्योम(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, पूर्णांक *Width, पूर्णांक *Height, अचिन्हित दीर्घ *Physical, पूर्णांक *Stride, पूर्णांक *bits_per_pixel);
    व्योम(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNativeWindowType(EGLAPIENTRY *fbCreateWindow)(EGLNativeDisplayType Display, पूर्णांक X, पूर्णांक Y, पूर्णांक Width, पूर्णांक Height);
    व्योम(EGLAPIENTRY *fbGetWindowGeometry)(EGLNativeWindowType Window, पूर्णांक *X, पूर्णांक *Y, पूर्णांक *Width, पूर्णांक *Height);
    व्योम(EGLAPIENTRY *fbGetWindowInfo)(EGLNativeWindowType Window, पूर्णांक *X, पूर्णांक *Y, पूर्णांक *Width, पूर्णांक *Height, पूर्णांक *bits_per_pixel, अचिन्हित पूर्णांक *Offset);
    व्योम(EGLAPIENTRY *fbDestroyWindow)(EGLNativeWindowType Window);
#पूर्ण_अगर
};

काष्ठा SDL_Display_तथ्य
{
    EGLNativeDisplayType native_display;
};

काष्ठा SDL_Window_तथ्य
{
    EGLNativeWindowType native_window;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
व्योम VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
व्योम VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
व्योम VIVANTE_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
व्योम VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
व्योम VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
व्योम VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// Event functions
व्योम VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_vivantevideo_h_
