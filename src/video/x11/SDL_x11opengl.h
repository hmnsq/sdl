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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_x11opengl_h_
#تعریف_کرو SDL_x11opengl_h_

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
#شامل <SDL3/SDL_opengl.h>
#شامل <GL/glx.h>

قسمتعریف خالی (*__GLXextFuncPtr)(خالی);

قسمتعریف شمار SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

ساخت SDL_GLDriver_ڈیٹا
{
    صحیح error_بنیاد, event_بنیاد;

    bool HAS_GLX_EXT_visual_rating;
    bool HAS_GLX_EXT_visual_info;
    bool HAS_GLX_EXT_تبادلہ_control_tear;
    bool HAS_GLX_ARB_context_flush_control;
    bool HAS_GLX_ARB_create_context_robustness;
    bool HAS_GLX_ARB_create_context_no_error;
    bool HAS_GLX_ARB_framebuffer_sRGB;

    /* Max version of OpenGL ES context that can be created if the
       implementation supports GLX_EXT_create_context_es2_profile.
       major = minor = 0 when unsupported.
     */
    ساخت
    {
        صحیح major;
        صحیح minor;
    } es_profile_max_supported_نسخہ;

    SDL_GLSwapIntervalTearBehavior تبادلہ_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, صحیح *, صحیح *);
    __GLXextFuncPtr (*gl_XGet_Proc_پتہ)(ثابت GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, صحیح, صحیح *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ثابت صحیح *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, صحیح, ثابت صحیح *, صحیح *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    خالی (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    خالی (*glXSwapBuffers)(Display *, GLXDrawable);
    خالی (*glXQueryDrawable)(Display *, GLXDrawable, صحیح, غیرعلامتی صحیح *);
    خالی (*glXSwapIntervalEXT)(Display *, GLXDrawable, صحیح);
    صحیح (*glXSwapIntervalSGI)(صحیح);
    صحیح (*glXSwapIntervalMESA)(صحیح);
    صحیح (*gl_XGet_تبادلہ_Interval_MESA)(خالی);
};

// OpenGL functions
خارجی bool X11_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_Function_اشارہ_گر X11_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی خالی X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجی bool X11_GL_UseEGL(SDL_VideoDevice *_this);
خارجی XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, صحیح screen, bool transparent);
خارجی SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                              SDL_GLContext context);
خارجی bool X11_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool X11_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);
خارجی bool X11_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#اگر_ختم // SDL_VIDEO_OPENGL_GLX

#اگر_ختم // SDL_x11opengl_h_
