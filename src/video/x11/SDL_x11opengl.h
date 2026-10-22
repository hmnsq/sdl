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

#यदि_अपरिभाषितम् SDL_x11opengl_h_
#परिभाषय SDL_x11opengl_h_

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
#अन्तर्भाव <SDL3/SDL_opengl.h>
#अन्तर्भाव <GL/glx.h>

प्रकारनिर्देश शून्य (*__GLXextFuncPtr)(शून्य);

प्रकारनिर्देश गणना SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

संरचना SDL_GLDriver_दत्त
{
    पूर्णाङ्क error_आधारः, event_आधारः;

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
    संरचना
    {
        पूर्णाङ्क major;
        पूर्णाङ्क minor;
    } es_profile_max_supported_संस्करणम्;

    SDL_GLSwapIntervalTearBehavior swap_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, पूर्णाङ्क *, पूर्णाङ्क *);
    __GLXextFuncPtr (*gl_XGet_Proc_स्थानाङ्कः)(ध्रुव GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, पूर्णाङ्क, पूर्णाङ्क *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ध्रुव पूर्णाङ्क *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, पूर्णाङ्क, ध्रुव पूर्णाङ्क *, पूर्णाङ्क *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    शून्य (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    शून्य (*glXSwapBuffers)(Display *, GLXDrawable);
    शून्य (*glXQueryDrawable)(Display *, GLXDrawable, पूर्णाङ्क, अचिह्नित पूर्णाङ्क *);
    शून्य (*glXSwapIntervalEXT)(Display *, GLXDrawable, पूर्णाङ्क);
    पूर्णाङ्क (*glXSwapIntervalSGI)(पूर्णाङ्क);
    पूर्णाङ्क (*glXSwapIntervalMESA)(पूर्णाङ्क);
    पूर्णाङ्क (*glXGetSwapIntervalMESA)(शून्य);
};

// OpenGL functions
बाह्य bool X11_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य SDL_FunctionPointer X11_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य शून्य X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य bool X11_GL_UseEGL(SDL_VideoDevice *_this);
बाह्य XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, पूर्णाङ्क screen, bool transparent);
बाह्य SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः,
                              SDL_GLContext context);
बाह्य bool X11_GL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval);
बाह्य bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
बाह्य bool X11_GL_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#यदि_अन्तः // SDL_VIDEO_OPENGL_GLX

#यदि_अन्तः // SDL_x11opengl_h_
