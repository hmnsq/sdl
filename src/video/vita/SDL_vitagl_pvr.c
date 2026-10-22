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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR) && defined(SDL_VIDEO_VITA_PVR_OGL)
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <psp2/kernel/modulemgr.h>
#અન્તર્ભાવ <gpu_es4/psp2_pvr_hint.h>
#અન્તર્ભાવ <gl4esinit.h>

#અન્તર્ભાવ "SDL_vitavideo.h"
#અન્તર્ભાવ "../SDL_egl_c.h"

#define MAX_PATH 256 // vita limits are somehow wrong

// Defaults
સ્થિર પૂર્ણાંક FB_WIDTH = 960;
સ્થિર પૂર્ણાંક FB_HEIGHT = 544;

સ્થિર શૂન્ય getFBSize(પૂર્ણાંક *width, પૂર્ણાંક *height)
{
    *width = FB_WIDTH;
    *height = FB_HEIGHT;
}

bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *path)
{
    PVRSRV_PSP2_APPHINT hint;
    અક્ષર *default_path = "app0:module";
    અક્ષર target_path[MAX_PATH];

    જો (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        અચલ અક્ષર *override = SDL_GetHint(SDL_HINT_VITA_MODULE_PATH);

        જો (override && *override) {
            default_path = override;
        }

        sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, ખાલી, 0, ખાલી, ખાલી);
        sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, ખાલી, 0, ખાલી, ખાલી);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libGL.suprx");
        sceKernelLoadStartModule(target_path, 0, ખાલી, 0, ખાલી, ખાલી);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libgpu_es4_ext.suprx");
        sceKernelLoadStartModule(target_path, 0, ખાલી, 0, ખાલી, ખાલી);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libIMGEGL.suprx");
        sceKernelLoadStartModule(target_path, 0, ખાલી, 0, ખાલી, ખાલી);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_PATH, "%s/%s", default_path, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_PATH, "%s/%s", default_path, "libGLESv2.suprx");
        SDL_snprintf(hint.szWindowSystem, MAX_PATH, "%s/%s", default_path, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    પાછા SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    અક્ષર gl_version[3];
    SDL_GLContext context = ખાલી;
    પૂર્ણાંક temp_major = _this->gl_config.major_version;
    પૂર્ણાંક temp_minor = _this->gl_config.minor_version;
    પૂર્ણાંક temp_profile = _this->gl_config.profile_mask;

    // Set version to 2.0 and PROFILE to ES
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;

    context = SDL_EGL_CreateContext(_this, window->internal->egl_surface);

    જો (context != ખાલી) {
        FB_WIDTH = window->w;
        FB_HEIGHT = window->h;
        set_getprocaddress((શૂન્ય *(*)(અચલ અક્ષર *))eglGetProcAddress);
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

    પાછા context;
}

SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, અચલ અક્ષર *proc)
{
    પાછા gl4es_GetProcAddress(proc);
}

#endif // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
