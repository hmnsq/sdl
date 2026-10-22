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

#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_waylandshmbuffer_h_
#परिभाषय SDL_waylandshmbuffer_h_

प्रकारनिर्देश संरचना Wayland_SHMPool Wayland_SHMPool;

बाह्य Wayland_SHMPool *Wayland_AllocSHMPool(पूर्णाङ्क आकार);
बाह्य संरचना wl_बफर *Wayland_Alloc_बफर_From_Pool(Wayland_SHMPool *shmPool, पूर्णाङ्क विस्तारः, पूर्णाङ्क height, शून्य **दत्त);
बाह्य शून्य Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool);

बाह्य संरचना wl_बफर *Wayland_Create_Single_Pixel_बफर(Uint32 r, Uint32 g, Uint32 b, Uint32 a);

#यदि_अन्तः
