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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_RPI) && defined(SDL_VIDEO_OPENGL_EGL)

#అన్తర్భావ "SDL_rpivideo.h"
#అన్తర్భావ "SDL_rpiopengles.h"

// EGL implementation of SDL OpenGL support

శూన్య RPI_GLES_సమితి_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.profile_ముసుగు = SDL_GL_CONTEXT_PROFILE_ES;
    _this->gl_config.major_సంస్కరణ = 2;
    _this->gl_config.minor_సంస్కరణ = 0;
}

bool RPI_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    తిరిగి SDL_EGL_ఎక్కించు_Library(_this, మార్గం, EGL_DEFAULT_DISPLAY);
}

bool RPI_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wdata = కిటికీ->అంతర్గత;

    ఒకవేళ (!(_this->egl_దత్తాంశం->egl_మార్పిడి_Buffers(_this->egl_దత్తాంశం->egl_display, wdata->egl_surface))) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "eglSwapBuffers failed.");
        తిరిగి true;
    }

    /* Wait immediately for vsync (as if we only had two buffers), for low input-lag scenarios.
     * Run your SDL program with "SDL_RPI_DOUBLE_BUFFER=1 <program_name>" to enable this. */
    ఒకవేళ (wdata->double_బఫరు) {
        SDL_తాళం_Mutex(wdata->vsync_cond_mutex);
        SDL_WaitCondition(wdata->vsync_cond, wdata->vsync_cond_mutex);
        SDL_UnlockMutex(wdata->vsync_cond_mutex);
    }

    తిరిగి true;
}

SDL_EGL_CreateContext_impl(RPI)
SDL_EGL_MakeCurrent_impl(RPI)

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RPI && SDL_VIDEO_OPENGL_EGL
