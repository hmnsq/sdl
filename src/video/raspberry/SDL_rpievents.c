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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RPI

#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "SDL_rpivideo.h"
#شامل "SDL_rpievents_c.h"

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
#شامل "../../core/linux/SDL_evdev.h"
#اگر_ختم

خالی RPI_PumpEvents(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_Poll();
#اگر_ختم
}

#اگر_ختم // SDL_VIDEO_DRIVER_RPI
