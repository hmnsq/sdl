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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "../SDL_sysvideo.h"

// src/core/openharmony/SDL_openharmony.c calls these when it gets events from the system.
ബാഹ്യ ശൂന്യം SDL_OpenHarmonyDispatchTouchEvent(ശൂന്യം *component, ശൂന്യം *window);
ബാഹ്യ ശൂന്യം SDL_OpenHarmonyDispatchMouseEvent(ശൂന്യം *component, ശൂന്യം *window);
ബാഹ്യ ശൂന്യം SDL_Open_Harmony_Dispatch_താക്കോൽ_Event(ശൂന്യം *component, ശൂന്യം *window);
ബാഹ്യ ശൂന്യം SDL_OpenHarmonyDispatchUIInputEvent(ശൂന്യം *component, ശൂന്യം *event, int32_t type);

ബാഹ്യ ശൂന്യം OPENHARMONY_InitEvents(ശൂന്യം);
ബാഹ്യ ശൂന്യം OPENHARMONY_PumpEvents(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം OPENHARMONY_QuitEvents(ശൂന്യം);
