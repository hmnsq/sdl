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

#اگر_تعریف_نشده SDL_BWINDOW_H
#تعریف_کن SDL_BWINDOW_H

#ضمن "../SDL_sysvideo.h"

خارجي bool HAIKU_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
خارجي فراغ HAIKU_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool HAIKU_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_مجموعه_پنجره_Minimum_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ HAIKU_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered);
خارجي فراغ HAIKU_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable);
خارجي SDL_Fullscreen_نتیجه HAIKU_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي bool HAIKU_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
خارجي bool HAIKU_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد);
خارجي bool HAIKU_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal);
خارجي فراغ HAIKU_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

#پایان_اگر
