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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_x11clipboard_h_
#define SDL_x11clipboard_h_

#ଅନ୍ତର୍ଭାଵ <X11/Xlib.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା X11_ClipboardData {
    SDL_ClipboardDataCallback callback;
    ଶୂନ୍ୟ *userdata;
    ଅଚଳ ଅକ୍ଷର *ଅଚଳ *mime_types;
    size_t mime_ଗଣନା;
    Uint32 sequence;
} SDLX11_ClipboardData;

ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *ଅଚଳ *X11_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ଅଙ୍କ_mime_types);
ବାହ୍ୟ bool X11_SetClipboardData(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ *X11_GetClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length);
ବାହ୍ୟ bool X11_HasClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type);
ବାହ୍ୟ bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *text);
ବାହ୍ୟ ଅକ୍ଷର *X11_GetPrimarySelectionText(SDL_VideoDevice *_this);
ବାହ୍ୟ bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ X11_QuitClipboard(SDL_VideoDevice *_this);
Window GetWindow(SDL_VideoDevice *_this);

#endif // SDL_x11clipboard_h_
