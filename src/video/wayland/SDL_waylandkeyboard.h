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

#جيڪڏهن_وصف_نه_ٿيل SDL_waylandkeyboard_h_
#وصف_ڪريو SDL_waylandkeyboard_h_

خارجي bool Wayland_InitKeyboard(SDL_VideoDevice *_this);
خارجي فراغ Wayland_QuitKeyboard(SDL_VideoDevice *_this);
خارجي bool Wayland_شروعات_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
خارجي bool Wayland_Stop_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Wayland_Update_متن_داخلا_Area(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_Seat_Update_متن_داخلا(SDL_WaylandSeat *seat);
خارجي bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this);

#جيڪڏهن_پورو // SDL_waylandkeyboard_h_
