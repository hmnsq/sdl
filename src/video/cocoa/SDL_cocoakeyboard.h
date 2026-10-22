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

#ifndef SDL_cocoakeyboard_h_
#define SDL_cocoakeyboard_h_

بیرونی تهی Cocoa_InitKeyboard(SDL_VideoDevice *_this);
بیرونی تهی Cocoa_Handle_کلید_Event(SDL_VideoDevice *_this, NSEvent *event);
بیرونی تهی Cocoa_QuitKeyboard(SDL_VideoDevice *_this);

بیرونی bool Cocoa_Start_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
بیرونی bool Cocoa_Stop_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Cocoa_Update_Text_درون_داد_Area(SDL_VideoDevice *_this, SDL_Window *window);

بیرونی bool Cocoa_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);

#endif // SDL_cocoakeyboard_h_
