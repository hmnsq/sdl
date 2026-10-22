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
#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_clipboard_c_h_
#define SDL_clipboard_c_h_

#অন্তর্ভাৱ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
বাহ্য bool SDL_IsTextMimeType(ধ্রুৱ ৱর্ণ *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
বাহ্য শূন্য SDL_CancelClipboardData(Uint32 sequence);

// Call the clipboard callback for application data
বাহ্য শূন্য *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *mime_type, size_t *size);
বাহ্য bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *mime_type);

// General purpose clipboard text callback
ধ্রুৱ শূন্য * SDLCALL SDL_ClipboardTextCallback(শূন্য *userdata, ধ্রুৱ ৱর্ণ *mime_type, size_t *size);

bool SDL_SaveClipboardMimeTypes(ধ্রুৱ ৱর্ণ *ধ্রুৱ *mime_types, size_t অঙ্ক_mime_types);
শূন্য SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
ৱর্ণ **SDL_CopyClipboardMimeTypes(ধ্রুৱ ৱর্ণ *ধ্রুৱ *clipboard_mime_types, size_t অঙ্ক_mime_types, bool temporary);

#endif // SDL_clipboard_c_h_
