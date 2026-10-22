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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylandcolor_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylandcolor_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

ರಚನೆ Wayland_ColorInfoState;

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_FreeColorInfoState(ರಚನೆ Wayland_ColorInfoState *state);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Get_Color_Info_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, bool defer_event_processing);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_GetColorInfoForOutput(SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ, bool defer_event_processing);

#ಆದರೆ_ಅಂತ್ಯ // SDL_waylandcolor_h_
