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

#جيڪڏهن_وصف_نه_ٿيل SDL_gdktextinput_h_
#وصف_ڪريو SDL_gdktextinput_h_

#جيڪڏهن_وصف_ٿيل SDL_GDK_TEXTINPUT
#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

#ضمن "../SDL_sysvideo.h"

فراغ GDK_EnsureHints(فراغ);

bool GDK_شروعات_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
bool GDK_Stop_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري);
bool GDK_Update_متن_داخلا_Area(SDL_VideoDevice *_this, SDL_دري *دري);
bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_دري *دري);

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
فراغ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
فراغ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري);

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_پورو
