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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_waylandcolor_h_
#घोषणा SDL_waylandcolor_h_

#समावेश "../SDL_sysvideo.h"

काष्ठा Wayland_ColorInfoState;

बाह्य व्योम Wayland_FreeColorInfoState(काष्ठा Wayland_ColorInfoState *state);
बाह्य व्योम Wayland_GetColorInfoForWindow(SDL_Window_तथ्य *window_तथ्य_2, bool defer_event_processing);
बाह्य व्योम Wayland_GetColorInfoForOutput(SDL_Display_तथ्य *display_तथ्य, bool defer_event_processing);

#पूर्ण_अगर // SDL_waylandcolor_h_
