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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਜੇ (!SDL_EGL_ਲੱਦੋ_Library_Only(_this, ਰਸਤਾ)) {
        ਵਾਪਸ false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool ਨਤੀਜਾ;
    _this->gl_config.driver_loaded++;
    ਨਤੀਜਾ = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    ਜੇ (!ਨਤੀਜਾ) {
        ਵਾਪਸ false;
    }

    ਜੇ (!SDL_EGL_ਚੁਣੋ_Config(_this)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *offscreen_ਖਿੜਕੀ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_ਖਿੜਕੀ->egl_surface);

    ਵਾਪਸ context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    ਜੇ (ਖਿੜਕੀ) {
        EGLSurface egl_surface = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface;
        ਵਾਪਸ SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_EGL_MakeCurrent(_this, ਨਿਰਾ, ਨਿਰਾ);
    }
}

bool OFFSCREEN_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *offscreen_wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਵਾਪਸ SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this, offscreen_wind->egl_surface);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
