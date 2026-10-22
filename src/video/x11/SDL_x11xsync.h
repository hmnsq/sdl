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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11xsync_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11xsync_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC

ਬਾਹਰੀ ਖਾਲੀ X11_InitXsync(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool X11_XsyncIsInitialized(ਖਾਲੀ);
ਬਾਹਰੀ bool X11_InitResizeSync(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_ਪਦ_Resize_Sync(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_HandleSyncRequest(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, XClient_ਸੁਨੇਹਾ_Event *event);
ਬਾਹਰੀ ਖਾਲੀ X11_HandleConfigure(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, XConfigureEvent *event);
ਬਾਹਰੀ ਖਾਲੀ X11_HandlePresent(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XSYNC

#ਜੇ_ਅੰਤ // SDL_x11xsync_h_
