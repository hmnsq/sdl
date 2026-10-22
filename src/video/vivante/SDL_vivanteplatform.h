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

#اگر_غیر_تعریف_شدہ SDL_vivanteplatform_h_
#تعریف_کرو SDL_vivanteplatform_h_

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE

#شامل "SDL_vivantevideo.h"

#اگر_تعریف_شدہ CAVIUM
#تعریف_کرو VIVANTE_PLATFORM_CAVIUM
#وگرنہ_اگر defined(MARVELL)
#تعریف_کرو VIVANTE_PLATFORM_MARVELL
#ورنہ
#تعریف_کرو VIVANTE_PLATFORM_GENERIC
#اگر_ختم

خارجی bool VIVANTE_تیاری_Platform(SDL_VideoDevice *_this);
خارجی حرف *VIVANTE_GetDisplayName(SDL_VideoDevice *_this);
خارجی خالی VIVANTE_UpdateDisplayScale(SDL_VideoDevice *_this);
خارجی خالی VIVANTE_CleanupPlatform(SDL_VideoDevice *_this);

#اگر_ختم // SDL_VIDEO_DRIVER_VIVANTE

#اگر_ختم // SDL_vivanteplatform_h_
