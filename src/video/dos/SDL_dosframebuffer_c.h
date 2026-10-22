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

#ifndef SDL_dosframebuffer_c_h_
#define SDL_dosframebuffer_c_h_

#அந்தர்பாவ "SDL_internal.h"

வெளி bool DOSVESA_CreateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, SDL_PixelFormat *format, வெறுமை **pixels, முழு *pitch);
வெளி bool DOSVESA_UpdateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, மாறிலி SDL_Rect *rects, முழு numrects);
வெளி வெறுமை DOSVESA_DestroyWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window);
வெளி bool DOSVESA_SetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, முழு vsync);
வெளி bool DOSVESA_GetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, முழு *vsync);
வெளி வெறுமை DOSVESA_InvalidateCachedFramebuffer(வெறுமை);

#endif // SDL_dosframebuffer_c_h_
