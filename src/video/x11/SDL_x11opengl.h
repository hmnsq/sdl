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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_x11opengl_h_
#నిర్వచించు SDL_x11opengl_h_

#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
#అన్తర్భావ <SDL3/SDL_opengl.h>
#అన్తర్భావ <GL/glx.h>

రకనిర్వచనం శూన్య (*__GLXextFuncPtr)(శూన్య);

రకనిర్వచనం గణన SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

నిర్మాణం SDL_GLDriver_దత్తాంశం
{
    పూర్ణాంకం error_పునాది, event_పునాది;

    bool HAS_GLX_EXT_visual_rating;
    bool HAS_GLX_EXT_visual_info;
    bool HAS_GLX_EXT_మార్పిడి_control_tear;
    bool HAS_GLX_ARB_context_flush_control;
    bool HAS_GLX_ARB_create_context_robustness;
    bool HAS_GLX_ARB_create_context_no_error;
    bool HAS_GLX_ARB_framebuffer_sRGB;

    /* Max version of OpenGL ES context that can be created if the
       implementation supports GLX_EXT_create_context_es2_profile.
       major = minor = 0 when unsupported.
     */
    నిర్మాణం
    {
        పూర్ణాంకం major;
        పూర్ణాంకం minor;
    } es_profile_max_supported_సంస్కరణ;

    SDL_GLSwapIntervalTearBehavior మార్పిడి_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, పూర్ణాంకం *, పూర్ణాంకం *);
    __GLXextFuncPtr (*gl_XGet_Proc_చిరునామా)(స్థిరరాశి GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, పూర్ణాంకం, పూర్ణాంకం *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, స్థిరరాశి పూర్ణాంకం *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, పూర్ణాంకం, స్థిరరాశి పూర్ణాంకం *, పూర్ణాంకం *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    శూన్య (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    శూన్య (*glXSwapBuffers)(Display *, GLXDrawable);
    శూన్య (*glXQueryDrawable)(Display *, GLXDrawable, పూర్ణాంకం, గుర్తులేని పూర్ణాంకం *);
    శూన్య (*glXSwapIntervalEXT)(Display *, GLXDrawable, పూర్ణాంకం);
    పూర్ణాంకం (*glXSwapIntervalSGI)(పూర్ణాంకం);
    పూర్ణాంకం (*glXSwapIntervalMESA)(పూర్ణాంకం);
    పూర్ణాంకం (*gl_XGet_మార్పిడి_Interval_MESA)(శూన్య);
};

// OpenGL functions
బాహ్య bool X11_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_Function_సూచిక X11_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య శూన్య X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య bool X11_GL_UseEGL(SDL_VideoDevice *_this);
బాహ్య XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, పూర్ణాంకం screen, bool transparent);
బాహ్య SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ,
                              SDL_GLContext context);
బాహ్య bool X11_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool X11_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
బాహ్య bool X11_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_GLX

#అయితే_ముగింపు // SDL_x11opengl_h_
