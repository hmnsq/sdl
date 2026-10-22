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

#यदि_अपरिभाषितम् SDL_waylandclipboard_h_
#परिभाषय SDL_waylandclipboard_h_

बाह्य ध्रुव वर्ण *ध्रुव *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अङ्कः_mime_types);
बाह्य bool Wayland_समुच्चयः_Clipboard_दत्त(SDL_VideoDevice *_this);
बाह्य शून्य *Wayland_Get_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *दीर्घता);
बाह्य bool Wayland_Has_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type);
बाह्य bool Wayland_समुच्चयः_Primary_Selection_Text(SDL_VideoDevice *_this, ध्रुव वर्ण *text);
बाह्य वर्ण *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this);
बाह्य bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this);

#यदि_अन्तः // SDL_waylandclipboard_h_
