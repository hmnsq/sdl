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
#अगर_अघोषित SDL_uikitopengles_
#घोषणा SDL_uikitopengles_

#अगर defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#समावेश "../SDL_sysvideo.h"

बाह्य bool UIKit_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                                SDL_GLContext context);
बाह्य bool UIKit_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_GLContext UIKit_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool UIKit_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य SDL_FunctionPointer UIKit_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य bool UIKit_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);

बाह्य व्योम UIKit_GL_RestoreCurrentContext(व्योम);

#पूर्ण_अगर // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

#पूर्ण_अगर // SDL_uikitopengles_
