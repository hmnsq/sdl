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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_x11opengl_h_
#define SDL_x11opengl_h_

#ifdef SDL_VIDEO_OPENGL_GLX
#അന്തര്ഭാവ <SDL3/SDL_opengl.h>
#അന്തര്ഭാവ <GL/glx.h>

തരനിർവചനം ശൂന്യം (*__GLXextFuncPtr)(ശൂന്യം);

തരനിർവചനം എണ്ണൽ SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

ഘടന SDL_GLDriverData
{
    പൂർണ്ണസംഖ്യ errorBase, eventBase;

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
    ഘടന
    {
        പൂർണ്ണസംഖ്യ major;
        പൂർണ്ണസംഖ്യ minor;
    } es_profile_max_supported_version;

    SDL_GLSwapIntervalTearBehavior swap_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *);
    __GLXextFuncPtr (*glXGetProcAddress)(സ്ഥിരം GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, സ്ഥിരം പൂർണ്ണസംഖ്യ *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, പൂർണ്ണസംഖ്യ, സ്ഥിരം പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    ശൂന്യം (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    ശൂന്യം (*glXSwapBuffers)(Display *, GLXDrawable);
    ശൂന്യം (*glXQueryDrawable)(Display *, GLXDrawable, പൂർണ്ണസംഖ്യ, unsigned പൂർണ്ണസംഖ്യ *);
    ശൂന്യം (*glXSwapIntervalEXT)(Display *, GLXDrawable, പൂർണ്ണസംഖ്യ);
    പൂർണ്ണസംഖ്യ (*glXSwapIntervalSGI)(പൂർണ്ണസംഖ്യ);
    പൂർണ്ണസംഖ്യ (*glXSwapIntervalMESA)(പൂർണ്ണസംഖ്യ);
    പൂർണ്ണസംഖ്യ (*glXGetSwapIntervalMESA)(ശൂന്യം);
};

// OpenGL functions
ബാഹ്യ bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
ബാഹ്യ SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc);
ബാഹ്യ ശൂന്യം X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
ബാഹ്യ bool X11_GL_UseEGL(SDL_VideoDevice *_this);
ബാഹ്യ XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, പൂർണ്ണസംഖ്യ screen, bool transparent);
ബാഹ്യ SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                              SDL_GLContext context);
ബാഹ്യ bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval);
ബാഹ്യ bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval);
ബാഹ്യ bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#endif // SDL_VIDEO_OPENGL_GLX

#endif // SDL_x11opengl_h_
