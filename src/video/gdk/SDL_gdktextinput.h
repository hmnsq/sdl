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

#अगर_अघोषित SDL_gdktextinput_h_
#घोषणा SDL_gdktextinput_h_

#अगर_घोषित SDL_GDK_TEXTINPUT
#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

#समावेश "../SDL_sysvideo.h"

व्योम GDK_EnsureHints(व्योम);

bool GDK_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool GDK_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window);
bool GDK_Update_Text_निवेश_Area(SDL_VideoDevice *_this, SDL_Window *window);
bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window);

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
व्योम GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
व्योम GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर
