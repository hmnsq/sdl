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

#ਜੇ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/kernel/modulemgr.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <gpu_es4/psp2_pvr_hint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਰਸਤਾ 256 // vita limits are somehow wrong

bool VITA_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    PVRSRV_PSP2_APPHINT hint;
    ਅਚਲ ਅੱਖਰ *default_ਰਸਤਾ = "app0:module";
    ਅੱਖਰ ਨਿਸ਼ਾਨਾ_ਰਸਤਾ[MAX_ਰਸਤਾ];

    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ਅਚਲ ਅੱਖਰ *override = SDL_GetHint(SDL_HINT_VITA_MODULE_ਰਸਤਾ);

        ਜੇ (override && *override) {
            default_ਰਸਤਾ = override;
        }

        sce_Kernel_ਲੱਦੋ_ਸ਼ੁਰੂ_Module("vs0:sys/external/libfios2.suprx", 0, ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);
        sce_Kernel_ਲੱਦੋ_ਸ਼ੁਰੂ_Module("vs0:sys/external/libc.suprx", 0, ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);

        SDL_snprintf(ਨਿਸ਼ਾਨਾ_ਰਸਤਾ, MAX_ਰਸਤਾ, "%s/%s", default_ਰਸਤਾ, "libgpu_es4_ext.suprx");
        sce_Kernel_ਲੱਦੋ_ਸ਼ੁਰੂ_Module(ਨਿਸ਼ਾਨਾ_ਰਸਤਾ, 0, ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);

        SDL_snprintf(ਨਿਸ਼ਾਨਾ_ਰਸਤਾ, MAX_ਰਸਤਾ, "%s/%s", default_ਰਸਤਾ, "libIMGEGL.suprx");
        sce_Kernel_ਲੱਦੋ_ਸ਼ੁਰੂ_Module(ਨਿਸ਼ਾਨਾ_ਰਸਤਾ, 0, ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_ਰਸਤਾ, "%s/%s", default_ਰਸਤਾ, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_ਰਸਤਾ, "%s/%s", default_ਰਸਤਾ, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_ਖਿੜਕੀ_System, MAX_ਰਸਤਾ, "%s/%s", default_ਰਸਤਾ, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    ਵਾਪਸ SDL_EGL_ਲੱਦੋ_Library(_this, ਰਸਤਾ, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ SDL_EGL_CreateContext(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    ਜੇ (ਖਿੜਕੀ && context) {
        ਵਾਪਸ SDL_EGL_MakeCurrent(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface, context);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_EGL_MakeCurrent(_this, ਨਿਰਾ, ਨਿਰਾ);
    }
}

bool VITA_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (videodata->ime_ਸਰਗਰਮ) {
        sceImeUpdate();
    }
    ਵਾਪਸ SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
