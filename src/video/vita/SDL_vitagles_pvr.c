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

#ಯದಿ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <psp2/kernel/modulemgr.h>
#ಅನ್ತರ್ಭಾವ <gpu_es4/psp2_pvr_hint.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

#define MAX_PATH 256 // vita limits are somehow wrong

bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    PVRSRV_PSP2_APPHINT hint;
    ಧ್ರುವ ವರ್ಣ *default_path = "app0:module";
    ವರ್ಣ target_path[MAX_PATH];

    ಯದಿ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ಧ್ರುವ ವರ್ಣ *override = SDL_GetHint(SDL_HINT_VITA_MODULE_PATH);

        ಯದಿ (override && *override) {
            default_path = override;
        }

        sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);
        sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libgpu_es4_ext.suprx");
        sceKernelLoadStartModule(target_path, 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libIMGEGL.suprx");
        sceKernelLoadStartModule(target_path, 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_PATH, "%s/%s", default_path, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_PATH, "%s/%s", default_path, "libGLESv2.suprx");
        SDL_snprintf(hint.szWindowSystem, MAX_PATH, "%s/%s", default_path, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    ಪ್ರತ್ಯಾಗಮ SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ SDL_EGL_CreateContext(_this, window->internal->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    ಯದಿ (window && context) {
        ಪ್ರತ್ಯಾಗಮ SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_EGL_MakeCurrent(_this, ರಿಕ್ತ, ರಿಕ್ತ);
    }
}

bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    ಯದಿ (videodata->ime_active) {
        sceImeUpdate();
    }
    ಪ್ರತ್ಯಾಗಮ SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);
}

#endif // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
