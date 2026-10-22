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

#که_نه_تعریف_شوی SDL_offscreenopengles_h
#تعریف_کړه SDL_offscreenopengles_h

#إذا defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

#تعریف_کړه OFFSCREEN_GLES_Get_Proc_پته  SDL_EGL_Get_Proc_پته_دننی
#تعریف_کړه OFFSCREEN_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کړه OFFSCREEN_GLES_Get_بدلون_Interval SDL_EGL_Get_بدلون_Interval
#تعریف_کړه OFFSCREEN_GLES_سېټ_بدلون_Interval SDL_EGL_سېټ_بدلون_Interval
#تعریف_کړه OFFSCREEN_GLES_DestroyContext   SDL_EGL_DestroyContext

خارجي bool OFFSCREEN_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context);
خارجي bool OFFSCREEN_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

#د_که_پای // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL

#د_که_پای // SDL_offscreenopengles_h
