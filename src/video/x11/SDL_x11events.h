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

#جيڪڏهن_وصف_نه_ٿيل SDL_x11events_h_
#وصف_ڪريو SDL_x11events_h_

خارجي فراغ X11_PumpEvents(SDL_VideoDevice *_this);
خارجي صحيح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
خارجي فراغ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجي فراغ X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
خارجي فراغ X11_Get_Border_قدرون(SDL_دري_معلومات *معلومات);
خارجي Uint64 X11_GetEventTimestamp(بنانشان ڊگهو وقت);
خارجي فراغ X11_Handle_ڪنجي_Event(SDL_VideoDevice *_this, SDL_دري_معلومات *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
خارجي فراغ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_دري_معلومات *windowdata, SDL_MouseID mouseID, صحيح button, عائم x, عائم y, بنانشان ڊگهو وقت, بنانشان ڊگهو serial);
خارجي فراغ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_دري_معلومات *windowdata, SDL_MouseID mouseID, صحيح button, بنانشان ڊگهو وقت);
خارجي SDL_دري_معلومات *X11_ڳوليو_دري(SDL_Video_معلومات *videodata, دري_2 دري);
خارجي bool X11_Process_ڪاميابي_Test(SDL_VideoDevice *_this, SDL_دري_معلومات *معلومات, ثابت عائم x, ثابت عائم y, bool force_new_نتيجو);
خارجي bool X11_Trigger_ڪاميابي_Test_Action(SDL_VideoDevice *_this, SDL_دري_معلومات *معلومات, ثابت عائم x, ثابت عائم y);
خارجي bool X11_IsWheelEvent(صحيح button, صحيح *xticks, صحيح *yticks);

#جيڪڏهن_پورو // SDL_x11events_h_
