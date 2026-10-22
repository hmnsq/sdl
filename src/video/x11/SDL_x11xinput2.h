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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_x11xinput2_h_
#تعریف_کرو SDL_x11xinput2_h_

#اگر_غیر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
/* Define XGenericEventCookie as forward declaration when
 *xinput2 is not available in order to compile */
ساخت XGenericEventCookie;
قسمتعریف ساخت XGenericEventCookie XGenericEventCookie;
#اگر_ختم

خارجی bool X11_InitXinput2(SDL_VideoDevice *_this);
خارجی خالی X11_QuitXinput2(SDL_VideoDevice *_this);
خارجی خالی X11_InitXinput2Multitouch(SDL_VideoDevice *_this);
خارجی خالی X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie);
خارجی bool X11_Xinput2IsInitialized(خالی);
خارجی خالی X11_Xinput2Select(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Xinput2UpdateDevices(SDL_VideoDevice *_this);
خارجی خالی X11_Xinput2_Update_اشارہ_گر_Mapping(SDL_VideoDevice *_this);
خارجی bool X11_Xinput2_Handles_Motion_For_کھڑکی(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2);

#اگر_ختم // SDL_x11xinput2_h_
