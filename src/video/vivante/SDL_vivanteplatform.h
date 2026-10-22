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

#నిర్వచితం_కాకపోతే SDL_vivanteplatform_h_
#నిర్వచించు SDL_vivanteplatform_h_

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE

#అన్తర్భావ "SDL_vivantevideo.h"

#నిర్వచితమైతే CAVIUM
#నిర్వచించు VIVANTE_PLATFORM_CAVIUM
#లేదావేళ defined(MARVELL)
#నిర్వచించు VIVANTE_PLATFORM_MARVELL
#లేకపోతే
#నిర్వచించు VIVANTE_PLATFORM_GENERIC
#అయితే_ముగింపు

బాహ్య bool VIVANTE_అమరిక_Platform(SDL_VideoDevice *_this);
బాహ్య అక్షరం *VIVANTE_GetDisplayName(SDL_VideoDevice *_this);
బాహ్య శూన్య VIVANTE_UpdateDisplayScale(SDL_VideoDevice *_this);
బాహ్య శూన్య VIVANTE_CleanupPlatform(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VIVANTE

#అయితే_ముగింపు // SDL_vivanteplatform_h_
