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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_x11opengl_h_
#define SDL_x11opengl_h_

#ifdef SDL_VIDEO_OPENGL_GLX
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengl.h>
#ଅନ୍ତର୍ଭାଵ <GL/glx.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (*__GLXextFuncPtr)(ଶୂନ୍ୟ);

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

ସଂରଚନା SDL_GLDriverData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା errorBase, eventBase;

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
    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା major;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା minor;
    } es_profile_max_supported_version;

    SDL_GLSwapIntervalTearBehavior swap_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *);
    __GLXextFuncPtr (*glXGetProcAddress)(ଅଚଳ GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    ଶୂନ୍ୟ (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    ଶୂନ୍ୟ (*glXSwapBuffers)(Display *, GLXDrawable);
    ଶୂନ୍ୟ (*glXQueryDrawable)(Display *, GLXDrawable, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *);
    ଶୂନ୍ୟ (*glXSwapIntervalEXT)(Display *, GLXDrawable, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*glXSwapIntervalSGI)(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*glXSwapIntervalMESA)(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*glXGetSwapIntervalMESA)(ଶୂନ୍ୟ);
};

// OpenGL functions
ବାହ୍ୟ bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
ବାହ୍ୟ SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc);
ବାହ୍ୟ ଶୂନ୍ୟ X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
ବାହ୍ୟ bool X11_GL_UseEGL(SDL_VideoDevice *_this);
ବାହ୍ୟ XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, bool transparent);
ବାହ୍ୟ SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                              SDL_GLContext context);
ବାହ୍ୟ bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval);
ବାହ୍ୟ bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval);
ବାହ୍ୟ bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#endif // SDL_VIDEO_OPENGL_GLX

#endif // SDL_x11opengl_h_
