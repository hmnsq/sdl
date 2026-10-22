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

#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_waylandmouse_h_
#define SDL_waylandmouse_h_

বাহ্যিক শূন্য Wayland_InitMouse(SDL_Video_তথ্য *তথ্য);
বাহ্যিক শূন্য Wayland_FiniMouse(SDL_Video_তথ্য *তথ্য);
বাহ্যিক শূন্য Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat);
বাহ্যিক শূন্য Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat);
বাহ্যিক শূন্য Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
বাহ্যিক শূন্য Wayland_DisplayUpdatePointerFocusedScale(SDL_Window_তথ্য *updated_window);
বাহ্যিক শূন্য Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
বাহ্যিক শূন্য Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_Window_তথ্য *window, দশমিক x, দশমিক y);
বাহ্যিক শূন্য Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, শূন্য *userdata);
বাহ্যিক শূন্য Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state);
বাহ্যিক শূন্য Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#যদি 0  // TODO RECONNECT: See waylandvideo.c for more information!
বাহ্যিক শূন্য Wayland_RecreateCursors(শূন্য);
#endif // 0

#endif
