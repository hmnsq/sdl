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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11opengl_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11opengl_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GL/glx.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*__GLXextFuncPtr)(ਖਾਲੀ);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ
{
    ਪੂਰਨ error_ਅਧਾਰ, event_ਅਧਾਰ;

    bool HAS_GLX_EXT_visual_rating;
    bool HAS_GLX_EXT_visual_info;
    bool HAS_GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear;
    bool HAS_GLX_ARB_context_flush_control;
    bool HAS_GLX_ARB_create_context_robustness;
    bool HAS_GLX_ARB_create_context_no_error;
    bool HAS_GLX_ARB_framebuffer_sRGB;

    /* Max version of OpenGL ES context that can be created if the
       implementation supports GLX_EXT_create_context_es2_profile.
       major = minor = 0 when unsupported.
     */
    ਬਣਤਰ
    {
        ਪੂਰਨ major;
        ਪੂਰਨ minor;
    } es_profile_max_supported_ਸੰਸਕਰਣ;

    SDL_GLSwapIntervalTearBehavior ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, ਪੂਰਨ *, ਪੂਰਨ *);
    __GLXextFuncPtr (*gl_XGet_Proc_ਪਤਾ)(ਅਚਲ GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, ਪੂਰਨ, ਪੂਰਨ *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ਅਚਲ ਪੂਰਨ *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, ਪੂਰਨ, ਅਚਲ ਪੂਰਨ *, ਪੂਰਨ *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    ਖਾਲੀ (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    ਖਾਲੀ (*glXSwapBuffers)(Display *, GLXDrawable);
    ਖਾਲੀ (*glXQueryDrawable)(Display *, GLXDrawable, ਪੂਰਨ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *);
    ਖਾਲੀ (*glXSwapIntervalEXT)(Display *, GLXDrawable, ਪੂਰਨ);
    ਪੂਰਨ (*glXSwapIntervalSGI)(ਪੂਰਨ);
    ਪੂਰਨ (*glXSwapIntervalMESA)(ਪੂਰਨ);
    ਪੂਰਨ (*gl_XGet_ਅਦਲਾ_ਬਦਲੀ_Interval_MESA)(ਖਾਲੀ);
};

// OpenGL functions
ਬਾਹਰੀ bool X11_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ X11_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ ਖਾਲੀ X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool X11_GL_UseEGL(SDL_VideoDevice *_this);
ਬਾਹਰੀ XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, ਪੂਰਨ screen, bool transparent);
ਬਾਹਰੀ SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                              SDL_GLContext context);
ਬਾਹਰੀ bool X11_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool X11_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
ਬਾਹਰੀ bool X11_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_GLX

#ਜੇ_ਅੰਤ // SDL_x11opengl_h_
