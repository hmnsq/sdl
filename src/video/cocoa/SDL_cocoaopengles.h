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

#اگر_تعریف_نشده SDL_cocoaopengles_h_
#تعریف_کن SDL_cocoaopengles_h_

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

// OpenGLES functions
#تعریف_کن Cocoa_GLES_GetAttribute    SDL_EGL_GetAttribute
#تعریف_کن Cocoa_GLES_Get_Proc_آدرس  SDL_EGL_Get_Proc_آدرس_داخلی
#تعریف_کن Cocoa_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کن Cocoa_GLES_Get_جابجا_Interval SDL_EGL_Get_جابجا_Interval
#تعریف_کن Cocoa_GLES_مجموعه_جابجا_Interval SDL_EGL_مجموعه_جابجا_Interval

خارجي bool Cocoa_GLES_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر);
خارجي SDL_GLContext Cocoa_GLES_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_GLES_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context);
خارجي bool Cocoa_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي bool Cocoa_GLES_راهاندازی_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي SDL_EGLSurface Cocoa_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

#پایان_اگر // SDL_VIDEO_OPENGL_EGL

#پایان_اگر // SDL_cocoaopengles_h_
