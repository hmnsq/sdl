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

#ifndef SDL_x11xfixes_h_
#define SDL_x11xfixes_h_

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES

#define X11_BARRIER_HANDLED_BY_EVENT 1

வெளி வெறுமை X11_InitXfixes(SDL_VideoDevice *_this);
வெளி bool X11_XfixesIsInitialized(வெறுமை);
வெளி bool X11_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rect, முழு flags);
வெளி வெறுமை X11_DestroyPointerBarrier(SDL_VideoDevice *_this, SDL_Window *window);
வெளி முழு X11_GetXFixesSelectionNotifyEvent(வெறுமை);
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

#endif // SDL_x11xfixes_h_
