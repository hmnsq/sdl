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

#اگر_غیر_تعریف_شدہ SDL_waylandkeyboard_h_
#تعریف_کرو SDL_waylandkeyboard_h_

خارجی bool Wayland_InitKeyboard(SDL_VideoDevice *_this);
خارجی خالی Wayland_QuitKeyboard(SDL_VideoDevice *_this);
خارجی bool Wayland_آغاز_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
خارجی bool Wayland_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Wayland_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_Seat_Update_متن_داخلہ(SDL_WaylandSeat *seat);
خارجی bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this);

#اگر_ختم // SDL_waylandkeyboard_h_
