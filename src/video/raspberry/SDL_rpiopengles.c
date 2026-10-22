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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಆದರೆ defined(SDL_VIDEO_DRIVER_RPI) && defined(SDL_VIDEO_OPENGL_EGL)

#ಅನ್ತರ್ಭಾವ "SDL_rpivideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_rpiopengles.h"

// EGL implementation of SDL OpenGL support

ಶೂನ್ಯ RPI_GLES_ಗಣ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.profile_ಮುಖವಾಡ = SDL_GL_CONTEXT_PROFILE_ES;
    _this->gl_config.major_ಆವೃತ್ತಿ = 2;
    _this->gl_config.minor_ಆವೃತ್ತಿ = 0;
}

bool RPI_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, EGL_DEFAULT_DISPLAY);
}

bool RPI_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (!(_this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Buffers(_this->egl_ದತ್ತಾಂಶ->egl_display, wdata->egl_surface))) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "eglSwapBuffers failed.");
        ಹಿಂತಿರುಗಿ true;
    }

    /* Wait immediately for vsync (as if we only had two buffers), for low input-lag scenarios.
     * Run your SDL program with "SDL_RPI_DOUBLE_BUFFER=1 <program_name>" to enable this. */
    ಆದರೆ (wdata->double_ಬಫರ್) {
        SDL_ಬೀಗ_Mutex(wdata->vsync_cond_mutex);
        SDL_WaitCondition(wdata->vsync_cond, wdata->vsync_cond_mutex);
        SDL_UnlockMutex(wdata->vsync_cond_mutex);
    }

    ಹಿಂತಿರುಗಿ true;
}

SDL_EGL_CreateContext_impl(RPI)
SDL_EGL_MakeCurrent_impl(RPI)

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RPI && SDL_VIDEO_OPENGL_EGL
