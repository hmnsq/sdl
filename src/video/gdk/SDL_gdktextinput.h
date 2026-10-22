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

#اگر_تعریف_نشده SDL_gdktextinput_h_
#تعریف_کن SDL_gdktextinput_h_

#اگر_تعریف_شده SDL_GDK_TEXTINPUT
#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

#ضمن "../SDL_sysvideo.h"

فراغ GDK_EnsureHints(فراغ);

bool GDK_شروع_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props);
bool GDK_Stop_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
bool GDK_Update_متن_درون_داد_Area(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
فراغ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props);
فراغ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر
#پایان_اگر

#پایان_اگر
