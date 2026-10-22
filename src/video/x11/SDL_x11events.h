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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_x11events_h_
#define SDL_x11events_h_

બાહ્ય શૂન્ય X11_PumpEvents(SDL_VideoDevice *_this);
બાહ્ય પૂર્ણાંક X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
બાહ્ય શૂન્ય X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય X11_Get_Border_કિંમતો(SDL_WindowData *data);
બાહ્ય Uint64 X11_GetEventTimestamp(unsigned long time);
બાહ્ય શૂન્ય X11_Handle_ચાવી_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
બાહ્ય શૂન્ય X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, પૂર્ણાંક button, દશાંશ x, દશાંશ y, unsigned long time, unsigned long serial);
બાહ્ય શૂન્ય X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, પૂર્ણાંક button, unsigned long time);
બાહ્ય SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window);
બાહ્ય bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, અચલ દશાંશ x, અચલ દશાંશ y, bool force_new_result);
બાહ્ય bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, અચલ દશાંશ x, અચલ દશાંશ y);
બાહ્ય bool X11_IsWheelEvent(પૂર્ણાંક button, પૂર્ણાંક *xticks, પૂર્ણાંક *yticks);

#endif // SDL_x11events_h_
