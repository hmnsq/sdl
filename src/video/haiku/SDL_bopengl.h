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

#अगर_अघोषित SDL_BOPENGL_H
#घोषणा SDL_BOPENGL_H

#अगर defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

#समावेश "../SDL_sysvideo.h"

बाह्य bool HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);      // FIXME
बाह्य SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc); // FIXME
बाह्य व्योम HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this);                     // TODO
बाह्य bool HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                                SDL_GLContext context);
बाह्य bool HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval); // TODO
बाह्य bool HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval); // TODO
बाह्य bool HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

बाह्य व्योम HAIKU_GL_RebootContexts(SDL_VideoDevice *_this);

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL

#पूर्ण_अगर
