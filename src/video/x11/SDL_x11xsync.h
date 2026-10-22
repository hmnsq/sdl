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

#اگر_تعریف_نشده SDL_x11xsync_h_
#تعریف_کن SDL_x11xsync_h_

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC

خارجي فراغ X11_InitXsync(SDL_VideoDevice *_this);
خارجي bool X11_XsyncIsInitialized(فراغ);
خارجي bool X11_InitResizeSync(SDL_پنجره *پنجره);
خارجي فراغ X11_جمله_Resize_Sync(SDL_پنجره *پنجره);
خارجي فراغ X11_HandleSyncRequest(SDL_پنجره *پنجره, XClient_پیام_Event *event);
خارجي فراغ X11_HandleConfigure(SDL_پنجره *پنجره, XConfigureEvent *event);
خارجي فراغ X11_HandlePresent(SDL_پنجره *پنجره);

#پایان_اگر // SDL_VIDEO_DRIVER_X11_XSYNC

#پایان_اگر // SDL_x11xsync_h_
