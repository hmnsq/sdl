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

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#अन्तर्भाव "SDL_kmsdrmvideo.h"
#अन्तर्भाव "SDL_kmsdrmevents.h"

#ifdef SDL_आदान_LINUXEV
#अन्तर्भाव "../../core/linux/SDL_evdev.h"
#नोचेद्यदि defined SDL_आदान_WSCONS
#अन्तर्भाव "../../core/openbsd/SDL_wscons.h"
#endif

शून्य KMSDRM_PumpEvents(SDL_VideoDevice *_this)
{
#ifdef SDL_आदान_LINUXEV
    SDL_EVDEV_Poll();
#नोचेद्यदि defined SDL_आदान_WSCONS
    SDL_WSCONS_PumpEvents();
#endif
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
