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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xsync.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11opengles.h"

#ਜੇ defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OPENGL "libGL.so"
#ਜਾਂਜੇ defined(SDL_PLATFORM_MACOS)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OPENGL "libGL.so.1"
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_NONE_EXT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_NONE_EXT 0x8000
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_multisample
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_multisample
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_SAMPLE_BUFFERS_ARB 100000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_SAMPLES_ARB        100001
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_EXT_visual_rating
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_EXT_visual_rating
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_VISUAL_CAVEAT_EXT         0x20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_NONE_EXT                  0x8000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_SLOW_VISUAL_EXT           0x8001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_EXT_visual_info
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_EXT_visual_info
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_X_VISUAL_TYPE_EXT 0x22
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ਸਿੱਧਾ_COLOR_EXT  0x8003
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_create_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_create_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_MAJOR_ਸੰਸਕਰਣ_ARB          0x2091
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_MINOR_ਸੰਸਕਰਣ_ARB          0x2092
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_FLAGS_ARB                  0x2094
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_DEBUG_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB              0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_FORWARD_COMPATIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB 0x0002

// Typedef for the GL 3.0 context creation function
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool ਸਿੱਧਾ,
                                                        ਅਚਲ ਪੂਰਨ
                                                            *attrib_list);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_create_context_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_create_context_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_PROFILE_ਨਕਾਬ_ARB              0x9126
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_CORE_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB          0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_COMPATIBILITY_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB 0x00000002
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_create_context_robustness
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_create_context_robustness
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_ROBUST_ACCESS_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB           0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_EXT_create_context_es2_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_EXT_create_context_es2_profile
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_CONTEXT_ES2_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_ES2_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT 0x00000002
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_framebuffer_sRGB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_framebuffer_sRGB
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_fbconfig_float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_fbconfig_float
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_RGBA_FLOAT_TYPE_ARB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_RGBA_FLOAT_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_RGBA_FLOAT_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB 0x00000004
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_create_context_no_error
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_create_context_no_error
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ਅਦਲਾ_ਬਦਲੀ_INTERVAL_EXT     0x20F1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_MAX_ਅਦਲਾ_ਬਦਲੀ_INTERVAL_EXT 0x20F2
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GLX_ARB_context_flush_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_ARB_context_flush_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENGL_REQUIRES_DLOPEN
#ਜੇ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#ਅਨ੍ਤਰ੍ਭਾਵ <dlfcn.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਲੱਦੋ_Object(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਲੱਦੋ_Function  dlsym
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UnloadObject  dlclose
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਲੱਦੋ_Object   SDL_ਲੱਦੋ_Object
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਲੱਦੋ_Function SDL_ਲੱਦੋ_Function
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UnloadObject SDL_UnloadObject
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ X11_GL_InitExtensions(SDL_VideoDevice *_this);

ਸਥਿਰ bool X11_GL_ਲੱਦੋ_Library_EGLFallback(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    X11_GL_UnloadLibrary(_this);
    _this->GL_ਲੱਦੋ_Library = X11_GLES_ਲੱਦੋ_Library;
    _this->GL_Get_Proc_ਪਤਾ = X11_GLES_Get_Proc_ਪਤਾ;
    _this->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
    _this->GL_CreateContext = X11_GLES_CreateContext;
    _this->GL_MakeCurrent = X11_GLES_MakeCurrent;
    _this->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    _this->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    _this->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = X11_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    _this->GL_DestroyContext = X11_GLES_DestroyContext;
    _this->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
    ਵਾਪਸ X11_GLES_ਲੱਦੋ_Library(_this, ਰਸਤਾ);
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not configured with EGL support");
#ਜੇ_ਅੰਤ
}

