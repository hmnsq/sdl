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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_cocoaopengles_h_
#परिभाषय SDL_cocoaopengles_h_

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_egl_c.h"

// OpenGLES functions
#परिभाषय Cocoa_GLES_GetAttribute    SDL_EGL_GetAttribute
#परिभाषय Cocoa_GLES_Get_Proc_स्थानाङ्कः  SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्
#परिभाषय Cocoa_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#परिभाषय Cocoa_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#परिभाषय Cocoa_GLES_समुच्चयः_Swap_Interval SDL_EGL_समुच्चयः_Swap_Interval

बाह्य bool Cocoa_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य SDL_GLContext Cocoa_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context);
बाह्य bool Cocoa_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य bool Cocoa_GLES_सज्जता_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_EGLSurface Cocoa_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

#यदि_अन्तः // SDL_VIDEO_OPENGL_EGL

#यदि_अन्तः // SDL_cocoaopengles_h_
