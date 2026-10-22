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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_offscreenopengles_h
#నిర్వచించు SDL_offscreenopengles_h

#ఒకవేళ defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_egl_c.h"

#నిర్వచించు OFFSCREEN_GLES_Get_Proc_చిరునామా  SDL_EGL_Get_Proc_చిరునామా_అంతర్గత
#నిర్వచించు OFFSCREEN_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#నిర్వచించు OFFSCREEN_GLES_Get_మార్పిడి_Interval SDL_EGL_Get_మార్పిడి_Interval
#నిర్వచించు OFFSCREEN_GLES_సమితి_మార్పిడి_Interval SDL_EGL_సమితి_మార్పిడి_Interval
#నిర్వచించు OFFSCREEN_GLES_DestroyContext   SDL_EGL_DestroyContext

బాహ్య bool OFFSCREEN_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context);
బాహ్య bool OFFSCREEN_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL

#అయితే_ముగింపు // SDL_offscreenopengles_h
