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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandmessagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../dialog/unix/SDL_zenitymessagebox.h"

bool Wayland_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
    // Are we trying to connect to or are currently in a Wayland session?
    ਜੇ (!SDL_getenv("WAYLAND_DISPLAY")) {
        ਅਚਲ ਅੱਖਰ *session = SDL_getenv("XDG_SESSION_TYPE");
        ਜੇ (session && SDL_strcasecmp(session, "wayland") != 0) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Not on a wayland display");
        }
    }

    ਵਾਪਸ SDL_Zenity_Show_ਸੁਨੇਹਾ_Box(messageboxdata, buttonID);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
