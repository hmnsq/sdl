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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_x11events_h_
#define SDL_x11events_h_

ബാഹ്യ ശൂന്യം X11_PumpEvents(SDL_VideoDevice *_this);
ബാഹ്യ പൂർണ്ണസംഖ്യ X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
ബാഹ്യ ശൂന്യം X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം X11_Get_Border_മൂല്യങ്ങൾ(SDL_WindowData *data);
ബാഹ്യ Uint64 X11_GetEventTimestamp(unsigned long time);
ബാഹ്യ ശൂന്യം X11_Handle_താക്കോൽ_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
ബാഹ്യ ശൂന്യം X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, പൂർണ്ണസംഖ്യ button, ദശാംശം x, ദശാംശം y, unsigned long time, unsigned long serial);
ബാഹ്യ ശൂന്യം X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, പൂർണ്ണസംഖ്യ button, unsigned long time);
ബാഹ്യ SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window);
ബാഹ്യ bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, സ്ഥിരം ദശാംശം x, സ്ഥിരം ദശാംശം y, bool force_new_result);
ബാഹ്യ bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, സ്ഥിരം ദശാംശം x, സ്ഥിരം ദശാംശം y);
ബാഹ്യ bool X11_IsWheelEvent(പൂർണ്ണസംഖ്യ button, പൂർണ്ണസംഖ്യ *xticks, പൂർണ്ണസംഖ്യ *yticks);

#endif // SDL_x11events_h_
