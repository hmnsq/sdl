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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_ANDROID) && defined(SDL_VIDEO_OPENGL_EGL)

// Android SDL video driver implementation

#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidwindow.h"

#ಅನ್ತರ್ಭಾವ "SDL_androidvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidgl.h"
#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

#ಅನ್ತರ್ಭಾವ <android/log.h>

#ಅನ್ತರ್ಭಾವ <dlfcn.h>

bool Android_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    ಆದರೆ (ಕಿಟಕಿ && context) {
        ಹಿಂತಿರುಗಿ SDL_EGL_MakeCurrent(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface, context);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_EGL_MakeCurrent(_this, ಖಾಲಿ, ಖಾಲಿ);
    }
}

SDL_GLContext Android_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_GLContext ಫಲಿತಾಂಶ;

    ಆದರೆ (!Android_Wait_ಸಕ್ರಿಯ_And_ಬೀಗ_Activity()) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಫಲಿತಾಂಶ = SDL_EGL_CreateContext(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);

    Android_UnlockActivityMutex();

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool Android_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    bool ಫಲಿತಾಂಶ;

    Android_ಬೀಗ_Activity_Mutex();

    /* The following two calls existed in the original Java code
     * If you happen to have a device that's affected by their removal,
     * please report to our bug tracker. -- Gabriel
     */

    /*_this->egl_data->eglWaitNative(EGL_CORE_NATIVE_ENGINE);
    _this->egl_data->eglWaitGL();*/
    ಫಲಿತಾಂಶ = SDL_EGL_ಅದಲುಬದಲು_Buffers(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);

    Android_UnlockActivityMutex();

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool Android_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, EGL_DEFAULT_DISPLAY);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_ANDROID
