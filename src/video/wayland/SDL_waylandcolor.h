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

#ifndef SDL_waylandcolor_h_
#define SDL_waylandcolor_h_

#অন্তর্ভাব "../SDL_sysvideo.h"

কাঠামো Wayland_ColorInfoState;

বাহ্যিক শূন্য Wayland_FreeColorInfoState(কাঠামো Wayland_ColorInfoState *state);
বাহ্যিক শূন্য Wayland_GetColorInfoForWindow(SDL_Window_তথ্য *window_তথ্য_2, bool defer_event_processing);
বাহ্যিক শূন্য Wayland_GetColorInfoForOutput(SDL_Display_তথ্য *display_তথ্য, bool defer_event_processing);

#endif // SDL_waylandcolor_h_
