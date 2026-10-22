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

#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_waylandshmbuffer_h_
#define SDL_waylandshmbuffer_h_

প্রকারনির্দেশ সংরচনা Wayland_SHMPool Wayland_SHMPool;

বাহ্য Wayland_SHMPool *Wayland_AllocSHMPool(পূর্ণাঙ্ক size);
বাহ্য সংরচনা wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, শূন্য **data);
বাহ্য শূন্য Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool);

বাহ্য সংরচনা wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a);

#endif
