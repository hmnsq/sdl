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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_windowskeyboard_h_
#define SDL_windowskeyboard_h_

बाह्य शून्य WIN_InitKeyboard(SDL_VideoDevice *_this);
बाह्य शून्य WIN_UpdateKeymap(bool send_event);
बाह्य शून्य WIN_QuitKeyboard(SDL_VideoDevice *_this);

बाह्य शून्य WIN_Reset_Dead_कुञ्चिकाः(शून्य);

बाह्य bool WIN_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
बाह्य bool WIN_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window);

बाह्य bool WIN_HandleIMEMessage(HWND hwnd, UINT सन्देशः, WPARAM wParam, LPARAM *lParam, संरचना SDL_VideoData *videodata);
बाह्य शून्य WIN_UpdateIMECandidates(SDL_VideoDevice *_this);

#endif // SDL_windowskeyboard_h_
