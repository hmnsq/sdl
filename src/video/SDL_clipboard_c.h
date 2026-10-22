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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_clipboard_c_h_
#घोषणा SDL_clipboard_c_h_

#समावेश "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
बाह्य bool SDL_IsTextMimeType(स्थिर अक्षर *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
बाह्य व्योम SDL_Cancel_Clipboard_तथ्य(Uint32 sequence);

// Call the clipboard callback for application data
बाह्य व्योम *SDL_Get_Internal_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type, माप_प्रकार *आकार);
बाह्य bool SDL_Has_Internal_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type);

// General purpose clipboard text callback
स्थिर व्योम * SDLCALL SDL_ClipboardTextCallback(व्योम *userdata, स्थिर अक्षर *mime_type, माप_प्रकार *आकार);

bool SDL_SaveClipboardMimeTypes(स्थिर अक्षर *स्थिर *mime_types, माप_प्रकार अंक_mime_types);
व्योम SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
अक्षर **SDL_CopyClipboardMimeTypes(स्थिर अक्षर *स्थिर *clipboard_mime_types, माप_प्रकार अंक_mime_types, bool temporary);

#पूर्ण_अगर // SDL_clipboard_c_h_
