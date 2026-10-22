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

#إذا defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <psp2/kernel/modulemgr.h>
#ضمن <gpu_es4/psp2_pvr_hint.h>

#ضمن "SDL_vitavideo.h"
#ضمن "../SDL_egl_c.h"

#تعریف_کړه MAX_لار 256 // vita limits are somehow wrong

bool VITA_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    PVRSRV_PSP2_APPHINT hint;
    ثابت حرف *default_لار = "app0:module";
    حرف موخه_لار[MAX_لار];

    إذا (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ثابت حرف *override = SDL_GetHint(SDL_HINT_VITA_MODULE_لار);

        إذا (override && *override) {
            default_لار = override;
        }

        sce_Kernel_بارول_پیل_Module("vs0:sys/external/libfios2.suprx", 0, عدم, 0, عدم, عدم);
        sce_Kernel_بارول_پیل_Module("vs0:sys/external/libc.suprx", 0, عدم, 0, عدم, عدم);

        SDL_snprintf(موخه_لار, MAX_لار, "%s/%s", default_لار, "libgpu_es4_ext.suprx");
        sce_Kernel_بارول_پیل_Module(موخه_لار, 0, عدم, 0, عدم, عدم);

        SDL_snprintf(موخه_لار, MAX_لار, "%s/%s", default_لار, "libIMGEGL.suprx");
        sce_Kernel_بارول_پیل_Module(موخه_لار, 0, عدم, 0, عدم, عدم);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_لار, "%s/%s", default_لار, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_لار, "%s/%s", default_لار, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_کړکۍ_System, MAX_لار, "%s/%s", default_لار, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    أرجع SDL_EGL_بارول_Library(_this, لار, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    أرجع SDL_EGL_CreateContext(_this, کړکۍ->دننی->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context)
{
    إذا (کړکۍ && context) {
        أرجع SDL_EGL_MakeCurrent(_this, کړکۍ->دننی->egl_surface, context);
    } وإلا {
        أرجع SDL_EGL_MakeCurrent(_this, عدم, عدم);
    }
}

bool VITA_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    إذا (videodata->ime_فعال) {
        sceImeUpdate();
    }
    أرجع SDL_EGL_بدلون_Buffers(_this, کړکۍ->دننی->egl_surface);
}

#د_که_پای // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
