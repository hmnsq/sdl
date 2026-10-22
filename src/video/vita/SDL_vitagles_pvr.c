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

#यदि defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <psp2/kernel/modulemgr.h>
#अन्तर्भाव <gpu_es4/psp2_pvr_hint.h>

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "../SDL_egl_c.h"

#परिभाषय MAX_मार्गः 256 // vita limits are somehow wrong

bool VITA_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    PVRSRV_PSP2_APPHINT hint;
    ध्रुव वर्ण *default_मार्गः = "app0:module";
    वर्ण target_मार्गः[MAX_मार्गः];

    यदि (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ध्रुव वर्ण *override = SDL_GetHint(SDL_HINT_VITA_MODULE_मार्गः);

        यदि (override && *override) {
            default_मार्गः = override;
        }

        sce_Kernel_आरोपय_Start_Module("vs0:sys/external/libfios2.suprx", 0, रिक्त, 0, रिक्त, रिक्त);
        sce_Kernel_आरोपय_Start_Module("vs0:sys/external/libc.suprx", 0, रिक्त, 0, रिक्त, रिक्त);

        SDL_snprintf(target_मार्गः, MAX_मार्गः, "%s/%s", default_मार्गः, "libgpu_es4_ext.suprx");
        sce_Kernel_आरोपय_Start_Module(target_मार्गः, 0, रिक्त, 0, रिक्त, रिक्त);

        SDL_snprintf(target_मार्गः, MAX_मार्गः, "%s/%s", default_मार्गः, "libIMGEGL.suprx");
        sce_Kernel_आरोपय_Start_Module(target_मार्गः, 0, रिक्त, 0, रिक्त, रिक्त);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_मार्गः, "%s/%s", default_मार्गः, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_मार्गः, "%s/%s", default_मार्गः, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_गवाक्षः_System, MAX_मार्गः, "%s/%s", default_मार्गः, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    प्रत्यागम SDL_EGL_आरोपय_Library(_this, मार्गः, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम SDL_EGL_CreateContext(_this, गवाक्षः->आन्तरिकम्->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    यदि (गवाक्षः && context) {
        प्रत्यागम SDL_EGL_MakeCurrent(_this, गवाक्षः->आन्तरिकम्->egl_surface, context);
    } अन्यथा {
        प्रत्यागम SDL_EGL_MakeCurrent(_this, रिक्त, रिक्त);
    }
}

bool VITA_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    यदि (videodata->ime_सक्रिय) {
        sceImeUpdate();
    }
    प्रत्यागम SDL_EGL_SwapBuffers(_this, गवाक्षः->आन्तरिकम्->egl_surface);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
