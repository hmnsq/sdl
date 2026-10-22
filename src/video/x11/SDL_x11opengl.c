/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>
  Copyright (C) 2021 NVIDIA Corporation

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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
#ಅನ್ತರ್ಭಾವ "SDL_x11opengles.h"

#ಆದರೆ defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OPENGL "libGL.so"
#ಅಥವಾಆದರೆ defined(SDL_PLATFORM_MACOS)
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OPENGL "libGL.so.1"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_NONE_EXT
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_NONE_EXT 0x8000
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_multisample
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_multisample
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_SAMPLE_BUFFERS_ARB 100000
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_SAMPLES_ARB        100001
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_EXT_visual_rating
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_EXT_visual_rating
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_VISUAL_CAVEAT_EXT         0x20
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_NONE_EXT                  0x8000
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_SLOW_VISUAL_EXT           0x8001
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_EXT_visual_info
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_EXT_visual_info
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_X_VISUAL_TYPE_EXT 0x22
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ನೇರ_COLOR_EXT  0x8003
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_create_context
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_create_context
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_MAJOR_ಆವೃತ್ತಿ_ARB          0x2091
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_MINOR_ಆವೃತ್ತಿ_ARB          0x2092
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_FLAGS_ARB                  0x2094
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_DEBUG_ಬಿಟ್_ARB              0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_FORWARD_COMPATIBLE_ಬಿಟ್_ARB 0x0002

