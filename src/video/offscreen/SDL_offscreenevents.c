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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OFFSCREEN

/* Being a offscreen driver, there's no event stream. We just define stubs for
   most of the API. */

#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_offscreenvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenevents_c.h"

ಶೂನ್ಯ OFFSCREEN_PumpEvents(SDL_VideoDevice *_this)
{
    // do nothing.
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OFFSCREEN
