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

#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_نه_ٿيل SDL_x11xfixes_h_
#وصف_ڪريو SDL_x11xfixes_h_

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES

#وصف_ڪريو X11_BARRIER_HANDLED_BY_EVENT 1

خارجي فراغ X11_InitXfixes(SDL_VideoDevice *_this);
خارجي bool X11_XfixesIsInitialized(فراغ);
خارجي bool X11_سيٽ_دري_Mouse_Rect(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rect, صحيح flags);
خارجي فراغ X11_Destroy_اشارو_Barrier(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي صحيح X11_GetXFixesSelectionNotifyEvent(فراغ);
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES

#جيڪڏهن_پورو // SDL_x11xfixes_h_
