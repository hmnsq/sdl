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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_androidvideo.h"

ബാഹ്യ ശൂന്യം Android_On_താക്കോൽ_Down(പൂർണ്ണസംഖ്യ keycode);
ബാഹ്യ ശൂന്യം Android_On_താക്കോൽ_Up(പൂർണ്ണസംഖ്യ keycode);

ബാഹ്യ bool Android_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം Android_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
ബാഹ്യ ശൂന്യം Android_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Android_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);
