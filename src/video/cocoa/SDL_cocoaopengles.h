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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_cocoaopengles_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_cocoaopengles_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

// OpenGLES functions
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Cocoa_GLES_GetAttribute    SDL_EGL_GetAttribute
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Cocoa_GLES_Get_Proc_ਪਤਾ  SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Cocoa_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Cocoa_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Cocoa_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval

ਬਾਹਰੀ bool Cocoa_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_GLContext Cocoa_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context);
ਬਾਹਰੀ bool Cocoa_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ਬਾਹਰੀ bool Cocoa_GLES_ਤਿਆਰੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_EGLSurface Cocoa_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_EGL

#ਜੇ_ਅੰਤ // SDL_cocoaopengles_h_
