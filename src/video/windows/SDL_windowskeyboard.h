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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_windowskeyboard_h_
#घोषणा SDL_windowskeyboard_h_

बाह्य व्योम WIN_InitKeyboard(SDL_VideoDevice *_this);
बाह्य व्योम WIN_UpdateKeymap(bool send_event);
बाह्य व्योम WIN_QuitKeyboard(SDL_VideoDevice *_this);

बाह्य व्योम WIN_Reset_Dead_कुंजियाँ(व्योम);

बाह्य bool WIN_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
बाह्य bool WIN_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_Update_Text_निवेश_Area(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window);

बाह्य bool WIN_HandleIMEMessage(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM *lParam, काष्ठा SDL_Video_तथ्य *videodata);
बाह्य व्योम WIN_UpdateIMECandidates(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_windowskeyboard_h_
