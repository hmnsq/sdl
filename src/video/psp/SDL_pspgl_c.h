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

#నిర్వచితం_కాకపోతే SDL_pspgl_c_h_
#నిర్వచించు SDL_pspgl_c_h_

#అన్తర్భావ <GLES/egl.h>
#అన్తర్భావ <GLES/gl.h>

#అన్తర్భావ "SDL_pspvideo.h"

రకనిర్వచనం నిర్మాణం SDL_GLDriver_దత్తాంశం
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_దత్తాంశం;

బాహ్య SDL_Function_సూచిక PSP_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context);
బాహ్య శూన్య PSP_GL_మార్పిడి_Buffers(SDL_VideoDevice *_this);

బాహ్య bool PSP_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

బాహ్య bool PSP_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య శూన్య PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య bool PSP_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool PSP_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);

#అయితే_ముగింపు // SDL_pspgl_c_h_
