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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_gdktextinput_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_gdktextinput_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_GDK_TEXTINPUT
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

ಶೂನ್ಯ GDK_EnsureHints(ಶೂನ್ಯ);

bool GDK_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
bool GDK_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
bool GDK_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ಶೂನ್ಯ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
ಶೂನ್ಯ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
