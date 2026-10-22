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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_clipboard_c_h_
#define SDL_clipboard_c_h_

#അന്തര്ഭാവ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
ബാഹ്യ bool SDL_IsTextMimeType(സ്ഥിരം അക്ഷരം *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
ബാഹ്യ ശൂന്യം SDL_CancelClipboardData(Uint32 sequence);

// Call the clipboard callback for application data
ബാഹ്യ ശൂന്യം *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type, size_t *size);
ബാഹ്യ bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type);

// General purpose clipboard text callback
സ്ഥിരം ശൂന്യം * SDLCALL SDL_ClipboardTextCallback(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *mime_type, size_t *size);

bool SDL_SaveClipboardMimeTypes(സ്ഥിരം അക്ഷരം *സ്ഥിരം *mime_types, size_t അക്കം_mime_types);
ശൂന്യം SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
അക്ഷരം **SDL_CopyClipboardMimeTypes(സ്ഥിരം അക്ഷരം *സ്ഥിരം *clipboard_mime_types, size_t അക്കം_mime_types, bool temporary);

#endif // SDL_clipboard_c_h_
