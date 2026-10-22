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

#నిర్వచితం_కాకపోతే SDL_windowsmodes_h_
#నిర్వచించు SDL_windowsmodes_h_

రకనిర్వచనం గణన
{
    DisplayUnchanged,
    DisplayAdded,
    DisplayRemoved,

} WIN_DisplayState;

నిర్మాణం SDL_Display_దత్తాంశం
{
    WCHAR DeviceName[32];
    HMONITOR MonitorHandle;
    WIN_DisplayState state;
    SDL_Rect bounds;
};

నిర్మాణం SDL_Display_బహుళకం_దత్తాంశం
{
    DEVMODEW Device_బహుళకం;
};

బాహ్య bool WIN_InitModes(SDL_VideoDevice *_this);
బాహ్య bool WIN_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
బాహ్య bool WIN_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
బాహ్య bool WIN_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య bool WIN_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య శూన్య WIN_RefreshDisplays(SDL_VideoDevice *_this);
బాహ్య శూన్య WIN_UpdateDisplayUsableBounds(SDL_VideoDevice *_this);
బాహ్య శూన్య WIN_QuitModes(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_windowsmodes_h_
