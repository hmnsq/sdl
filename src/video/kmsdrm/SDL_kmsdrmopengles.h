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

#جيڪڏهن_وصف_نه_ٿيل SDL_kmsdrmopengles_h_
#وصف_ڪريو SDL_kmsdrmopengles_h_

#ضمن "../SDL_egl_c.h"

// OpenGLES functions
#وصف_ڪريو KMSDRM_GLES_GetAttribute    SDL_EGL_GetAttribute
#وصف_ڪريو KMSDRM_GLES_Get_Proc_پتو  SDL_EGL_Get_Proc_پتو_اندروني
#وصف_ڪريو KMSDRM_GLES_DestroyContext   SDL_EGL_DestroyContext
#وصف_ڪريو KMSDRM_GLES_Get_مٽا_سٽا_Interval SDL_EGL_Get_مٽا_سٽا_Interval

خارجي فراغ KMSDRM_GLES_سيٽ_Default_Profile_Config(SDL_VideoDevice *_this);
خارجي bool KMSDRM_GLES_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool KMSDRM_GLES_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
خارجي فراغ KMSDRM_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext KMSDRM_GLES_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool KMSDRM_GLES_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool KMSDRM_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context);

#جيڪڏهن_پورو // SDL_kmsdrmopengles_h_
