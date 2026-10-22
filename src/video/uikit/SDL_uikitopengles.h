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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_uikitopengles_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_uikitopengles_

#ਜੇ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

ਬਾਹਰੀ bool UIKit_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                SDL_GLContext context);
ਬਾਹਰੀ bool UIKit_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_GLContext UIKit_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool UIKit_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ UIKit_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ bool UIKit_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);

ਬਾਹਰੀ ਖਾਲੀ UIKit_GL_RestoreCurrentContext(ਖਾਲੀ);

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

#ਜੇ_ਅੰਤ // SDL_uikitopengles_
