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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11events_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11events_h_

ಬಾಹ್ಯ ಶೂನ್ಯ X11_PumpEvents(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Get_Border_ಮೌಲ್ಯಗಳು(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ Uint64 X11_GetEventTimestamp(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸಮಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Handle_ಕೀಲಿ_Event(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata, SDL_MouseID mouseID, ಪೂರ್ಣಾಂಕ button, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸಮಯ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ serial);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata, SDL_MouseID mouseID, ಪೂರ್ಣಾಂಕ button, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸಮಯ);
ಬಾಹ್ಯ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *X11_ಕಂಡುಹಿಡಿ_ಕಿಟಕಿ(SDL_Video_ದತ್ತಾಂಶ *videodata, ಕಿಟಕಿ_2 ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_Process_ದೊರಕಿತು_Test(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ x, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ y, bool force_new_ಫಲಿತಾಂಶ);
ಬಾಹ್ಯ bool X11_Trigger_ದೊರಕಿತು_Test_Action(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ x, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ y);
ಬಾಹ್ಯ bool X11_IsWheelEvent(ಪೂರ್ಣಾಂಕ button, ಪೂರ್ಣಾಂಕ *xticks, ಪೂರ್ಣಾಂಕ *yticks);

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11events_h_
