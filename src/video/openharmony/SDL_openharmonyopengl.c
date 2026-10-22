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

#إذا defined(SDL_VIDEO_DRIVER_OPENHARMONY) && defined(SDL_VIDEO_OPENGL_EGL)

// OpenHarmony/HarmonyOS SDL video driver implementation

#ضمن "../SDL_egl_c.h"
#ضمن "SDL_openharmonywindow.h"

#ضمن "SDL_openharmonyvideo.h"
#ضمن "SDL_openharmonyevents.h"
#ضمن "SDL_openharmonyopengl.h"
#ضمن "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context)
{
    إذا (پنجره && context) {
        أرجع SDL_EGL_MakeCurrent(_this, پنجره->داخلی->egl_surface, context);
    } وإلا {
        أرجع SDL_EGL_MakeCurrent(_this, عدم, عدم);
    }
}

SDL_GLContext OPENHARMONY_GLES_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_GLContext نتیجه;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return NULL;
    //}

    نتیجه = SDL_EGL_CreateContext(_this, پنجره->داخلی->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    أرجع نتیجه;
}

bool OPENHARMONY_GLES_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    bool نتیجه;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //OPENHARMONY_LockActivityMutex();

    نتیجه = SDL_EGL_جابجا_Buffers(_this, پنجره->داخلی->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    أرجع نتیجه;
}

bool OPENHARMONY_GLES_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
    أرجع SDL_EGL_بارگیری_Library(_this, مسیر, EGL_DEFAULT_DISPLAY);
}

#پایان_اگر // SDL_VIDEO_DRIVER_OPENHARMONY
