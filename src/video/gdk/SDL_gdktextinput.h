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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_gdktextinput_h_
#define SDL_gdktextinput_h_

#ifdef SDL_GDK_TEXTINPUT
#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

ଶୂନ୍ୟ GDK_EnsureHints(ଶୂନ୍ୟ);

bool GDK_Start_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool GDK_Stop_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window);
bool GDK_Update_Text_ନିବେଶ_Area(SDL_VideoDevice *_this, SDL_Window *window);
bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window);

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ଶୂନ୍ୟ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
ଶୂନ୍ୟ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

#ifdef __cplusplus
}
#endif
#endif

#endif
