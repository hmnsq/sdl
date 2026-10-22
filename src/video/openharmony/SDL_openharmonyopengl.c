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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_OPENHARMONY) && defined(SDL_VIDEO_OPENGL_EGL)

// OpenHarmony/HarmonyOS SDL video driver implementation

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonywindow.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyopengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    ਜੇ (ਖਿੜਕੀ && context) {
        ਵਾਪਸ SDL_EGL_MakeCurrent(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface, context);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_EGL_MakeCurrent(_this, ਨਿਰਾ, ਨਿਰਾ);
    }
}

SDL_GLContext OPENHARMONY_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_GLContext ਨਤੀਜਾ;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return NULL;
    //}

    ਨਤੀਜਾ = SDL_EGL_CreateContext(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool OPENHARMONY_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    bool ਨਤੀਜਾ;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //OPENHARMONY_LockActivityMutex();

    ਨਤੀਜਾ = SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool OPENHARMONY_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਵਾਪਸ SDL_EGL_ਲੱਦੋ_Library(_this, ਰਸਤਾ, EGL_DEFAULT_DISPLAY);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OPENHARMONY
