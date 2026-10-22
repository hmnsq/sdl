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

#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_waylandshmbuffer_h_
#تعریف_کرو SDL_waylandshmbuffer_h_

قسمتعریف ساخت Wayland_SHMPool Wayland_SHMPool;

خارجی Wayland_SHMPool *Wayland_AllocSHMPool(صحیح سائز);
خارجی ساخت wl_بفر *Wayland_Alloc_بفر_From_Pool(Wayland_SHMPool *shmPool, صحیح چوڑائی, صحیح اونچائی, خالی **ڈیٹا);
خارجی خالی Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool);

خارجی ساخت wl_بفر *Wayland_Create_Single_Pixel_بفر(Uint32 r, Uint32 g, Uint32 b, Uint32 a);

#اگر_ختم
