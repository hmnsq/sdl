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

#إذا defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR) && defined(SDL_VIDEO_VITA_PVR_OGL)
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <psp2/kernel/modulemgr.h>
#ضمن <gpu_es4/psp2_pvr_hint.h>
#ضمن <gl4esinit.h>

#ضمن "SDL_vitavideo.h"
#ضمن "../SDL_egl_c.h"

#تعریف_کرو MAX_رستہ 256 // vita limits are somehow wrong

// Defaults
ساكن صحيح FB_چوڑائی = 960;
ساكن صحيح FB_اچائی = 544;

ساكن فراغ getFBSize(صحيح *چوڑائی, صحيح *اچائی)
{
    *چوڑائی = FB_چوڑائی;
    *اچائی = FB_اچائی;
}

bool VITA_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    PVRSRV_PSP2_APPHINT hint;
    حرف *default_رستہ = "app0:module";
    حرف نشانہ_رستہ[MAX_رستہ];

    إذا (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ثابت حرف *override = SDL_GetHint(SDL_HINT_VITA_MODULE_رستہ);

        إذا (override && *override) {
            default_رستہ = override;
        }

        sce_Kernel_لدو_شروع_Module("vs0:sys/external/libfios2.suprx", 0, عدم, 0, عدم, عدم);
        sce_Kernel_لدو_شروع_Module("vs0:sys/external/libc.suprx", 0, عدم, 0, عدم, عدم);

        SDL_snprintf(نشانہ_رستہ, MAX_رستہ, "%s/%s", default_رستہ, "libGL.suprx");
        sce_Kernel_لدو_شروع_Module(نشانہ_رستہ, 0, عدم, 0, عدم, عدم);

        SDL_snprintf(نشانہ_رستہ, MAX_رستہ, "%s/%s", default_رستہ, "libgpu_es4_ext.suprx");
        sce_Kernel_لدو_شروع_Module(نشانہ_رستہ, 0, عدم, 0, عدم, عدم);

        SDL_snprintf(نشانہ_رستہ, MAX_رستہ, "%s/%s", default_رستہ, "libIMGEGL.suprx");
        sce_Kernel_لدو_شروع_Module(نشانہ_رستہ, 0, عدم, 0, عدم, عدم);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_رستہ, "%s/%s", default_رستہ, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_رستہ, "%s/%s", default_رستہ, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_کھڑکی_System, MAX_رستہ, "%s/%s", default_رستہ, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    أرجع SDL_EGL_لدو_Library(_this, رستہ, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    حرف gl_نسخہ[3];
    SDL_GLContext context = عدم;
    صحيح عارضی_major = _this->gl_config.major_نسخہ;
    صحيح عارضی_minor = _this->gl_config.minor_نسخہ;
    صحيح عارضی_profile = _this->gl_config.profile_نقاب;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_نسخہ = 2;
    _this->gl_config.minor_نسخہ = 0;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, کھڑکی->اندرونی->egl_surface);

    إذا (context != عدم) {
        FB_چوڑائی = کھڑکی->w;
        FB_اچائی = کھڑکی->h;
        سیٹ_getprocaddress((فراغ *(*)(ثابت حرف *))egl_Get_Proc_پتہ);
        سیٹ_getmainfbsize(getFBSize);
        SDL_snprintf(gl_نسخہ, 3, "%d%d", عارضی_major, عارضی_minor);
        gl4es_setenv("LIBGL_NOTEXRECT", "1", 1); // Currently broken in driver
        gl4es_setenv("LIBGL_GL", gl_نسخہ, 1);
        initialize_gl4es();
    }

    // Restore gl_config
    _this->gl_config.major_نسخہ = عارضی_major;
    _this->gl_config.minor_نسخہ = عارضی_minor;
    _this->gl_config.profile_نقاب = عارضی_profile;

    أرجع context;
}

SDL_Function_اشارہ_گر VITA_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع gl4es_Get_Proc_پتہ(proc);
}

#جے_انت // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
