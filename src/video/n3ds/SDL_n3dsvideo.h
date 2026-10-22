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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_n3dsvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_n3dsvideo_h_

#ಅನ್ತರ್ಭಾವ <3ds.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    SDL_DisplayID ತುದಿ_display;
    SDL_DisplayID touch_display;
};

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    gfxScreen_t screen; /**< Keeps track of which N3DS screen is targeted */
};

#ಆದರೆ_ಅಂತ್ಯ // SDL_n3dsvideo_h_
