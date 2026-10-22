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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_ANDROID) && defined(SDL_VIDEO_OPENGL_EGL)

// Android SDL video driver implementation

#அந்தர்பாவ "../SDL_egl_c.h"
#அந்தர்பாவ "SDL_androidwindow.h"

#அந்தர்பாவ "SDL_androidvideo.h"
#அந்தர்பாவ "SDL_androidevents.h"
#அந்தர்பாவ "SDL_androidgl.h"
#அந்தர்பாவ "../../core/android/SDL_android.h"

#அந்தர்பாவ <android/log.h>

#அந்தர்பாவ <dlfcn.h>

bool Android_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    எனில் (window && context) {
        திரும்பு SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } இல்லையெனில் {
        திரும்பு SDL_EGL_MakeCurrent(_this, வெற்று, வெற்று);
    }
}

SDL_GLContext Android_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext result;

    எனில் (!Android_WaitActiveAndLockActivity()) {
        திரும்பு வெற்று;
    }

    result = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    Android_UnlockActivityMutex();

    திரும்பு result;
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

    திரும்பு result;
}

bool Android_GLES_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    திரும்பு SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

#endif // SDL_VIDEO_DRIVER_ANDROID
