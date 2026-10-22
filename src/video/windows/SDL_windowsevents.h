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

#اگر_غیر_تعریف_شدہ SDL_windowsevents_h_
#تعریف_کرو SDL_windowsevents_h_

خارجی LPTSTR SDL_Appname;
خارجی Uint32 SDL_Appstyle;
خارجی HINSTANCE SDL_Instance;

خارجی LRESULT CALLBACK WIN_KeyboardHookProc(صحیح n_رمز, WPARAM wParam, LPARAM lParam);
خارجی LRESULT CALLBACK WIN_کھڑکی_Proc(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM lParam);
خارجی خالی WIN_Poll_Raw_داخلہ(SDL_VideoDevice *_this, Uint64 poll_آغاز);
خارجی خالی WIN_PumpEvents(SDL_VideoDevice *_this);
خارجی خالی WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd);
خارجی خالی WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی صحیح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

#اگر_ختم // SDL_windowsevents_h_
