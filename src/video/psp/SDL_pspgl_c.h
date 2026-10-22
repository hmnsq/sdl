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

#অন্তর্ভাৱ <GLES/egl.h>
#অন্তর্ভাৱ <GLES/gl.h>

#অন্তর্ভাৱ "SDL_pspvideo.h"

প্রকারনির্দেশ সংরচনা SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;

বাহ্য SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *proc);
বাহ্য bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
বাহ্য শূন্য PSP_GL_SwapBuffers(SDL_VideoDevice *_this);

বাহ্য bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

বাহ্য bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path);
বাহ্য শূন্য PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
বাহ্য bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval);
বাহ্য bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval);

#endif // SDL_pspgl_c_h_
