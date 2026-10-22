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

#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_waylandmouse_h_
#define SDL_waylandmouse_h_

બાહ્ય શૂન્ય Wayland_InitMouse(SDL_VideoData *data);
બાહ્ય શૂન્ય Wayland_FiniMouse(SDL_VideoData *data);
બાહ્ય શૂન્ય Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat);
બાહ્ય શૂન્ય Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat);
બાહ્ય શૂન્ય Wayland_SeatResetCursor(SDL_WaylandSeat *seat);
બાહ્ય શૂન્ય Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window);
બાહ્ય શૂન્ય Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool);
બાહ્ય શૂન્ય Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, દશાંશ x, દશાંશ y);
બાહ્ય શૂન્ય Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, શૂન્ય *userdata);
બાહ્ય શૂન્ય Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state);
બાહ્ય શૂન્ય Wayland_CursorStateRelease(SDL_WaylandCursorState *state);
#જો 0  // TODO RECONNECT: See waylandvideo.c for more information!
બાહ્ય શૂન્ય Wayland_RecreateCursors(શૂન્ય);
#endif // 0

#endif
