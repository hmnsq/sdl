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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_OPENHARMONY) && defined(SDL_VIDEO_OPENGL_EGL)

// OpenHarmony/HarmonyOS SDL video driver implementation

#అన్తర్భావ "../SDL_egl_c.h"
#అన్తర్భావ "SDL_openharmonywindow.h"

#అన్తర్భావ "SDL_openharmonyvideo.h"
#అన్తర్భావ "SDL_openharmonyevents.h"
#అన్తర్భావ "SDL_openharmonyopengl.h"
#అన్తర్భావ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    ఒకవేళ (కిటికీ && context) {
        తిరిగి SDL_EGL_MakeCurrent(_this, కిటికీ->అంతర్గత->egl_surface, context);
    } లేకపోతే {
        తిరిగి SDL_EGL_MakeCurrent(_this, ఖాళీ, ఖాళీ);
    }
}

SDL_GLContext OPENHARMONY_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_GLContext ఫలితం;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return NULL;
    //}

    ఫలితం = SDL_EGL_CreateContext(_this, కిటికీ->అంతర్గత->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    తిరిగి ఫలితం;
}

bool OPENHARMONY_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    bool ఫలితం;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //OPENHARMONY_LockActivityMutex();

    ఫలితం = SDL_EGL_మార్పిడి_Buffers(_this, కిటికీ->అంతర్గత->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    తిరిగి ఫలితం;
}

bool OPENHARMONY_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    తిరిగి SDL_EGL_ఎక్కించు_Library(_this, మార్గం, EGL_DEFAULT_DISPLAY);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OPENHARMONY
