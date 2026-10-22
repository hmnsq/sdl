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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_نه_ٿيل SDL_cocoaopengles_h_
#وصف_ڪريو SDL_cocoaopengles_h_

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

// OpenGLES functions
#وصف_ڪريو Cocoa_GLES_GetAttribute    SDL_EGL_GetAttribute
#وصف_ڪريو Cocoa_GLES_Get_Proc_پتو  SDL_EGL_Get_Proc_پتو_اندروني
#وصف_ڪريو Cocoa_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#وصف_ڪريو Cocoa_GLES_Get_مٽا_سٽا_Interval SDL_EGL_Get_مٽا_سٽا_Interval
#وصف_ڪريو Cocoa_GLES_سيٽ_مٽا_سٽا_Interval SDL_EGL_سيٽ_مٽا_سٽا_Interval

خارجي bool Cocoa_GLES_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
خارجي SDL_GLContext Cocoa_GLES_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_GLES_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context);
خارجي bool Cocoa_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي bool Cocoa_GLES_تياري_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي SDL_EGLSurface Cocoa_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_دري *دري);

#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_EGL

#جيڪڏهن_پورو // SDL_cocoaopengles_h_
