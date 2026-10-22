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

#अगर_अघोषित SDL_windowsmodes_h_
#घोषणा SDL_windowsmodes_h_

प्रकार क्रमागत
{
    DisplayUnchanged,
    DisplayAdded,
    DisplayRemoved,

} WIN_DisplayState;

काष्ठा SDL_Display_तथ्य
{
    WCHAR DeviceName[32];
    HMONITOR MonitorHandle;
    WIN_DisplayState state;
    SDL_Rect bounds;
};

काष्ठा SDL_Display_Mode_तथ्य
{
    DEVMODEW DeviceMode;
};

बाह्य bool WIN_InitModes(SDL_VideoDevice *_this);
बाह्य bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
बाह्य bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
बाह्य bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool WIN_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य व्योम WIN_RefreshDisplays(SDL_VideoDevice *_this);
बाह्य व्योम WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this);
बाह्य व्योम WIN_QuitModes(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_windowsmodes_h_
