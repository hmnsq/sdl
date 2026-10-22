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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_vitatouch_h
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_vitatouch_h

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

// Touch functions
ਬਾਹਰੀ ਖਾਲੀ VITA_InitTouch(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_QuitTouch(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_PollTouch(ਖਾਲੀ);
ਖਾਲੀ VITA_ConvertTouchXYToSDLXY(ਦਸ਼ਮਲਵ *sdl_x, ਦਸ਼ਮਲਵ *sdl_y, ਪੂਰਨ vita_x, ਪੂਰਨ vita_y, ਪੂਰਨ ਪੋਰਟ);

#ਜੇ_ਅੰਤ // SDL_vitatouch_h
