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

#ifndef SDL_waylandclipboard_h_
#define SDL_waylandclipboard_h_

बाह्य स्थिरांक अक्षर *स्थिरांक *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types);
बाह्य bool Wayland_SetClipboardData(SDL_VideoDevice *_this);
बाह्य शून्य *Wayland_GetClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type, माप_प्रकार *length);
बाह्य bool Wayland_HasClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type);
बाह्य bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, स्थिरांक अक्षर *text);
बाह्य अक्षर *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this);
बाह्य bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this);

#endif // SDL_waylandclipboard_h_
