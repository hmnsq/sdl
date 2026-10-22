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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_BFRAMEBUFFER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_BFRAMEBUFFER_H
#ਅਨ੍ਤਰ੍ਭਾਵ <SupportDefs.h>
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRAWTHREAD

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

ਬਾਹਰੀ bool HAIKU_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                          SDL_PixelFormat *format,
                                          ਖਾਲੀ **pixels, ਪੂਰਨ *pitch);
ਬਾਹਰੀ bool HAIKU_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                          ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects);
ਬਾਹਰੀ ਖਾਲੀ HAIKU_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ int32 HAIKU_DrawThread(ਖਾਲੀ *ਅੰਕੜੇ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
