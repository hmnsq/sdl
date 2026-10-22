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

#اگر_غیر_تعریف_شدہ SDL_x11framebuffer_h_
#تعریف_کرو SDL_x11framebuffer_h_

#شامل "SDL_internal.h"

خارجی bool X11_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                                        SDL_PixelFormat *format,
                                        خالی **pixels, صحیح *pitch);
خارجی bool X11_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                                        ثابت SDL_Rect *rects, صحیح numrects);
خارجی خالی X11_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

#اگر_ختم // SDL_x11framebuffer_h_
