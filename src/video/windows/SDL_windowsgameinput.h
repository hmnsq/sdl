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
#समावेश "SDL_internal.h"

प्रकार काष्ठा WIN_Game_निवेश_तथ्य WIN_Game_निवेश_तथ्य;

// Set up for C function definitions, even when using C++
#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

बाह्य bool WIN_Init_Game_निवेश(SDL_VideoDevice *_this);
बाह्य bool WIN_Update_Game_निवेश_Enabled(SDL_VideoDevice *_this);
बाह्य व्योम WIN_Update_Game_निवेश(SDL_VideoDevice *_this);
बाह्य व्योम WIN_Quit_Game_निवेश(SDL_VideoDevice *_this);

// Ends C function definitions when using C++
#अगर_घोषित __cplusplus
}
#पूर्ण_अगर
