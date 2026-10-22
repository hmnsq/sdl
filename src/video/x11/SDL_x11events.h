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

#اگر_غیر_تعریف_شدہ SDL_x11events_h_
#تعریف_کرو SDL_x11events_h_

خارجی خالی X11_PumpEvents(SDL_VideoDevice *_this);
خارجی صحیح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
خارجی خالی X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجی خالی X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
خارجی خالی X11_Get_Border_اقدار(SDL_کھڑکی_ڈیٹا *ڈیٹا);
خارجی Uint64 X11_GetEventTimestamp(غیرعلامتی طویل وقت);
خارجی خالی X11_Handle_کلید_Event(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
خارجی خالی X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windowdata, SDL_MouseID mouseID, صحیح button, اعشاری x, اعشاری y, غیرعلامتی طویل وقت, غیرعلامتی طویل serial);
خارجی خالی X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windowdata, SDL_MouseID mouseID, صحیح button, غیرعلامتی طویل وقت);
خارجی SDL_کھڑکی_ڈیٹا *X11_ڈھونڈو_کھڑکی(SDL_Video_ڈیٹا *videodata, کھڑکی_2 کھڑکی);
خارجی bool X11_Process_کامیابی_Test(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت اعشاری x, ثابت اعشاری y, bool force_new_نتیجہ);
خارجی bool X11_Trigger_کامیابی_Test_Action(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت اعشاری x, ثابت اعشاری y);
خارجی bool X11_IsWheelEvent(صحیح button, صحیح *xticks, صحیح *yticks);

#اگر_ختم // SDL_x11events_h_
