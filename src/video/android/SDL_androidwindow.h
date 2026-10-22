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

#ifndef SDL_androidwindow_h_
#define SDL_androidwindow_h_

#અન્તર્ભાવ "../../core/android/SDL_android.h"
#અન્તર્ભાવ "../SDL_egl_c.h"

બાહ્ય bool Android_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
બાહ્ય શૂન્ય Android_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય SDL_FullscreenResult Android_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
બાહ્ય શૂન્ય Android_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Android_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);

બાહ્ય શૂન્ય Android_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય SDL_Window *Android_Window;

સંરચના SDL_WindowData
{
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    પૂર્ણાંક has_swap_interval;  // Save/Restore the swap interval / vsync
    પૂર્ણાંક swap_interval;
#endif
    bool backup_done;
    ANativeWindow *native_window;

};

#endif // SDL_androidwindow_h_
