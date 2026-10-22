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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_waylandmouse_h_
#define SDL_waylandmouse_h_

ବାହ୍ୟ ଶୂନ୍ୟ Wayland_InitMouse(SDL_VideoData *data);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_FiniMouse(SDL_VideoData *data);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, ଦଶମିକ x, ଦଶମିକ y);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, ଶୂନ୍ୟ *userdata);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#ଯଦି 0  // TODO RECONNECT: See waylandvideo.c for more information!
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_RecreateCursors(ଶୂନ୍ୟ);
#endif // 0

#endif
