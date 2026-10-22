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
#اگر_غیر_تعریف_شدہ SDL_uikitopengles_
#تعریف_کرو SDL_uikitopengles_

#اگر defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#شامل "../SDL_sysvideo.h"

خارجی bool UIKit_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                                SDL_GLContext context);
خارجی bool UIKit_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_GLContext UIKit_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool UIKit_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجی SDL_Function_اشارہ_گر UIKit_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی bool UIKit_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);

خارجی خالی UIKit_GL_RestoreCurrentContext(خالی);

#اگر_ختم // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

#اگر_ختم // SDL_uikitopengles_
