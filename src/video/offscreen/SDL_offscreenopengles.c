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
#include "SDL_internal.h"

#အကယ်၍ defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#include "SDL_offscreenopengles.h"
#include "SDL_offscreenvideo.h"
#include "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_LoadLibrary(SDL_VideoDevice *_this, const var_na *path)
{
    အကယ်၍ (!SDL_EGL_LoadLibraryOnly(_this, path)) {
        ပြန်ပေး false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool result;
    _this->gl_config.driver_loaded++;
    result = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    အကယ်၍ (!result) {
        ပြန်ပေး false;
    }

    အကယ်၍ (!SDL_EGL_ChooseConfig(_this)) {
        ပြန်ပေး false;
    }

    ပြန်ပေး true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *offscreen_window = window->internal;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_window->egl_surface);

    ပြန်ပေး context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    အကယ်၍ (window) {
        EGLSurface egl_surface = window->internal->egl_surface;
        ပြန်ပေး SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_EGL_MakeCurrent(_this, NULL, NULL);
    }
}

bool OFFSCREEN_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *offscreen_wind = window->internal;

    ပြန်ပေး SDL_EGL_SwapBuffers(_this, offscreen_wind->egl_surface);
}

#endif // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
