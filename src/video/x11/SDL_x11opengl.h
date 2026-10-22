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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11opengl_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11opengl_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>
#ಅನ್ತರ್ಭಾವ <GL/glx.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*__GLXextFuncPtr)(ಶೂನ್ಯ);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_GLSwapIntervalTearBehavior
{
    SDL_SWAPINTERVALTEAR_UNTESTED,
    SDL_SWAPINTERVALTEAR_UNKNOWN,
    SDL_SWAPINTERVALTEAR_MESA,
    SDL_SWAPINTERVALTEAR_NVIDIA
} SDL_GLSwapIntervalTearBehavior;

ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ error_ತಳ, event_ತಳ;

    bool HAS_GLX_EXT_visual_rating;
    bool HAS_GLX_EXT_visual_info;
    bool HAS_GLX_EXT_ಅದಲುಬದಲು_control_tear;
    bool HAS_GLX_ARB_context_flush_control;
    bool HAS_GLX_ARB_create_context_robustness;
    bool HAS_GLX_ARB_create_context_no_error;
    bool HAS_GLX_ARB_framebuffer_sRGB;

    /* Max version of OpenGL ES context that can be created if the
       implementation supports GLX_EXT_create_context_es2_profile.
       major = minor = 0 when unsupported.
     */
    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ major;
        ಪೂರ್ಣಾಂಕ minor;
    } es_profile_max_supported_ಆವೃತ್ತಿ;

    SDL_GLSwapIntervalTearBehavior ಅದಲುಬದಲು_interval_tear_behavior;

    Bool (*glXQueryExtension)(Display *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *);
    __GLXextFuncPtr (*gl_XGet_Proc_ವಿಳಾಸ)(ಸ್ಥಿರಾಂಕ GLubyte *);
    XVisualInfo *(*glXChooseVisual)(Display *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ *);
    GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *);
    GLXFBConfig *(*glXChooseFBConfig)(Display *, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *);
    XVisualInfo *(*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
    ಶೂನ್ಯ (*glXDestroyContext)(Display *, GLXContext);
    Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
    ಶೂನ್ಯ (*glXSwapBuffers)(Display *, GLXDrawable);
    ಶೂನ್ಯ (*glXQueryDrawable)(Display *, GLXDrawable, ಪೂರ್ಣಾಂಕ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *);
    ಶೂನ್ಯ (*glXSwapIntervalEXT)(Display *, GLXDrawable, ಪೂರ್ಣಾಂಕ);
    ಪೂರ್ಣಾಂಕ (*glXSwapIntervalSGI)(ಪೂರ್ಣಾಂಕ);
    ಪೂರ್ಣಾಂಕ (*glXSwapIntervalMESA)(ಪೂರ್ಣಾಂಕ);
    ಪೂರ್ಣಾಂಕ (*gl_XGet_ಅದಲುಬದಲು_Interval_MESA)(ಶೂನ್ಯ);
};

// OpenGL functions
ಬಾಹ್ಯ bool X11_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ X11_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_GL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool X11_GL_UseEGL(SDL_VideoDevice *_this);
ಬಾಹ್ಯ XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, ಪೂರ್ಣಾಂಕ screen, bool transparent);
ಬಾಹ್ಯ SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                              SDL_GLContext context);
ಬಾಹ್ಯ bool X11_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
ಬಾಹ್ಯ bool X11_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);
ಬಾಹ್ಯ bool X11_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_GLX

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11opengl_h_
