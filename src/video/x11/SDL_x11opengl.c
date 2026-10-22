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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xsync.h"
#अन्तर्भाव "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
#अन्तर्भाव "SDL_x11opengles.h"

#यदि defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#परिभाषय DEFAULT_OPENGL "libGL.so"
#नोचेद्यदि defined(SDL_PLATFORM_MACOS)
#परिभाषय DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#अन्यथा
#परिभाषय DEFAULT_OPENGL "libGL.so.1"
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_NONE_EXT
#परिभाषय GLX_NONE_EXT 0x8000
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_multisample
#परिभाषय GLX_ARB_multisample
#परिभाषय GLX_SAMPLE_BUFFERS_ARB 100000
#परिभाषय GLX_SAMPLES_ARB        100001
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_EXT_visual_rating
#परिभाषय GLX_EXT_visual_rating
#परिभाषय GLX_VISUAL_CAVEAT_EXT         0x20
#परिभाषय GLX_NONE_EXT                  0x8000
#परिभाषय GLX_SLOW_VISUAL_EXT           0x8001
#परिभाषय GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_EXT_visual_info
#परिभाषय GLX_EXT_visual_info
#परिभाषय GLX_X_VISUAL_TYPE_EXT 0x22
#परिभाषय GLX_प्रत्यक्षम्_COLOR_EXT  0x8003
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_create_context
#परिभाषय GLX_ARB_create_context
#परिभाषय GLX_CONTEXT_MAJOR_संस्करणम्_ARB          0x2091
#परिभाषय GLX_CONTEXT_MINOR_संस्करणम्_ARB          0x2092
#परिभाषय GLX_CONTEXT_FLAGS_ARB                  0x2094
#परिभाषय GLX_CONTEXT_DEBUG_BIT_ARB              0x0001
#परिभाषय GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002

// Typedef for the GL 3.0 context creation function
प्रकारनिर्देश GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool प्रत्यक्षम्,
                                                        ध्रुव पूर्णाङ्क
                                                            *attrib_list);
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_create_context_profile
#परिभाषय GLX_ARB_create_context_profile
#परिभाषय GLX_CONTEXT_PROFILE_आवरणम्_ARB              0x9126
#परिभाषय GLX_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#परिभाषय GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_create_context_robustness
#परिभाषय GLX_ARB_create_context_robustness
#परिभाषय GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB           0x00000004
#परिभाषय GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#परिभाषय GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#परिभाषय GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_EXT_create_context_es2_profile
#परिभाषय GLX_EXT_create_context_es2_profile
#यदि_अपरिभाषितम् GLX_CONTEXT_ES2_PROFILE_BIT_EXT
#परिभाषय GLX_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000002
#यदि_अन्तः
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_framebuffer_sRGB
#परिभाषय GLX_ARB_framebuffer_sRGB
#यदि_अपरिभाषितम् GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#परिभाषय GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#यदि_अन्तः
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_fbconfig_float
#परिभाषय GLX_ARB_fbconfig_float
#यदि_अपरिभाषितम् GLX_RGBA_FLOAT_TYPE_ARB
#परिभाषय GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#यदि_अन्तः
#यदि_अपरिभाषितम् GLX_RGBA_FLOAT_BIT_ARB
#परिभाषय GLX_RGBA_FLOAT_BIT_ARB 0x00000004
#यदि_अन्तः
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_create_context_no_error
#परिभाषय GLX_ARB_create_context_no_error
#यदि_अपरिभाषितम् GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#परिभाषय GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#यदि_अन्तः
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_EXT_swap_control
#परिभाषय GLX_SWAP_INTERVAL_EXT     0x20F1
#परिभाषय GLX_MAX_SWAP_INTERVAL_EXT 0x20F2
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_EXT_swap_control_tear
#परिभाषय GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#यदि_अन्तः

#यदि_अपरिभाषितम् GLX_ARB_context_flush_control
#परिभाषय GLX_ARB_context_flush_control
#परिभाषय GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#परिभाषय GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#परिभाषय GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#यदि_अन्तः

#परिभाषय OPENGL_REQUIRES_DLOPEN
#यदि defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#अन्तर्भाव <dlfcn.h>
#परिभाषय GL_आरोपय_Object(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#परिभाषय GL_आरोपय_Function  dlsym
#परिभाषय GL_UnloadObject  dlclose
#अन्यथा
#परिभाषय GL_आरोपय_Object   SDL_आरोपय_Object
#परिभाषय GL_आरोपय_Function SDL_आरोपय_Function
#परिभाषय GL_UnloadObject SDL_UnloadObject
#यदि_अन्तः

