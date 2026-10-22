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

#अगर_अघोषित SDL_x11opengles_h_
#घोषणा SDL_x11opengles_h_

#अगर_घोषित SDL_VIDEO_OPENGL_EGL

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_egl_c.h"

प्रकार काष्ठा SDL_PrivateGLESData
{
    // 1401 If the struct-declaration-list contains no named members, the behavior is undefined.
    // warning: empty struct has size 0 in C, size 1 in C++ [-Wc++-compat]
    पूर्णांक dummy;
} SDL_PrivateGLESData;

// OpenGLES functions
#घोषणा X11_GLES_GetAttribute    SDL_EGL_GetAttribute
#घोषणा X11_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#घोषणा X11_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#घोषणा X11_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#घोषणा X11_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#घोषणा X11_GLES_DestroyContext   SDL_EGL_DestroyContext

बाह्य bool X11_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, पूर्णांक screen, bool transparent);
बाह्य SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_GLES_SetDefaultProfileConfig(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_VIDEO_OPENGL_EGL

#पूर्ण_अगर // SDL_x11opengles_h_
