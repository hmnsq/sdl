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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_waylandshmbuffer_h_
#నిర్వచించు SDL_waylandshmbuffer_h_

రకనిర్వచనం నిర్మాణం Wayland_SHMPool Wayland_SHMPool;

బాహ్య Wayland_SHMPool *Wayland_AllocSHMPool(పూర్ణాంకం కొలత);
బాహ్య నిర్మాణం wl_బఫరు *Wayland_Alloc_బఫరు_From_Pool(Wayland_SHMPool *shmPool, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, శూన్య **దత్తాంశం);
బాహ్య శూన్య Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool);

బాహ్య నిర్మాణం wl_బఫరు *Wayland_Create_Single_Pixel_బఫరు(Uint32 r, Uint32 g, Uint32 b, Uint32 a);

#అయితే_ముగింపు
