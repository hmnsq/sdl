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

#ifndef SDL_androidmouse_h_
#define SDL_androidmouse_h_

#ଅନ୍ତର୍ଭାଵ "SDL_androidvideo.h"

ବାହ୍ୟ ଶୂନ୍ୟ Android_InitMouse(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ Android_OnMouse(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା button, ପୂର୍ଣ୍ଣସଂଖ୍ୟା action, ଦଶମିକ x, ଦଶମିକ y, bool relative);
ବାହ୍ୟ ଶୂନ୍ୟ Android_QuitMouse(ଶୂନ୍ୟ);

#endif // SDL_androidmouse_h_
