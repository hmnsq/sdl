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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM

#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmevents.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_evdev.h"
#ಅಥವಾಆದರೆ defined SDL_ಒಳಹರಿವು_WSCONS
#ಅನ್ತರ್ಭಾವ "../../core/openbsd/SDL_wscons.h"
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ KMSDRM_PumpEvents(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_Poll();
#ಅಥವಾಆದರೆ defined SDL_ಒಳಹರಿವು_WSCONS
    SDL_WSCONS_PumpEvents();
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_KMSDRM
