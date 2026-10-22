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

#यदि_अपरिभाषितम् SDL_x11opengles_h_
#परिभाषय SDL_x11opengles_h_

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_egl_c.h"

प्रकारनिर्देश संरचना SDL_वैयक्तिकम्_GLESData
{
    // 1401 If the struct-declaration-list contains no named members, the behavior is undefined.
    // warning: empty struct has size 0 in C, size 1 in C++ [-Wc++-compat]
    पूर्णाङ्क dummy;
} SDL_वैयक्तिकम्_GLESData;

// OpenGLES functions
#परिभाषय X11_GLES_GetAttribute    SDL_EGL_GetAttribute
#परिभाषय X11_GLES_Get_Proc_स्थानाङ्कः  SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्
#परिभाषय X11_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#परिभाषय X11_GLES_समुच्चयः_Swap_Interval SDL_EGL_समुच्चयः_Swap_Interval
#परिभाषय X11_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#परिभाषय X11_GLES_DestroyContext   SDL_EGL_DestroyContext

बाह्य bool X11_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, पूर्णाङ्क screen, bool transparent);
बाह्य SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context);
बाह्य SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_GLES_समुच्चयः_Default_Profile_Config(SDL_VideoDevice *_this);

#यदि_अन्तः // SDL_VIDEO_OPENGL_EGL

#यदि_अन्तः // SDL_x11opengles_h_