// Typedef for the GL 3.0 context creation function
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool ನೇರ,
                                                        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ
                                                            *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_create_context_profile
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_create_context_profile
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_PROFILE_ಮುಖವಾಡ_ARB              0x9126
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_CORE_PROFILE_ಬಿಟ್_ARB          0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_COMPATIBILITY_PROFILE_ಬಿಟ್_ARB 0x00000002
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_create_context_robustness
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_create_context_robustness
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_ROBUST_ACCESS_ಬಿಟ್_ARB           0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_EXT_create_context_es2_profile
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_EXT_create_context_es2_profile
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_CONTEXT_ES2_PROFILE_ಬಿಟ್_EXT
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_ES2_PROFILE_ಬಿಟ್_EXT 0x00000002
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_framebuffer_sRGB
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_framebuffer_sRGB
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_fbconfig_float
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_fbconfig_float
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_RGBA_FLOAT_TYPE_ARB
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_RGBA_FLOAT_ಬಿಟ್_ARB
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_RGBA_FLOAT_ಬಿಟ್_ARB 0x00000004
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_create_context_no_error
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_create_context_no_error
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_EXT_ಅದಲುಬದಲು_control
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ಅದಲುಬದಲು_INTERVAL_EXT     0x20F1
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_MAX_ಅದಲುಬದಲು_INTERVAL_EXT 0x20F2
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_EXT_ಅದಲುಬದಲು_control_tear
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GLX_ARB_context_flush_control
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_ARB_context_flush_control
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#ವ್ಯಾಖ್ಯಾನಿಸು GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು OPENGL_REQUIRES_DLOPEN
#ಆದರೆ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#ಅನ್ತರ್ಭಾವ <dlfcn.h>
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತುಂಬು_Object(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತುಂಬು_Function  dlsym
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UnloadObject  dlclose
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತುಂಬು_Object   SDL_ತುಂಬು_Object
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತುಂಬು_Function SDL_ತುಂಬು_Function
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UnloadObject SDL_UnloadObject
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ X11_GL_InitExtensions(SDL_VideoDevice *_this);

ಸ್ಥಿರ bool X11_GL_ತುಂಬು_Library_EGLFallback(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    X11_GL_UnloadLibrary(_this);
    _this->GL_ತುಂಬು_Library = X11_GLES_ತುಂಬು_Library;
    _this->GL_Get_Proc_ವಿಳಾಸ = X11_GLES_Get_Proc_ವಿಳಾಸ;
    _this->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
    _this->GL_CreateContext = X11_GLES_CreateContext;
    _this->GL_MakeCurrent = X11_GLES_MakeCurrent;
    _this->GL_ಗಣ_ಅದಲುಬದಲು_Interval = X11_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    _this->GL_Get_ಅದಲುಬದಲು_Interval = X11_GLES_Get_ಅದಲುಬದಲು_Interval;
    _this->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = X11_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    _this->GL_DestroyContext = X11_GLES_DestroyContext;
    _this->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
    ಹಿಂತಿರುಗಿ X11_GLES_ತುಂಬು_Library(_this, ಮಾರ್ಗ);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not configured with EGL support");
#ಆದರೆ_ಅಂತ್ಯ
}

bool X11_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    Display *display;
    SDL_SharedObject *handle;

    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenGL context already created");
    }

    ಆದರೆ ((_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ಹಿಂತಿರುಗಿ X11_GL_ತುಂಬು_Library_EGLFallback(_this, ಮಾರ್ಗ);
    }

    // Load the OpenGL library
    ಆದರೆ (ಮಾರ್ಗ == ಖಾಲಿ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    ಆದರೆ (ಮಾರ್ಗ == ಖಾಲಿ) {
        ಮಾರ್ಗ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_ತುಂಬು_Object(ಮಾರ್ಗ);
    ಆದರೆ (!_this->gl_config.dll_handle) {
#ಆದರೆ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_ಗಣ_Error("Failed loading %s: %s", ಮಾರ್ಗ, dlerror());
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ false;
    }
    SDL_strlcpy(_this->gl_config.driver_ಮಾರ್ಗ, ಮಾರ್ಗ,
                SDL_arraysize(_this->gl_config.driver_ಮಾರ್ಗ));

    // Allocate OpenGL memory
    _this->gl_ದತ್ತಾಂಶ =
        (ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ *)SDL_calloc(1,
                                              ಗಾತ್ರ(ರಚನೆ
                                                     SDL_GLDriver_ದತ್ತಾಂಶ));
    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_ದತ್ತಾಂಶ->glXQueryExtension =
        (Bool(*)(Display *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *))
            GL_ತುಂಬು_Function(handle, "glXQueryExtension");
    _this->gl_ದತ್ತಾಂಶ->gl_XGet_Proc_ವಿಳಾಸ =
        (__GLXextFuncPtr (*)(ಸ್ಥಿರಾಂಕ GLubyte *))
            GL_ತುಂಬು_Function(handle, "glXGetProcAddressARB");
    _this->gl_ದತ್ತಾಂಶ->glXChooseVisual =
        (XVisualInfo * (*)(Display *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ *))
            X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXChooseVisual");
    _this->gl_ದತ್ತಾಂಶ->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, ಪೂರ್ಣಾಂಕ))
            X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXCreateContext");
    _this->gl_ದತ್ತಾಂಶ->glXDestroyContext =
        (ಶೂನ್ಯ (*)(Display *, GLXContext))
            X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXDestroyContext");
    _this->gl_ದತ್ತಾಂಶ->glXMakeCurrent =
        (ಪೂರ್ಣಾಂಕ (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXMakeCurrent");
    _this->gl_ದತ್ತಾಂಶ->glXSwapBuffers =
        (ಶೂನ್ಯ (*)(Display *, GLXDrawable))
            X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXSwapBuffers");
    _this->gl_ದತ್ತಾಂಶ->glXQueryDrawable =
        (ಶೂನ್ಯ (*)(Display *, GLXDrawable, ಪೂರ್ಣಾಂಕ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *))
            X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXQueryDrawable");

    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ->glXQueryExtension ||
        !_this->gl_ದತ್ತಾಂಶ->glXChooseVisual ||
        !_this->gl_ದತ್ತಾಂಶ->glXCreateContext ||
        !_this->gl_ದತ್ತಾಂಶ->glXDestroyContext ||
        !_this->gl_ದತ್ತಾಂಶ->glXMakeCurrent ||
        !_this->gl_ದತ್ತಾಂಶ->glXSwapBuffers) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not retrieve OpenGL functions");
    }

    display = _this->ಆಂತರಿಕ->display;
    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ->glXQueryExtension(display, &_this->gl_ದತ್ತಾಂಶ->error_ತಳ, &_this->gl_ದತ್ತಾಂಶ->event_ತಳ)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("GLX is not supported");
    }

    _this->gl_ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    ಆದರೆ (((_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        ಹಿಂತಿರುಗಿ X11_GL_ತುಂಬು_Library_EGLFallback(_this, ಖಾಲಿ);
    }

    ಹಿಂತಿರುಗಿ true;
}

SDL_Function_ಸೂಚಕ X11_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->gl_XGet_Proc_ವಿಳಾಸ) {
        ಹಿಂತಿರುಗಿ _this->gl_ದತ್ತಾಂಶ->gl_XGet_Proc_ವಿಳಾಸ((ಸ್ಥಿರಾಂಕ GLubyte *)proc);
    }
    ಹಿಂತಿರುಗಿ GL_ತುಂಬು_Function(_this->gl_config.dll_handle, proc);
}

