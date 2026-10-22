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

#جيڪڏهن_وصف_نه_ٿيل SDL_pspgl_c_h_
#وصف_ڪريو SDL_pspgl_c_h_

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

خارجي SDL_Function_اشارو PSP_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context);
خارجي فراغ PSP_GL_مٽا_سٽا_Buffers(SDL_VideoDevice *_this);

خارجي bool PSP_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);

خارجي bool PSP_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
خارجي فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي bool PSP_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool PSP_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval);

#جيڪڏهن_پورو // SDL_pspgl_c_h_
