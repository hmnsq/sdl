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

#ಯದಿ defined(SDL_VIDEO_DRIVER_ANDROID) && defined(SDL_VIDEO_OPENGL_EGL)

// Android SDL video driver implementation

#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidwindow.h"

#ಅನ್ತರ್ಭಾವ "SDL_androidvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidgl.h"
#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

#ಅನ್ತರ್ಭಾವ <android/log.h>

#ಅನ್ತರ್ಭಾವ <dlfcn.h>

bool Android_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    ಯದಿ (window && context) {
        ಪ್ರತ್ಯಾಗಮ SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_EGL_MakeCurrent(_this, ರಿಕ್ತ, ರಿಕ್ತ);
    }
}

SDL_GLContext Android_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext result;

    ಯದಿ (!Android_WaitActiveAndLockActivity()) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    result = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    Android_UnlockActivityMutex();

    ಪ್ರತ್ಯಾಗಮ result;
}

bool Android_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    bool result;

    Android_LockActivityMutex();

    /* The following two calls existed in the original Java code
     * If you happen to have a device that's affected by their removal,
     * please report to our bug tracker. -- Gabriel
     */

    /*_this->egl_data->eglWaitNative(EGL_CORE_NATIVE_ENGINE);
    _this->egl_data->eglWaitGL();*/
    result = SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);

    Android_UnlockActivityMutex();

    ಪ್ರತ್ಯಾಗಮ result;
}

bool Android_GLES_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    ಪ್ರತ್ಯಾಗಮ SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

#endif // SDL_VIDEO_DRIVER_ANDROID
