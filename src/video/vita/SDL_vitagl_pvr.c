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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR) && defined(SDL_VIDEO_VITA_PVR_OGL)
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <psp2/kernel/modulemgr.h>
#అన్తర్భావ <gpu_es4/psp2_pvr_hint.h>
#అన్తర్భావ <gl4esinit.h>

#అన్తర్భావ "SDL_vitavideo.h"
#అన్తర్భావ "../SDL_egl_c.h"

#నిర్వచించు MAX_మార్గం 256 // vita limits are somehow wrong

// Defaults
స్థిర పూర్ణాంకం FB_వెడల్పు = 960;
స్థిర పూర్ణాంకం FB_ఎత్తు = 544;

స్థిర శూన్య getFBSize(పూర్ణాంకం *వెడల్పు, పూర్ణాంకం *ఎత్తు)
{
    *వెడల్పు = FB_వెడల్పు;
    *ఎత్తు = FB_ఎత్తు;
}

bool VITA_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    PVRSRV_PSP2_APPHINT hint;
    అక్షరం *default_మార్గం = "app0:module";
    అక్షరం లక్ష్యం_మార్గం[MAX_మార్గం];

    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        స్థిరరాశి అక్షరం *override = SDL_GetHint(SDL_HINT_VITA_MODULE_మార్గం);

        ఒకవేళ (override && *override) {
            default_మార్గం = override;
        }

        sce_Kernel_ఎక్కించు_ప్రారంభం_Module("vs0:sys/external/libfios2.suprx", 0, ఖాళీ, 0, ఖాళీ, ఖాళీ);
        sce_Kernel_ఎక్కించు_ప్రారంభం_Module("vs0:sys/external/libc.suprx", 0, ఖాళీ, 0, ఖాళీ, ఖాళీ);

        SDL_snprintf(లక్ష్యం_మార్గం, MAX_మార్గం, "%s/%s", default_మార్గం, "libGL.suprx");
        sce_Kernel_ఎక్కించు_ప్రారంభం_Module(లక్ష్యం_మార్గం, 0, ఖాళీ, 0, ఖాళీ, ఖాళీ);

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

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    అక్షరం gl_సంస్కరణ[3];
    SDL_GLContext context = ఖాళీ;
    పూర్ణాంకం తాత్కాలిక_major = _this->gl_config.major_సంస్కరణ;
    పూర్ణాంకం తాత్కాలిక_minor = _this->gl_config.minor_సంస్కరణ;
    పూర్ణాంకం తాత్కాలిక_profile = _this->gl_config.profile_ముసుగు;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_సంస్కరణ = 2;
    _this->gl_config.minor_సంస్కరణ = 0;
    _this->gl_config.profile_ముసుగు = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, కిటికీ->అంతర్గత->egl_surface);

    ఒకవేళ (context != ఖాళీ) {
        FB_వెడల్పు = కిటికీ->w;
        FB_ఎత్తు = కిటికీ->h;
        సమితి_getprocaddress((శూన్య *(*)(స్థిరరాశి అక్షరం *))egl_Get_Proc_చిరునామా);
        సమితి_getmainfbsize(getFBSize);
        SDL_snprintf(gl_సంస్కరణ, 3, "%d%d", తాత్కాలిక_major, తాత్కాలిక_minor);
        gl4es_setenv("LIBGL_NOTEXRECT", "1", 1); // Currently broken in driver
        gl4es_setenv("LIBGL_GL", gl_సంస్కరణ, 1);
        initialize_gl4es();
    }

    // Restore gl_config
    _this->gl_config.major_సంస్కరణ = తాత్కాలిక_major;
    _this->gl_config.minor_సంస్కరణ = తాత్కాలిక_minor;
    _this->gl_config.profile_ముసుగు = తాత్కాలిక_profile;

    తిరిగి context;
}

SDL_Function_సూచిక VITA_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    తిరిగి gl4es_Get_Proc_చిరునామా(proc);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
