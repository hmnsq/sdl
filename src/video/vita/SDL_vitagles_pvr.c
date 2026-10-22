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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <psp2/kernel/modulemgr.h>
#అన్తర్భావ <gpu_es4/psp2_pvr_hint.h>

#అన్తర్భావ "SDL_vitavideo.h"
#అన్తర్భావ "../SDL_egl_c.h"

#నిర్వచించు MAX_మార్గం 256 // vita limits are somehow wrong

bool VITA_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    PVRSRV_PSP2_APPHINT hint;
    స్థిరరాశి అక్షరం *default_మార్గం = "app0:module";
    అక్షరం లక్ష్యం_మార్గం[MAX_మార్గం];

    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        స్థిరరాశి అక్షరం *override = SDL_GetHint(SDL_HINT_VITA_MODULE_మార్గం);

        ఒకవేళ (override && *override) {
            default_మార్గం = override;
        }

        sce_Kernel_ఎక్కించు_ప్రారంభం_Module("vs0:sys/external/libfios2.suprx", 0, ఖాళీ, 0, ఖాళీ, ఖాళీ);
        sce_Kernel_ఎక్కించు_ప్రారంభం_Module("vs0:sys/external/libc.suprx", 0, ఖాళీ, 0, ఖాళీ, ఖాళీ);

        SDL_snprintf(లక్ష్యం_మార్గం, MAX_మార్గం, "%s/%s", default_మార్గం, "libgpu_es4_ext.suprx");
        sce_Kernel_ఎక్కించు_ప్రారంభం_Module(లక్ష్యం_మార్గం, 0, ఖాళీ, 0, ఖాళీ, ఖాళీ);

        SDL_snprintf(లక్ష్యం_మార్గం, MAX_మార్గం, "%s/%s", default_మార్గం, "libIMGEGL.suprx");
        sce_Kernel_ఎక్కించు_ప్రారంభం_Module(లక్ష్యం_మార్గం, 0, ఖాళీ, 0, ఖాళీ, ఖాళీ);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_మార్గం, "%s/%s", default_మార్గం, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_మార్గం, "%s/%s", default_మార్గం, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_కిటికీ_System, MAX_మార్గం, "%s/%s", default_మార్గం, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    తిరిగి SDL_EGL_ఎక్కించు_Library(_this, మార్గం, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    తిరిగి SDL_EGL_CreateContext(_this, కిటికీ->అంతర్గత->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    ఒకవేళ (కిటికీ && context) {
        తిరిగి SDL_EGL_MakeCurrent(_this, కిటికీ->అంతర్గత->egl_surface, context);
    } లేకపోతే {
        తిరిగి SDL_EGL_MakeCurrent(_this, ఖాళీ, ఖాళీ);
    }
}

bool VITA_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    ఒకవేళ (videodata->ime_చురుకైన) {
        sceImeUpdate();
    }
    తిరిగి SDL_EGL_మార్పిడి_Buffers(_this, కిటికీ->అంతర్గత->egl_surface);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
