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

#اگر defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#شامل <stdlib.h>
#شامل <string.h>
#شامل <psp2/kernel/modulemgr.h>
#شامل <gpu_es4/psp2_pvr_hint.h>

#شامل "SDL_vitavideo.h"
#شامل "../SDL_egl_c.h"

#define MAX_PATH 256 // vita limits are somehow wrong

bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *path)
{
    PVRSRV_PSP2_APPHINT hint;
    ثابت نویسه *default_path = "app0:module";
    نویسه target_path[MAX_PATH];

    اگر (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ثابت نویسه *override = SDL_GetHint(SDL_HINT_VITA_MODULE_PATH);

        اگر (override && *override) {
            default_path = override;
        }

        sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, پوچ, 0, پوچ, پوچ);
        sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, پوچ, 0, پوچ, پوچ);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libgpu_es4_ext.suprx");
        sceKernelLoadStartModule(target_path, 0, پوچ, 0, پوچ, پوچ);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libIMGEGL.suprx");
        sceKernelLoadStartModule(target_path, 0, پوچ, 0, پوچ, پوچ);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_PATH, "%s/%s", default_path, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_PATH, "%s/%s", default_path, "libGLESv2.suprx");
        SDL_snprintf(hint.szWindowSystem, MAX_PATH, "%s/%s", default_path, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    بازگشت SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    بازگشت SDL_EGL_CreateContext(_this, window->internal->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    اگر (window && context) {
        بازگشت SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } وگرنه {
        بازگشت SDL_EGL_MakeCurrent(_this, پوچ, پوچ);
    }
}

bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    اگر (videodata->ime_active) {
        sceImeUpdate();
    }
    بازگشت SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);
}

#endif // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
