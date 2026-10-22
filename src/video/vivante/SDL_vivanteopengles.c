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

#إذا defined(SDL_VIDEO_DRIVER_VIVANTE) && defined(SDL_VIDEO_OPENGL_EGL)

#ضمن "SDL_vivanteopengles.h"
#ضمن "SDL_vivantevideo.h"

// EGL implementation of SDL OpenGL support

bool VIVANTE_GLES_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات(SDL_GetPrimaryDisplay());

    أرجع SDL_EGL_ڀريو_Library(_this, رستو, displaydata->native_display);
}

SDL_EGL_CreateContext_impl(VIVANTE)
SDL_EGL_مٽا_سٽا_دري_impl(VIVANTE)
SDL_EGL_MakeCurrent_impl(VIVANTE)

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VIVANTE && SDL_VIDEO_OPENGL_EGL
