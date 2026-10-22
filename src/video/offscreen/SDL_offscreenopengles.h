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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_offscreenopengles_h
#تعریف_کرو SDL_offscreenopengles_h

#اگر defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_egl_c.h"

#تعریف_کرو OFFSCREEN_GLES_Get_Proc_پتہ  SDL_EGL_Get_Proc_پتہ_اندرونی
#تعریف_کرو OFFSCREEN_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کرو OFFSCREEN_GLES_Get_تبادلہ_Interval SDL_EGL_Get_تبادلہ_Interval
#تعریف_کرو OFFSCREEN_GLES_سیٹ_تبادلہ_Interval SDL_EGL_سیٹ_تبادلہ_Interval
#تعریف_کرو OFFSCREEN_GLES_DestroyContext   SDL_EGL_DestroyContext

خارجی bool OFFSCREEN_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجی bool OFFSCREEN_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

#اگر_ختم // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL

#اگر_ختم // SDL_offscreenopengles_h
