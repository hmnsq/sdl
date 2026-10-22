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

#यदि_अपरिभाषितम् SDL_x11xsync_h_
#परिभाषय SDL_x11xsync_h_

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC

बाह्य शून्य X11_InitXsync(SDL_VideoDevice *_this);
बाह्य bool X11_XsyncIsInitialized(शून्य);
बाह्य bool X11_InitResizeSync(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_पदांशः_Resize_Sync(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_HandleSyncRequest(SDL_गवाक्षः *गवाक्षः, XClient_सन्देशः_Event *event);
बाह्य शून्य X11_HandleConfigure(SDL_गवाक्षः *गवाक्षः, XConfigureEvent *event);
बाह्य शून्य X11_HandlePresent(SDL_गवाक्षः *गवाक्षः);

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XSYNC

#यदि_अन्तः // SDL_x11xsync_h_
