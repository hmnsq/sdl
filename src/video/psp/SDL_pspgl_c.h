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

#اگر_غیر_تعریف_شدہ SDL_pspgl_c_h_
#تعریف_کرو SDL_pspgl_c_h_

#شامل <GLES/egl.h>
#شامل <GLES/gl.h>

#شامل "SDL_pspvideo.h"

قسمتعریف ساخت SDL_GLDriver_ڈیٹا
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_ڈیٹا;

خارجی SDL_Function_اشارہ_گر PSP_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجی خالی PSP_GL_تبادلہ_Buffers(SDL_VideoDevice *_this);

خارجی bool PSP_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

خارجی bool PSP_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی خالی PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجی bool PSP_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool PSP_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);

#اگر_ختم // SDL_pspgl_c_h_
