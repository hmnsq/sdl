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

#अगर defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#समावेश "SDL_offscreenopengles.h"
#समावेश "SDL_offscreenvideo.h"
#समावेश "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    अगर (!SDL_EGL_LoadLibraryOnly(_this, path)) {
        वापस false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool परिणाम;
    _this->gl_config.driver_loaded++;
    परिणाम = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    अगर (!परिणाम) {
        वापस false;
    }

    अगर (!SDL_EGL_ChooseConfig(_this)) {
        वापस false;
    }

    वापस true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *offscreen_window = window->internal;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_window->egl_surface);

    वापस context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    अगर (window) {
        EGLSurface egl_surface = window->internal->egl_surface;
        वापस SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } अन्यथा {
        वापस SDL_EGL_MakeCurrent(_this, शून्य, शून्य);
    }
}

bool OFFSCREEN_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *offscreen_wind = window->internal;

    वापस SDL_EGL_SwapBuffers(_this, offscreen_wind->egl_surface);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
