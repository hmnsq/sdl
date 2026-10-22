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

#ifndef SDL_BOPENGL_H
#define SDL_BOPENGL_H

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

#അന്തര്ഭാവ "../SDL_sysvideo.h"

ബാഹ്യ bool HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);      // FIXME
ബാഹ്യ SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc); // FIXME
ബാഹ്യ ശൂന്യം HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this);                     // TODO
ബാഹ്യ bool HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                                SDL_GLContext context);
ബാഹ്യ bool HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval); // TODO
ബാഹ്യ bool HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval); // TODO
ബാഹ്യ bool HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

ബാഹ്യ ശൂന്യം HAIKU_GL_RebootContexts(SDL_VideoDevice *_this);

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL

#endif
