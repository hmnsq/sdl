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

#अगर_अघोषित SDL_waylandmouse_h_
#घोषणा SDL_waylandmouse_h_

बाह्य व्योम Wayland_InitMouse(SDL_Video_तथ्य *तथ्य);
बाह्य व्योम Wayland_FiniMouse(SDL_Video_तथ्य *तथ्य);
बाह्य व्योम Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat);
बाह्य व्योम Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat);
बाह्य व्योम Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
बाह्य व्योम Wayland_DisplayUpdatePointerFocusedScale(SDL_Window_तथ्य *updated_window);
बाह्य व्योम Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
बाह्य व्योम Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_Window_तथ्य *window, भग्न x, भग्न y);
बाह्य व्योम Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, व्योम *userdata);
बाह्य व्योम Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state);
बाह्य व्योम Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#अगर 0  // TODO RECONNECT: See waylandvideo.c for more information!
बाह्य व्योम Wayland_RecreateCursors(व्योम);
#पूर्ण_अगर // 0

#पूर्ण_अगर
