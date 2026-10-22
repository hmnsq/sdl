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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11xsync_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11xsync_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC

ಬಾಹ್ಯ ಶೂನ್ಯ X11_InitXsync(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool X11_XsyncIsInitialized(ಶೂನ್ಯ);
ಬಾಹ್ಯ bool X11_InitResizeSync(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಪದ_Resize_Sync(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandleSyncRequest(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, XClient_ಸಂದೇಶ_Event *event);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandleConfigure(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, XConfigureEvent *event);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandlePresent(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XSYNC

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11xsync_h_
