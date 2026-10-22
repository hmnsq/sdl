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
#অন্তর্ভাৱ "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_ANDROID) && defined(SDL_VIDEO_OPENGL_EGL)

// Android SDL video driver implementation

#অন্তর্ভাৱ "../SDL_egl_c.h"
#অন্তর্ভাৱ "SDL_androidwindow.h"

#অন্তর্ভাৱ "SDL_androidvideo.h"
#অন্তর্ভাৱ "SDL_androidevents.h"
#অন্তর্ভাৱ "SDL_androidgl.h"
#অন্তর্ভাৱ "../../core/android/SDL_android.h"

#অন্তর্ভাৱ <android/log.h>

#অন্তর্ভাৱ <dlfcn.h>

bool Android_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    যদি (window && context) {
        ঘূৰাই SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } অন্যথা {
        ঘূৰাই SDL_EGL_MakeCurrent(_this, রিক্ত, রিক্ত);
    }
}

SDL_GLContext Android_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext result;

    যদি (!Android_WaitActiveAndLockActivity()) {
        ঘূৰাই রিক্ত;
    }

    result = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    Android_UnlockActivityMutex();

    ঘূৰাই result;
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

    ঘূৰাই result;
}

bool Android_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path)
{
    ঘূৰাই SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

#endif // SDL_VIDEO_DRIVER_ANDROID
