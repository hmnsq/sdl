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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#شامل "SDL_offscreenopengles.h"
#شامل "SDL_offscreenvideo.h"
#شامل "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    اگر (!SDL_EGL_بھرو_Library_Only(_this, راستہ)) {
        واپس false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool نتیجہ;
    _this->gl_config.driver_loaded++;
    نتیجہ = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    اگر (!نتیجہ) {
        واپس false;
    }

    اگر (!SDL_EGL_انتخاب_Config(_this)) {
        واپس false;
    }

    واپس true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *offscreen_کھڑکی = کھڑکی->اندرونی_2;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_کھڑکی->egl_surface);

    واپس context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    اگر (کھڑکی) {
        EGLSurface egl_surface = کھڑکی->اندرونی_2->egl_surface;
        واپس SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } ورنہ {
        واپس SDL_EGL_MakeCurrent(_this, تہی, تہی);
    }
}

bool OFFSCREEN_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *offscreen_wind = کھڑکی->اندرونی_2;

    واپس SDL_EGL_تبادلہ_Buffers(_this, offscreen_wind->egl_surface);
}

#اگر_ختم // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
