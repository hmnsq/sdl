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

#جيڪڏهن_وصف_نه_ٿيل SDL_BWINDOW_H
#وصف_ڪريو SDL_BWINDOW_H

#ضمن "../SDL_sysvideo.h"

خارجي bool HAIKU_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
خارجي فراغ HAIKU_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool HAIKU_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_سيٽ_دري_Minimum_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ HAIKU_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered);
خارجي فراغ HAIKU_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable);
خارجي SDL_Fullscreen_نتيجو HAIKU_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي bool HAIKU_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي bool HAIKU_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد);
خارجي bool HAIKU_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal);
خارجي فراغ HAIKU_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);

#جيڪڏهن_پورو
