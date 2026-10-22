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

#اگر_غیر_تعریف_شدہ SDL_x11xsync_h_
#تعریف_کرو SDL_x11xsync_h_

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC

خارجی خالی X11_InitXsync(SDL_VideoDevice *_this);
خارجی bool X11_XsyncIsInitialized(خالی);
خارجی bool X11_InitResizeSync(SDL_کھڑکی *کھڑکی);
خارجی خالی X11_رکن_Resize_Sync(SDL_کھڑکی *کھڑکی);
خارجی خالی X11_HandleSyncRequest(SDL_کھڑکی *کھڑکی, XClient_پیغام_Event *event);
خارجی خالی X11_HandleConfigure(SDL_کھڑکی *کھڑکی, XConfigureEvent *event);
خارجی خالی X11_HandlePresent(SDL_کھڑکی *کھڑکی);

#اگر_ختم // SDL_VIDEO_DRIVER_X11_XSYNC

#اگر_ختم // SDL_x11xsync_h_
