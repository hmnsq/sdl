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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_NGAGE

#अन्तर्भाव "../SDL_sysvideo.h"

#यदि_अपरिभाषितम् _SDL_ngagevideo_h
#परिभाषय _SDL_ngagevideo_h

प्रकारनिर्देश संरचना SDL_Video_दत्त
{
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_VideoDisplay display;

} SDL_Video_दत्त;

#यदि_अन्तः // _SDL_ngagevideo_h

#यदि_अन्तः // SDL_VIDEO_DRIVER_NGAGE
