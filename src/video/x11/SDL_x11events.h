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

#ifndef SDL_x11events_h_
#define SDL_x11events_h_

बाह्य शून्य X11_PumpEvents(SDL_VideoDevice *_this);
बाह्य पूर्णाङ्क X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
बाह्य शून्य X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
बाह्य शून्य X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
बाह्य शून्य X11_Get_Border_मूल्यावली(SDL_WindowData *data);
बाह्य Uint64 X11_GetEventTimestamp(unsigned long time);
बाह्य शून्य X11_Handle_कुंजी_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
बाह्य शून्य X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, भिन्न x, भिन्न y, unsigned long time, unsigned long serial);
बाह्य शून्य X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, unsigned long time);
बाह्य SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window);
बाह्य bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, ध्रुव भिन्न x, ध्रुव भिन्न y, bool force_new_result);
बाह्य bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, ध्रुव भिन्न x, ध्रुव भिन्न y);
बाह्य bool X11_IsWheelEvent(पूर्णाङ्क button, पूर्णाङ्क *xticks, पूर्णाङ्क *yticks);

#endif // SDL_x11events_h_
