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

#अगर_अघोषित SDL_rpiopengles_h_
#घोषणा SDL_rpiopengles_h_

#अगर defined(SDL_VIDEO_DRIVER_RPI) && defined(SDL_VIDEO_OPENGL_EGL)

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_egl_c.h"

// OpenGLES functions
#घोषणा RPI_GLES_GetAttribute    SDL_EGL_GetAttribute
#घोषणा RPI_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#घोषणा RPI_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#घोषणा RPI_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#घोषणा RPI_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#घोषणा RPI_GLES_DestroyContext   SDL_EGL_DestroyContext

बाह्य bool RPI_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool RPI_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य व्योम RPI_GLES_SetDefaultProfileConfig(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_VIDEO_DRIVER_RPI && SDL_VIDEO_OPENGL_EGL

#पूर्ण_अगर // SDL_rpiopengles_h_
