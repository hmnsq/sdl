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

#यदि_अपरिभाषितम् SDL_x11events_h_
#परिभाषय SDL_x11events_h_

बाह्य शून्य X11_PumpEvents(SDL_VideoDevice *_this);
बाह्य पूर्णाङ्क X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
बाह्य शून्य X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
बाह्य शून्य X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
बाह्य शून्य X11_Get_Border_मानानि(SDL_गवाक्षः_दत्त *दत्त);
बाह्य Uint64 X11_GetEventTimestamp(अचिह्नित दीर्घ time);
बाह्य शून्य X11_Handle_कुञ्चिका_Event(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
बाह्य शून्य X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, भिन्न x, भिन्न y, अचिह्नित दीर्घ time, अचिह्नित दीर्घ serial);
बाह्य शून्य X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, अचिह्नित दीर्घ time);
बाह्य SDL_गवाक्षः_दत्त *X11_Find_गवाक्षः(SDL_Video_दत्त *videodata, गवाक्षः_2 गवाक्षः);
बाह्य bool X11_Process_लब्धम्_Test(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *दत्त, ध्रुव भिन्न x, ध्रुव भिन्न y, bool force_new_परिणाम);
बाह्य bool X11_Trigger_लब्धम्_Test_Action(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *दत्त, ध्रुव भिन्न x, ध्रुव भिन्न y);
बाह्य bool X11_IsWheelEvent(पूर्णाङ्क button, पूर्णाङ्क *xticks, पूर्णाङ्क *yticks);

#यदि_अन्तः // SDL_x11events_h_
