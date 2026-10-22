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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_نه_ٿيل SDL_x11opengl_h_
#وصف_ڪريو SDL_x11opengl_h_

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
#ضمن <SDL3/SDL_opengl.h>
#ضمن <GL/glx.h>

تعريفنوع فراغ (*__GLXextFuncPtr)(فراغ);

تعريفنوع تعداد SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

بنية SDL_GLDriver_معلومات
{
    صحيح error_بنياد, event_بنياد;

    bool HAS_GLX_EXT_visual_rating;
    bool HAS_GLX_EXT_visual_info;
    bool HAS_GLX_EXT_مٽا_سٽا_control_tear;
    bool HAS_GLX_ARB_context_flush_control;
    bool HAS_GLX_ARB_create_context_robustness;
    bool HAS_GLX_ARB_create_context_no_error;
    bool HAS_GLX_ARB_framebuffer_sRGB;

    /* Max version of OpenGL ES context that can be created if the
       implementation supports GLX_EXT_create_context_es2_profile.
       major = minor = 0 when unsupported.
     */
    بنية
    {
        صحيح major;
        صحيح minor;
    } es_profile_max_supported_نسخو;

    SDL_GLSwapIntervalTearBehavior مٽا_سٽا_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, صحيح *, صحيح *);
    __GLXextFuncPtr (*gl_XGet_Proc_پتو)(ثابت GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, صحيح, صحيح *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ثابت صحيح *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, صحيح, ثابت صحيح *, صحيح *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    فراغ (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    فراغ (*glXSwapBuffers)(Display *, GLXDrawable);
    فراغ (*glXQueryDrawable)(Display *, GLXDrawable, صحيح, بنانشان صحيح *);
    فراغ (*glXSwapIntervalEXT)(Display *, GLXDrawable, صحيح);
    صحيح (*glXSwapIntervalSGI)(صحيح);
    صحيح (*glXSwapIntervalMESA)(صحيح);
    صحيح (*gl_XGet_مٽا_سٽا_Interval_MESA)(فراغ);
};

// OpenGL functions
خارجي bool X11_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
خارجي SDL_Function_اشارو X11_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي bool X11_GL_UseEGL(SDL_VideoDevice *_this);
خارجي XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, صحيح screen, bool transparent);
خارجي SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري,
                              SDL_GLContext context);
خارجي bool X11_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool X11_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool X11_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_GLX

#جيڪڏهن_پورو // SDL_x11opengl_h_
