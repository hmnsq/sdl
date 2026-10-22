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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_gdktextinput_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_gdktextinput_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_GDK_TEXTINPUT
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

ਖਾਲੀ GDK_EnsureHints(ਖਾਲੀ);

bool GDK_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
bool GDK_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
bool GDK_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ਖਾਲੀ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
ਖਾਲੀ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
