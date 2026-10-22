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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_cocoaclipboard_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_cocoaclipboard_h_

// Forward declaration
@class SDL_Cocoa_Video_ದತ್ತಾಂಶ;

ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_CheckClipboardUpdate(SDL_Cocoa_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ *Cocoa_Get_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2);
ಬಾಹ್ಯ bool Cocoa_Has_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);

#ಆದರೆ_ಅಂತ್ಯ // SDL_cocoaclipboard_h_
