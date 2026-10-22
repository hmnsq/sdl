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

#اگر defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR) && defined(SDL_VIDEO_VITA_PVR_OGL)
#شامل <stdlib.h>
#شامل <string.h>
#شامل <psp2/kernel/modulemgr.h>
#شامل <gpu_es4/psp2_pvr_hint.h>
#شامل <gl4esinit.h>

#شامل "SDL_vitavideo.h"
#شامل "../SDL_egl_c.h"

#تعریف_کرو MAX_راستہ 256 // vita limits are somehow wrong

// Defaults
ساکن صحیح FB_چوڑائی = 960;
ساکن صحیح FB_اونچائی = 544;

ساکن خالی getFBSize(صحیح *چوڑائی, صحیح *اونچائی)
{
    *چوڑائی = FB_چوڑائی;
    *اونچائی = FB_اونچائی;
}

bool VITA_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    PVRSRV_PSP2_APPHINT hint;
    حرف *default_راستہ = "app0:module";
    حرف ہدف_راستہ[MAX_راستہ];

    اگر (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ثابت حرف *override = SDL_GetHint(SDL_HINT_VITA_MODULE_راستہ);

        اگر (override && *override) {
            default_راستہ = override;
        }

        sce_Kernel_بھرو_آغاز_Module("vs0:sys/external/libfios2.suprx", 0, تہی, 0, تہی, تہی);
        sce_Kernel_بھرو_آغاز_Module("vs0:sys/external/libc.suprx", 0, تہی, 0, تہی, تہی);

        SDL_snprintf(ہدف_راستہ, MAX_راستہ, "%s/%s", default_راستہ, "libGL.suprx");
        sce_Kernel_بھرو_آغاز_Module(ہدف_راستہ, 0, تہی, 0, تہی, تہی);

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

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    حرف gl_نسخہ[3];
    SDL_GLContext context = تہی;
    صحیح عارضی_major = _this->gl_config.major_نسخہ;
    صحیح عارضی_minor = _this->gl_config.minor_نسخہ;
    صحیح عارضی_profile = _this->gl_config.profile_نقاب;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_نسخہ = 2;
    _this->gl_config.minor_نسخہ = 0;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, کھڑکی->اندرونی_2->egl_surface);

    اگر (context != تہی) {
        FB_چوڑائی = کھڑکی->w;
        FB_اونچائی = کھڑکی->h;
        سیٹ_getprocaddress((خالی *(*)(ثابت حرف *))egl_Get_Proc_پتہ);
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

    واپس context;
}

SDL_Function_اشارہ_گر VITA_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    واپس gl4es_Get_Proc_پتہ(proc);
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
