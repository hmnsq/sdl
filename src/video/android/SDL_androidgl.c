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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_ANDROID) && defined(SDL_VIDEO_OPENGL_EGL)

// Android SDL video driver implementation

#شامل "../SDL_egl_c.h"
#شامل "SDL_androidwindow.h"

#شامل "SDL_androidvideo.h"
#شامل "SDL_androidevents.h"
#شامل "SDL_androidgl.h"
#شامل "../../core/android/SDL_android.h"

#شامل <android/log.h>

#شامل <dlfcn.h>

bool Android_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    اگر (کھڑکی && context) {
        واپس SDL_EGL_MakeCurrent(_this, کھڑکی->اندرونی_2->egl_surface, context);
    } ورنہ {
        واپس SDL_EGL_MakeCurrent(_this, تہی, تہی);
    }
}

SDL_GLContext Android_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_GLContext نتیجہ;

    اگر (!Android_Wait_فعال_And_تالا_Activity()) {
        واپس تہی;
    }

    نتیجہ = SDL_EGL_CreateContext(_this, کھڑکی->اندرونی_2->egl_surface);

    Android_UnlockActivityMutex();

    واپس نتیجہ;
}

bool Android_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    bool نتیجہ;

    Android_تالا_Activity_Mutex();

    /* The following two calls existed in the original Java code
     * If you happen to have a device that's affected by their removal,
     * please report to our bug tracker. -- Gabriel
     */

    /*_this->egl_data->eglWaitNative(EGL_CORE_NATIVE_ENGINE);
    _this->egl_data->eglWaitGL();*/
    نتیجہ = SDL_EGL_تبادلہ_Buffers(_this, کھڑکی->اندرونی_2->egl_surface);

    Android_UnlockActivityMutex();

    واپس نتیجہ;
}

bool Android_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    واپس SDL_EGL_بھرو_Library(_this, راستہ, EGL_DEFAULT_DISPLAY);
}

#اگر_ختم // SDL_VIDEO_DRIVER_ANDROID
