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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_waylandmouse_h_
#నిర్వచించు SDL_waylandmouse_h_

బాహ్య శూన్య Wayland_InitMouse(SDL_Video_దత్తాంశం *దత్తాంశం);
బాహ్య శూన్య Wayland_FiniMouse(SDL_Video_దత్తాంశం *దత్తాంశం);
బాహ్య శూన్య Wayland_Seat_Update_సూచిక_Cursor(SDL_WaylandSeat *seat);
బాహ్య శూన్య Wayland_Seat_సమితి_Default_Cursor(SDL_WaylandSeat *seat);
బాహ్య శూన్య Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
బాహ్య శూన్య Wayland_Display_Update_సూచిక_Focused_Scale(SDL_కిటికీ_దత్తాంశం *updated_కిటికీ);
బాహ్య శూన్య Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
బాహ్య శూన్య Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_కిటికీ_దత్తాంశం *కిటికీ, దశాంశం x, దశాంశం y);
బాహ్య శూన్య Wayland_Cursor_State_సమితి_చట్రం_Callback(SDL_WaylandCursorState *state, శూన్య *userdata);
బాహ్య శూన్య Wayland_Cursor_State_Destroy_చట్రం_Callback(SDL_WaylandCursorState *state);
బాహ్య శూన్య Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#ఒకవేళ 0  // TODO RECONNECT: See waylandvideo.c for more information!
బాహ్య శూన్య Wayland_RecreateCursors(శూన్య);
#అయితే_ముగింపు // 0

#అయితే_ముగింపు
