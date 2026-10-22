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

#تعریف_کرو MAX_راستہ 256 // vita limits are somehow wrong

bool VITA_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    PVRSRV_PSP2_APPHINT hint;
    ثابت حرف *default_راستہ = "app0:module";
    حرف ہدف_راستہ[MAX_راستہ];

    اگر (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ثابت حرف *override = SDL_GetHint(SDL_HINT_VITA_MODULE_راستہ);

        اگر (override && *override) {
            default_راستہ = override;
        }

        sce_Kernel_بھرو_آغاز_Module("vs0:sys/external/libfios2.suprx", 0, تہی, 0, تہی, تہی);
        sce_Kernel_بھرو_آغاز_Module("vs0:sys/external/libc.suprx", 0, تہی, 0, تہی, تہی);

        SDL_snprintf(ہدف_راستہ, MAX_راستہ, "%s/%s", default_راستہ, "libgpu_es4_ext.suprx");
        sce_Kernel_بھرو_آغاز_Module(ہدف_راستہ, 0, تہی, 0, تہی, تہی);

        SDL_snprintf(ہدف_راستہ, MAX_راستہ, "%s/%s", default_راستہ, "libIMGEGL.suprx");
        sce_Kernel_بھرو_آغاز_Module(ہدف_راستہ, 0, تہی, 0, تہی, تہی);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_راستہ, "%s/%s", default_راستہ, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_راستہ, "%s/%s", default_راستہ, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_کھڑکی_System, MAX_راستہ, "%s/%s", default_راستہ, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    واپس SDL_EGL_بھرو_Library(_this, راستہ, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    واپس SDL_EGL_CreateContext(_this, کھڑکی->اندرونی_2->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    اگر (کھڑکی && context) {
        واپس SDL_EGL_MakeCurrent(_this, کھڑکی->اندرونی_2->egl_surface, context);
    } ورنہ {
        واپس SDL_EGL_MakeCurrent(_this, تہی, تہی);
    }
}

bool VITA_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    اگر (videodata->ime_فعال) {
        sceImeUpdate();
    }
    واپس SDL_EGL_تبادلہ_Buffers(_this, کھڑکی->اندرونی_2->egl_surface);
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
