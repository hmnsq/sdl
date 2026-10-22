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

#جے_بنا_تعریف SDL_dosframebuffer_c_h_
#تعریف_کرو SDL_dosframebuffer_c_h_

#ضمن "SDL_internal.h"

خارجي bool DOSVESA_Create_کھڑکی_Framebuffer(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch);
خارجي bool DOSVESA_Update_کھڑکی_Framebuffer(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects);
خارجي فراغ DOSVESA_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی);
خارجي bool DOSVESA_سیٹ_کھڑکی_Framebuffer_VSync(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, صحيح vsync);
خارجي bool DOSVESA_Get_کھڑکی_Framebuffer_VSync(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, صحيح *vsync);
خارجي فراغ DOSVESA_InvalidateCachedFramebuffer(فراغ);

#جے_انت // SDL_dosframebuffer_c_h_
