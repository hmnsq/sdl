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

#اگر_تعریف_نشده SDL_waylandmouse_h_
#تعریف_کن SDL_waylandmouse_h_

خارجي فراغ Wayland_InitMouse(SDL_Video_داده *داده);
خارجي فراغ Wayland_FiniMouse(SDL_Video_داده *داده);
خارجي فراغ Wayland_Seat_Update_اشاره_گر_Cursor(SDL_WaylandSeat *seat);
خارجي فراغ Wayland_Seat_مجموعه_Default_Cursor(SDL_WaylandSeat *seat);
خارجي فراغ Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
خارجي فراغ Wayland_Display_Update_اشاره_گر_Focused_Scale(SDL_پنجره_داده *updated_پنجره);
خارجي فراغ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
خارجي فراغ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_پنجره_داده *پنجره, عائم x, عائم y);
خارجي فراغ Wayland_Cursor_State_مجموعه_قاب_Callback(SDL_WaylandCursorState *state, فراغ *userdata);
خارجي فراغ Wayland_Cursor_State_Destroy_قاب_Callback(SDL_WaylandCursorState *state);
خارجي فراغ Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#إذا 0  // TODO RECONNECT: See waylandvideo.c for more information!
خارجي فراغ Wayland_RecreateCursors(فراغ);
#پایان_اگر // 0

#پایان_اگر
