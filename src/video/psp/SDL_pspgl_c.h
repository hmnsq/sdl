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

#ifndef SDL_pspgl_c_h_
#define SDL_pspgl_c_h_

#ಅನ್ತರ್ಭಾವ <GLES/egl.h>
#ಅನ್ತರ್ಭಾವ <GLES/gl.h>

#ಅನ್ತರ್ಭಾವ "SDL_pspvideo.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;

ಬಾಹ್ಯ SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc);
ಬಾಹ್ಯ bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
ಬಾಹ್ಯ ಶೂನ್ಯ PSP_GL_SwapBuffers(SDL_VideoDevice *_this);

ಬಾಹ್ಯ bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

ಬಾಹ್ಯ bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
ಬಾಹ್ಯ ಶೂನ್ಯ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval);
ಬಾಹ್ಯ bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval);

#endif // SDL_pspgl_c_h_
