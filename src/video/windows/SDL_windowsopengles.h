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

#अगर_अघोषित SDL_winopengles_h_
#घोषणा SDL_winopengles_h_

#अगर_घोषित SDL_VIDEO_OPENGL_EGL

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_egl_c.h"

// OpenGLES functions
#घोषणा WIN_GLES_GetAttribute    SDL_EGL_GetAttribute
#घोषणा WIN_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#घोषणा WIN_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#घोषणा WIN_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#घोषणा WIN_GLES_SetSwapInterval SDL_EGL_SetSwapInterval

बाह्य bool WIN_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य bool WIN_GLES_SetupWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window);

#पूर्ण_अगर // SDL_VIDEO_OPENGL_EGL

#पूर्ण_अगर // SDL_winopengles_h_
