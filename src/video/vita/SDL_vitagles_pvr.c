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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <psp2/kernel/modulemgr.h>
#ಅನ್ತರ್ಭಾವ <gpu_es4/psp2_pvr_hint.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ಮಾರ್ಗ 256 // vita limits are somehow wrong

bool VITA_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    PVRSRV_PSP2_APPHINT hint;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *default_ಮಾರ್ಗ = "app0:module";
    ಅಕ್ಷರ ಗುರಿ_ಮಾರ್ಗ[MAX_ಮಾರ್ಗ];

    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *override = SDL_GetHint(SDL_HINT_VITA_MODULE_ಮಾರ್ಗ);

        ಆದರೆ (override && *override) {
            default_ಮಾರ್ಗ = override;
        }

        sce_Kernel_ತುಂಬು_ಆರಂಭ_Module("vs0:sys/external/libfios2.suprx", 0, ಖಾಲಿ, 0, ಖಾಲಿ, ಖಾಲಿ);
        sce_Kernel_ತುಂಬು_ಆರಂಭ_Module("vs0:sys/external/libc.suprx", 0, ಖಾಲಿ, 0, ಖಾಲಿ, ಖಾಲಿ);

        SDL_snprintf(ಗುರಿ_ಮಾರ್ಗ, MAX_ಮಾರ್ಗ, "%s/%s", default_ಮಾರ್ಗ, "libgpu_es4_ext.suprx");
        sce_Kernel_ತುಂಬು_ಆರಂಭ_Module(ಗುರಿ_ಮಾರ್ಗ, 0, ಖಾಲಿ, 0, ಖಾಲಿ, ಖಾಲಿ);

        SDL_snprintf(ಗುರಿ_ಮಾರ್ಗ, MAX_ಮಾರ್ಗ, "%s/%s", default_ಮಾರ್ಗ, "libIMGEGL.suprx");
        sce_Kernel_ತುಂಬು_ಆರಂಭ_Module(ಗುರಿ_ಮಾರ್ಗ, 0, ಖಾಲಿ, 0, ಖಾಲಿ, ಖಾಲಿ);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_ಮಾರ್ಗ, "%s/%s", default_ಮಾರ್ಗ, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_ಮಾರ್ಗ, "%s/%s", default_ಮಾರ್ಗ, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_ಕಿಟಕಿ_System, MAX_ಮಾರ್ಗ, "%s/%s", default_ಮಾರ್ಗ, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_CreateContext(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    ಆದರೆ (ಕಿಟಕಿ && context) {
        ಹಿಂತಿರುಗಿ SDL_EGL_MakeCurrent(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface, context);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_EGL_MakeCurrent(_this, ಖಾಲಿ, ಖಾಲಿ);
    }
}

bool VITA_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    ಆದರೆ (videodata->ime_ಸಕ್ರಿಯ) {
        sceImeUpdate();
    }
    ಹಿಂತಿರುಗಿ SDL_EGL_ಅದಲುಬದಲು_Buffers(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
