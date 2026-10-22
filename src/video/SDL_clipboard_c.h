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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_clipboard_c_h_
#define SDL_clipboard_c_h_

#અન્તર્ભાવ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
બાહ્ય bool SDL_IsTextMimeType(અચલ અક્ષર *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
બાહ્ય શૂન્ય SDL_CancelClipboardData(Uint32 sequence);

// Call the clipboard callback for application data
બાહ્ય શૂન્ય *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type, size_t *size);
બાહ્ય bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type);

// General purpose clipboard text callback
અચલ શૂન્ય * SDLCALL SDL_ClipboardTextCallback(શૂન્ય *userdata, અચલ અક્ષર *mime_type, size_t *size);

bool SDL_SaveClipboardMimeTypes(અચલ અક્ષર *અચલ *mime_types, size_t અંક_mime_types);
શૂન્ય SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
અક્ષર **SDL_CopyClipboardMimeTypes(અચલ અક્ષર *અચલ *clipboard_mime_types, size_t અંક_mime_types, bool temporary);

#endif // SDL_clipboard_c_h_
