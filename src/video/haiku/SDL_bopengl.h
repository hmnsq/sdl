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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_BOPENGL_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_BOPENGL_H

#ਜੇ defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

ਬਾਹਰੀ bool HAIKU_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);      // FIXME
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ HAIKU_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc); // FIXME
ਬਾਹਰੀ ਖਾਲੀ HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this);                     // TODO
ਬਾਹਰੀ bool HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                SDL_GLContext context);
ਬਾਹਰੀ bool HAIKU_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval); // TODO
ਬਾਹਰੀ bool HAIKU_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval); // TODO
ਬਾਹਰੀ bool HAIKU_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

ਬਾਹਰੀ ਖਾਲੀ HAIKU_GL_RebootContexts(SDL_VideoDevice *_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL

#ਜੇ_ਅੰਤ