ಶೂನ್ಯ X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#ಆದರೆ 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ

    // Free OpenGL memory
    SDL_free(_this->gl_ದತ್ತಾಂಶ);
    _this->gl_ದತ್ತಾಂಶ = ಖಾಲಿ;
}

ಸ್ಥಿರ bool HasExtension(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extension, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extensions)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಆರಂಭ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *where, *terminator;

    ಆದರೆ (!extensions) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ಆದರೆ (where || *extension == '\0') {
        ಹಿಂತಿರುಗಿ false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    ಆರಂಭ = extensions;

    ಗಾಗಿ (;;) {
        where = SDL_strstr(ಆರಂಭ, extension);
        ಆದರೆ (!where) {
            ನಿಲ್ಲಿಸು;
        }

        terminator = where + SDL_strlen(extension);
        ಆದರೆ (where == ಆರಂಭ || *(where - 1) == ' ') {
            ಆದರೆ (*terminator == ' ' || *terminator == '\0') {
                ಹಿಂತಿರುಗಿ true;
            }
        }

        ಆರಂಭ = terminator;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->ಆಂತರಿಕ->display;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ screen = DefaultScreen(display);
    XVisualInfo *vinfo = ಖಾಲಿ;
    ಕಿಟಕಿ_2 w = 0;
    GLXContext prev_ctx = ಖಾಲಿ;
    GLXDrawable prev_drawable = 0;
    GLXContext context = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(*glXQueryExtensionsStringFunc)(Display *, ಪೂರ್ಣಾಂಕ);
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    ಆದರೆ (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(ಶೂನ್ಯ) =
            (GLXContext(*)(ಶೂನ್ಯ))
                X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(ಶೂನ್ಯ) =
            (GLXDrawable(*)(ಶೂನ್ಯ))
                X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXGetCurrentDrawable");

        ಆದರೆ (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು xattr;
            prev_ctx = glXGetCurrentContextFunc();
            prev_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, ಬೇರು_ಕಿಟಕಿ(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreate_ಕಿಟಕಿ(display, ಬೇರು_ಕಿಟಕಿ(display, screen), 0, 0,
                                  32, 32, 0, vinfo->ಆಳ_2, ಒಳಹರಿವು_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_ದತ್ತಾಂಶ->glXCreateContext(display, vinfo,
                                                       ಖಾಲಿ, True);
            ಆದರೆ (context) {
                _this->gl_ದತ್ತಾಂಶ->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(*)(Display *, ಪೂರ್ಣಾಂಕ))X11_GL_Get_Proc_ವಿಳಾಸ(_this,
                                                               "glXQueryExtensionsString");
    ಆದರೆ (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } ಇಲ್ಲದಿದ್ದರೆ {
        extensions = ಖಾಲಿ;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_ಅದಲುಬದಲು_control_tear = false;
    ಆದರೆ (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT =
            (ಶೂನ್ಯ (*)(Display *, GLXDrawable, ಪೂರ್ಣಾಂಕ))
                X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXSwapIntervalEXT");
        ಆದರೆ (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_ಅದಲುಬದಲು_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    ಆದರೆ (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalMESA =
            (ಪೂರ್ಣಾಂಕ (*)(ಪೂರ್ಣಾಂಕ))X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXSwapIntervalMESA");
        _this->gl_ದತ್ತಾಂಶ->gl_XGet_ಅದಲುಬದಲು_Interval_MESA =
            (ಪೂರ್ಣಾಂಕ (*)(ಶೂನ್ಯ))X11_GL_Get_Proc_ವಿಳಾಸ(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    ಆದರೆ (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalSGI =
            (ಪೂರ್ಣಾಂಕ (*)(ಪೂರ್ಣಾಂಕ))X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    ಆದರೆ (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *))
                X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXCreateContextAttribsARB");
        _this->gl_ದತ್ತಾಂಶ->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *))
                X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXChooseFBConfig");
        _this->gl_ದತ್ತಾಂಶ->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_Get_Proc_ವಿಳಾಸ(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    ಆದರೆ (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    ಆದರೆ (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    ಆದರೆ (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        ಆದರೆ (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.major,
                &_this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    ಆದರೆ (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    ಆದರೆ (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    ಆದರೆ (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    ಆದರೆ (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_framebuffer_sRGB = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    ಆದರೆ (context) {
        _this->gl_ದತ್ತಾಂಶ->glXMakeCurrent(display, None, ಖಾಲಿ);
        _this->gl_ದತ್ತಾಂಶ->glXDestroyContext(display, context);
        ಆದರೆ (prev_ctx && prev_drawable) {
            _this->gl_ದತ್ತಾಂಶ->glXMakeCurrent(display, prev_drawable, prev_ctx);
        }
    }

    ಆದರೆ (w) {
        X11_XDestroy_ಕಿಟಕಿ(display, w);
    }
    X11_PumpEvents(_this);
}

/* glXChooseVisual and glXChooseFBConfig have some small differences in
 * the attribute encoding, it can be chosen with the for_FBConfig parameter.
 * Some targets fail if you use GLX_X_VISUAL_TYPE_EXT/GLX_DIRECT_COLOR_EXT,
 *  so it gets specified last if used and is pointed to by *_pvistypeattr.
 *  In case of failure, if that pointer is not NULL, set that pointer to None
 *  and try again.
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ X11_GL_Get_ಗುಣಲಕ್ಷಣಗಳು(SDL_VideoDevice *_this, Display *display, ಪೂರ್ಣಾಂಕ screen, ಪೂರ್ಣಾಂಕ *attribs, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, Bool for_FBConfig, ಪೂರ್ಣಾಂಕ **_pvistypeattr, bool transparent)
{
    ಪೂರ್ಣಾಂಕ i = 0;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ MAX_ಗುಣಲಕ್ಷಣಗಳು = 64;
    ಪೂರ್ಣಾಂಕ *pvistypeattr = ಖಾಲಿ;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(ಗಾತ್ರ_2 >= MAX_ಗುಣಲಕ್ಷಣಗಳು);

    // Setup our GLX attributes according to the gl_config.
    ಆದರೆ (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        ಆದರೆ (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_ಬಿಟ್_ARB;
        } ಇಲ್ಲದಿದ್ದರೆ {
            attribs[i++] = GLX_RGBA_ಬಿಟ್;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.red_ಗಾತ್ರ;
    attribs[i++] = GLX_GREEN_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.green_ಗಾತ್ರ;
    attribs[i++] = GLX_BLUE_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.blue_ಗಾತ್ರ;

    ಆದರೆ (_this->gl_config.alpha_ಗಾತ್ರ) {
        attribs[i++] = GLX_ALPHA_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.alpha_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.double_ಬಫರ್) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        ಆದರೆ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_ಆಳ_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.ಆಳ_ಗಾತ್ರ;

    ಆದರೆ (_this->gl_config.stencil_ಗಾತ್ರ) {
        attribs[i++] = GLX_STENCIL_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.stencil_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_red_ಗಾತ್ರ) {
        attribs[i++] = GLX_ACCUM_RED_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.accum_red_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_green_ಗಾತ್ರ) {
        attribs[i++] = GLX_ACCUM_GREEN_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.accum_green_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_blue_ಗಾತ್ರ) {
        attribs[i++] = GLX_ACCUM_BLUE_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.accum_blue_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_alpha_ಗಾತ್ರ) {
        attribs[i++] = GLX_ACCUM_ALPHA_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.accum_alpha_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        ಆದರೆ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    ಆದರೆ (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    ಆದರೆ (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    ಆದರೆ (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_framebuffer_sRGB) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ಆದರೆ (srgbhint && *srgbhint) {
            ಆದರೆ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ಇಲ್ಲದಿದ್ದರೆ {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    ಆದರೆ (_this->gl_config.accelerated >= 0 &&
        _this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    ಆದರೆ (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        ಆದರೆ (X11_Use_ನೇರ_Color_Visuals() && _this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_ನೇರ_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_ಗುಣಲಕ್ಷಣಗಳು);

    ಆದರೆ (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    ಹಿಂತಿರುಗಿ i;
}

//get the first transparent Visual
ಸ್ಥಿರ XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, ಪೂರ್ಣಾಂಕ screen)
{
    XVisualInfo *visualinfo = ಖಾಲಿ;
    XVisualInfo vi_ಒಳ;
    ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು_ಎಣಿಕೆ = 0;

    vi_ಒಳ.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ಮುಖವಾಡ, &vi_ಒಳ, &ಹೊರಹೋಗು_ಎಣಿಕೆ);
    ಆದರೆ (visualinfo != ಖಾಲಿ) {
        ಪೂರ್ಣಾಂಕ i = 0;
        ಗಾಗಿ (i = 0; i < ಹೊರಹೋಗು_ಎಣಿಕೆ; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_ಒಳ.screen = screen;
                vi_ಒಳ.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ಮುಖವಾಡ | VisualIDMask, &vi_ಒಳ, &ಹೊರಹೋಗು_ಎಣಿಕೆ);
                ನಿಲ್ಲಿಸು;
            }
        }
    }
    ಹಿಂತಿರುಗಿ visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, ಪೂರ್ಣಾಂಕ screen, bool transparent)
{
    // 64 seems nice.
    ಪೂರ್ಣಾಂಕ attribs[64];
    XVisualInfo *vinfo = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ *pvistypeattr = ಖಾಲಿ;

    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->glXChooseFBConfig &&
        _this->gl_ದತ್ತಾಂಶ->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ fbcount = 0;

        X11_GL_Get_ಗುಣಲಕ್ಷಣಗಳು(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_ದತ್ತಾಂಶ->glXChooseFBConfig(display, screen, attribs, &fbcount);
        ಆದರೆ (!framebuffer_config && (pvistypeattr != ಖಾಲಿ)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_ದತ್ತಾಂಶ->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        ಆದರೆ (transparent) {
            // Return the first transparent Visual
            ಪೂರ್ಣಾಂಕ i;
            ಗಾಗಿ (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_ದತ್ತಾಂಶ->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = ಖಾಲಿ;
                    ನಿಲ್ಲಿಸು;
                }
                X11_XFree(vinfo);
                vinfo = ಖಾಲಿ;
            }
        }

        ಆದರೆ (framebuffer_config) {
            vinfo = _this->gl_ದತ್ತಾಂಶ->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    ಆದರೆ (!vinfo) {
        X11_GL_Get_ಗುಣಲಕ್ಷಣಗಳು(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_ದತ್ತಾಂಶ->glXChooseVisual(display, screen, attribs);

        ಆದರೆ (!vinfo && (pvistypeattr != ಖಾಲಿ)) {
            *pvistypeattr = None;
            vinfo = _this->gl_ದತ್ತಾಂಶ->glXChooseVisual(display, screen, attribs);
        }
    }

    ಆದರೆ (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        ಆದರೆ (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            ಆದರೆ (visualinfo != ಖಾಲಿ) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    ಆದರೆ (!vinfo) {
        SDL_ಗಣ_Error("Couldn't find matching GLX visual");
    }
    ಹಿಂತಿರುಗಿ vinfo;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ (*handler)(Display *, XErrorEvent *) = ಖಾಲಿ;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *errorHandlerOperation = ಖಾಲಿ;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ error_ತಳ = 0;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ error_ಸಂಕೇತ_2 = 0;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    ಅಕ್ಷರ *x11_error = ಖಾಲಿ;
    ಅಕ್ಷರ x11_error_locale[256];

    error_ಸಂಕೇತ_2 = e->error_ಸಂಕೇತ;
    ಆದರೆ (X11_XGet_Error_ಪಠ್ಯ(d, error_ಸಂಕೇತ_2, x11_error_locale, ಗಾತ್ರ(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    ಆದರೆ (x11_error) {
        SDL_ಗಣ_Error("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Could not %s: %i (Base %i)", errorHandlerOperation, error_ಸಂಕೇತ_2, error_ತಳ);
    }

    ಹಿಂತಿರುಗಿ 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_ದತ್ತಾಂಶ != ಖಾಲಿ);
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        ಹಿಂತಿರುಗಿ true;
    }

    SDL_assert(_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES);
    ಹಿಂತಿರುಗಿ (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_ಆವೃತ್ತಿ == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_ಆವೃತ್ತಿ > _this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.major || (_this->gl_config.major_ಆವೃತ್ತಿ == _this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.major && _this->gl_config.minor_ಆವೃತ್ತಿ > _this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಪೂರ್ಣಾಂಕ screen = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ)->screen;
    XWindow_ಗುಣಲಕ್ಷಣಗಳು xattr;
    XVisualInfo v, *vinfo;
    ಪೂರ್ಣಾಂಕ n;
    SDL_GLContext context = ಖಾಲಿ;
    GLXContext share_context;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ transparent = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) ? true : false;

    ಆದರೆ (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } ಇಲ್ಲದಿದ್ದರೆ {
        share_context = ಖಾಲಿ;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    error_ತಳ = _this->gl_ದತ್ತಾಂಶ->error_ತಳ;
    error_ಸಂಕೇತ_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, ದತ್ತಾಂಶ->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, Visual_Screen_ಮುಖವಾಡ | VisualIDMask, &v, &n);
    ಆದರೆ (vinfo) {
        ಆದರೆ (_this->gl_config.major_ಆವೃತ್ತಿ < 3 &&
            _this->gl_config.profile_ಮುಖವಾಡ == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_ದತ್ತಾಂಶ->glXCreateContext(display, vinfo, share_context, True);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // max 14 attributes plus terminator
            ಪೂರ್ಣಾಂಕ attribs[15] = {
                GLX_CONTEXT_MAJOR_ಆವೃತ್ತಿ_ARB,
                _this->gl_config.major_ಆವೃತ್ತಿ,
                GLX_CONTEXT_MINOR_ಆವೃತ್ತಿ_ARB,
                _this->gl_config.minor_ಆವೃತ್ತಿ,
                0
            };
            ಪೂರ್ಣಾಂಕ iattr = 4;

            // SDL profile bits match GLX profile bits
            ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_ಮುಖವಾಡ_ARB;
                attribs[iattr++] = _this->gl_config.profile_ಮುಖವಾಡ;
            }

            // SDL flags match GLX flags
            ಆದರೆ (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            ಆದರೆ ((_this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            ಆದರೆ ((_this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            ಆದರೆ ((_this->gl_ದತ್ತಾಂಶ->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ->glXCreateContextAttribsARB) {
                SDL_ಗಣ_Error("OpenGL 3.0 and later are not supported by this system");
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಪೂರ್ಣಾಂಕ glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = ಖಾಲಿ;
                ಪೂರ್ಣಾಂಕ fbcount = 0;
                ಪೂರ್ಣಾಂಕ *pvistypeattr = ಖಾಲಿ;

                X11_GL_Get_ಗುಣಲಕ್ಷಣಗಳು(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_ದತ್ತಾಂಶ->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    ಆದರೆ (!framebuffer_config && (pvistypeattr != ಖಾಲಿ)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_ದತ್ತಾಂಶ->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    ಆದರೆ (transparent && (framebuffer_config != ಖಾಲಿ)) {
                        ಪೂರ್ಣಾಂಕ i;
                        ಗಾಗಿ (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_ತಾತ್ಕಾಲಿಕ = _this->gl_ದತ್ತಾಂಶ->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            ಆದರೆ ( vinfo_ತಾತ್ಕಾಲಿಕ != ಖಾಲಿ) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_ತಾತ್ಕಾಲಿಕ);
                                ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_ದತ್ತಾಂಶ->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = ಖಾಲಿ;
                                    X11_XFree(vinfo_ತಾತ್ಕಾಲಿಕ);
                                    ನಿಲ್ಲಿಸು;
                                }
                                X11_XFree(vinfo_ತಾತ್ಕಾಲಿಕ);
                            }
                        }
                    }
                    ಆದರೆ (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_ದತ್ತಾಂಶ->glXCreateContextAttribsARB(display,
                                                                             framebuffer_config[0],
                                                                             share_context, True, attribs);
                        X11_XFree(framebuffer_config);
                    }
                }
            }
        }
        X11_XFree(vinfo);
    }
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    ಆದರೆ (!context) {
        ಆದರೆ (error_ಸಂಕೇತ_2 == Success) {
            SDL_ಗಣ_Error("Could not create GL context");
        }
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!X11_GL_MakeCurrent(_this, ಕಿಟಕಿ, context)) {
        X11_GL_DestroyContext(_this, context);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    Display *display = _this->ಆಂತರಿಕ->display;
    ಕಿಟಕಿ_2 drawable =
        (context ? ಕಿಟಕಿ->ಆಂತರಿಕ->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    ಪೂರ್ಣಾಂಕ rc;

    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    error_ತಳ = _this->gl_ದತ್ತಾಂಶ->error_ತಳ;
    error_ಸಂಕೇತ_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_ದತ್ತಾಂಶ->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    ಆದರೆ (error_ಸಂಕೇತ_2 != Success) { // uhoh, an X error was thrown!
        ಹಿಂತಿರುಗಿ false;              // the error handler called SDL_SetError() already.
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!rc) {           // glXMakeCurrent() failed without throwing an X error
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to make GL context current");
    }

    ಹಿಂತಿರುಗಿ true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ swapinterval = 0;
bool X11_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    bool ಫಲಿತಾಂಶ = false;

    ಆದರೆ ((interval < 0) && (!_this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_ಅದಲುಬದಲು_control_tear)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Negative swap interval unsupported in this GL");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT) {
        Display *display = _this->ಆಂತರಿಕ->display;
        ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = SDL_GL_Get_Current_ಕಿಟಕಿ()->ಆಂತರಿಕ;

        ಕಿಟಕಿ_2 drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        ಪೂರ್ಣಾಂಕ currentInterval = 0;
        X11_GL_Get_ಅದಲುಬದಲು_Interval(_this, &currentInterval);
        _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT(display, drawable, interval);
        ಫಲಿತಾಂಶ = true;
        swapinterval = interval;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->glXSwapIntervalMESA) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rc = _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalMESA(interval);
        ಆದರೆ (rc == 0) {
            swapinterval = interval;
            ಫಲಿತಾಂಶ = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("glXSwapIntervalMESA failed");
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->glXSwapIntervalSGI) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rc = _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalSGI(interval);
        ಆದರೆ (rc == 0) {
            swapinterval = interval;
            ಫಲಿತಾಂಶ = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("glXSwapIntervalSGI failed");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ SDL_GLSwapIntervalTearBehavior Check_ಅದಲುಬದಲು_Interval_Tear_Behavior(SDL_VideoDevice *_this, ಕಿಟಕಿ_2 drawable, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ current_val, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_ಅದಲುಬದಲು_control_tear) {
            _this->gl_ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } ಇಲ್ಲದಿದ್ದರೆ {
            Display *display = _this->ಆಂತರಿಕ->display;
            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ allow_late_ಅದಲುಬದಲು_tearing = 22;
            ಪೂರ್ಣಾಂಕ original_val = (ಪೂರ್ಣಾಂಕ) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_ದತ್ತಾಂಶ->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_ಅದಲುಬದಲು_tearing);

            ಆದರೆ (allow_late_ಅದಲುಬದಲು_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                ಆದರೆ (current_allow_late) {
                    original_val = -original_val;
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (allow_late_ಅದಲುಬದಲು_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } ಇಲ್ಲದಿದ್ದರೆ {  // unexpected outcome!
                _this->gl_ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    ಹಿಂತಿರುಗಿ _this->gl_ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_tear_behavior;
}


bool X11_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->glXSwapIntervalEXT) {
        Display *display = _this->ಆಂತರಿಕ->display;
        ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = SDL_GL_Get_Current_ಕಿಟಕಿ()->ಆಂತರಿಕ;
        ಕಿಟಕಿ_2 drawable = windowdata->xwindow;
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ allow_late_ಅದಲುಬದಲು_tearing = 0;
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ val = 0;

        ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->HAS_GLX_EXT_ಅದಲುಬದಲು_control_tear) {
            allow_late_ಅದಲುಬದಲು_tearing = 22;  // set this to nonsense.
            _this->gl_ದತ್ತಾಂಶ->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_ಅದಲುಬದಲು_tearing);
        }

        _this->gl_ದತ್ತಾಂಶ->glXQueryDrawable(display, drawable,
                                         GLX_ಅದಲುಬದಲು_INTERVAL_EXT, &val);

        *interval = (ಪೂರ್ಣಾಂಕ)val;

        ಆಯ್ಕೆ (Check_ಅದಲುಬದಲು_Interval_Tear_Behavior(_this, drawable, val, allow_late_ಅದಲುಬದಲು_tearing)) {
            ಸ್ಥಿತಿ SDL_SWAPINTERVALTEAR_MESA:
                *interval = (ಪೂರ್ಣಾಂಕ)val;  // unsigned int cast to signed that generates negative value if necessary.
                ನಿಲ್ಲಿಸು;

            ಸ್ಥಿತಿ SDL_SWAPINTERVALTEAR_NVIDIA:
            ಪೂರ್ವನಿಯೋಜಿತ:
                ಆದರೆ ((allow_late_ಅದಲುಬದಲು_tearing) && (val > 0)) {
                    *interval = -((ಪೂರ್ಣಾಂಕ)val);
                }
                ನಿಲ್ಲಿಸು;
        }

        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->gl_XGet_ಅದಲುಬದಲು_Interval_MESA) {
        ಪೂರ್ಣಾಂಕ val = _this->gl_ದತ್ತಾಂಶ->gl_XGet_ಅದಲುಬದಲು_Interval_MESA();
        ಆದರೆ (val == GLX_BAD_CONTEXT) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("GLX_BAD_CONTEXT");
        }
        *interval = val;
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *interval = swapinterval;
        ಹಿಂತಿರುಗಿ true;
    }
}

bool X11_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;

    _this->gl_ದತ್ತಾಂಶ->glXSwapBuffers(display, ದತ್ತಾಂಶ->xwindow);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    ಹಿಂತಿರುಗಿ true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->ಆಂತರಿಕ->display;
    GLXContext glx_context = (GLXContext)context;

    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ true;
    }
    _this->gl_ದತ್ತಾಂಶ->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_GLX

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
