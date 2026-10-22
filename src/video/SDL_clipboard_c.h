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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_clipboard_c_h_
#define SDL_clipboard_c_h_

#அந்தர்பாவ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
வெளி bool SDL_IsTextMimeType(மாறிலி எழுத்து *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
வெளி வெறுமை SDL_CancelClipboardData(Uint32 sequence);

// Call the clipboard callback for application data
வெளி வெறுமை *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type, size_t *size);
வெளி bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type);

// General purpose clipboard text callback
மாறிலி வெறுமை * SDLCALL SDL_ClipboardTextCallback(வெறுமை *userdata, மாறிலி எழுத்து *mime_type, size_t *size);

bool SDL_SaveClipboardMimeTypes(மாறிலி எழுத்து *மாறிலி *mime_types, size_t இலக்கம்_mime_types);
வெறுமை SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
எழுத்து **SDL_CopyClipboardMimeTypes(மாறிலி எழுத்து *மாறிலி *clipboard_mime_types, size_t இலக்கம்_mime_types, bool temporary);

#endif // SDL_clipboard_c_h_
