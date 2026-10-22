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

#ਜੇ defined(SDL_VIDEO_DRIVER_RPI) && defined(SDL_VIDEO_OPENGL_EGL)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rpivideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rpiopengles.h"

// EGL implementation of SDL OpenGL support

ਖਾਲੀ RPI_GLES_ਸੈੱਟ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.profile_ਨਕਾਬ = SDL_GL_CONTEXT_PROFILE_ES;
    _this->gl_config.major_ਸੰਸਕਰਣ = 2;
    _this->gl_config.minor_ਸੰਸਕਰਣ = 0;
}

bool RPI_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਵਾਪਸ SDL_EGL_ਲੱਦੋ_Library(_this, ਰਸਤਾ, EGL_DEFAULT_DISPLAY);
}

bool RPI_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (!(_this->egl_ਅੰਕੜੇ->egl_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this->egl_ਅੰਕੜੇ->egl_display, wdata->egl_surface))) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "eglSwapBuffers failed.");
        ਵਾਪਸ true;
    }

    /* Wait immediately for vsync (as if we only had two buffers), for low input-lag scenarios.
     * Run your SDL program with "SDL_RPI_DOUBLE_BUFFER=1 <program_name>" to enable this. */
    ਜੇ (wdata->double_ਬਫਰ) {
        SDL_ਤਾਲਾ_Mutex(wdata->vsync_cond_mutex);
        SDL_WaitCondition(wdata->vsync_cond, wdata->vsync_cond_mutex);
        SDL_UnlockMutex(wdata->vsync_cond_mutex);
    }

    ਵਾਪਸ true;
}

SDL_EGL_CreateContext_impl(RPI)
SDL_EGL_MakeCurrent_impl(RPI)

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RPI && SDL_VIDEO_OPENGL_EGL
