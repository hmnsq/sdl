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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#شامل "SDL_waylandmessagebox.h"
#شامل "../../dialog/unix/SDL_zenitymessagebox.h"

bool Wayland_Show_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
    // Are we trying to connect to or are currently in a Wayland session?
    اگر (!SDL_getenv("WAYLAND_DISPLAY")) {
        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        اگر (session && SDL_strcasecmp(session, "wayland") != 0) {
            واپس SDL_سیٹ_Error("Not on a wayland display");
        }
    }

    واپس SDL_Zenity_Show_پیغام_Box(messageboxdata, buttonID);
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
