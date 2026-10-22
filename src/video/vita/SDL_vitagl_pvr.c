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

#ಯದಿ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR) && defined(SDL_VIDEO_VITA_PVR_OGL)
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <psp2/kernel/modulemgr.h>
#ಅನ್ತರ್ಭಾವ <gpu_es4/psp2_pvr_hint.h>
#ಅನ್ತರ್ಭಾವ <gl4esinit.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

#define MAX_PATH 256 // vita limits are somehow wrong

// Defaults
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ FB_WIDTH = 960;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ FB_HEIGHT = 544;

ಸ್ಥಿರ ಶೂನ್ಯ getFBSize(ಪೂರ್ಣಾಙ್ಕ *width, ಪೂರ್ಣಾಙ್ಕ *height)
{
    *width = FB_WIDTH;
    *height = FB_HEIGHT;
}

bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    PVRSRV_PSP2_APPHINT hint;
    ವರ್ಣ *default_path = "app0:module";
    ವರ್ಣ target_path[MAX_PATH];

    ಯದಿ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ಧ್ರುವ ವರ್ಣ *override = SDL_GetHint(SDL_HINT_VITA_MODULE_PATH);

        ಯದಿ (override && *override) {
            default_path = override;
        }

        sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);
        sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libGL.suprx");
        sceKernelLoadStartModule(target_path, 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libgpu_es4_ext.suprx");
        sceKernelLoadStartModule(target_path, 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libIMGEGL.suprx");
        sceKernelLoadStartModule(target_path, 0, ರಿಕ್ತ, 0, ರಿಕ್ತ, ರಿಕ್ತ);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_PATH, "%s/%s", default_path, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_PATH, "%s/%s", default_path, "libGLESv2.suprx");
        SDL_snprintf(hint.szWindowSystem, MAX_PATH, "%s/%s", default_path, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    ಪ್ರತ್ಯಾಗಮ SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    ವರ್ಣ gl_version[3];
    SDL_GLContext context = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ temp_major = _this->gl_config.major_version;
    ಪೂರ್ಣಾಙ್ಕ temp_minor = _this->gl_config.minor_version;
    ಪೂರ್ಣಾಙ್ಕ temp_profile = _this->gl_config.profile_mask;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    ಯದಿ (context != ರಿಕ್ತ) {
        FB_WIDTH = window->w;
        FB_HEIGHT = window->h;
        set_getprocaddress((ಶೂನ್ಯ *(*)(ಧ್ರುವ ವರ್ಣ *))eglGetProcAddress);
        set_getmainfbsize(getFBSize);
        SDL_snprintf(gl_version, 3, "%d%d", temp_major, temp_minor);
        gl4es_setenv("LIBGL_NOTEXRECT", "1", 1); // Currently broken in driver
        gl4es_setenv("LIBGL_GL", gl_version, 1);
        initialize_gl4es();
    }

    // Restore gl_config
    _this->gl_config.major_version = temp_major;
    _this->gl_config.minor_version = temp_minor;
    _this->gl_config.profile_mask = temp_profile;

    ಪ್ರತ್ಯಾಗಮ context;
}

SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc)
{
    ಪ್ರತ್ಯಾಗಮ gl4es_GetProcAddress(proc);
}

#endif // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
