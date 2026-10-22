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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11clipboard_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11clipboard_h_

#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ X11_Clipboard_ದತ್ತಾಂಶ {
    SDL_Clipboard_ದತ್ತಾಂಶ_Callback callback;
    ಶೂನ್ಯ *userdata;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *mime_types;
    size_t mime_ಎಣಿಕೆ;
    Uint32 sequence;
} SDLX11_Clipboard_ದತ್ತಾಂಶ;

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *X11_Get_ಪಠ್ಯ_Mime_Types(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types);
ಬಾಹ್ಯ bool X11_ಗಣ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ *X11_Get_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ);
ಬಾಹ್ಯ bool X11_Has_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);
ಬಾಹ್ಯ bool X11_ಗಣ_Primary_Selection_ಪಠ್ಯ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ);
ಬಾಹ್ಯ ಅಕ್ಷರ *X11_Get_Primary_Selection_ಪಠ್ಯ(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool X11_Has_Primary_Selection_ಪಠ್ಯ(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_QuitClipboard(SDL_VideoDevice *_this);
ಕಿಟಕಿ_2 Get_ಕಿಟಕಿ(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11clipboard_h_
