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

#ଅନ୍ତର୍ଭାଵ <GLES/egl.h>
#ଅନ୍ତର୍ଭାଵ <GLES/gl.h>

#ଅନ୍ତର୍ଭାଵ "SDL_pspvideo.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;

ବାହ୍ୟ SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc);
ବାହ୍ୟ bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
ବାହ୍ୟ ଶୂନ୍ୟ PSP_GL_SwapBuffers(SDL_VideoDevice *_this);

ବାହ୍ୟ bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

ବାହ୍ୟ bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
ବାହ୍ୟ ଶୂନ୍ୟ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
ବାହ୍ୟ bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval);
ବାହ୍ୟ bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval);

#endif // SDL_pspgl_c_h_
