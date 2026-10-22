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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_windowsmodes_h_
#परिभाषय SDL_windowsmodes_h_

प्रकारनिर्देश गणना
{
    DisplayUnchanged,
    DisplayAdded,
    DisplayRemoved,

} WIN_DisplayState;

संरचना SDL_Display_दत्त
{
    WCHAR DeviceName[32];
    HMONITOR MonitorHandle;
    WIN_DisplayState state;
    SDL_Rect bounds;
};

संरचना SDL_Display_बहुलकम्_दत्त
{
    DEVMODEW Device_बहुलकम्;
};

बाह्य bool WIN_InitModes(SDL_VideoDevice *_this);
बाह्य bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
बाह्य bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
बाह्य bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool WIN_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
बाह्य शून्य WIN_RefreshDisplays(SDL_VideoDevice *_this);
बाह्य शून्य WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this);
बाह्य शून्य WIN_QuitModes(SDL_VideoDevice *_this);

#यदि_अन्तः // SDL_windowsmodes_h_
