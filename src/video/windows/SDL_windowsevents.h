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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_windowsevents_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_windowsevents_h_

ਬਾਹਰੀ LPTSTR SDL_Appname;
ਬਾਹਰੀ Uint32 SDL_Appstyle;
ਬਾਹਰੀ HINSTANCE SDL_Instance;

ਬਾਹਰੀ LRESULT CALLBACK WIN_KeyboardHookProc(ਪੂਰਨ n_ਕੋਡ, WPARAM wParam, LPARAM lParam);
ਬਾਹਰੀ LRESULT CALLBACK WIN_ਖਿੜਕੀ_Proc(HWND hwnd, UINT ਸੁਨੇਹਾ_2, WPARAM wParam, LPARAM lParam);
ਬਾਹਰੀ ਖਾਲੀ WIN_Poll_Raw_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, Uint64 poll_ਸ਼ੁਰੂ);
ਬਾਹਰੀ ਖਾਲੀ WIN_PumpEvents(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd);
ਬਾਹਰੀ ਖਾਲੀ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਪੂਰਨ WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

#ਜੇ_ਅੰਤ // SDL_windowsevents_h_
