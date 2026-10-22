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

#جيڪڏهن_وصف_نه_ٿيل SDL_windowskeyboard_h_
#وصف_ڪريو SDL_windowskeyboard_h_

خارجي فراغ WIN_InitKeyboard(SDL_VideoDevice *_this);
خارجي فراغ WIN_UpdateKeymap(bool send_event);
خارجي فراغ WIN_QuitKeyboard(SDL_VideoDevice *_this);

خارجي فراغ WIN_Reset_Dead_ڪنجيون(فراغ);

خارجي bool WIN_شروعات_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
خارجي bool WIN_Stop_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_Update_متن_داخلا_Area(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_دري *دري);

خارجي bool WIN_HandleIMEMessage(HWND hwnd, UINT نياپو, WPARAM wParam, LPARAM *lParam, بنية SDL_Video_معلومات *videodata);
خارجي فراغ WIN_UpdateIMECandidates(SDL_VideoDevice *_this);

#جيڪڏهن_پورو // SDL_windowskeyboard_h_
