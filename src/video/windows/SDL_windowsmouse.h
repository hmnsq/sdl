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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_windowsmouse_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_windowsmouse_h_

ಬಾಹ್ಯ DWORD SDL_ಕೊನೆಯ_warp_ಸಮಯ;
ಬಾಹ್ಯ HCURSOR SDL_cursor;

ಬಾಹ್ಯ ಶೂನ್ಯ WIN_InitMouse(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_QuitMouse(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_ಗಣ_Cursor_Pos(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_UpdateMouseSystemScale(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_windowsmouse_h_
