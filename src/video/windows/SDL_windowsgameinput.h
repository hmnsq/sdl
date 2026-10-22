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
#ضمن "SDL_internal.h"

تعريفنوع بنية WIN_Game_داخلہ_Data WIN_Game_داخلہ_Data;

// Set up for C function definitions, even when using C++
#ifdef __cplusplus
خارجي "C" {
#endif

خارجي bool WIN_Init_Game_داخلہ(SDL_VideoDevice *_this);
خارجي bool WIN_Update_Game_داخلہ_Enabled(SDL_VideoDevice *_this);
خارجي فراغ WIN_Update_Game_داخلہ(SDL_VideoDevice *_this);
خارجي فراغ WIN_Quit_Game_داخلہ(SDL_VideoDevice *_this);

// Ends C function definitions when using C++
#ifdef __cplusplus
}
#endif
