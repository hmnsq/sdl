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

#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_waylandmouse_h_
#define SDL_waylandmouse_h_

बाह्य शून्य Wayland_InitMouse(SDL_VideoData *data);
बाह्य शून्य Wayland_FiniMouse(SDL_VideoData *data);
बाह्य शून्य Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat);
बाह्य शून्य Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat);
बाह्य शून्य Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
बाह्य शून्य Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window);
बाह्य शून्य Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
बाह्य शून्य Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, भिन्न x, भिन्न y);
बाह्य शून्य Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, शून्य *userdata);
बाह्य शून्य Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state);
बाह्य शून्य Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#यदि 0  // TODO RECONNECT: See waylandvideo.c for more information!
बाह्य शून्य Wayland_RecreateCursors(शून्य);
#endif // 0

#endif
