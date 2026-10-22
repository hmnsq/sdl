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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_windowsmodes_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_windowsmodes_h_

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    DisplayUnchanged,
    DisplayAdded,
    DisplayRemoved,

} WIN_DisplayState;

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    WCHAR DeviceName[32];
    HMONITOR MonitorHandle;
    WIN_DisplayState state;
    SDL_Rect bounds;
};

ರಚನೆ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ
{
    DEVMODEW Device_ಬಹುಲಕ;
};

ಬಾಹ್ಯ bool WIN_InitModes(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ಬಾಹ್ಯ bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ಬಾಹ್ಯ bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ಬಾಹ್ಯ bool WIN_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_RefreshDisplays(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_QuitModes(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_windowsmodes_h_
