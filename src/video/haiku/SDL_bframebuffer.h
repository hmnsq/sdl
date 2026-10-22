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

#ifndef SDL_BFRAMEBUFFER_H
#define SDL_BFRAMEBUFFER_H
#অন্তর্ভাৱ <SupportDefs.h>
#ifdef __cplusplus
বাহ্য "C" {
#endif

#define DRAWTHREAD

#অন্তর্ভাৱ "../SDL_sysvideo.h"

বাহ্য bool HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window,
                                          SDL_PixelFormat *format,
                                          শূন্য **pixels, পূর্ণাঙ্ক *pitch);
বাহ্য bool HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window,
                                          ধ্রুৱ SDL_Rect *rects, পূর্ণাঙ্ক numrects);
বাহ্য শূন্য HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য int32 HAIKU_DrawThread(শূন্য *data);

#ifdef __cplusplus
}
#endif

#endif
