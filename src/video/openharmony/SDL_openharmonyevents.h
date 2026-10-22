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

#ضمن "../SDL_sysvideo.h"

// src/core/openharmony/SDL_openharmony.c calls these when it gets events from the system.
خارجي فراغ SDL_OpenHarmonyDispatchTouchEvent(فراغ *component, فراغ *window);
خارجي فراغ SDL_OpenHarmonyDispatchMouseEvent(فراغ *component, فراغ *window);
خارجي فراغ SDL_Open_Harmony_Dispatch_مبودي_Event(فراغ *component, فراغ *window);
خارجي فراغ SDL_OpenHarmonyDispatchUIInputEvent(فراغ *component, فراغ *event, int32_t type);

خارجي فراغ OPENHARMONY_InitEvents(فراغ);
خارجي فراغ OPENHARMONY_PumpEvents(SDL_VideoDevice *_this);
خارجي فراغ OPENHARMONY_QuitEvents(فراغ);
