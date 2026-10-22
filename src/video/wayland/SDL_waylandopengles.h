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

#جے_بنا_تعریف SDL_waylandopengles_h_
#تعریف_کرو SDL_waylandopengles_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

تعريفنوع بنية SDL_نجی_GLESData
{
    صحيح dummy;
} SDL_نجی_GLESData;

// OpenGLES functions
#تعریف_کرو Wayland_GLES_GetAttribute   SDL_EGL_GetAttribute
#تعریف_کرو Wayland_GLES_Get_Proc_پتہ SDL_EGL_Get_Proc_پتہ_اندرونی
#تعریف_کرو Wayland_GLES_UnloadLibrary  SDL_EGL_UnloadLibrary

خارجي bool Wayland_GLES_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ);
خارجي SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Wayland_GLES_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool Wayland_GLES_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool Wayland_GLES_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجي bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي فراغ Wayland_GLES_سیٹ_Default_Profile_Config(SDL_VideoDevice *_this);
خارجي SDL_EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

#جے_انت // SDL_waylandopengles_h_
