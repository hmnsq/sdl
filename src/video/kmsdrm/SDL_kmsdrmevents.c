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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM

#అన్తర్భావ "SDL_kmsdrmvideo.h"
#అన్తర్భావ "SDL_kmsdrmevents.h"

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
#అన్తర్భావ "../../core/linux/SDL_evdev.h"
#లేదావేళ defined SDL_ఆదానం_WSCONS
#అన్తర్భావ "../../core/openbsd/SDL_wscons.h"
#అయితే_ముగింపు

శూన్య KMSDRM_PumpEvents(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    SDL_EVDEV_Poll();
#లేదావేళ defined SDL_ఆదానం_WSCONS
    SDL_WSCONS_PumpEvents();
#అయితే_ముగింపు
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_KMSDRM
