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

#اگر_غیر_تعریف_شدہ SDL_waylandmouse_h_
#تعریف_کرو SDL_waylandmouse_h_

خارجی خالی Wayland_InitMouse(SDL_Video_ڈیٹا *ڈیٹا);
خارجی خالی Wayland_FiniMouse(SDL_Video_ڈیٹا *ڈیٹا);
خارجی خالی Wayland_Seat_Update_اشارہ_گر_Cursor(SDL_WaylandSeat *seat);
خارجی خالی Wayland_Seat_سیٹ_Default_Cursor(SDL_WaylandSeat *seat);
خارجی خالی Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
خارجی خالی Wayland_Display_Update_اشارہ_گر_Focused_Scale(SDL_کھڑکی_ڈیٹا *updated_کھڑکی);
خارجی خالی Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
خارجی خالی Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_کھڑکی_ڈیٹا *کھڑکی, اعشاری x, اعشاری y);
خارجی خالی Wayland_Cursor_State_سیٹ_چوکھٹا_Callback(SDL_WaylandCursorState *state, خالی *userdata);
خارجی خالی Wayland_Cursor_State_Destroy_چوکھٹا_Callback(SDL_WaylandCursorState *state);
خارجی خالی Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#اگر 0  // TODO RECONNECT: See waylandvideo.c for more information!
خارجی خالی Wayland_RecreateCursors(خالی);
#اگر_ختم // 0

#اگر_ختم
