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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_ANDROID) && defined(SDL_VIDEO_OPENGL_EGL)

// Android SDL video driver implementation

#ضمن "../SDL_egl_c.h"
#ضمن "SDL_androidwindow.h"

#ضمن "SDL_androidvideo.h"
#ضمن "SDL_androidevents.h"
#ضمن "SDL_androidgl.h"
#ضمن "../../core/android/SDL_android.h"

#ضمن <android/log.h>

#ضمن <dlfcn.h>

bool Android_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context)
{
    إذا (کړکۍ && context) {
        أرجع SDL_EGL_MakeCurrent(_this, کړکۍ->دننی->egl_surface, context);
    } وإلا {
        أرجع SDL_EGL_MakeCurrent(_this, عدم, عدم);
    }
}

SDL_GLContext Android_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_GLContext پایله;

    إذا (!Android_Wait_فعال_And_قلف_Activity()) {
        أرجع عدم;
    }

    پایله = SDL_EGL_CreateContext(_this, کړکۍ->دننی->egl_surface);

    Android_UnlockActivityMutex();

    أرجع پایله;
}

bool Android_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    bool پایله;

    Android_قلف_Activity_Mutex();

    /* The following two calls existed in the original Java code
     * If you happen to have a device that's affected by their removal,
     * please report to our bug tracker. -- Gabriel
     */

    /*_this->egl_data->eglWaitNative(EGL_CORE_NATIVE_ENGINE);
    _this->egl_data->eglWaitGL();*/
    پایله = SDL_EGL_بدلون_Buffers(_this, کړکۍ->دننی->egl_surface);

    Android_UnlockActivityMutex();

    أرجع پایله;
}

bool Android_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    أرجع SDL_EGL_بارول_Library(_this, لار, EGL_DEFAULT_DISPLAY);
}

#د_که_پای // SDL_VIDEO_DRIVER_ANDROID
