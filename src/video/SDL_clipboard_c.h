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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_clipboard_c_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_clipboard_c_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
ਬਾਹਰੀ bool SDL_Is_ਪਾਠ_Mime_Type(ਅਚਲ ਅੱਖਰ *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
ਬਾਹਰੀ ਖਾਲੀ SDL_Cancel_Clipboard_ਅੰਕੜੇ(Uint32 sequence);

// Call the clipboard callback for application data
ਬਾਹਰੀ ਖਾਲੀ *SDL_Get_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਮਾਪ);
ਬਾਹਰੀ bool SDL_Has_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type);

// General purpose clipboard text callback
ਅਚਲ ਖਾਲੀ * SDLCALL SDL_Clipboard_ਪਾਠ_Callback(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਮਾਪ);

bool SDL_SaveClipboardMimeTypes(ਅਚਲ ਅੱਖਰ *ਅਚਲ *mime_types, size_t ਅੰਕ_mime_types);
ਖਾਲੀ SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
ਅੱਖਰ **SDL_CopyClipboardMimeTypes(ਅਚਲ ਅੱਖਰ *ਅਚਲ *clipboard_mime_types, size_t ਅੰਕ_mime_types, bool temporary);

#ਜੇ_ਅੰਤ // SDL_clipboard_c_h_
