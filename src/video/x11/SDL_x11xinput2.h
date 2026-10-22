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

#جيڪڏهن_وصف_نه_ٿيل SDL_x11xinput2_h_
#وصف_ڪريو SDL_x11xinput2_h_

#جيڪڏهن_وصف_نه_ٿيل SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
/* Define XGenericEventCookie as forward declaration when
 *xinput2 is not available in order to compile */
بنية XGenericEventCookie;
تعريفنوع بنية XGenericEventCookie XGenericEventCookie;
#جيڪڏهن_پورو

خارجي bool X11_InitXinput2(SDL_VideoDevice *_this);
خارجي فراغ X11_QuitXinput2(SDL_VideoDevice *_this);
خارجي فراغ X11_InitXinput2Multitouch(SDL_VideoDevice *_this);
خارجي فراغ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie);
خارجي bool X11_Xinput2IsInitialized(فراغ);
خارجي فراغ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this);
خارجي فراغ X11_Xinput2_Update_اشارو_Mapping(SDL_VideoDevice *_this);
خارجي bool X11_Xinput2_Handles_Motion_For_دري(SDL_دري_معلومات *دري_معلومات_2);

#جيڪڏهن_پورو // SDL_x11xinput2_h_
