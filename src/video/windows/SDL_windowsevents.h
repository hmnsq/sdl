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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_windowsevents_h_
#నిర్వచించు SDL_windowsevents_h_

బాహ్య LPTSTR SDL_Appname;
బాహ్య Uint32 SDL_Appstyle;
బాహ్య HINSTANCE SDL_Instance;

బాహ్య LRESULT CALLBACK WIN_KeyboardHookProc(పూర్ణాంకం n_సంకేతం, WPARAM wParam, LPARAM lParam);
బాహ్య LRESULT CALLBACK WIN_కిటికీ_Proc(HWND hwnd, UINT సందేశం_2, WPARAM wParam, LPARAM lParam);
బాహ్య శూన్య WIN_Poll_Raw_ఆదానం(SDL_VideoDevice *_this, Uint64 poll_ప్రారంభం);
బాహ్య శూన్య WIN_PumpEvents(SDL_VideoDevice *_this);
బాహ్య శూన్య WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd);
బాహ్య శూన్య WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య పూర్ణాంకం WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

#అయితే_ముగింపు // SDL_windowsevents_h_
