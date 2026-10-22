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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_waylandclipboard_h_
#define SDL_waylandclipboard_h_

બાહ્ય અચલ અક્ષર *અચલ *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *અંક_mime_types);
બાહ્ય bool Wayland_SetClipboardData(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય *Wayland_GetClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type, size_t *length);
બાહ્ય bool Wayland_HasClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type);
બાહ્ય bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, અચલ અક્ષર *text);
બાહ્ય અક્ષર *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this);
બાહ્ય bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this);

#endif // SDL_waylandclipboard_h_
