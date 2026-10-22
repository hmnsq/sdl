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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_windowsevents_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_windowsevents_h_

ಬಾಹ್ಯ LPTSTR SDL_Appname;
ಬಾಹ್ಯ Uint32 SDL_Appstyle;
ಬಾಹ್ಯ HINSTANCE SDL_Instance;

ಬಾಹ್ಯ LRESULT CALLBACK WIN_KeyboardHookProc(ಪೂರ್ಣಾಂಕ n_ಸಂಕೇತ, WPARAM wParam, LPARAM lParam);
ಬಾಹ್ಯ LRESULT CALLBACK WIN_ಕಿಟಕಿ_Proc(HWND hwnd, UINT ಸಂದೇಶ_2, WPARAM wParam, LPARAM lParam);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Poll_Raw_ಒಳಹರಿವು(SDL_VideoDevice *_this, Uint64 poll_ಆರಂಭ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_PumpEvents(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

#ಆದರೆ_ಅಂತ್ಯ // SDL_windowsevents_h_
