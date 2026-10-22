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

#यदि_अपरिभाषितम् SDL_x11xfixes_h_
#परिभाषय SDL_x11xfixes_h_

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES

#परिभाषय X11_BARRIER_HANDLED_BY_EVENT 1

बाह्य शून्य X11_InitXfixes(SDL_VideoDevice *_this);
बाह्य bool X11_XfixesIsInitialized(शून्य);
बाह्य bool X11_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rect, पूर्णाङ्क flags);
बाह्य शून्य X11_DestroyPointerBarrier(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य पूर्णाङ्क X11_GetXFixesSelectionNotifyEvent(शून्य);
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES

#यदि_अन्तः // SDL_x11xfixes_h_
