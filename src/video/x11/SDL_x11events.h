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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_x11events_h_
#define SDL_x11events_h_

বাহ্যিক শূন্য X11_PumpEvents(SDL_VideoDevice *_this);
বাহ্যিক পূর্ণসংখ্যা X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
বাহ্যিক শূন্য X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
বাহ্যিক শূন্য X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
বাহ্যিক শূন্য X11_Get_Border_মানসমূহ(SDL_Window_তথ্য *তথ্য);
বাহ্যিক Uint64 X11_GetEventTimestamp(unsigned long time);
বাহ্যিক শূন্য X11_Handle_চাবি_Event(SDL_VideoDevice *_this, SDL_Window_তথ্য *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
বাহ্যিক শূন্য X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_Window_তথ্য *windowdata, SDL_MouseID mouseID, পূর্ণসংখ্যা button, দশমিক x, দশমিক y, unsigned long time, unsigned long serial);
বাহ্যিক শূন্য X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_Window_তথ্য *windowdata, SDL_MouseID mouseID, পূর্ণসংখ্যা button, unsigned long time);
বাহ্যিক SDL_Window_তথ্য *X11_FindWindow(SDL_Video_তথ্য *videodata, Window window);
বাহ্যিক bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_Window_তথ্য *তথ্য, ধ্রুবক দশমিক x, ধ্রুবক দশমিক y, bool force_new_ফলাফল);
বাহ্যিক bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_Window_তথ্য *তথ্য, ধ্রুবক দশমিক x, ধ্রুবক দশমিক y);
বাহ্যিক bool X11_IsWheelEvent(পূর্ণসংখ্যা button, পূর্ণসংখ্যা *xticks, পূর্ণসংখ্যা *yticks);

#endif // SDL_x11events_h_
