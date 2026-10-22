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

#ifdef SDL_VIDEO_DRIVER_N3DS

#ಅನ್ತರ್ಭಾವ <3ds.h>

#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dstouch.h"

ಶೂನ್ಯ N3DS_PumpEvents(SDL_VideoDevice *_this)
{
    hid_Scan_ಒಳಹರಿವು();
    N3DS_PollTouch(_this);

    ಯದಿ (!aptMainLoop()) {
        SDL_Event ev;
        ev.type = SDL_EVENT_QUIT;
        ev.common.timestamp = 0;
        SDL_ತಳ್ಳು_Event(&ev);
        ಪ್ರತ್ಯಾಗಮ;
    }
}

#endif // SDL_VIDEO_DRIVER_N3DS
