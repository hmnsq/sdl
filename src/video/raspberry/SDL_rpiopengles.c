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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_RPI) && defined(SDL_VIDEO_OPENGL_EGL)

#अन्तर्भाव "SDL_rpivideo.h"
#अन्तर्भाव "SDL_rpiopengles.h"

// EGL implementation of SDL OpenGL support

शून्य RPI_GLES_समुच्चयः_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.profile_आवरणम् = SDL_GL_CONTEXT_PROFILE_ES;
    _this->gl_config.major_संस्करणम् = 2;
    _this->gl_config.minor_संस्करणम् = 0;
}

bool RPI_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    प्रत्यागम SDL_EGL_आरोपय_Library(_this, मार्गः, EGL_DEFAULT_DISPLAY);
}

bool RPI_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wdata = गवाक्षः->आन्तरिकम्;

    यदि (!(_this->egl_दत्त->eglSwapBuffers(_this->egl_दत्त->egl_display, wdata->egl_surface))) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "eglSwapBuffers failed.");
        प्रत्यागम true;
    }

    /* Wait immediately for vsync (as if we only had two buffers), for low input-lag scenarios.
     * Run your SDL program with "SDL_RPI_DOUBLE_BUFFER=1 <program_name>" to enable this. */
    यदि (wdata->double_बफर) {
        SDL_तालकम्_Mutex(wdata->vsync_cond_mutex);
        SDL_WaitCondition(wdata->vsync_cond, wdata->vsync_cond_mutex);
        SDL_UnlockMutex(wdata->vsync_cond_mutex);
    }

    प्रत्यागम true;
}

SDL_EGL_CreateContext_impl(RPI)
SDL_EGL_MakeCurrent_impl(RPI)

#यदि_अन्तः // SDL_VIDEO_DRIVER_RPI && SDL_VIDEO_OPENGL_EGL
