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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_x11events_h_
#define SDL_x11events_h_

ବାହ୍ୟ ଶୂନ୍ୟ X11_PumpEvents(SDL_VideoDevice *_this);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
ବାହ୍ୟ ଶୂନ୍ୟ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ X11_Get_Border_ମୂଲ୍ୟଗୁଡ଼ିକ(SDL_WindowData *data);
ବାହ୍ୟ Uint64 X11_GetEventTimestamp(unsigned long time);
ବାହ୍ୟ ଶୂନ୍ୟ X11_Handle_ଚାବି_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
ବାହ୍ୟ ଶୂନ୍ୟ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, ପୂର୍ଣ୍ଣସଂଖ୍ୟା button, ଦଶମିକ x, ଦଶମିକ y, unsigned long time, unsigned long serial);
ବାହ୍ୟ ଶୂନ୍ୟ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, ପୂର୍ଣ୍ଣସଂଖ୍ୟା button, unsigned long time);
ବାହ୍ୟ SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window);
ବାହ୍ୟ bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, ଅଚଳ ଦଶମିକ x, ଅଚଳ ଦଶମିକ y, bool force_new_result);
ବାହ୍ୟ bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, ଅଚଳ ଦଶମିକ x, ଅଚଳ ଦଶମିକ y);
ବାହ୍ୟ bool X11_IsWheelEvent(ପୂର୍ଣ୍ଣସଂଖ୍ୟା button, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *xticks, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *yticks);

#endif // SDL_x11events_h_
