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

#تعریف_کن MAX_مسیر 256 // vita limits are somehow wrong

// Defaults
ساكن صحيح FB_عرض = 960;
ساكن صحيح FB_ارتفاع = 544;

ساكن فراغ getFBSize(صحيح *عرض, صحيح *ارتفاع)
{
    *عرض = FB_عرض;
    *ارتفاع = FB_ارتفاع;
}

bool VITA_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
    PVRSRV_PSP2_APPHINT hint;
    حرف *default_مسیر = "app0:module";
    حرف هدف_مسیر[MAX_مسیر];

    إذا (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ثابت حرف *override = SDL_GetHint(SDL_HINT_VITA_MODULE_مسیر);

        إذا (override && *override) {
            default_مسیر = override;
        }

        sce_Kernel_بارگیری_شروع_Module("vs0:sys/external/libfios2.suprx", 0, عدم, 0, عدم, عدم);
        sce_Kernel_بارگیری_شروع_Module("vs0:sys/external/libc.suprx", 0, عدم, 0, عدم, عدم);

        SDL_snprintf(هدف_مسیر, MAX_مسیر, "%s/%s", default_مسیر, "libGL.suprx");
        sce_Kernel_بارگیری_شروع_Module(هدف_مسیر, 0, عدم, 0, عدم, عدم);

        SDL_snprintf(هدف_مسیر, MAX_مسیر, "%s/%s", default_مسیر, "libgpu_es4_ext.suprx");
        sce_Kernel_بارگیری_شروع_Module(هدف_مسیر, 0, عدم, 0, عدم, عدم);

        SDL_snprintf(هدف_مسیر, MAX_مسیر, "%s/%s", default_مسیر, "libIMGEGL.suprx");
        sce_Kernel_بارگیری_شروع_Module(هدف_مسیر, 0, عدم, 0, عدم, عدم);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_مسیر, "%s/%s", default_مسیر, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_مسیر, "%s/%s", default_مسیر, "libGLESv2.suprx");
        SDL_snprintf(hint.sz_پنجره_System, MAX_مسیر, "%s/%s", default_مسیر, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    أرجع SDL_EGL_بارگیری_Library(_this, مسیر, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    حرف gl_نسخه[3];
    SDL_GLContext context = عدم;
    صحيح موقت_major = _this->gl_config.major_نسخه;
    صحيح موقت_minor = _this->gl_config.minor_نسخه;
    صحيح موقت_profile = _this->gl_config.profile_ماسک;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_نسخه = 2;
    _this->gl_config.minor_نسخه = 0;
    _this->gl_config.profile_ماسک = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, پنجره->داخلی->egl_surface);

    إذا (context != عدم) {
        FB_عرض = پنجره->w;
        FB_ارتفاع = پنجره->h;
        مجموعه_getprocaddress((فراغ *(*)(ثابت حرف *))egl_Get_Proc_آدرس);
        مجموعه_getmainfbsize(getFBSize);
        SDL_snprintf(gl_نسخه, 3, "%d%d", موقت_major, موقت_minor);
        gl4es_setenv("LIBGL_NOTEXRECT", "1", 1); // Currently broken in driver
        gl4es_setenv("LIBGL_GL", gl_نسخه, 1);
        initialize_gl4es();
    }

    // Restore gl_config
    _this->gl_config.major_نسخه = موقت_major;
    _this->gl_config.minor_نسخه = موقت_minor;
    _this->gl_config.profile_ماسک = موقت_profile;

    أرجع context;
}

SDL_Function_اشاره_گر VITA_GL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع gl4es_Get_Proc_آدرس(proc);
}

#پایان_اگر // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
