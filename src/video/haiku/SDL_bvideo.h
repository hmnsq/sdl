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

#جے_بنا_تعریف BVIDEO_H
#تعریف_کرو BVIDEO_H

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

#ضمن "../../core/haiku/SDL_BeApp.h"
#ضمن "../SDL_sysvideo.h"

خارجي فراغ HAIKU_VideoQuit(SDL_VideoDevice *_this);
خارجي bool HAIKU_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ HAIKU_DeleteDevice(SDL_VideoDevice *_this);

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
