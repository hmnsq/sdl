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

#నిర్వచితం_కాకపోతే SDL_waylandcolor_h_
#నిర్వచించు SDL_waylandcolor_h_

#అన్తర్భావ "../SDL_sysvideo.h"

నిర్మాణం Wayland_ColorInfoState;

బాహ్య శూన్య Wayland_FreeColorInfoState(నిర్మాణం Wayland_ColorInfoState *state);
బాహ్య శూన్య Wayland_Get_Color_Info_For_కిటికీ(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, bool defer_event_processing);
బాహ్య శూన్య Wayland_GetColorInfoForOutput(SDL_Display_దత్తాంశం *display_దత్తాంశం, bool defer_event_processing);

#అయితే_ముగింపు // SDL_waylandcolor_h_
