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
#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_x11events_h_
#define SDL_x11events_h_

বাহ্য শূন্য X11_PumpEvents(SDL_VideoDevice *_this);
বাহ্য পূর্ণাঙ্ক X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
বাহ্য শূন্য X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
বাহ্য শূন্য X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
বাহ্য শূন্য X11_Get_Border_মানসমূহ(SDL_WindowData *data);
বাহ্য Uint64 X11_GetEventTimestamp(unsigned long time);
বাহ্য শূন্য X11_Handle_চাবি_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
বাহ্য শূন্য X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, পূর্ণাঙ্ক button, ভিন্ন x, ভিন্ন y, unsigned long time, unsigned long serial);
বাহ্য শূন্য X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, পূর্ণাঙ্ক button, unsigned long time);
বাহ্য SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window);
বাহ্য bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, ধ্রুৱ ভিন্ন x, ধ্রুৱ ভিন্ন y, bool force_new_result);
বাহ্য bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, ধ্রুৱ ভিন্ন x, ধ্রুৱ ভিন্ন y);
বাহ্য bool X11_IsWheelEvent(পূর্ণাঙ্ক button, পূর্ণাঙ্ক *xticks, পূর্ণাঙ্ক *yticks);

#endif // SDL_x11events_h_
