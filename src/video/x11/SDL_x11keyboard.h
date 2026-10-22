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

#جيڪڏهن_وصف_نه_ٿيل SDL_x11keyboard_h_
#وصف_ڪريو SDL_x11keyboard_h_

خارجي bool X11_InitKeyboard(SDL_VideoDevice *_this);
خارجي فراغ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event);
خارجي فراغ X11_QuitKeyboard(SDL_VideoDevice *_this);
خارجي فراغ X11_Create_داخلا_Context(SDL_دري_معلومات *معلومات);
خارجي فراغ X11_Destroy_داخلا_Context(SDL_دري_معلومات *معلومات);
خارجي فراغ X11_ClearComposition(SDL_دري_معلومات *معلومات);
خارجي bool X11_شروعات_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
خارجي bool X11_Stop_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_Update_متن_داخلا_Area(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجي فراغ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
خارجي فراغ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري);

#جيڪڏهن_پورو // SDL_x11keyboard_h_
