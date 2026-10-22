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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश "SDL_waylandmessagebox.h"
#समावेश "../../dialog/unix/SDL_zenitymessagebox.h"

bool Wayland_ShowMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
    // Are we trying to connect to or are currently in a Wayland session?
    अगर (!SDL_getenv("WAYLAND_DISPLAY")) {
        स्थिर अक्षर *session = SDL_getenv("XDG_SESSION_TYPE");
        अगर (session && SDL_strcasecmp(session, "wayland") != 0) {
            वापस SDL_SetError("Not on a wayland display");
        }
    }

    वापस SDL_Zenity_ShowMessageBox(messageboxdata, buttonID);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
