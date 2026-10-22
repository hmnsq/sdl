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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_x11opengl_h_
#define SDL_x11opengl_h_

#ifdef SDL_VIDEO_OPENGL_GLX
#অন্তর্ভাব <SDL3/SDL_opengl.h>
#অন্তর্ভাব <GL/glx.h>

প্রকারনির্দেশ শূন্য (*__GLXextFuncPtr)(শূন্য);

প্রকারনির্দেশ গণনা SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

সংরচনা SDL_GLDriverData
{
    পূর্ণাঙ্ক errorBase, eventBase;

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
    সংরচনা
    {
        পূর্ণাঙ্ক major;
        পূর্ণাঙ্ক minor;
    } es_profile_max_supported_version;

    SDL_GLSwapIntervalTearBehavior swap_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, পূর্ণাঙ্ক *, পূর্ণাঙ্ক *);
    __GLXextFuncPtr (*glXGetProcAddress)(ধ্রুব GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, পূর্ণাঙ্ক, পূর্ণাঙ্ক *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ধ্রুব পূর্ণাঙ্ক *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, পূর্ণাঙ্ক, ধ্রুব পূর্ণাঙ্ক *, পূর্ণাঙ্ক *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    শূন্য (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    শূন্য (*glXSwapBuffers)(Display *, GLXDrawable);
    শূন্য (*glXQueryDrawable)(Display *, GLXDrawable, পূর্ণাঙ্ক, unsigned পূর্ণাঙ্ক *);
    শূন্য (*glXSwapIntervalEXT)(Display *, GLXDrawable, পূর্ণাঙ্ক);
    পূর্ণাঙ্ক (*glXSwapIntervalSGI)(পূর্ণাঙ্ক);
    পূর্ণাঙ্ক (*glXSwapIntervalMESA)(পূর্ণাঙ্ক);
    পূর্ণাঙ্ক (*glXGetSwapIntervalMESA)(শূন্য);
};

// OpenGL functions
বাহ্য bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *path);
বাহ্য SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুব বর্ণ *proc);
বাহ্য শূন্য X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
বাহ্য bool X11_GL_UseEGL(SDL_VideoDevice *_this);
বাহ্য XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, পূর্ণাঙ্ক screen, bool transparent);
বাহ্য SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                              SDL_GLContext context);
বাহ্য bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval);
বাহ্য bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval);
বাহ্য bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#endif // SDL_VIDEO_OPENGL_GLX

#endif // SDL_x11opengl_h_
