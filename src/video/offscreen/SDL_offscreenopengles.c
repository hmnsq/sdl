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
#অন্তর্ভাৱ "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#অন্তর্ভাৱ "SDL_offscreenopengles.h"
#অন্তর্ভাৱ "SDL_offscreenvideo.h"
#অন্তর্ভাৱ "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path)
{
    যদি (!SDL_EGL_LoadLibraryOnly(_this, path)) {
        ঘূৰাই false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool result;
    _this->gl_config.driver_loaded++;
    result = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    যদি (!result) {
        ঘূৰাই false;
    }

    যদি (!SDL_EGL_ChooseConfig(_this)) {
        ঘূৰাই false;
    }

    ঘূৰাই true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *offscreen_window = window->internal;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_window->egl_surface);

    ঘূৰাই context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    যদি (window) {
        EGLSurface egl_surface = window->internal->egl_surface;
        ঘূৰাই SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } অন্যথা {
        ঘূৰাই SDL_EGL_MakeCurrent(_this, রিক্ত, রিক্ত);
    }
}

bool OFFSCREEN_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *offscreen_wind = window->internal;

    ঘূৰাই SDL_EGL_SwapBuffers(_this, offscreen_wind->egl_surface);
}

#endif // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
