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

#ifndef SDL_windowsevents_h_
#define SDL_windowsevents_h_

বাহ্যিক LPTSTR SDL_Appname;
বাহ্যিক Uint32 SDL_Appstyle;
বাহ্যিক HINSTANCE SDL_Instance;

বাহ্যিক LRESULT CALLBACK WIN_KeyboardHookProc(পূর্ণসংখ্যা nCode, WPARAM wParam, LPARAM lParam);
বাহ্যিক LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM lParam);
বাহ্যিক শূন্য WIN_Poll_Raw_প্রবেশ(SDL_VideoDevice *_this, Uint64 poll_start);
বাহ্যিক শূন্য WIN_PumpEvents(SDL_VideoDevice *_this);
বাহ্যিক শূন্য WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd);
বাহ্যিক শূন্য WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক পূর্ণসংখ্যা WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

#endif // SDL_windowsevents_h_
