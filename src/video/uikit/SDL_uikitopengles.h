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
#నిర్వచితం_కాకపోతే SDL_uikitopengles_
#నిర్వచించు SDL_uikitopengles_

#ఒకవేళ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#అన్తర్భావ "../SDL_sysvideo.h"

బాహ్య bool UIKit_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ,
                                SDL_GLContext context);
బాహ్య bool UIKit_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_GLContext UIKit_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool UIKit_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
బాహ్య SDL_Function_సూచిక UIKit_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య bool UIKit_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);

బాహ్య శూన్య UIKit_GL_RestoreCurrentContext(శూన్య);

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

#అయితే_ముగింపు // SDL_uikitopengles_
