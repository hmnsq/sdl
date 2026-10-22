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

#எனில் defined(SDL_VIDEO_DRIVER_OPENHARMONY) && defined(SDL_VIDEO_OPENGL_EGL)

// OpenHarmony/HarmonyOS SDL video driver implementation

#அந்தர்பாவ "../SDL_egl_c.h"
#அந்தர்பாவ "SDL_openharmonywindow.h"

#அந்தர்பாவ "SDL_openharmonyvideo.h"
#அந்தர்பாவ "SDL_openharmonyevents.h"
#அந்தர்பாவ "SDL_openharmonyopengl.h"
#அந்தர்பாவ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    எனில் (window && context) {
        திரும்பு SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } இல்லையெனில் {
        திரும்பு SDL_EGL_MakeCurrent(_this, வெற்று, வெற்று);
    }
}

SDL_GLContext OPENHARMONY_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext result;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return NULL;
    //}

    result = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    திரும்பு result;
}

bool OPENHARMONY_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    bool result;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //OPENHARMONY_LockActivityMutex();

    result = SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);

    //OPENHARMONY_UnlockActivityMutex();

    திரும்பு result;
}

bool OPENHARMONY_GLES_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    திரும்பு SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
