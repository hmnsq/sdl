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

#جے_بنا_تعریف SDL_BOPENGL_H
#تعریف_کرو SDL_BOPENGL_H

#إذا defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

#ضمن "../SDL_sysvideo.h"

خارجي bool HAIKU_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ);      // FIXME
خارجي SDL_Function_اشارہ_گر HAIKU_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc); // FIXME
خارجي فراغ HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this);                     // TODO
خارجي bool HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                                SDL_GLContext context);
خارجي bool HAIKU_GL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval); // TODO
خارجي bool HAIKU_GL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval); // TODO
خارجي bool HAIKU_GL_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

خارجي فراغ HAIKU_GL_RebootContexts(SDL_VideoDevice *_this);

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL

#جے_انت
