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

#ਜੇ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR) && defined(SDL_VIDEO_VITA_PVR_OGL)
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/kernel/modulemgr.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <gpu_es4/psp2_pvr_hint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <gl4esinit.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਰਸਤਾ 256 // vita limits are somehow wrong

// Defaults
ਸਥਿਰ ਪੂਰਨ FB_ਚੌੜਾਈ = 960;
ਸਥਿਰ ਪੂਰਨ FB_ਉਚਾਈ = 544;

ਸਥਿਰ ਖਾਲੀ getFBSize(ਪੂਰਨ *ਚੌੜਾਈ, ਪੂਰਨ *ਉਚਾਈ)
{
    *ਚੌੜਾਈ = FB_ਚੌੜਾਈ;
    *ਉਚਾਈ = FB_ਉਚਾਈ;
}

bool VITA_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    PVRSRV_PSP2_APPHINT hint;
    ਅੱਖਰ *default_ਰਸਤਾ = "app0:module";
    ਅੱਖਰ ਨਿਸ਼ਾਨਾ_ਰਸਤਾ[MAX_ਰਸਤਾ];

    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ਅਚਲ ਅੱਖਰ *override = SDL_GetHint(SDL_HINT_VITA_MODULE_ਰਸਤਾ);

        ਜੇ (override && *override) {
            default_ਰਸਤਾ = override;
        }

        sce_Kernel_ਲੱਦੋ_ਸ਼ੁਰੂ_Module("vs0:sys/external/libfios2.suprx", 0, ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);
        sce_Kernel_ਲੱਦੋ_ਸ਼ੁਰੂ_Module("vs0:sys/external/libc.suprx", 0, ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);

        SDL_snprintf(ਨਿਸ਼ਾਨਾ_ਰਸਤਾ, MAX_ਰਸਤਾ, "%s/%s", default_ਰਸਤਾ, "libGL.suprx");
        sce_Kernel_ਲੱਦੋ_ਸ਼ੁਰੂ_Module(ਨਿਸ਼ਾਨਾ_ਰਸਤਾ, 0, ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);

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

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਅੱਖਰ gl_ਸੰਸਕਰਣ[3];
    SDL_GLContext context = ਨਿਰਾ;
    ਪੂਰਨ ਆਰਜ਼ੀ_major = _this->gl_config.major_ਸੰਸਕਰਣ;
    ਪੂਰਨ ਆਰਜ਼ੀ_minor = _this->gl_config.minor_ਸੰਸਕਰਣ;
    ਪੂਰਨ ਆਰਜ਼ੀ_profile = _this->gl_config.profile_ਨਕਾਬ;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_ਸੰਸਕਰਣ = 2;
    _this->gl_config.minor_ਸੰਸਕਰਣ = 0;
    _this->gl_config.profile_ਨਕਾਬ = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);

    ਜੇ (context != ਨਿਰਾ) {
        FB_ਚੌੜਾਈ = ਖਿੜਕੀ->w;
        FB_ਉਚਾਈ = ਖਿੜਕੀ->h;
        ਸੈੱਟ_getprocaddress((ਖਾਲੀ *(*)(ਅਚਲ ਅੱਖਰ *))egl_Get_Proc_ਪਤਾ);
        ਸੈੱਟ_getmainfbsize(getFBSize);
        SDL_snprintf(gl_ਸੰਸਕਰਣ, 3, "%d%d", ਆਰਜ਼ੀ_major, ਆਰਜ਼ੀ_minor);
        gl4es_setenv("LIBGL_NOTEXRECT", "1", 1); // Currently broken in driver
        gl4es_setenv("LIBGL_GL", gl_ਸੰਸਕਰਣ, 1);
        initialize_gl4es();
    }

    // Restore gl_config
    _this->gl_config.major_ਸੰਸਕਰਣ = ਆਰਜ਼ੀ_major;
    _this->gl_config.minor_ਸੰਸਕਰਣ = ਆਰਜ਼ੀ_minor;
    _this->gl_config.profile_ਨਕਾਬ = ਆਰਜ਼ੀ_profile;

    ਵਾਪਸ context;
}

SDL_Function_ਸੂਚਕ VITA_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    ਵਾਪਸ gl4es_Get_Proc_ਪਤਾ(proc);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
