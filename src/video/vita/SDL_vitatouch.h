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

#अगर_अघोषित SDL_vitatouch_h
#घोषणा SDL_vitatouch_h

#समावेश "SDL_internal.h"

// Touch functions
बाह्य व्योम VITA_InitTouch(व्योम);
बाह्य व्योम VITA_QuitTouch(व्योम);
बाह्य व्योम VITA_PollTouch(व्योम);
व्योम VITA_ConvertTouchXYToSDLXY(भग्न *sdl_x, भग्न *sdl_y, पूर्णांक vita_x, पूर्णांक vita_y, पूर्णांक port);

#पूर्ण_अगर // SDL_vitatouch_h