bool X11_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    Display *display;
    SDL_SharedObject *handle;

    ਜੇ (_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenGL context already created");
    }

    ਜੇ ((_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ਵਾਪਸ X11_GL_ਲੱਦੋ_Library_EGLFallback(_this, ਰਸਤਾ);
    }

    // Load the OpenGL library
    ਜੇ (ਰਸਤਾ == ਨਿਰਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    ਜੇ (ਰਸਤਾ == ਨਿਰਾ) {
        ਰਸਤਾ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_ਲੱਦੋ_Object(ਰਸਤਾ);
    ਜੇ (!_this->gl_config.dll_handle) {
#ਜੇ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_ਸੈੱਟ_Error("Failed loading %s: %s", ਰਸਤਾ, dlerror());
#ਜੇ_ਅੰਤ
        ਵਾਪਸ false;
    }
    SDL_strlcpy(_this->gl_config.driver_ਰਸਤਾ, ਰਸਤਾ,
                SDL_arraysize(_this->gl_config.driver_ਰਸਤਾ));

    // Allocate OpenGL memory
    _this->gl_ਅੰਕੜੇ =
        (ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ *)SDL_calloc(1,
                                              ਆਕਾਰ(ਬਣਤਰ
                                                     SDL_GLDriver_ਅੰਕੜੇ));
    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_ਅੰਕੜੇ->glXQueryExtension =
        (Bool(*)(Display *, ਪੂਰਨ *, ਪੂਰਨ *))
            GL_ਲੱਦੋ_Function(handle, "glXQueryExtension");
    _this->gl_ਅੰਕੜੇ->gl_XGet_Proc_ਪਤਾ =
        (__GLXextFuncPtr (*)(ਅਚਲ GLubyte *))
            GL_ਲੱਦੋ_Function(handle, "glXGetProcAddressARB");
    _this->gl_ਅੰਕੜੇ->glXChooseVisual =
        (XVisualInfo * (*)(Display *, ਪੂਰਨ, ਪੂਰਨ *))
            X11_GL_Get_Proc_ਪਤਾ(_this, "glXChooseVisual");
    _this->gl_ਅੰਕੜੇ->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, ਪੂਰਨ))
            X11_GL_Get_Proc_ਪਤਾ(_this, "glXCreateContext");
    _this->gl_ਅੰਕੜੇ->glXDestroyContext =
        (ਖਾਲੀ (*)(Display *, GLXContext))
            X11_GL_Get_Proc_ਪਤਾ(_this, "glXDestroyContext");
    _this->gl_ਅੰਕੜੇ->glXMakeCurrent =
        (ਪੂਰਨ (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_Get_Proc_ਪਤਾ(_this, "glXMakeCurrent");
    _this->gl_ਅੰਕੜੇ->glXSwapBuffers =
        (ਖਾਲੀ (*)(Display *, GLXDrawable))
            X11_GL_Get_Proc_ਪਤਾ(_this, "glXSwapBuffers");
    _this->gl_ਅੰਕੜੇ->glXQueryDrawable =
        (ਖਾਲੀ (*)(Display *, GLXDrawable, ਪੂਰਨ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *))
            X11_GL_Get_Proc_ਪਤਾ(_this, "glXQueryDrawable");

    ਜੇ (!_this->gl_ਅੰਕੜੇ->glXQueryExtension ||
        !_this->gl_ਅੰਕੜੇ->glXChooseVisual ||
        !_this->gl_ਅੰਕੜੇ->glXCreateContext ||
        !_this->gl_ਅੰਕੜੇ->glXDestroyContext ||
        !_this->gl_ਅੰਕੜੇ->glXMakeCurrent ||
        !_this->gl_ਅੰਕੜੇ->glXSwapBuffers) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not retrieve OpenGL functions");
    }

    display = _this->ਅੰਦਰੂਨੀ->display;
    ਜੇ (!_this->gl_ਅੰਕੜੇ->glXQueryExtension(display, &_this->gl_ਅੰਕੜੇ->error_ਅਧਾਰ, &_this->gl_ਅੰਕੜੇ->event_ਅਧਾਰ)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("GLX is not supported");
    }

    _this->gl_ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    ਜੇ (((_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        ਵਾਪਸ X11_GL_ਲੱਦੋ_Library_EGLFallback(_this, ਨਿਰਾ);
    }

    ਵਾਪਸ true;
}

SDL_Function_ਸੂਚਕ X11_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    ਜੇ (_this->gl_ਅੰਕੜੇ->gl_XGet_Proc_ਪਤਾ) {
        ਵਾਪਸ _this->gl_ਅੰਕੜੇ->gl_XGet_Proc_ਪਤਾ((ਅਚਲ GLubyte *)proc);
    }
    ਵਾਪਸ GL_ਲੱਦੋ_Function(_this->gl_config.dll_handle, proc);
}

ਖਾਲੀ X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#ਜੇ 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ਨਿਰਾ;
#ਜੇ_ਅੰਤ

    // Free OpenGL memory
    SDL_free(_this->gl_ਅੰਕੜੇ);
    _this->gl_ਅੰਕੜੇ = ਨਿਰਾ;
}

ਸਥਿਰ bool HasExtension(ਅਚਲ ਅੱਖਰ *extension, ਅਚਲ ਅੱਖਰ *extensions)
{
    ਅਚਲ ਅੱਖਰ *ਸ਼ੁਰੂ;
    ਅਚਲ ਅੱਖਰ *where, *terminator;

    ਜੇ (!extensions) {
        ਵਾਪਸ false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ਜੇ (where || *extension == '\0') {
        ਵਾਪਸ false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    ਸ਼ੁਰੂ = extensions;

    ਲਈ (;;) {
        where = SDL_strstr(ਸ਼ੁਰੂ, extension);
        ਜੇ (!where) {
            ਰੋਕੋ;
        }

        terminator = where + SDL_strlen(extension);
        ਜੇ (where == ਸ਼ੁਰੂ || *(where - 1) == ' ') {
            ਜੇ (*terminator == ' ' || *terminator == '\0') {
                ਵਾਪਸ true;
            }
        }

        ਸ਼ੁਰੂ = terminator;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ ਖਾਲੀ X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->ਅੰਦਰੂਨੀ->display;
    ਅਚਲ ਪੂਰਨ screen = DefaultScreen(display);
    XVisualInfo *vinfo = ਨਿਰਾ;
    ਖਿੜਕੀ_2 w = 0;
    GLXContext prev_ctx = ਨਿਰਾ;
    GLXDrawable prev_drawable = 0;
    GLXContext context = ਨਿਰਾ;
    ਅਚਲ ਅੱਖਰ *(*glXQueryExtensionsStringFunc)(Display *, ਪੂਰਨ);
    ਅਚਲ ਅੱਖਰ *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    ਜੇ (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(ਖਾਲੀ) =
            (GLXContext(*)(ਖਾਲੀ))
                X11_GL_Get_Proc_ਪਤਾ(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(ਖਾਲੀ) =
            (GLXDrawable(*)(ਖਾਲੀ))
                X11_GL_Get_Proc_ਪਤਾ(_this, "glXGetCurrentDrawable");

        ਜੇ (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSet_ਖਿੜਕੀ_ਗੁਣ xattr;
            prev_ctx = glXGetCurrentContextFunc();
            prev_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreate_ਖਿੜਕੀ(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, screen), 0, 0,
                                  32, 32, 0, vinfo->ਡੂੰਘਾਈ_2, ਨਿਵੇਸ਼_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_ਅੰਕੜੇ->glXCreateContext(display, vinfo,
                                                       ਨਿਰਾ, True);
            ਜੇ (context) {
                _this->gl_ਅੰਕੜੇ->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (ਅਚਲ ਅੱਖਰ *(*)(Display *, ਪੂਰਨ))X11_GL_Get_Proc_ਪਤਾ(_this,
                                                               "glXQueryExtensionsString");
    ਜੇ (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } ਨਹੀਂਤਾਂ {
        extensions = ਨਿਰਾ;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear = false;
    ਜੇ (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT =
            (ਖਾਲੀ (*)(Display *, GLXDrawable, ਪੂਰਨ))
                X11_GL_Get_Proc_ਪਤਾ(_this, "glXSwapIntervalEXT");
        ਜੇ (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    ਜੇ (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_ਅੰਕੜੇ->glXSwapIntervalMESA =
            (ਪੂਰਨ (*)(ਪੂਰਨ))X11_GL_Get_Proc_ਪਤਾ(_this, "glXSwapIntervalMESA");
        _this->gl_ਅੰਕੜੇ->gl_XGet_ਅਦਲਾ_ਬਦਲੀ_Interval_MESA =
            (ਪੂਰਨ (*)(ਖਾਲੀ))X11_GL_Get_Proc_ਪਤਾ(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    ਜੇ (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_ਅੰਕੜੇ->glXSwapIntervalSGI =
            (ਪੂਰਨ (*)(ਪੂਰਨ))X11_GL_Get_Proc_ਪਤਾ(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    ਜੇ (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_ਅੰਕੜੇ->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, ਅਚਲ ਪੂਰਨ *))
                X11_GL_Get_Proc_ਪਤਾ(_this, "glXCreateContextAttribsARB");
        _this->gl_ਅੰਕੜੇ->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, ਪੂਰਨ, ਅਚਲ ਪੂਰਨ *, ਪੂਰਨ *))
                X11_GL_Get_Proc_ਪਤਾ(_this, "glXChooseFBConfig");
        _this->gl_ਅੰਕੜੇ->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_Get_Proc_ਪਤਾ(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    ਜੇ (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    ਜੇ (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    ਜੇ (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        ਜੇ (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.major,
                &_this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    ਜੇ (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    ਜੇ (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    ਜੇ (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    ਜੇ (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_framebuffer_sRGB = true;
    } ਨਹੀਂਤਾਂ ਜੇ (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    ਜੇ (context) {
        _this->gl_ਅੰਕੜੇ->glXMakeCurrent(display, None, ਨਿਰਾ);
        _this->gl_ਅੰਕੜੇ->glXDestroyContext(display, context);
        ਜੇ (prev_ctx && prev_drawable) {
            _this->gl_ਅੰਕੜੇ->glXMakeCurrent(display, prev_drawable, prev_ctx);
        }
    }

    ਜੇ (w) {
        X11_XDestroy_ਖਿੜਕੀ(display, w);
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
ਸਥਿਰ ਪੂਰਨ X11_GL_Get_ਗੁਣ(SDL_VideoDevice *_this, Display *display, ਪੂਰਨ screen, ਪੂਰਨ *attribs, ਪੂਰਨ ਮਾਪ, Bool for_FBConfig, ਪੂਰਨ **_pvistypeattr, bool transparent)
{
    ਪੂਰਨ i = 0;
    ਅਚਲ ਪੂਰਨ MAX_ਗੁਣ = 64;
    ਪੂਰਨ *pvistypeattr = ਨਿਰਾ;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(ਮਾਪ >= MAX_ਗੁਣ);

    // Setup our GLX attributes according to the gl_config.
    ਜੇ (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        ਜੇ (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB;
        } ਨਹੀਂਤਾਂ {
            attribs[i++] = GLX_RGBA_ਦੋਆਧਾਰੀ_ਅੰਕ;
        }
    } ਨਹੀਂਤਾਂ {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_ਮਾਪ;
    attribs[i++] = _this->gl_config.red_ਮਾਪ;
    attribs[i++] = GLX_GREEN_ਮਾਪ;
    attribs[i++] = _this->gl_config.green_ਮਾਪ;
    attribs[i++] = GLX_BLUE_ਮਾਪ;
    attribs[i++] = _this->gl_config.blue_ਮਾਪ;

    ਜੇ (_this->gl_config.alpha_ਮਾਪ) {
        attribs[i++] = GLX_ALPHA_ਮਾਪ;
        attribs[i++] = _this->gl_config.alpha_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.double_ਬਫਰ) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        ਜੇ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_ਡੂੰਘਾਈ_ਮਾਪ;
    attribs[i++] = _this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ;

    ਜੇ (_this->gl_config.stencil_ਮਾਪ) {
        attribs[i++] = GLX_STENCIL_ਮਾਪ;
        attribs[i++] = _this->gl_config.stencil_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_red_ਮਾਪ) {
        attribs[i++] = GLX_ACCUM_RED_ਮਾਪ;
        attribs[i++] = _this->gl_config.accum_red_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_green_ਮਾਪ) {
        attribs[i++] = GLX_ACCUM_GREEN_ਮਾਪ;
        attribs[i++] = _this->gl_config.accum_green_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_blue_ਮਾਪ) {
        attribs[i++] = GLX_ACCUM_BLUE_ਮਾਪ;
        attribs[i++] = _this->gl_config.accum_blue_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_alpha_ਮਾਪ) {
        attribs[i++] = GLX_ACCUM_ALPHA_ਮਾਪ;
        attribs[i++] = _this->gl_config.accum_alpha_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        ਜੇ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    ਜੇ (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    ਜੇ (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    ਜੇ (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    ਜੇ (_this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_framebuffer_sRGB) {
        ਅਚਲ ਅੱਖਰ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ਜੇ (srgbhint && *srgbhint) {
            ਜੇ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ਨਹੀਂਤਾਂ {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    ਜੇ (_this->gl_config.accelerated >= 0 &&
        _this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    ਜੇ (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        ਜੇ (X11_Use_ਸਿੱਧਾ_Color_Visuals() && _this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_ਸਿੱਧਾ_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_ਗੁਣ);

    ਜੇ (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    ਵਾਪਸ i;
}

//get the first transparent Visual
ਸਥਿਰ XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, ਪੂਰਨ screen)
{
    XVisualInfo *visualinfo = ਨਿਰਾ;
    XVisualInfo vi_ਵਿੱਚ;
    ਪੂਰਨ ਬਾਹਰਲਾ_ਗਿਣਤੀ = 0;

    vi_ਵਿੱਚ.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ਨਕਾਬ, &vi_ਵਿੱਚ, &ਬਾਹਰਲਾ_ਗਿਣਤੀ);
    ਜੇ (visualinfo != ਨਿਰਾ) {
        ਪੂਰਨ i = 0;
        ਲਈ (i = 0; i < ਬਾਹਰਲਾ_ਗਿਣਤੀ; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            ਜੇ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_ਵਿੱਚ.screen = screen;
                vi_ਵਿੱਚ.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ਨਕਾਬ | VisualIDMask, &vi_ਵਿੱਚ, &ਬਾਹਰਲਾ_ਗਿਣਤੀ);
                ਰੋਕੋ;
            }
        }
    }
    ਵਾਪਸ visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, ਪੂਰਨ screen, bool transparent)
{
    // 64 seems nice.
    ਪੂਰਨ attribs[64];
    XVisualInfo *vinfo = ਨਿਰਾ;
    ਪੂਰਨ *pvistypeattr = ਨਿਰਾ;

    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (_this->gl_ਅੰਕੜੇ->glXChooseFBConfig &&
        _this->gl_ਅੰਕੜੇ->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = ਨਿਰਾ;
        ਪੂਰਨ fbcount = 0;

        X11_GL_Get_ਗੁਣ(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_ਅੰਕੜੇ->glXChooseFBConfig(display, screen, attribs, &fbcount);
        ਜੇ (!framebuffer_config && (pvistypeattr != ਨਿਰਾ)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_ਅੰਕੜੇ->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        ਜੇ (transparent) {
            // Return the first transparent Visual
            ਪੂਰਨ i;
            ਲਈ (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_ਅੰਕੜੇ->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                ਜੇ (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = ਨਿਰਾ;
                    ਰੋਕੋ;
                }
                X11_XFree(vinfo);
                vinfo = ਨਿਰਾ;
            }
        }

        ਜੇ (framebuffer_config) {
            vinfo = _this->gl_ਅੰਕੜੇ->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    ਜੇ (!vinfo) {
        X11_GL_Get_ਗੁਣ(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_ਅੰਕੜੇ->glXChooseVisual(display, screen, attribs);

        ਜੇ (!vinfo && (pvistypeattr != ਨਿਰਾ)) {
            *pvistypeattr = None;
            vinfo = _this->gl_ਅੰਕੜੇ->glXChooseVisual(display, screen, attribs);
        }
    }

    ਜੇ (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        ਜੇ (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            ਜੇ (visualinfo != ਨਿਰਾ) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    ਜੇ (!vinfo) {
        SDL_ਸੈੱਟ_Error("Couldn't find matching GLX visual");
    }
    ਵਾਪਸ vinfo;
}

ਸਥਿਰ ਪੂਰਨ (*handler)(Display *, XErrorEvent *) = ਨਿਰਾ;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *errorHandlerOperation = ਨਿਰਾ;
ਸਥਿਰ ਪੂਰਨ error_ਅਧਾਰ = 0;
ਸਥਿਰ ਪੂਰਨ error_ਕੋਡ_2 = 0;
ਸਥਿਰ ਪੂਰਨ X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    ਅੱਖਰ *x11_error = ਨਿਰਾ;
    ਅੱਖਰ x11_error_locale[256];

    error_ਕੋਡ_2 = e->error_ਕੋਡ;
    ਜੇ (X11_XGet_Error_ਪਾਠ(d, error_ਕੋਡ_2, x11_error_locale, ਆਕਾਰ(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    ਜੇ (x11_error) {
        SDL_ਸੈੱਟ_Error("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Could not %s: %i (Base %i)", errorHandlerOperation, error_ਕੋਡ_2, error_ਅਧਾਰ);
    }

    ਵਾਪਸ 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_ਅੰਕੜੇ != ਨਿਰਾ);
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        ਵਾਪਸ true;
    }

    SDL_assert(_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES);
    ਵਾਪਸ (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_ਸੰਸਕਰਣ == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_ਸੰਸਕਰਣ > _this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.major || (_this->gl_config.major_ਸੰਸਕਰਣ == _this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.major && _this->gl_config.minor_ਸੰਸਕਰਣ > _this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਪੂਰਨ screen = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ)->screen;
    XWindow_ਗੁਣ xattr;
    XVisualInfo v, *vinfo;
    ਪੂਰਨ n;
    SDL_GLContext context = ਨਿਰਾ;
    GLXContext share_context;
    ਅਚਲ ਪੂਰਨ transparent = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) ? true : false;

    ਜੇ (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } ਨਹੀਂਤਾਂ {
        share_context = ਨਿਰਾ;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    error_ਅਧਾਰ = _this->gl_ਅੰਕੜੇ->error_ਅਧਾਰ;
    error_ਕੋਡ_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, ਅੰਕੜੇ->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, Visual_Screen_ਨਕਾਬ | VisualIDMask, &v, &n);
    ਜੇ (vinfo) {
        ਜੇ (_this->gl_config.major_ਸੰਸਕਰਣ < 3 &&
            _this->gl_config.profile_ਨਕਾਬ == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_ਅੰਕੜੇ->glXCreateContext(display, vinfo, share_context, True);
        } ਨਹੀਂਤਾਂ {
            // max 14 attributes plus terminator
            ਪੂਰਨ attribs[15] = {
                GLX_CONTEXT_MAJOR_ਸੰਸਕਰਣ_ARB,
                _this->gl_config.major_ਸੰਸਕਰਣ,
                GLX_CONTEXT_MINOR_ਸੰਸਕਰਣ_ARB,
                _this->gl_config.minor_ਸੰਸਕਰਣ,
                0
            };
            ਪੂਰਨ iattr = 4;

            // SDL profile bits match GLX profile bits
            ਜੇ (_this->gl_config.profile_ਨਕਾਬ != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_ਨਕਾਬ_ARB;
                attribs[iattr++] = _this->gl_config.profile_ਨਕਾਬ;
            }

            // SDL flags match GLX flags
            ਜੇ (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            ਜੇ ((_this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            ਜੇ ((_this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            ਜੇ ((_this->gl_ਅੰਕੜੇ->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            ਜੇ (!_this->gl_ਅੰਕੜੇ->glXCreateContextAttribsARB) {
                SDL_ਸੈੱਟ_Error("OpenGL 3.0 and later are not supported by this system");
            } ਨਹੀਂਤਾਂ {
                ਪੂਰਨ glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = ਨਿਰਾ;
                ਪੂਰਨ fbcount = 0;
                ਪੂਰਨ *pvistypeattr = ਨਿਰਾ;

                X11_GL_Get_ਗੁਣ(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                ਜੇ (_this->gl_ਅੰਕੜੇ->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_ਅੰਕੜੇ->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    ਜੇ (!framebuffer_config && (pvistypeattr != ਨਿਰਾ)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_ਅੰਕੜੇ->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    ਜੇ (transparent && (framebuffer_config != ਨਿਰਾ)) {
                        ਪੂਰਨ i;
                        ਲਈ (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_ਆਰਜ਼ੀ = _this->gl_ਅੰਕੜੇ->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            ਜੇ ( vinfo_ਆਰਜ਼ੀ != ਨਿਰਾ) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_ਆਰਜ਼ੀ);
                                ਜੇ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_ਅੰਕੜੇ->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = ਨਿਰਾ;
                                    X11_XFree(vinfo_ਆਰਜ਼ੀ);
                                    ਰੋਕੋ;
                                }
                                X11_XFree(vinfo_ਆਰਜ਼ੀ);
                            }
                        }
                    }
                    ਜੇ (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_ਅੰਕੜੇ->glXCreateContextAttribsARB(display,
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

    ਜੇ (!context) {
        ਜੇ (error_ਕੋਡ_2 == Success) {
            SDL_ਸੈੱਟ_Error("Could not create GL context");
        }
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!X11_GL_MakeCurrent(_this, ਖਿੜਕੀ, context)) {
        X11_GL_DestroyContext(_this, context);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    Display *display = _this->ਅੰਦਰੂਨੀ->display;
    ਖਿੜਕੀ_2 drawable =
        (context ? ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    ਪੂਰਨ rc;

    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    error_ਅਧਾਰ = _this->gl_ਅੰਕੜੇ->error_ਅਧਾਰ;
    error_ਕੋਡ_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_ਅੰਕੜੇ->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    ਜੇ (error_ਕੋਡ_2 != Success) { // uhoh, an X error was thrown!
        ਵਾਪਸ false;              // the error handler called SDL_SetError() already.
    } ਨਹੀਂਤਾਂ ਜੇ (!rc) {           // glXMakeCurrent() failed without throwing an X error
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to make GL context current");
    }

    ਵਾਪਸ true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

ਸਥਿਰ ਪੂਰਨ swapinterval = 0;
bool X11_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    bool ਨਤੀਜਾ = false;

    ਜੇ ((interval < 0) && (!_this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Negative swap interval unsupported in this GL");
    } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT) {
        Display *display = _this->ਅੰਦਰੂਨੀ->display;
        ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = SDL_GL_Get_Current_ਖਿੜਕੀ()->ਅੰਦਰੂਨੀ;

        ਖਿੜਕੀ_2 drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        ਪੂਰਨ currentInterval = 0;
        X11_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(_this, &currentInterval);
        _this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT(display, drawable, interval);
        ਨਤੀਜਾ = true;
        swapinterval = interval;
    } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_ਅੰਕੜੇ->glXSwapIntervalMESA) {
        ਅਚਲ ਪੂਰਨ rc = _this->gl_ਅੰਕੜੇ->glXSwapIntervalMESA(interval);
        ਜੇ (rc == 0) {
            swapinterval = interval;
            ਨਤੀਜਾ = true;
        } ਨਹੀਂਤਾਂ {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("glXSwapIntervalMESA failed");
        }
    } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_ਅੰਕੜੇ->glXSwapIntervalSGI) {
        ਅਚਲ ਪੂਰਨ rc = _this->gl_ਅੰਕੜੇ->glXSwapIntervalSGI(interval);
        ਜੇ (rc == 0) {
            swapinterval = interval;
            ਨਤੀਜਾ = true;
        } ਨਹੀਂਤਾਂ {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("glXSwapIntervalSGI failed");
        }
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Unsupported();
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ SDL_GLSwapIntervalTearBehavior Check_ਅਦਲਾ_ਬਦਲੀ_Interval_Tear_Behavior(SDL_VideoDevice *_this, ਖਿੜਕੀ_2 drawable, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ current_val, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    ਜੇ (_this->gl_ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        ਜੇ (!_this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear) {
            _this->gl_ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } ਨਹੀਂਤਾਂ {
            Display *display = _this->ਅੰਦਰੂਨੀ->display;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing = 22;
            ਪੂਰਨ original_val = (ਪੂਰਨ) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_ਅੰਕੜੇ->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing);

            ਜੇ (allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                ਜੇ (current_allow_late) {
                    original_val = -original_val;
                }
            } ਨਹੀਂਤਾਂ ਜੇ (allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } ਨਹੀਂਤਾਂ {  // unexpected outcome!
                _this->gl_ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    ਵਾਪਸ _this->gl_ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_tear_behavior;
}


bool X11_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    ਜੇ (_this->gl_ਅੰਕੜੇ->glXSwapIntervalEXT) {
        Display *display = _this->ਅੰਦਰੂਨੀ->display;
        ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = SDL_GL_Get_Current_ਖਿੜਕੀ()->ਅੰਦਰੂਨੀ;
        ਖਿੜਕੀ_2 drawable = windowdata->xwindow;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing = 0;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ val = 0;

        ਜੇ (_this->gl_ਅੰਕੜੇ->HAS_GLX_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear) {
            allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing = 22;  // set this to nonsense.
            _this->gl_ਅੰਕੜੇ->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing);
        }

        _this->gl_ਅੰਕੜੇ->glXQueryDrawable(display, drawable,
                                         GLX_ਅਦਲਾ_ਬਦਲੀ_INTERVAL_EXT, &val);

        *interval = (ਪੂਰਨ)val;

        ਚੋਣ (Check_ਅਦਲਾ_ਬਦਲੀ_Interval_Tear_Behavior(_this, drawable, val, allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing)) {
            ਹਾਲਤ SDL_SWAPINTERVALTEAR_MESA:
                *interval = (ਪੂਰਨ)val;  // unsigned int cast to signed that generates negative value if necessary.
                ਰੋਕੋ;

            ਹਾਲਤ SDL_SWAPINTERVALTEAR_NVIDIA:
            ਮੂਲ:
                ਜੇ ((allow_late_ਅਦਲਾ_ਬਦਲੀ_tearing) && (val > 0)) {
                    *interval = -((ਪੂਰਨ)val);
                }
                ਰੋਕੋ;
        }

        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_ਅੰਕੜੇ->gl_XGet_ਅਦਲਾ_ਬਦਲੀ_Interval_MESA) {
        ਪੂਰਨ val = _this->gl_ਅੰਕੜੇ->gl_XGet_ਅਦਲਾ_ਬਦਲੀ_Interval_MESA();
        ਜੇ (val == GLX_BAD_CONTEXT) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("GLX_BAD_CONTEXT");
        }
        *interval = val;
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        *interval = swapinterval;
        ਵਾਪਸ true;
    }
}

bool X11_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;

    _this->gl_ਅੰਕੜੇ->glXSwapBuffers(display, ਅੰਕੜੇ->xwindow);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ਅੰਕੜੇ->ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    ਵਾਪਸ true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->ਅੰਦਰੂਨੀ->display;
    GLXContext glx_context = (GLXContext)context;

    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ true;
    }
    _this->gl_ਅੰਕੜੇ->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_GLX

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
