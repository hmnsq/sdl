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

#اگر_تعریف_نشده SDL_x11opengles_h_
#تعریف_کن SDL_x11opengles_h_

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

تعريفنوع بنية SDL_خصوصی_GLESData
{
    // 1401 If the struct-declaration-list contains no named members, the behavior is undefined.
    // warning: empty struct has size 0 in C, size 1 in C++ [-Wc++-compat]
    صحيح dummy;
} SDL_خصوصی_GLESData;

// OpenGLES functions
#تعریف_کن X11_GLES_GetAttribute    SDL_EGL_GetAttribute
#تعریف_کن X11_GLES_Get_Proc_آدرس  SDL_EGL_Get_Proc_آدرس_داخلی
#تعریف_کن X11_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کن X11_GLES_مجموعه_جابجا_Interval SDL_EGL_مجموعه_جابجا_Interval
#تعریف_کن X11_GLES_Get_جابجا_Interval SDL_EGL_Get_جابجا_Interval
#تعریف_کن X11_GLES_DestroyContext   SDL_EGL_DestroyContext

خارجي bool X11_GLES_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر);
خارجي XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, صحيح screen, bool transparent);
خارجي SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool X11_GLES_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool X11_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context);
خارجي SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ X11_GLES_مجموعه_Default_Profile_Config(SDL_VideoDevice *_this);

#پایان_اگر // SDL_VIDEO_OPENGL_EGL

#پایان_اگر // SDL_x11opengles_h_
