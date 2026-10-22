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

#که_نه_تعریف_شوی SDL_windowsevents_h_
#تعریف_کړه SDL_windowsevents_h_

خارجي LPTSTR SDL_Appname;
خارجي Uint32 SDL_Appstyle;
خارجي HINSTANCE SDL_Instance;

خارجي LRESULT CALLBACK WIN_KeyboardHookProc(صحيح n_کوډ, WPARAM wParam, LPARAM lParam);
خارجي LRESULT CALLBACK WIN_کړکۍ_Proc(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM lParam);
خارجي فراغ WIN_Poll_Raw_ننوت(SDL_VideoDevice *_this, Uint64 poll_پیل);
خارجي فراغ WIN_PumpEvents(SDL_VideoDevice *_this);
خارجي فراغ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd);
خارجي فراغ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي صحيح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

#د_که_پای // SDL_windowsevents_h_
