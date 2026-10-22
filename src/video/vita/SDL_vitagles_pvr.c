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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PVR)
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <psp2/kernel/modulemgr.h>
#समावेश <gpu_es4/psp2_pvr_hint.h>

#समावेश "SDL_vitavideo.h"
#समावेश "../SDL_egl_c.h"

#घोषणा MAX_PATH 256 // vita limits are somehow wrong

bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    PVRSRV_PSP2_APPHINT hint;
    स्थिर अक्षर *default_path = "app0:module";
    अक्षर target_path[MAX_PATH];

    अगर (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_INIT, true)) {
        स्थिर अक्षर *override = SDL_GetHint(SDL_HINT_VITA_MODULE_PATH);

        अगर (override && *override) {
            default_path = override;
        }

        sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, शून्य, 0, शून्य, शून्य);
        sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, शून्य, 0, शून्य, शून्य);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libgpu_es4_ext.suprx");
        sceKernelLoadStartModule(target_path, 0, शून्य, 0, शून्य, शून्य);

        SDL_snprintf(target_path, MAX_PATH, "%s/%s", default_path, "libIMGEGL.suprx");
        sceKernelLoadStartModule(target_path, 0, शून्य, 0, शून्य, शून्य);

        PVRSRVInitializeAppHint(&hint);

        SDL_snprintf(hint.szGLES1, MAX_PATH, "%s/%s", default_path, "libGLESv1_CM.suprx");
        SDL_snprintf(hint.szGLES2, MAX_PATH, "%s/%s", default_path, "libGLESv2.suprx");
        SDL_snprintf(hint.szWindowSystem, MAX_PATH, "%s/%s", default_path, "libpvrPSP2_WSEGL.suprx");

        PVRSRVCreateVirtualAppHint(&hint);
    }

    वापस SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    वापस SDL_EGL_CreateContext(_this, window->internal->egl_surface);
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    अगर (window && context) {
        वापस SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } अन्यथा {
        वापस SDL_EGL_MakeCurrent(_this, शून्य, शून्य);
    }
}

bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    अगर (videodata->ime_active) {
        sceImeUpdate();
    }
    वापस SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VITA && SDL_VIDEO_VITA_PVR
