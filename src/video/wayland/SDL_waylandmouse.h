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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylandmouse_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylandmouse_h_

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_InitMouse(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_FiniMouse(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Seat_Update_ಸೂಚಕ_Cursor(SDL_WaylandSeat *seat);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Seat_ಗಣ_Default_Cursor(SDL_WaylandSeat *seat);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Update_ಸೂಚಕ_Focused_Scale(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *updated_ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Cursor_State_ಗಣ_ಚೌಕಟ್ಟು_Callback(SDL_WaylandCursorState *state, ಶೂನ್ಯ *userdata);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(SDL_WaylandCursorState *state);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#ಆದರೆ 0  // TODO RECONNECT: See waylandvideo.c for more information!
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_RecreateCursors(ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ // 0

#ಆದರೆ_ಅಂತ್ಯ
