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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_VIVANTE) && defined(SDL_VIDEO_OPENGL_EGL)

#అన్తర్భావ "SDL_vivanteopengles.h"
#అన్తర్భావ "SDL_vivantevideo.h"

// EGL implementation of SDL OpenGL support

bool VIVANTE_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం(SDL_GetPrimaryDisplay());

    తిరిగి SDL_EGL_ఎక్కించు_Library(_this, మార్గం, displaydata->native_display);
}

SDL_EGL_CreateContext_impl(VIVANTE)
SDL_EGL_మార్పిడి_కిటికీ_impl(VIVANTE)
SDL_EGL_MakeCurrent_impl(VIVANTE)

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VIVANTE && SDL_VIDEO_OPENGL_EGL
