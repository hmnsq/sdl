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

#اگر_تعریف_نشده SDL_windowsrawinput_h_
#تعریف_کن SDL_windowsrawinput_h_

خارجي فراغ WIN_Quit_Raw_درون_داد(SDL_VideoDevice *_this);
خارجي bool WIN_مجموعه_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled);
خارجي bool WIN_مجموعه_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled);
خارجي bool WIN_مجموعه_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled);
خارجي bool WIN_مجموعه_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled);
خارجي bool WIN_مجموعه_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled);

#پایان_اگر // SDL_windowsrawinput_h_
