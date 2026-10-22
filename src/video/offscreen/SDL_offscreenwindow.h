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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_offscreenwindow_h
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_offscreenwindow_h

#ಅನ್ತರ್ಭಾವ "SDL_offscreenvideo.h"

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    SDL_ಕಿಟಕಿ *sdl_ಕಿಟಕಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ಆದರೆ_ಅಂತ್ಯ
};

ಬಾಹ್ಯ bool OFFSCREEN_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ OFFSCREEN_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ OFFSCREEN_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_offscreenwindow_h
