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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_x11opengl_h_
#घोषणा SDL_x11opengl_h_

#अगर_घोषित SDL_VIDEO_OPENGL_GLX
#समावेश <SDL3/SDL_opengl.h>
#समावेश <GL/glx.h>

प्रकार व्योम (*__GLXextFuncPtr)(व्योम);

प्रकार क्रमागत SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

काष्ठा SDL_GLDriver_तथ्य
{
    पूर्णांक errorBase, eventBase;

    bool HAS_GLX_EXT_visual_rating;
    bool HAS_GLX_EXT_visual_info;
    bool HAS_GLX_EXT_swap_control_tear;
    bool HAS_GLX_ARB_context_flush_control;
    bool HAS_GLX_ARB_create_context_robustness;
    bool HAS_GLX_ARB_create_context_no_error;
    bool HAS_GLX_ARB_framebuffer_sRGB;

    /* Max version of OpenGL ES context that can be created if the
       implementation supports GLX_EXT_create_context_es2_profile.
       major = minor = 0 when unsupported.
     */
    काष्ठा
    {
        पूर्णांक major;
        पूर्णांक minor;
    } es_profile_max_supported_version;

    SDL_GLSwapIntervalTearBehavior swap_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, पूर्णांक *, पूर्णांक *);
    __GLXextFuncPtr (*glXGetProcAddress)(स्थिर GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, पूर्णांक, पूर्णांक *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, स्थिर पूर्णांक *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, पूर्णांक, स्थिर पूर्णांक *, पूर्णांक *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    व्योम (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    व्योम (*glXSwapBuffers)(Display *, GLXDrawable);
    व्योम (*glXQueryDrawable)(Display *, GLXDrawable, पूर्णांक, अचिन्हित पूर्णांक *);
    व्योम (*glXSwapIntervalEXT)(Display *, GLXDrawable, पूर्णांक);
    पूर्णांक (*glXSwapIntervalSGI)(पूर्णांक);
    पूर्णांक (*glXSwapIntervalMESA)(पूर्णांक);
    पूर्णांक (*glXGetSwapIntervalMESA)(व्योम);
};

// OpenGL functions
बाह्य bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य व्योम X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य bool X11_GL_UseEGL(SDL_VideoDevice *_this);
बाह्य XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, पूर्णांक screen, bool transparent);
बाह्य SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                              SDL_GLContext context);
बाह्य bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#पूर्ण_अगर // SDL_VIDEO_OPENGL_GLX

#पूर्ण_अगर // SDL_x11opengl_h_
