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

#اگر_تعریف_نشده SDL_BFRAMEBUFFER_H
#تعریف_کن SDL_BFRAMEBUFFER_H
#ضمن <SupportDefs.h>
#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

#تعریف_کن DRAWTHREAD

#ضمن "../SDL_sysvideo.h"

خارجي bool HAIKU_Create_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره,
                                          SDL_PixelFormat *format,
                                          فراغ **pixels, صحيح *pitch);
خارجي bool HAIKU_Update_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره,
                                          ثابت SDL_Rect *rects, صحيح numrects);
خارجي فراغ HAIKU_Destroy_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي int32 HAIKU_DrawThread(فراغ *داده);

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
