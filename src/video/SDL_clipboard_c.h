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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_clipboard_c_h_
#تعریف_کرو SDL_clipboard_c_h_

#شامل "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
خارجی bool SDL_Is_متن_Mime_Type(ثابت حرف *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
خارجی خالی SDL_Cancel_Clipboard_ڈیٹا(Uint32 sequence);

// Call the clipboard callback for application data
خارجی خالی *SDL_Get_اندرونی_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *سائز);
خارجی bool SDL_Has_اندرونی_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type);

// General purpose clipboard text callback
ثابت خالی * SDLCALL SDL_Clipboard_متن_Callback(خالی *userdata, ثابت حرف *mime_type, size_t *سائز);

bool SDL_SaveClipboardMimeTypes(ثابت حرف *ثابت *mime_types, size_t عدد_mime_types);
خالی SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
حرف **SDL_CopyClipboardMimeTypes(ثابت حرف *ثابت *clipboard_mime_types, size_t عدد_mime_types, bool temporary);

#اگر_ختم // SDL_clipboard_c_h_
