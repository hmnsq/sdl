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

#ifndef SDL_x11clipboard_h_
#define SDL_x11clipboard_h_

#অন্তর্ভাৱ <X11/Xlib.h>

প্রকারনির্দেশ সংরচনা X11_ClipboardData {
    SDL_ClipboardDataCallback callback;
    শূন্য *userdata;
    ধ্রুৱ ৱর্ণ *ধ্রুৱ *mime_types;
    size_t mime_গুনতি;
    Uint32 sequence;
} SDLX11_ClipboardData;

বাহ্য ধ্রুৱ ৱর্ণ *ধ্রুৱ *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types);
বাহ্য bool X11_SetClipboardData(SDL_VideoDevice *_this);
বাহ্য শূন্য *X11_GetClipboardData(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *mime_type, size_t *length);
বাহ্য bool X11_HasClipboardData(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *mime_type);
বাহ্য bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *text);
বাহ্য ৱর্ণ *X11_GetPrimarySelectionText(SDL_VideoDevice *_this);
বাহ্য bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this);
বাহ্য শূন্য X11_QuitClipboard(SDL_VideoDevice *_this);
Window GetWindow(SDL_VideoDevice *_this);

#endif // SDL_x11clipboard_h_
