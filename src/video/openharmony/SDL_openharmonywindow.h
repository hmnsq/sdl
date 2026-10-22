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

#अगर_अघोषित SDL_openharmonywindow_h_
#घोषणा SDL_openharmonywindow_h_

#समावेश "../../core/openharmony/SDL_openharmony.h"
#समावेश "../SDL_egl_c.h"

बाह्य bool OPENHARMONY_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम OPENHARMONY_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_Fullscreen_परिणाम OPENHARMONY_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य व्योम OPENHARMONY_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम OPENHARMONY_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);

बाह्य व्योम OPENHARMONY_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_Window *OPENHARMONY_Window;

काष्ठा SDL_Window_तथ्य
{
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    पूर्णांक has_swap_interval;  // Save/Restore the swap interval / vsync
    पूर्णांक swap_interval;
#पूर्ण_अगर
    bool backup_done;
    व्योम *native_xcomponent;
    व्योम *native_window;
};

#पूर्ण_अगर // SDL_openharmonywindow_h_
