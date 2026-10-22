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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11events_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11events_h_

ਬਾਹਰੀ ਖਾਲੀ X11_PumpEvents(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਪੂਰਨ X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
ਬਾਹਰੀ ਖਾਲੀ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ X11_Get_Border_ਮੁੱਲਾਂ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ Uint64 X11_GetEventTimestamp(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸਮਾਂ);
ਬਾਹਰੀ ਖਾਲੀ X11_Handle_ਕੁੰਜੀ_Event(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
ਬਾਹਰੀ ਖਾਲੀ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata, SDL_MouseID mouseID, ਪੂਰਨ button, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸਮਾਂ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ serial);
ਬਾਹਰੀ ਖਾਲੀ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata, SDL_MouseID mouseID, ਪੂਰਨ button, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸਮਾਂ);
ਬਾਹਰੀ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *X11_ਲੱਭੋ_ਖਿੜਕੀ(SDL_Video_ਅੰਕੜੇ *videodata, ਖਿੜਕੀ_2 ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_Process_ਪ੍ਰਾਪਤੀ_Test(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ ਦਸ਼ਮਲਵ x, ਅਚਲ ਦਸ਼ਮਲਵ y, bool force_new_ਨਤੀਜਾ);
ਬਾਹਰੀ bool X11_Trigger_ਪ੍ਰਾਪਤੀ_Test_Action(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ ਦਸ਼ਮਲਵ x, ਅਚਲ ਦਸ਼ਮਲਵ y);
ਬਾਹਰੀ bool X11_IsWheelEvent(ਪੂਰਨ button, ਪੂਰਨ *xticks, ਪੂਰਨ *yticks);

#ਜੇ_ਅੰਤ // SDL_x11events_h_
