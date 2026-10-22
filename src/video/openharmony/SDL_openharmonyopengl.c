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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_OPENHARMONY) && defined(SDL_VIDEO_OPENGL_EGL)

// OpenHarmony/HarmonyOS SDL video driver implementation

#अन्तर्भाव "../SDL_egl_c.h"
#अन्तर्भाव "SDL_openharmonywindow.h"

#अन्तर्भाव "SDL_openharmonyvideo.h"
#अन्तर्भाव "SDL_openharmonyevents.h"
#अन्तर्भाव "SDL_openharmonyopengl.h"
#अन्तर्भाव "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    यदि (गवाक्षः && context) {
        प्रत्यागम SDL_EGL_MakeCurrent(_this, गवाक्षः->आन्तरिकम्->egl_surface, context);
    } अन्यथा {
        प्रत्यागम SDL_EGL_MakeCurrent(_this, रिक्त, रिक्त);
    }
}

SDL_GLContext OPENHARMONY_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_GLContext परिणाम;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return NULL;
    //}

    परिणाम = SDL_EGL_CreateContext(_this, गवाक्षः->आन्तरिकम्->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    प्रत्यागम परिणाम;
}

bool OPENHARMONY_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    bool परिणाम;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //OPENHARMONY_LockActivityMutex();

    परिणाम = SDL_EGL_SwapBuffers(_this, गवाक्षः->आन्तरिकम्->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    प्रत्यागम परिणाम;
}

bool OPENHARMONY_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    प्रत्यागम SDL_EGL_आरोपय_Library(_this, मार्गः, EGL_DEFAULT_DISPLAY);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_OPENHARMONY
