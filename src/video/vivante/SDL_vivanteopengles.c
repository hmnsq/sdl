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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_VIVANTE) && defined(SDL_VIDEO_OPENGL_EGL)

#ಅನ್ತರ್ಭಾವ "SDL_vivanteopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_vivantevideo.h"

// EGL implementation of SDL OpenGL support

bool VIVANTE_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ(SDL_GetPrimaryDisplay());

    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, displaydata->native_display);
}

SDL_EGL_CreateContext_impl(VIVANTE)
SDL_EGL_ಅದಲುಬದಲು_ಕಿಟಕಿ_impl(VIVANTE)
SDL_EGL_MakeCurrent_impl(VIVANTE)

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VIVANTE && SDL_VIDEO_OPENGL_EGL
