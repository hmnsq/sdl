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
#ଅନ୍ତର୍ଭାଵ <SupportDefs.h>
#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

#define DRAWTHREAD

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

ବାହ୍ୟ bool HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window,
                                          SDL_PixelFormat *format,
                                          ଶୂନ୍ୟ **pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch);
ବାହ୍ୟ bool HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window,
                                          ଅଚଳ SDL_Rect *rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects);
ବାହ୍ୟ ଶୂନ୍ୟ HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ int32 HAIKU_DrawThread(ଶୂନ୍ୟ *data);

#ifdef __cplusplus
}
#endif

#endif
