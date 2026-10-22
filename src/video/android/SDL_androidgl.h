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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_androidgl_h_
#परिभाषय SDL_androidgl_h_

बाह्य SDL_GLContext Android_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Android_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context);
बाह्य bool Android_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Android_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);

#यदि_अन्तः // SDL_androidgl_h_
