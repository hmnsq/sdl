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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR) && defined(SDL_VIDEO_VITA_PVR_OGL)
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <psp2/kernel/modulemgr.h>
#অন্তর্ভাব <gpu_es4/psp2_pvr_hint.h>
#অন্তর্ভাব <gl4esinit.h>

#অন্তর্ভাব "SDL_vitavideo.h"
#অন্তর্ভাব "../SDL_egl_c.h"

#define MAX_PATH 256 // vita limits are somehow wrong

// Defaults
স্থির পূর্ণাঙ্ক FB_WIDTH = 960;
স্থির পূর্ণাঙ্ক FB_HEIGHT = 544;

স্থির শূন্য getFBSize(পূর্ণাঙ্ক *width, পূর্ণাঙ্ক *height)
{
    *width = FB_WIDTH;
    *height = FB_HEIGHT;
}

bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *path)
{
    PVRSRV_PSP2_APPHINT hint;
    বর্ণ *default_path = "app0:module";
    বর্ণ target_path[MAX_PATH];

    যদি (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        ধ্রুব বর্ণ *override = SDL_GetHint(SDL_HINT_VITA_MODULE_PATH);

        যদি (override && *override) {
            default_path = override;
        }

        sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, রিক্ত, 0, রিক্ত, রিক্ত);
        sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, রিক্ত, 0, রিক্ত, রিক্ত);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libGL.suprx");
        sceKernelLoadStartModule(target_path, 0, রিক্ত, 0, রিক্ত, রিক্ত);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libgpu_es4_ext.suprx");
        sceKernelLoadStartModule(target_path, 0, রিক্ত, 0, রিক্ত, রিক্ত);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libIMGEGL.suprx");
        sceKernelLoadStartModule(target_path, 0, রিক্ত, 0, রিক্ত, রিক্ত);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_PATH, "%s/%s", default_path, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_PATH, "%s/%s", default_path, "libGLESv2.suprx");
        SDL_snprintf(hint.szWindowSystem, MAX_PATH, "%s/%s", default_path, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    প্রত্যাগম SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    বর্ণ gl_version[3];
    SDL_GLContext context = রিক্ত;
    পূর্ণাঙ্ক temp_major = _this->gl_config.major_version;
    পূর্ণাঙ্ক temp_minor = _this->gl_config.minor_version;
    পূর্ণাঙ্ক temp_profile = _this->gl_config.profile_mask;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    যদি (context != রিক্ত) {
        FB_WIDTH = window->w;
        FB_HEIGHT = window->h;
        set_getprocaddress((শূন্য *(*)(ধ্রুব বর্ণ *))eglGetProcAddress);
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

    প্রত্যাগম context;
}

SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুব বর্ণ *proc)
{
    প্রত্যাগম gl4es_GetProcAddress(proc);
}

#endif // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
