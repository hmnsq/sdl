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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_clipboard_c_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_clipboard_c_h_

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
ಬಾಹ್ಯ bool SDL_Is_ಪಠ್ಯ_Mime_Type(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Cancel_Clipboard_ದತ್ತಾಂಶ(Uint32 sequence);

// Call the clipboard callback for application data
ಬಾಹ್ಯ ಶೂನ್ಯ *SDL_Get_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2);
ಬಾಹ್ಯ bool SDL_Has_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);

// General purpose clipboard text callback
ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * SDLCALL SDL_Clipboard_ಪಠ್ಯ_Callback(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2);

bool SDL_SaveClipboardMimeTypes(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *mime_types, size_t ಅಂಕೆ_mime_types);
ಶೂನ್ಯ SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
ಅಕ್ಷರ **SDL_CopyClipboardMimeTypes(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *clipboard_mime_types, size_t ಅಂಕೆ_mime_types, bool temporary);

#ಆದರೆ_ಅಂತ್ಯ // SDL_clipboard_c_h_
