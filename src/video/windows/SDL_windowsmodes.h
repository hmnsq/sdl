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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_windowsmodes_h_
#define SDL_windowsmodes_h_

வகைவரை எண்ணிக்கை
{
    DisplayUnchanged,
    DisplayAdded,
    DisplayRemoved,

} WIN_DisplayState;

கட்டமைப்பு SDL_DisplayData
{
    WCHAR DeviceName[32];
    HMONITOR MonitorHandle;
    WIN_DisplayState state;
    SDL_Rect bounds;
};

கட்டமைப்பு SDL_DisplayModeData
{
    DEVMODEW DeviceMode;
};

வெளி bool WIN_InitModes(SDL_VideoDevice *_this);
வெளி bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
வெளி bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
வெளி bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
வெளி bool WIN_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
வெளி வெறுமை WIN_RefreshDisplays(SDL_VideoDevice *_this);
வெளி வெறுமை WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this);
வெளி வெறுமை WIN_QuitModes(SDL_VideoDevice *_this);

#endif // SDL_windowsmodes_h_
