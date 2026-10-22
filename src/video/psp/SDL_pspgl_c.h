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

#که_نه_تعریف_شوی SDL_pspgl_c_h_
#تعریف_کړه SDL_pspgl_c_h_

#ضمن <GLES/egl.h>
#ضمن <GLES/gl.h>

#ضمن "SDL_pspvideo.h"

تعريفنوع بنية SDL_GLDriver_معلومات
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_معلومات;

خارجي SDL_Function_اشاره_ګر PSP_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context);
خارجي فراغ PSP_GL_بدلون_Buffers(SDL_VideoDevice *_this);

خارجي bool PSP_GL_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

خارجي bool PSP_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي bool PSP_GL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool PSP_GL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval);

#د_که_پای // SDL_pspgl_c_h_
