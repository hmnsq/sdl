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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_clipboard_c_h_
#परिभाषय SDL_clipboard_c_h_

#अन्तर्भाव "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
बाह्य bool SDL_IsTextMimeType(ध्रुव वर्ण *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
बाह्य शून्य SDL_Cancel_Clipboard_दत्त(Uint32 sequence);

// Call the clipboard callback for application data
बाह्य शून्य *SDL_Get_आन्तरिकम्_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *आकार);
बाह्य bool SDL_Has_आन्तरिकम्_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type);

// General purpose clipboard text callback
ध्रुव शून्य * SDLCALL SDL_ClipboardTextCallback(शून्य *userdata, ध्रुव वर्ण *mime_type, size_t *आकार);

bool SDL_SaveClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *mime_types, size_t अङ्कः_mime_types);
शून्य SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
वर्ण **SDL_CopyClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *clipboard_mime_types, size_t अङ्कः_mime_types, bool temporary);

#यदि_अन्तः // SDL_clipboard_c_h_
