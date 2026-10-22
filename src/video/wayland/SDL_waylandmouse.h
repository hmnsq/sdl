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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylandmouse_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylandmouse_h_

ਬਾਹਰੀ ਖਾਲੀ Wayland_InitMouse(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_FiniMouse(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Seat_Update_ਸੂਚਕ_Cursor(SDL_WaylandSeat *seat);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Seat_ਸੈੱਟ_Default_Cursor(SDL_WaylandSeat *seat);
ਬਾਹਰੀ ਖਾਲੀ Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Display_Update_ਸੂਚਕ_Focused_Scale(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *updated_ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
ਬਾਹਰੀ ਖਾਲੀ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Cursor_State_ਸੈੱਟ_ਚੌਖਟਾ_Callback(SDL_WaylandCursorState *state, ਖਾਲੀ *userdata);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(SDL_WaylandCursorState *state);
ਬਾਹਰੀ ਖਾਲੀ Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#ਜੇ 0  // TODO RECONNECT: See waylandvideo.c for more information!
ਬਾਹਰੀ ਖਾਲੀ Wayland_RecreateCursors(ਖਾਲੀ);
#ਜੇ_ਅੰਤ // 0

#ਜੇ_ਅੰਤ
