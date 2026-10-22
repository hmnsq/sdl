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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_vivanteplatform_h_
#घोषणा SDL_vivanteplatform_h_

#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE

#समावेश "SDL_vivantevideo.h"

#अगर_घोषित CAVIUM
#घोषणा VIVANTE_PLATFORM_CAVIUM
#या_अगर defined(MARVELL)
#घोषणा VIVANTE_PLATFORM_MARVELL
#अन्यथा
#घोषणा VIVANTE_PLATFORM_GENERIC
#पूर्ण_अगर

बाह्य bool VIVANTE_SetupPlatform(SDL_VideoDevice *_this);
बाह्य अक्षर *VIVANTE_GetDisplayName(SDL_VideoDevice *_this);
बाह्य व्योम VIVANTE_UpdateDisplayScale(SDL_VideoDevice *_this);
बाह्य व्योम VIVANTE_CleanupPlatform(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VIVANTE

#पूर्ण_अगर // SDL_vivanteplatform_h_
