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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_x11xinput2_h_
#घोषणा SDL_x11xinput2_h_

#अगर_अघोषित SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
/* Define XGenericEventCookie as forward declaration when
 *xinput2 is not available in order to compile */
काष्ठा XGenericEventCookie;
प्रकार काष्ठा XGenericEventCookie XGenericEventCookie;
#पूर्ण_अगर

बाह्य bool X11_InitXinput2(SDL_VideoDevice *_this);
बाह्य व्योम X11_QuitXinput2(SDL_VideoDevice *_this);
बाह्य व्योम X11_InitXinput2Multitouch(SDL_VideoDevice *_this);
बाह्य व्योम X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie);
बाह्य bool X11_Xinput2IsInitialized(व्योम);
बाह्य व्योम X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_Xinput2UpdateDevices(SDL_VideoDevice *_this);
बाह्य व्योम X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this);
बाह्य bool X11_Xinput2HandlesMotionForWindow(SDL_Window_तथ्य *window_तथ्य_2);

#पूर्ण_अगर // SDL_x11xinput2_h_
