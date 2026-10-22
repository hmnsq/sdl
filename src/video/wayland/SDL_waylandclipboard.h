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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_waylandclipboard_h_
#define SDL_waylandclipboard_h_

বাহ্যিক ধ্রুবক অক্ষর *ধ্রুবক *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types);
বাহ্যিক bool Wayland_Set_Clipboard_তথ্য(SDL_VideoDevice *_this);
বাহ্যিক শূন্য *Wayland_Get_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য);
বাহ্যিক bool Wayland_Has_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type);
বাহ্যিক bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *text);
বাহ্যিক অক্ষর *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this);
বাহ্যিক bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this);

#endif // SDL_waylandclipboard_h_
