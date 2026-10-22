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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_waylandshmbuffer_h_
#घोषणा SDL_waylandshmbuffer_h_

प्रकार काष्ठा Wayland_SHMPool Wayland_SHMPool;

बाह्य Wayland_SHMPool *Wayland_AllocSHMPool(पूर्णांक आकार);
बाह्य काष्ठा wl_बफर *Wayland_Alloc_बफर_From_Pool(Wayland_SHMPool *shmPool, पूर्णांक width, पूर्णांक height, व्योम **तथ्य);
बाह्य व्योम Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool);

बाह्य काष्ठा wl_बफर *Wayland_Create_Single_Pixel_बफर(Uint32 r, Uint32 g, Uint32 b, Uint32 a);

#पूर्ण_अगर
