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
#شامل "SDL_internal.h"

#ifndef SDL_x11events_h_
#define SDL_x11events_h_

بیرونی تهی X11_PumpEvents(SDL_VideoDevice *_this);
بیرونی صحیح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
بیرونی تهی X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
بیرونی تهی X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
بیرونی تهی X11_Get_Border_مقادیر(SDL_WindowData *data);
بیرونی Uint64 X11_GetEventTimestamp(unsigned long time);
بیرونی تهی X11_Handle_کلید_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
بیرونی تهی X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, صحیح button, اعشاری x, اعشاری y, unsigned long time, unsigned long serial);
بیرونی تهی X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, صحیح button, unsigned long time);
بیرونی SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window);
بیرونی bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, ثابت اعشاری x, ثابت اعشاری y, bool force_new_result);
بیرونی bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, ثابت اعشاری x, ثابت اعشاری y);
بیرونی bool X11_IsWheelEvent(صحیح button, صحیح *xticks, صحیح *yticks);

#endif // SDL_x11events_h_
