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
#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_windowsmouse_h_
#define SDL_windowsmouse_h_

বাহ্য DWORD SDL_last_warp_time;
বাহ্য HCURSOR SDL_cursor;

বাহ্য শূন্য WIN_InitMouse(SDL_VideoDevice *_this);
বাহ্য শূন্য WIN_QuitMouse(SDL_VideoDevice *_this);
বাহ্য শূন্য WIN_SetCursorPos(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y);
বাহ্য শূন্য WIN_UpdateMouseSystemScale(শূন্য);

#endif // SDL_windowsmouse_h_
