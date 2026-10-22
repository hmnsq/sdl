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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11keyboard_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11keyboard_h_

ਬਾਹਰੀ bool X11_InitKeyboard(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event);
ਬਾਹਰੀ ਖਾਲੀ X11_QuitKeyboard(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ X11_Create_ਨਿਵੇਸ਼_Context(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ X11_Destroy_ਨਿਵੇਸ਼_Context(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ X11_ClearComposition(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ bool X11_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
ਬਾਹਰੀ bool X11_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
ਬਾਹਰੀ ਖਾਲੀ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

#ਜੇ_ਅੰਤ // SDL_x11keyboard_h_
