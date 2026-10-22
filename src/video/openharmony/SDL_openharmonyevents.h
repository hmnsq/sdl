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
#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ "../SDL_sysvideo.h"

// src/core/openharmony/SDL_openharmony.c calls these when it gets events from the system.
வெளி வெறுமை SDL_OpenHarmonyDispatchTouchEvent(வெறுமை *component, வெறுமை *window);
வெளி வெறுமை SDL_OpenHarmonyDispatchMouseEvent(வெறுமை *component, வெறுமை *window);
வெளி வெறுமை SDL_Open_Harmony_Dispatch_சாவி_Event(வெறுமை *component, வெறுமை *window);
வெளி வெறுமை SDL_OpenHarmonyDispatchUIInputEvent(வெறுமை *component, வெறுமை *event, int32_t type);

வெளி வெறுமை OPENHARMONY_InitEvents(வெறுமை);
வெளி வெறுமை OPENHARMONY_PumpEvents(SDL_VideoDevice *_this);
வெளி வெறுமை OPENHARMONY_QuitEvents(வெறுமை);
