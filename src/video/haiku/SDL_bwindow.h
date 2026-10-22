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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_BWINDOW_H
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_BWINDOW_H

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

ಬಾಹ್ಯ bool HAIKU_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool HAIKU_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable);
ಬಾಹ್ಯ SDL_Fullscreen_ಫಲಿತಾಂಶ HAIKU_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ bool HAIKU_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ bool HAIKU_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ);
ಬಾಹ್ಯ bool HAIKU_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal);
ಬಾಹ್ಯ ಶೂನ್ಯ HAIKU_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

#ಆದರೆ_ಅಂತ್ಯ
