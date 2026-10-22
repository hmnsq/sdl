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

#ifndef SDL_x11clipboard_h_
#define SDL_x11clipboard_h_

#شامل <X11/Xlib.h>

تعریفنوع ساختار X11_ClipboardData {
    SDL_ClipboardDataCallback callback;
    تهی *userdata;
    ثابت نویسه *ثابت *mime_types;
    size_t mime_شمار;
    Uint32 sequence;
} SDLX11_ClipboardData;

بیرونی ثابت نویسه *ثابت *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *رقم_mime_types);
بیرونی bool X11_SetClipboardData(SDL_VideoDevice *_this);
بیرونی تهی *X11_GetClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type, size_t *length);
بیرونی bool X11_HasClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type);
بیرونی bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, ثابت نویسه *text);
بیرونی نویسه *X11_GetPrimarySelectionText(SDL_VideoDevice *_this);
بیرونی bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this);
بیرونی تهی X11_QuitClipboard(SDL_VideoDevice *_this);
Window GetWindow(SDL_VideoDevice *_this);

#endif // SDL_x11clipboard_h_
