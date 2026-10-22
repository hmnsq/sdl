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

#अगर defined(SDL_VIDEO_DRIVER_OPENHARMONY) && defined(SDL_VIDEO_OPENGL_EGL)

// OpenHarmony/HarmonyOS SDL video driver implementation

#समावेश "../SDL_egl_c.h"
#समावेश "SDL_openharmonywindow.h"

#समावेश "SDL_openharmonyvideo.h"
#समावेश "SDL_openharmonyevents.h"
#समावेश "SDL_openharmonyopengl.h"
#समावेश "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    अगर (window && context) {
        वापस SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } अन्यथा {
        वापस SDL_EGL_MakeCurrent(_this, शून्य, शून्य);
    }
}

SDL_GLContext OPENHARMONY_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext परिणाम;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return NULL;
    //}

    परिणाम = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    वापस परिणाम;
}

bool OPENHARMONY_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    bool परिणाम;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //OPENHARMONY_LockActivityMutex();

    परिणाम = SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    वापस परिणाम;
}

bool OPENHARMONY_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    वापस SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_OPENHARMONY
