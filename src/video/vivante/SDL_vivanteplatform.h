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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_نه_ٿيل SDL_vivanteplatform_h_
#وصف_ڪريو SDL_vivanteplatform_h_

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE

#ضمن "SDL_vivantevideo.h"

#جيڪڏهن_وصف_ٿيل CAVIUM
#وصف_ڪريو VIVANTE_PLATFORM_CAVIUM
#وإلاإذا defined(MARVELL)
#وصف_ڪريو VIVANTE_PLATFORM_MARVELL
#وإلا
#وصف_ڪريو VIVANTE_PLATFORM_GENERIC
#جيڪڏهن_پورو

خارجي bool VIVANTE_تياري_Platform(SDL_VideoDevice *_this);
خارجي حرف *VIVANTE_GetDisplayName(SDL_VideoDevice *_this);
خارجي فراغ VIVANTE_UpdateDisplayScale(SDL_VideoDevice *_this);
خارجي فراغ VIVANTE_CleanupPlatform(SDL_VideoDevice *_this);

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VIVANTE

#جيڪڏهن_پورو // SDL_vivanteplatform_h_
