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
#ضمن "SDL_internal.h"

#جے_بنا_تعریف SDL_waylandclipboard_h_
#تعریف_کرو SDL_waylandclipboard_h_

خارجي ثابت حرف *ثابت *Wayland_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types);
خارجي bool Wayland_سیٹ_Clipboard_انکڑے(SDL_VideoDevice *_this);
خارجي فراغ *Wayland_Get_Clipboard_انکڑے(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *لمائی);
خارجي bool Wayland_Has_Clipboard_انکڑے(SDL_VideoDevice *_this, ثابت حرف *mime_type);
خارجي bool Wayland_سیٹ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن);
خارجي حرف *Wayland_Get_Primary_Selection_متن(SDL_VideoDevice *_this);
خارجي bool Wayland_Has_Primary_Selection_متن(SDL_VideoDevice *_this);

#جے_انت // SDL_waylandclipboard_h_
