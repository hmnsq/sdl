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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_x11xinput2_h_
#परिभाषय SDL_x11xinput2_h_

#यदि_अपरिभाषितम् SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
/* Define XGenericEventCookie as forward declaration when
 *xinput2 is not available in order to compile */
संरचना XGenericEventCookie;
प्रकारनिर्देश संरचना XGenericEventCookie XGenericEventCookie;
#यदि_अन्तः

बाह्य bool X11_InitXinput2(SDL_VideoDevice *_this);
बाह्य शून्य X11_QuitXinput2(SDL_VideoDevice *_this);
बाह्य शून्य X11_InitXinput2Multitouch(SDL_VideoDevice *_this);
बाह्य शून्य X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie);
बाह्य bool X11_Xinput2IsInitialized(शून्य);
बाह्य शून्य X11_Xinput2Select(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Xinput2UpdateDevices(SDL_VideoDevice *_this);
बाह्य शून्य X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this);
बाह्य bool X11_Xinput2_Handles_Motion_For_गवाक्षः(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2);

#यदि_अन्तः // SDL_x11xinput2_h_
