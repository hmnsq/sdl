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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#ضمن "SDL_offscreenopengles.h"
#ضمن "SDL_offscreenvideo.h"
#ضمن "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    إذا (!SDL_EGL_لدو_Library_Only(_this, رستہ)) {
        أرجع false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool نتیجہ;
    _this->gl_config.driver_loaded++;
    نتیجہ = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    إذا (!نتیجہ) {
        أرجع false;
    }

    إذا (!SDL_EGL_چنو_Config(_this)) {
        أرجع false;
    }

    أرجع true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *offscreen_کھڑکی = کھڑکی->اندرونی;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_کھڑکی->egl_surface);

    أرجع context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    إذا (کھڑکی) {
        EGLSurface egl_surface = کھڑکی->اندرونی->egl_surface;
        أرجع SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } وإلا {
        أرجع SDL_EGL_MakeCurrent(_this, عدم, عدم);
    }
}

bool OFFSCREEN_GLES_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *offscreen_wind = کھڑکی->اندرونی;

    أرجع SDL_EGL_وٹاندرا_Buffers(_this, offscreen_wind->egl_surface);
}

#جے_انت // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
