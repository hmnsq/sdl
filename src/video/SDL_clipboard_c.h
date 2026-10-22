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

#ifndef SDL_clipboard_c_h_
#define SDL_clipboard_c_h_

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
ಬಾಹ್ಯ bool SDL_IsTextMimeType(ಧ್ರುವ ವರ್ಣ *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_CancelClipboardData(Uint32 sequence);

// Call the clipboard callback for application data
ಬಾಹ್ಯ ಶೂನ್ಯ *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *size);
ಬಾಹ್ಯ bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type);

// General purpose clipboard text callback
ಧ್ರುವ ಶೂನ್ಯ * SDLCALL SDL_ClipboardTextCallback(ಶೂನ್ಯ *userdata, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *size);

bool SDL_SaveClipboardMimeTypes(ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *mime_types, size_t ಅಂಕೆ_mime_types);
ಶೂನ್ಯ SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
ವರ್ಣ **SDL_CopyClipboardMimeTypes(ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *clipboard_mime_types, size_t ಅಂಕೆ_mime_types, bool temporary);

#endif // SDL_clipboard_c_h_
