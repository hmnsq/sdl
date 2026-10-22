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

#ifndef SDL_vitatouch_h
#define SDL_vitatouch_h

#অন্তর্ভাব "SDL_internal.h"

// Touch functions
বাহ্য শূন্য VITA_InitTouch(শূন্য);
বাহ্য শূন্য VITA_QuitTouch(শূন্য);
বাহ্য শূন্য VITA_PollTouch(শূন্য);
শূন্য VITA_ConvertTouchXYToSDLXY(ভিন্ন *sdl_x, ভিন্ন *sdl_y, পূর্ণাঙ্ক vita_x, পূর্ণাঙ্ক vita_y, পূর্ণাঙ্ক port);

#endif // SDL_vitatouch_h