स्थिर शून्य X11_GL_InitExtensions(SDL_VideoDevice *_this);

स्थिर bool X11_GL_आरोपय_Library_EGLFallback(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    X11_GL_UnloadLibrary(_this);
    _this->GL_आरोपय_Library = X11_GLES_आरोपय_Library;
    _this->GL_Get_Proc_स्थानाङ्कः = X11_GLES_Get_Proc_स्थानाङ्कः;
    _this->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
    _this->GL_CreateContext = X11_GLES_CreateContext;
    _this->GL_MakeCurrent = X11_GLES_MakeCurrent;
    _this->GL_समुच्चयः_Swap_Interval = X11_GLES_समुच्चयः_Swap_Interval;
    _this->GL_GetSwapInterval = X11_GLES_GetSwapInterval;
    _this->GL_Swap_गवाक्षः = X11_GLES_Swap_गवाक्षः;
    _this->GL_DestroyContext = X11_GLES_DestroyContext;
    _this->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
    प्रत्यागम X11_GLES_आरोपय_Library(_this, मार्गः);
#अन्यथा
    प्रत्यागम SDL_समुच्चयः_Error("SDL not configured with EGL support");
#यदि_अन्तः
}

bool X11_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    Display *display;
    SDL_SharedObject *handle;

    यदि (_this->gl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("OpenGL context already created");
    }

    यदि ((_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        प्रत्यागम X11_GL_आरोपय_Library_EGLFallback(_this, मार्गः);
    }

    // Load the OpenGL library
    यदि (मार्गः == रिक्त) {
        मार्गः = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    यदि (मार्गः == रिक्त) {
        मार्गः = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_आरोपय_Object(मार्गः);
    यदि (!_this->gl_config.dll_handle) {
#यदि defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_समुच्चयः_Error("Failed loading %s: %s", मार्गः, dlerror());
#यदि_अन्तः
        प्रत्यागम false;
    }
    SDL_strlcpy(_this->gl_config.driver_मार्गः, मार्गः,
                SDL_arraysize(_this->gl_config.driver_मार्गः));

    // Allocate OpenGL memory
    _this->gl_दत्त =
        (संरचना SDL_GLDriver_दत्त *)SDL_calloc(1,
                                              परिमाण(संरचना
                                                     SDL_GLDriver_दत्त));
    यदि (!_this->gl_दत्त) {
        प्रत्यागम false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_दत्त->glXQueryExtension =
        (Bool(*)(Display *, पूर्णाङ्क *, पूर्णाङ्क *))
            GL_आरोपय_Function(handle, "glXQueryExtension");
    _this->gl_दत्त->gl_XGet_Proc_स्थानाङ्कः =
        (__GLXextFuncPtr (*)(ध्रुव GLubyte *))
            GL_आरोपय_Function(handle, "glXGetProcAddressARB");
    _this->gl_दत्त->glXChooseVisual =
        (XVisualInfo * (*)(Display *, पूर्णाङ्क, पूर्णाङ्क *))
            X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXChooseVisual");
    _this->gl_दत्त->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, पूर्णाङ्क))
            X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXCreateContext");
    _this->gl_दत्त->glXDestroyContext =
        (शून्य (*)(Display *, GLXContext))
            X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXDestroyContext");
    _this->gl_दत्त->glXMakeCurrent =
        (पूर्णाङ्क (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXMakeCurrent");
    _this->gl_दत्त->glXSwapBuffers =
        (शून्य (*)(Display *, GLXDrawable))
            X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXSwapBuffers");
    _this->gl_दत्त->glXQueryDrawable =
        (शून्य (*)(Display *, GLXDrawable, पूर्णाङ्क, अचिह्नित पूर्णाङ्क *))
            X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXQueryDrawable");

    यदि (!_this->gl_दत्त->glXQueryExtension ||
        !_this->gl_दत्त->glXChooseVisual ||
        !_this->gl_दत्त->glXCreateContext ||
        !_this->gl_दत्त->glXDestroyContext ||
        !_this->gl_दत्त->glXMakeCurrent ||
        !_this->gl_दत्त->glXSwapBuffers) {
        प्रत्यागम SDL_समुच्चयः_Error("Could not retrieve OpenGL functions");
    }

    display = _this->आन्तरिकम्->display;
    यदि (!_this->gl_दत्त->glXQueryExtension(display, &_this->gl_दत्त->error_आधारः, &_this->gl_दत्त->event_आधारः)) {
        प्रत्यागम SDL_समुच्चयः_Error("GLX is not supported");
    }

    _this->gl_दत्त->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    यदि (((_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        प्रत्यागम X11_GL_आरोपय_Library_EGLFallback(_this, रिक्त);
    }

    प्रत्यागम true;
}

SDL_FunctionPointer X11_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    यदि (_this->gl_दत्त->gl_XGet_Proc_स्थानाङ्कः) {
        प्रत्यागम _this->gl_दत्त->gl_XGet_Proc_स्थानाङ्कः((ध्रुव GLubyte *)proc);
    }
    प्रत्यागम GL_आरोपय_Function(_this->gl_config.dll_handle, proc);
}

शून्य X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#यदि 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = रिक्त;
#यदि_अन्तः

    // Free OpenGL memory
    SDL_free(_this->gl_दत्त);
    _this->gl_दत्त = रिक्त;
}

स्थिर bool HasExtension(ध्रुव वर्ण *extension, ध्रुव वर्ण *extensions)
{
    ध्रुव वर्ण *start;
    ध्रुव वर्ण *where, *terminator;

    यदि (!extensions) {
        प्रत्यागम false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    यदि (where || *extension == '\0') {
        प्रत्यागम false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    start = extensions;

    प्रति (;;) {
        where = SDL_strstr(start, extension);
        यदि (!where) {
            भङ्ग;
        }

        terminator = where + SDL_strlen(extension);
        यदि (where == start || *(where - 1) == ' ') {
            यदि (*terminator == ' ' || *terminator == '\0') {
                प्रत्यागम true;
            }
        }

        start = terminator;
    }
    प्रत्यागम false;
}

स्थिर शून्य X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->आन्तरिकम्->display;
    ध्रुव पूर्णाङ्क screen = DefaultScreen(display);
    XVisualInfo *vinfo = रिक्त;
    गवाक्षः_2 w = 0;
    GLXContext पूर्व_ctx = रिक्त;
    GLXDrawable पूर्व_drawable = 0;
    GLXContext context = रिक्त;
    ध्रुव वर्ण *(*glXQueryExtensionsStringFunc)(Display *, पूर्णाङ्क);
    ध्रुव वर्ण *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    यदि (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(शून्य) =
            (GLXContext(*)(शून्य))
                X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(शून्य) =
            (GLXDrawable(*)(शून्य))
                X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXGetCurrentDrawable");

        यदि (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSet_गवाक्षः_गुणाः xattr;
            पूर्व_ctx = glXGetCurrentContextFunc();
            पूर्व_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, मूलम्_गवाक्षः(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreate_गवाक्षः(display, मूलम्_गवाक्षः(display, screen), 0, 0,
                                  32, 32, 0, vinfo->गभीरता_2, निवेशः_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_दत्त->glXCreateContext(display, vinfo,
                                                       रिक्त, True);
            यदि (context) {
                _this->gl_दत्त->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (ध्रुव वर्ण *(*)(Display *, पूर्णाङ्क))X11_GL_Get_Proc_स्थानाङ्कः(_this,
                                                               "glXQueryExtensionsString");
    यदि (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } अन्यथा {
        extensions = रिक्त;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_दत्त->HAS_GLX_EXT_swap_control_tear = false;
    यदि (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_दत्त->glXSwapIntervalEXT =
            (शून्य (*)(Display *, GLXDrawable, पूर्णाङ्क))
                X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXSwapIntervalEXT");
        यदि (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_दत्त->HAS_GLX_EXT_swap_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    यदि (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_दत्त->glXSwapIntervalMESA =
            (पूर्णाङ्क (*)(पूर्णाङ्क))X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXSwapIntervalMESA");
        _this->gl_दत्त->glXGetSwapIntervalMESA =
            (पूर्णाङ्क (*)(शून्य))X11_GL_Get_Proc_स्थानाङ्कः(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    यदि (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_दत्त->glXSwapIntervalSGI =
            (पूर्णाङ्क (*)(पूर्णाङ्क))X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    यदि (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_दत्त->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, ध्रुव पूर्णाङ्क *))
                X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXCreateContextAttribsARB");
        _this->gl_दत्त->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, पूर्णाङ्क, ध्रुव पूर्णाङ्क *, पूर्णाङ्क *))
                X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXChooseFBConfig");
        _this->gl_दत्त->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_Get_Proc_स्थानाङ्कः(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    यदि (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_दत्त->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    यदि (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_दत्त->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    यदि (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        यदि (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_दत्त->es_profile_max_supported_संस्करणम्.major,
                &_this->gl_दत्त->es_profile_max_supported_संस्करणम्.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    यदि (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_दत्त->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    यदि (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_दत्त->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    यदि (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_दत्त->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    यदि (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_दत्त->HAS_GLX_ARB_framebuffer_sRGB = true;
    } अन्यथा यदि (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_दत्त->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    यदि (context) {
        _this->gl_दत्त->glXMakeCurrent(display, None, रिक्त);
        _this->gl_दत्त->glXDestroyContext(display, context);
        यदि (पूर्व_ctx && पूर्व_drawable) {
            _this->gl_दत्त->glXMakeCurrent(display, पूर्व_drawable, पूर्व_ctx);
        }
    }

    यदि (w) {
        X11_XDestroy_गवाक्षः(display, w);
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
स्थिर पूर्णाङ्क X11_GL_Get_गुणाः(SDL_VideoDevice *_this, Display *display, पूर्णाङ्क screen, पूर्णाङ्क *attribs, पूर्णाङ्क आकार, Bool for_FBConfig, पूर्णाङ्क **_pvistypeattr, bool transparent)
{
    पूर्णाङ्क i = 0;
    ध्रुव पूर्णाङ्क MAX_गुणाः = 64;
    पूर्णाङ्क *pvistypeattr = रिक्त;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(आकार >= MAX_गुणाः);

    // Setup our GLX attributes according to the gl_config.
    यदि (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        यदि (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_BIT_ARB;
        } अन्यथा {
            attribs[i++] = GLX_RGBA_BIT;
        }
    } अन्यथा {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_आकार;
    attribs[i++] = _this->gl_config.red_आकार;
    attribs[i++] = GLX_GREEN_आकार;
    attribs[i++] = _this->gl_config.green_आकार;
    attribs[i++] = GLX_BLUE_आकार;
    attribs[i++] = _this->gl_config.blue_आकार;

    यदि (_this->gl_config.alpha_आकार) {
        attribs[i++] = GLX_ALPHA_आकार;
        attribs[i++] = _this->gl_config.alpha_आकार;
    }

    यदि (_this->gl_config.double_बफर) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        यदि (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_गभीरता_आकार;
    attribs[i++] = _this->gl_config.गभीरता_आकार;

    यदि (_this->gl_config.stencil_आकार) {
        attribs[i++] = GLX_STENCIL_आकार;
        attribs[i++] = _this->gl_config.stencil_आकार;
    }

    यदि (_this->gl_config.accum_red_आकार) {
        attribs[i++] = GLX_ACCUM_RED_आकार;
        attribs[i++] = _this->gl_config.accum_red_आकार;
    }

    यदि (_this->gl_config.accum_green_आकार) {
        attribs[i++] = GLX_ACCUM_GREEN_आकार;
        attribs[i++] = _this->gl_config.accum_green_आकार;
    }

    यदि (_this->gl_config.accum_blue_आकार) {
        attribs[i++] = GLX_ACCUM_BLUE_आकार;
        attribs[i++] = _this->gl_config.accum_blue_आकार;
    }

    यदि (_this->gl_config.accum_alpha_आकार) {
        attribs[i++] = GLX_ACCUM_ALPHA_आकार;
        attribs[i++] = _this->gl_config.accum_alpha_आकार;
    }

    यदि (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        यदि (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    यदि (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    यदि (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    यदि (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    यदि (_this->gl_दत्त->HAS_GLX_ARB_framebuffer_sRGB) {
        ध्रुव वर्ण *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        यदि (srgbhint && *srgbhint) {
            यदि (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } अन्यथा {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } अन्यथा यदि (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    यदि (_this->gl_config.accelerated >= 0 &&
        _this->gl_दत्त->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    यदि (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        यदि (X11_Use_प्रत्यक्षम्_Color_Visuals() && _this->gl_दत्त->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_प्रत्यक्षम्_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_गुणाः);

    यदि (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    प्रत्यागम i;
}

//get the first transparent Visual
स्थिर XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, पूर्णाङ्क screen)
{
    XVisualInfo *visualinfo = रिक्त;
    XVisualInfo vi_अन्तर्;
    पूर्णाङ्क बहिर्गमनम्_गणनम् = 0;

    vi_अन्तर्.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, Visual_Screen_आवरणम्, &vi_अन्तर्, &बहिर्गमनम्_गणनम्);
    यदि (visualinfo != रिक्त) {
        पूर्णाङ्क i = 0;
        प्रति (i = 0; i < बहिर्गमनम्_गणनम्; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            यदि (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_अन्तर्.screen = screen;
                vi_अन्तर्.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, Visual_Screen_आवरणम् | VisualIDMask, &vi_अन्तर्, &बहिर्गमनम्_गणनम्);
                भङ्ग;
            }
        }
    }
    प्रत्यागम visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, पूर्णाङ्क screen, bool transparent)
{
    // 64 seems nice.
    पूर्णाङ्क attribs[64];
    XVisualInfo *vinfo = रिक्त;
    पूर्णाङ्क *pvistypeattr = रिक्त;

    यदि (!_this->gl_दत्त) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        प्रत्यागम रिक्त;
    }

    यदि (_this->gl_दत्त->glXChooseFBConfig &&
        _this->gl_दत्त->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = रिक्त;
        पूर्णाङ्क fbcount = 0;

        X11_GL_Get_गुणाः(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_दत्त->glXChooseFBConfig(display, screen, attribs, &fbcount);
        यदि (!framebuffer_config && (pvistypeattr != रिक्त)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_दत्त->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        यदि (transparent) {
            // Return the first transparent Visual
            पूर्णाङ्क i;
            प्रति (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_दत्त->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                यदि (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = रिक्त;
                    भङ्ग;
                }
                X11_XFree(vinfo);
                vinfo = रिक्त;
            }
        }

        यदि (framebuffer_config) {
            vinfo = _this->gl_दत्त->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    यदि (!vinfo) {
        X11_GL_Get_गुणाः(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_दत्त->glXChooseVisual(display, screen, attribs);

        यदि (!vinfo && (pvistypeattr != रिक्त)) {
            *pvistypeattr = None;
            vinfo = _this->gl_दत्त->glXChooseVisual(display, screen, attribs);
        }
    }

    यदि (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        यदि (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            यदि (visualinfo != रिक्त) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    यदि (!vinfo) {
        SDL_समुच्चयः_Error("Couldn't find matching GLX visual");
    }
    प्रत्यागम vinfo;
}

स्थिर पूर्णाङ्क (*handler)(Display *, XErrorEvent *) = रिक्त;
स्थिर ध्रुव वर्ण *errorHandlerOperation = रिक्त;
स्थिर पूर्णाङ्क error_आधारः = 0;
स्थिर पूर्णाङ्क error_संहिता_2 = 0;
स्थिर पूर्णाङ्क X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    वर्ण *x11_error = रिक्त;
    वर्ण x11_error_locale[256];

    error_संहिता_2 = e->error_संहिता;
    यदि (X11_XGetErrorText(d, error_संहिता_2, x11_error_locale, परिमाण(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    यदि (x11_error) {
        SDL_समुच्चयः_Error("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } अन्यथा {
        SDL_समुच्चयः_Error("Could not %s: %i (Base %i)", errorHandlerOperation, error_संहिता_2, error_आधारः);
    }

    प्रत्यागम 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_दत्त != रिक्त);
    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        प्रत्यागम true;
    }

    SDL_assert(_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES);
    प्रत्यागम (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_संस्करणम् == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_संस्करणम् > _this->gl_दत्त->es_profile_max_supported_संस्करणम्.major || (_this->gl_config.major_संस्करणम् == _this->gl_दत्त->es_profile_max_supported_संस्करणम्.major && _this->gl_config.minor_संस्करणम् > _this->gl_दत्त->es_profile_max_supported_संस्करणम्.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    पूर्णाङ्क screen = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः)->screen;
    XWindow_गुणाः xattr;
    XVisualInfo v, *vinfo;
    पूर्णाङ्क n;
    SDL_GLContext context = रिक्त;
    GLXContext share_context;
    ध्रुव पूर्णाङ्क transparent = (गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) ? true : false;

    यदि (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } अन्यथा {
        share_context = रिक्त;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    error_आधारः = _this->gl_दत्त->error_आधारः;
    error_संहिता_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGet_गवाक्षः_गुणाः(display, दत्त->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, Visual_Screen_आवरणम् | VisualIDMask, &v, &n);
    यदि (vinfo) {
        यदि (_this->gl_config.major_संस्करणम् < 3 &&
            _this->gl_config.profile_आवरणम् == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_दत्त->glXCreateContext(display, vinfo, share_context, True);
        } अन्यथा {
            // max 14 attributes plus terminator
            पूर्णाङ्क attribs[15] = {
                GLX_CONTEXT_MAJOR_संस्करणम्_ARB,
                _this->gl_config.major_संस्करणम्,
                GLX_CONTEXT_MINOR_संस्करणम्_ARB,
                _this->gl_config.minor_संस्करणम्,
                0
            };
            पूर्णाङ्क iattr = 4;

            // SDL profile bits match GLX profile bits
            यदि (_this->gl_config.profile_आवरणम् != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_आवरणम्_ARB;
                attribs[iattr++] = _this->gl_config.profile_आवरणम्;
            }

            // SDL flags match GLX flags
            यदि (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            यदि ((_this->gl_दत्त->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            यदि ((_this->gl_दत्त->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            यदि ((_this->gl_दत्त->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            यदि (!_this->gl_दत्त->glXCreateContextAttribsARB) {
                SDL_समुच्चयः_Error("OpenGL 3.0 and later are not supported by this system");
            } अन्यथा {
                पूर्णाङ्क glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = रिक्त;
                पूर्णाङ्क fbcount = 0;
                पूर्णाङ्क *pvistypeattr = रिक्त;

                X11_GL_Get_गुणाः(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                यदि (_this->gl_दत्त->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_दत्त->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    यदि (!framebuffer_config && (pvistypeattr != रिक्त)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_दत्त->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    यदि (transparent && (framebuffer_config != रिक्त)) {
                        पूर्णाङ्क i;
                        प्रति (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_अस्थायी = _this->gl_दत्त->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            यदि ( vinfo_अस्थायी != रिक्त) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_अस्थायी);
                                यदि (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_दत्त->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = रिक्त;
                                    X11_XFree(vinfo_अस्थायी);
                                    भङ्ग;
                                }
                                X11_XFree(vinfo_अस्थायी);
                            }
                        }
                    }
                    यदि (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_दत्त->glXCreateContextAttribsARB(display,
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

    यदि (!context) {
        यदि (error_संहिता_2 == Success) {
            SDL_समुच्चयः_Error("Could not create GL context");
        }
        प्रत्यागम रिक्त;
    }

    यदि (!X11_GL_MakeCurrent(_this, गवाक्षः, context)) {
        X11_GL_DestroyContext(_this, context);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    Display *display = _this->आन्तरिकम्->display;
    गवाक्षः_2 drawable =
        (context ? गवाक्षः->आन्तरिकम्->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    पूर्णाङ्क rc;

    यदि (!_this->gl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    error_आधारः = _this->gl_दत्त->error_आधारः;
    error_संहिता_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_दत्त->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    यदि (error_संहिता_2 != Success) { // uhoh, an X error was thrown!
        प्रत्यागम false;              // the error handler called SDL_SetError() already.
    } अन्यथा यदि (!rc) {           // glXMakeCurrent() failed without throwing an X error
        प्रत्यागम SDL_समुच्चयः_Error("Unable to make GL context current");
    }

    प्रत्यागम true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

स्थिर पूर्णाङ्क swapinterval = 0;
bool X11_GL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    bool परिणाम = false;

    यदि ((interval < 0) && (!_this->gl_दत्त->HAS_GLX_EXT_swap_control_tear)) {
        प्रत्यागम SDL_समुच्चयः_Error("Negative swap interval unsupported in this GL");
    } अन्यथा यदि (_this->gl_दत्त->glXSwapIntervalEXT) {
        Display *display = _this->आन्तरिकम्->display;
        ध्रुव SDL_गवाक्षः_दत्त *windowdata = SDL_GL_Get_Current_गवाक्षः()->आन्तरिकम्;

        गवाक्षः_2 drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        पूर्णाङ्क currentInterval = 0;
        X11_GL_GetSwapInterval(_this, &currentInterval);
        _this->gl_दत्त->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_दत्त->glXSwapIntervalEXT(display, drawable, interval);
        परिणाम = true;
        swapinterval = interval;
    } अन्यथा यदि (_this->gl_दत्त->glXSwapIntervalMESA) {
        ध्रुव पूर्णाङ्क rc = _this->gl_दत्त->glXSwapIntervalMESA(interval);
        यदि (rc == 0) {
            swapinterval = interval;
            परिणाम = true;
        } अन्यथा {
            परिणाम = SDL_समुच्चयः_Error("glXSwapIntervalMESA failed");
        }
    } अन्यथा यदि (_this->gl_दत्त->glXSwapIntervalSGI) {
        ध्रुव पूर्णाङ्क rc = _this->gl_दत्त->glXSwapIntervalSGI(interval);
        यदि (rc == 0) {
            swapinterval = interval;
            परिणाम = true;
        } अन्यथा {
            परिणाम = SDL_समुच्चयः_Error("glXSwapIntervalSGI failed");
        }
    } अन्यथा {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम परिणाम;
}

स्थिर SDL_GLSwapIntervalTearBehavior CheckSwapIntervalTearBehavior(SDL_VideoDevice *_this, गवाक्षः_2 drawable, अचिह्नित पूर्णाङ्क current_val, अचिह्नित पूर्णाङ्क current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    यदि (_this->gl_दत्त->swap_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        यदि (!_this->gl_दत्त->HAS_GLX_EXT_swap_control_tear) {
            _this->gl_दत्त->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } अन्यथा {
            Display *display = _this->आन्तरिकम्->display;
            अचिह्नित पूर्णाङ्क allow_late_swap_tearing = 22;
            पूर्णाङ्क original_val = (पूर्णाङ्क) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_दत्त->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_दत्त->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_दत्त->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_swap_tearing);

            यदि (allow_late_swap_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_दत्त->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                यदि (current_allow_late) {
                    original_val = -original_val;
                }
            } अन्यथा यदि (allow_late_swap_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_दत्त->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } अन्यथा {  // unexpected outcome!
                _this->gl_दत्त->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_दत्त->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    प्रत्यागम _this->gl_दत्त->swap_interval_tear_behavior;
}


bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    यदि (_this->gl_दत्त->glXSwapIntervalEXT) {
        Display *display = _this->आन्तरिकम्->display;
        ध्रुव SDL_गवाक्षः_दत्त *windowdata = SDL_GL_Get_Current_गवाक्षः()->आन्तरिकम्;
        गवाक्षः_2 drawable = windowdata->xwindow;
        अचिह्नित पूर्णाङ्क allow_late_swap_tearing = 0;
        अचिह्नित पूर्णाङ्क val = 0;

        यदि (_this->gl_दत्त->HAS_GLX_EXT_swap_control_tear) {
            allow_late_swap_tearing = 22;  // set this to nonsense.
            _this->gl_दत्त->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_swap_tearing);
        }

        _this->gl_दत्त->glXQueryDrawable(display, drawable,
                                         GLX_SWAP_INTERVAL_EXT, &val);

        *interval = (पूर्णाङ्क)val;

        विकल्प (CheckSwapIntervalTearBehavior(_this, drawable, val, allow_late_swap_tearing)) {
            पक्ष SDL_SWAPINTERVALTEAR_MESA:
                *interval = (पूर्णाङ्क)val;  // unsigned int cast to signed that generates negative value if necessary.
                भङ्ग;

            पक्ष SDL_SWAPINTERVALTEAR_NVIDIA:
            स्वभाव:
                यदि ((allow_late_swap_tearing) && (val > 0)) {
                    *interval = -((पूर्णाङ्क)val);
                }
                भङ्ग;
        }

        प्रत्यागम true;
    } अन्यथा यदि (_this->gl_दत्त->glXGetSwapIntervalMESA) {
        पूर्णाङ्क val = _this->gl_दत्त->glXGetSwapIntervalMESA();
        यदि (val == GLX_BAD_CONTEXT) {
            प्रत्यागम SDL_समुच्चयः_Error("GLX_BAD_CONTEXT");
        }
        *interval = val;
        प्रत्यागम true;
    } अन्यथा {
        *interval = swapinterval;
        प्रत्यागम true;
    }
}

bool X11_GL_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;

    _this->gl_दत्त->glXSwapBuffers(display, दत्त->xwindow);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(दत्त->गवाक्षः);
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */

    प्रत्यागम true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->आन्तरिकम्->display;
    GLXContext glx_context = (GLXContext)context;

    यदि (!_this->gl_दत्त) {
        प्रत्यागम true;
    }
    _this->gl_दत्त->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_OPENGL_GLX

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
