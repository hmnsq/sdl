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

#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_x11xfixes_h_
#تعریف_کرو SDL_x11xfixes_h_

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES

#تعریف_کرو X11_BARRIER_HANDLED_BY_EVENT 1

خارجی خالی X11_InitXfixes(SDL_VideoDevice *_this);
خارجی bool X11_XfixesIsInitialized(خالی);
خارجی bool X11_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rect, صحیح flags);
خارجی خالی X11_Destroy_اشارہ_گر_Barrier(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی صحیح X11_GetXFixesSelectionNotifyEvent(خالی);
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES

#اگر_ختم // SDL_x11xfixes_h_
