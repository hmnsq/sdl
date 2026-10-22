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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_windowskeyboard_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_windowskeyboard_h_

ಬಾಹ್ಯ ಶೂನ್ಯ WIN_InitKeyboard(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_UpdateKeymap(bool send_event);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_QuitKeyboard(SDL_VideoDevice *_this);

ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Reset_Dead_ಕೀಲಿಗಳು(ಶೂನ್ಯ);

ಬಾಹ್ಯ bool WIN_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
ಬಾಹ್ಯ bool WIN_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_ClearComposition(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

ಬಾಹ್ಯ bool WIN_HandleIMEMessage(HWND hwnd, UINT ಸಂದೇಶ_2, WPARAM wParam, LPARAM *lParam, ರಚನೆ SDL_Video_ದತ್ತಾಂಶ *videodata);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_UpdateIMECandidates(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_windowskeyboard_h_
