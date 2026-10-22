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

#جے_بنا_تعریف SDL_x11events_h_
#تعریف_کرو SDL_x11events_h_

خارجي فراغ X11_PumpEvents(SDL_VideoDevice *_this);
خارجي صحيح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
خارجي فراغ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجي فراغ X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
خارجي فراغ X11_Get_Border_اقدار(SDL_کھڑکی_انکڑے *انکڑے);
خارجي Uint64 X11_GetEventTimestamp(بنانشانی لما ویلا);
خارجي فراغ X11_Handle_کلید_Event(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
خارجي فراغ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *windowdata, SDL_MouseID mouseID, صحيح button, عائم x, عائم y, بنانشانی لما ویلا, بنانشانی لما serial);
خارجي فراغ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *windowdata, SDL_MouseID mouseID, صحيح button, بنانشانی لما ویلا);
خارجي SDL_کھڑکی_انکڑے *X11_لبھو_کھڑکی(SDL_Video_انکڑے *videodata, کھڑکی_2 کھڑکی);
خارجي bool X11_Process_کامیابی_Test(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *انکڑے, ثابت عائم x, ثابت عائم y, bool force_new_نتیجہ);
خارجي bool X11_Trigger_کامیابی_Test_Action(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *انکڑے, ثابت عائم x, ثابت عائم y);
خارجي bool X11_IsWheelEvent(صحيح button, صحيح *xticks, صحيح *yticks);

#جے_انت // SDL_x11events_h_
