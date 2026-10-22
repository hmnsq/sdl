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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_x11opengl_h_
#define SDL_x11opengl_h_

#ifdef SDL_VIDEO_OPENGL_GLX
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>
#ಅನ್ತರ್ಭಾವ <GL/glx.h>

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*__GLXextFuncPtr)(ಶೂನ್ಯ);

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

ಸಂರಚನಾ SDL_GLDriverData
{
    ಪೂರ್ಣಾಙ್ಕ errorBase, eventBase;

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
    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ major;
        ಪೂರ್ಣಾಙ್ಕ minor;
    } es_profile_max_supported_version;

    SDL_GLSwapIntervalTearBehavior swap_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *);
    __GLXextFuncPtr (*glXGetProcAddress)(ಧ್ರುವ GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, ಪೂರ್ಣಾಙ್ಕ, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    ಶೂನ್ಯ (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    ಶೂನ್ಯ (*glXSwapBuffers)(Display *, GLXDrawable);
    ಶೂನ್ಯ (*glXQueryDrawable)(Display *, GLXDrawable, ಪೂರ್ಣಾಙ್ಕ, unsigned ಪೂರ್ಣಾಙ್ಕ *);
    ಶೂನ್ಯ (*glXSwapIntervalEXT)(Display *, GLXDrawable, ಪೂರ್ಣಾಙ್ಕ);
    ಪೂರ್ಣಾಙ್ಕ (*glXSwapIntervalSGI)(ಪೂರ್ಣಾಙ್ಕ);
    ಪೂರ್ಣಾಙ್ಕ (*glXSwapIntervalMESA)(ಪೂರ್ಣಾಙ್ಕ);
    ಪೂರ್ಣಾಙ್ಕ (*glXGetSwapIntervalMESA)(ಶೂನ್ಯ);
};

// OpenGL functions
ಬಾಹ್ಯ bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
ಬಾಹ್ಯ SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool X11_GL_UseEGL(SDL_VideoDevice *_this);
ಬಾಹ್ಯ XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, ಪೂರ್ಣಾಙ್ಕ screen, bool transparent);
ಬಾಹ್ಯ SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                              SDL_GLContext context);
ಬಾಹ್ಯ bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval);
ಬಾಹ್ಯ bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval);
ಬಾಹ್ಯ bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#endif // SDL_VIDEO_OPENGL_GLX

#endif // SDL_x11opengl_h_
