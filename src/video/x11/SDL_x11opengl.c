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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل "SDL_x11video.h"
#شامل "SDL_x11xsync.h"
#شامل "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
#شامل "SDL_x11opengles.h"

#اگر defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#تعریف_کرو DEFAULT_OPENGL "libGL.so"
#وگرنہ_اگر defined(SDL_PLATFORM_MACOS)
#تعریف_کرو DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#ورنہ
#تعریف_کرو DEFAULT_OPENGL "libGL.so.1"
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_NONE_EXT
#تعریف_کرو GLX_NONE_EXT 0x8000
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_multisample
#تعریف_کرو GLX_ARB_multisample
#تعریف_کرو GLX_SAMPLE_BUFFERS_ARB 100000
#تعریف_کرو GLX_SAMPLES_ARB        100001
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_EXT_visual_rating
#تعریف_کرو GLX_EXT_visual_rating
#تعریف_کرو GLX_VISUAL_CAVEAT_EXT         0x20
#تعریف_کرو GLX_NONE_EXT                  0x8000
#تعریف_کرو GLX_SLOW_VISUAL_EXT           0x8001
#تعریف_کرو GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_EXT_visual_info
#تعریف_کرو GLX_EXT_visual_info
#تعریف_کرو GLX_X_VISUAL_TYPE_EXT 0x22
#تعریف_کرو GLX_براہ_راست_COLOR_EXT  0x8003
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_create_context
#تعریف_کرو GLX_ARB_create_context
#تعریف_کرو GLX_CONTEXT_MAJOR_نسخہ_ARB          0x2091
#تعریف_کرو GLX_CONTEXT_MINOR_نسخہ_ARB          0x2092
#تعریف_کرو GLX_CONTEXT_FLAGS_ARB                  0x2094
#تعریف_کرو GLX_CONTEXT_DEBUG_ثنائی_ہندسہ_ARB              0x0001
#تعریف_کرو GLX_CONTEXT_FORWARD_COMPATIBLE_ثنائی_ہندسہ_ARB 0x0002

// Typedef for the GL 3.0 context creation function
قسمتعریف GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool براہ_راست,
                                                        ثابت صحیح
                                                            *attrib_list);
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_create_context_profile
#تعریف_کرو GLX_ARB_create_context_profile
#تعریف_کرو GLX_CONTEXT_PROFILE_نقاب_ARB              0x9126
#تعریف_کرو GLX_CONTEXT_CORE_PROFILE_ثنائی_ہندسہ_ARB          0x00000001
#تعریف_کرو GLX_CONTEXT_COMPATIBILITY_PROFILE_ثنائی_ہندسہ_ARB 0x00000002
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_create_context_robustness
#تعریف_کرو GLX_ARB_create_context_robustness
#تعریف_کرو GLX_CONTEXT_ROBUST_ACCESS_ثنائی_ہندسہ_ARB           0x00000004
#تعریف_کرو GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#تعریف_کرو GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#تعریف_کرو GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_EXT_create_context_es2_profile
#تعریف_کرو GLX_EXT_create_context_es2_profile
#اگر_غیر_تعریف_شدہ GLX_CONTEXT_ES2_PROFILE_ثنائی_ہندسہ_EXT
#تعریف_کرو GLX_CONTEXT_ES2_PROFILE_ثنائی_ہندسہ_EXT 0x00000002
#اگر_ختم
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_framebuffer_sRGB
#تعریف_کرو GLX_ARB_framebuffer_sRGB
#اگر_غیر_تعریف_شدہ GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#تعریف_کرو GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#اگر_ختم
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_fbconfig_float
#تعریف_کرو GLX_ARB_fbconfig_float
#اگر_غیر_تعریف_شدہ GLX_RGBA_FLOAT_TYPE_ARB
#تعریف_کرو GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#اگر_ختم
#اگر_غیر_تعریف_شدہ GLX_RGBA_FLOAT_ثنائی_ہندسہ_ARB
#تعریف_کرو GLX_RGBA_FLOAT_ثنائی_ہندسہ_ARB 0x00000004
#اگر_ختم
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_create_context_no_error
#تعریف_کرو GLX_ARB_create_context_no_error
#اگر_غیر_تعریف_شدہ GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#تعریف_کرو GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#اگر_ختم
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_EXT_تبادلہ_control
#تعریف_کرو GLX_تبادلہ_INTERVAL_EXT     0x20F1
#تعریف_کرو GLX_MAX_تبادلہ_INTERVAL_EXT 0x20F2
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_EXT_تبادلہ_control_tear
#تعریف_کرو GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#اگر_ختم

#اگر_غیر_تعریف_شدہ GLX_ARB_context_flush_control
#تعریف_کرو GLX_ARB_context_flush_control
#تعریف_کرو GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#تعریف_کرو GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#تعریف_کرو GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#اگر_ختم

#تعریف_کرو OPENGL_REQUIRES_DLOPEN
#اگر defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#شامل <dlfcn.h>
#تعریف_کرو GL_بھرو_Object(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#تعریف_کرو GL_بھرو_Function  dlsym
#تعریف_کرو GL_UnloadObject  dlclose
#ورنہ
#تعریف_کرو GL_بھرو_Object   SDL_بھرو_Object
#تعریف_کرو GL_بھرو_Function SDL_بھرو_Function
#تعریف_کرو GL_UnloadObject SDL_UnloadObject
#اگر_ختم

ساکن خالی X11_GL_InitExtensions(SDL_VideoDevice *_this);

ساکن bool X11_GL_بھرو_Library_EGLFallback(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    X11_GL_UnloadLibrary(_this);
    _this->GL_بھرو_Library = X11_GLES_بھرو_Library;
    _this->GL_Get_Proc_پتہ = X11_GLES_Get_Proc_پتہ;
    _this->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
    _this->GL_CreateContext = X11_GLES_CreateContext;
    _this->GL_MakeCurrent = X11_GLES_MakeCurrent;
    _this->GL_سیٹ_تبادلہ_Interval = X11_GLES_سیٹ_تبادلہ_Interval;
    _this->GL_Get_تبادلہ_Interval = X11_GLES_Get_تبادلہ_Interval;
    _this->GL_تبادلہ_کھڑکی = X11_GLES_تبادلہ_کھڑکی;
    _this->GL_DestroyContext = X11_GLES_DestroyContext;
    _this->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
    واپس X11_GLES_بھرو_Library(_this, راستہ);
#ورنہ
    واپس SDL_سیٹ_Error("SDL not configured with EGL support");
#اگر_ختم
}

bool X11_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    Display *display;
    SDL_SharedObject *handle;

    اگر (_this->gl_ڈیٹا) {
        واپس SDL_سیٹ_Error("OpenGL context already created");
    }

    اگر ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        واپس X11_GL_بھرو_Library_EGLFallback(_this, راستہ);
    }

    // Load the OpenGL library
    اگر (راستہ == تہی) {
        راستہ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    اگر (راستہ == تہی) {
        راستہ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_بھرو_Object(راستہ);
    اگر (!_this->gl_config.dll_handle) {
#اگر defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_سیٹ_Error("Failed loading %s: %s", راستہ, dlerror());
#اگر_ختم
        واپس false;
    }
    SDL_strlcpy(_this->gl_config.driver_راستہ, راستہ,
                SDL_arraysize(_this->gl_config.driver_راستہ));

    // Allocate OpenGL memory
    _this->gl_ڈیٹا =
        (ساخت SDL_GLDriver_ڈیٹا *)SDL_calloc(1,
                                              حجم(ساخت
                                                     SDL_GLDriver_ڈیٹا));
    اگر (!_this->gl_ڈیٹا) {
        واپس false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_ڈیٹا->glXQueryExtension =
        (Bool(*)(Display *, صحیح *, صحیح *))
            GL_بھرو_Function(handle, "glXQueryExtension");
    _this->gl_ڈیٹا->gl_XGet_Proc_پتہ =
        (__GLXextFuncPtr (*)(ثابت GLubyte *))
            GL_بھرو_Function(handle, "glXGetProcAddressARB");
    _this->gl_ڈیٹا->glXChooseVisual =
        (XVisualInfo * (*)(Display *, صحیح, صحیح *))
            X11_GL_Get_Proc_پتہ(_this, "glXChooseVisual");
    _this->gl_ڈیٹا->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, صحیح))
            X11_GL_Get_Proc_پتہ(_this, "glXCreateContext");
    _this->gl_ڈیٹا->glXDestroyContext =
        (خالی (*)(Display *, GLXContext))
            X11_GL_Get_Proc_پتہ(_this, "glXDestroyContext");
    _this->gl_ڈیٹا->glXMakeCurrent =
        (صحیح (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_Get_Proc_پتہ(_this, "glXMakeCurrent");
    _this->gl_ڈیٹا->glXSwapBuffers =
        (خالی (*)(Display *, GLXDrawable))
            X11_GL_Get_Proc_پتہ(_this, "glXSwapBuffers");
    _this->gl_ڈیٹا->glXQueryDrawable =
        (خالی (*)(Display *, GLXDrawable, صحیح, غیرعلامتی صحیح *))
            X11_GL_Get_Proc_پتہ(_this, "glXQueryDrawable");

    اگر (!_this->gl_ڈیٹا->glXQueryExtension ||
        !_this->gl_ڈیٹا->glXChooseVisual ||
        !_this->gl_ڈیٹا->glXCreateContext ||
        !_this->gl_ڈیٹا->glXDestroyContext ||
        !_this->gl_ڈیٹا->glXMakeCurrent ||
        !_this->gl_ڈیٹا->glXSwapBuffers) {
        واپس SDL_سیٹ_Error("Could not retrieve OpenGL functions");
    }

    display = _this->اندرونی_2->display;
    اگر (!_this->gl_ڈیٹا->glXQueryExtension(display, &_this->gl_ڈیٹا->error_بنیاد, &_this->gl_ڈیٹا->event_بنیاد)) {
        واپس SDL_سیٹ_Error("GLX is not supported");
    }

    _this->gl_ڈیٹا->تبادلہ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    اگر (((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        واپس X11_GL_بھرو_Library_EGLFallback(_this, تہی);
    }

    واپس true;
}

SDL_Function_اشارہ_گر X11_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    اگر (_this->gl_ڈیٹا->gl_XGet_Proc_پتہ) {
        واپس _this->gl_ڈیٹا->gl_XGet_Proc_پتہ((ثابت GLubyte *)proc);
    }
    واپس GL_بھرو_Function(_this->gl_config.dll_handle, proc);
}

خالی X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#اگر 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = تہی;
#اگر_ختم

    // Free OpenGL memory
    SDL_free(_this->gl_ڈیٹا);
    _this->gl_ڈیٹا = تہی;
}

ساکن bool HasExtension(ثابت حرف *extension, ثابت حرف *extensions)
{
    ثابت حرف *آغاز;
    ثابت حرف *where, *terminator;

    اگر (!extensions) {
        واپس false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    اگر (where || *extension == '\0') {
        واپس false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    آغاز = extensions;

    برائے (;;) {
        where = SDL_strstr(آغاز, extension);
        اگر (!where) {
            توڑو;
        }

        terminator = where + SDL_strlen(extension);
        اگر (where == آغاز || *(where - 1) == ' ') {
            اگر (*terminator == ' ' || *terminator == '\0') {
                واپس true;
            }
        }

        آغاز = terminator;
    }
    واپس false;
}

ساکن خالی X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->اندرونی_2->display;
    ثابت صحیح screen = DefaultScreen(display);
    XVisualInfo *vinfo = تہی;
    کھڑکی_2 w = 0;
    GLXContext پچھلا_ctx = تہی;
    GLXDrawable پچھلا_drawable = 0;
    GLXContext context = تہی;
    ثابت حرف *(*glXQueryExtensionsStringFunc)(Display *, صحیح);
    ثابت حرف *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    اگر (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(خالی) =
            (GLXContext(*)(خالی))
                X11_GL_Get_Proc_پتہ(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(خالی) =
            (GLXDrawable(*)(خالی))
                X11_GL_Get_Proc_پتہ(_this, "glXGetCurrentDrawable");

        اگر (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSet_کھڑکی_اوصاف xattr;
            پچھلا_ctx = glXGetCurrentContextFunc();
            پچھلا_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, جڑ_کھڑکی(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreate_کھڑکی(display, جڑ_کھڑکی(display, screen), 0, 0,
                                  32, 32, 0, vinfo->گہرائی_2, داخلہ_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_ڈیٹا->glXCreateContext(display, vinfo,
                                                       تہی, True);
            اگر (context) {
                _this->gl_ڈیٹا->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (ثابت حرف *(*)(Display *, صحیح))X11_GL_Get_Proc_پتہ(_this,
                                                               "glXQueryExtensionsString");
    اگر (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } ورنہ {
        extensions = تہی;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_ڈیٹا->HAS_GLX_EXT_تبادلہ_control_tear = false;
    اگر (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_ڈیٹا->glXSwapIntervalEXT =
            (خالی (*)(Display *, GLXDrawable, صحیح))
                X11_GL_Get_Proc_پتہ(_this, "glXSwapIntervalEXT");
        اگر (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_ڈیٹا->HAS_GLX_EXT_تبادلہ_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    اگر (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_ڈیٹا->glXSwapIntervalMESA =
            (صحیح (*)(صحیح))X11_GL_Get_Proc_پتہ(_this, "glXSwapIntervalMESA");
        _this->gl_ڈیٹا->gl_XGet_تبادلہ_Interval_MESA =
            (صحیح (*)(خالی))X11_GL_Get_Proc_پتہ(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    اگر (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_ڈیٹا->glXSwapIntervalSGI =
            (صحیح (*)(صحیح))X11_GL_Get_Proc_پتہ(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    اگر (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_ڈیٹا->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, ثابت صحیح *))
                X11_GL_Get_Proc_پتہ(_this, "glXCreateContextAttribsARB");
        _this->gl_ڈیٹا->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, صحیح, ثابت صحیح *, صحیح *))
                X11_GL_Get_Proc_پتہ(_this, "glXChooseFBConfig");
        _this->gl_ڈیٹا->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_Get_Proc_پتہ(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    اگر (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_ڈیٹا->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    اگر (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_ڈیٹا->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    اگر (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        اگر (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_ڈیٹا->es_profile_max_supported_نسخہ.major,
                &_this->gl_ڈیٹا->es_profile_max_supported_نسخہ.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    اگر (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_ڈیٹا->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    اگر (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_ڈیٹا->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    اگر (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_ڈیٹا->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    اگر (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_ڈیٹا->HAS_GLX_ARB_framebuffer_sRGB = true;
    } ورنہ اگر (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_ڈیٹا->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    اگر (context) {
        _this->gl_ڈیٹا->glXMakeCurrent(display, None, تہی);
        _this->gl_ڈیٹا->glXDestroyContext(display, context);
        اگر (پچھلا_ctx && پچھلا_drawable) {
            _this->gl_ڈیٹا->glXMakeCurrent(display, پچھلا_drawable, پچھلا_ctx);
        }
    }

    اگر (w) {
        X11_XDestroy_کھڑکی(display, w);
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
ساکن صحیح X11_GL_Get_اوصاف(SDL_VideoDevice *_this, Display *display, صحیح screen, صحیح *attribs, صحیح سائز, Bool for_FBConfig, صحیح **_pvistypeattr, bool transparent)
{
    صحیح i = 0;
    ثابت صحیح MAX_اوصاف = 64;
    صحیح *pvistypeattr = تہی;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(سائز >= MAX_اوصاف);

    // Setup our GLX attributes according to the gl_config.
    اگر (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        اگر (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_ثنائی_ہندسہ_ARB;
        } ورنہ {
            attribs[i++] = GLX_RGBA_ثنائی_ہندسہ;
        }
    } ورنہ {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_سائز;
    attribs[i++] = _this->gl_config.red_سائز;
    attribs[i++] = GLX_GREEN_سائز;
    attribs[i++] = _this->gl_config.green_سائز;
    attribs[i++] = GLX_BLUE_سائز;
    attribs[i++] = _this->gl_config.blue_سائز;

    اگر (_this->gl_config.alpha_سائز) {
        attribs[i++] = GLX_ALPHA_سائز;
        attribs[i++] = _this->gl_config.alpha_سائز;
    }

    اگر (_this->gl_config.double_بفر) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        اگر (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_گہرائی_سائز;
    attribs[i++] = _this->gl_config.گہرائی_سائز;

    اگر (_this->gl_config.stencil_سائز) {
        attribs[i++] = GLX_STENCIL_سائز;
        attribs[i++] = _this->gl_config.stencil_سائز;
    }

    اگر (_this->gl_config.accum_red_سائز) {
        attribs[i++] = GLX_ACCUM_RED_سائز;
        attribs[i++] = _this->gl_config.accum_red_سائز;
    }

    اگر (_this->gl_config.accum_green_سائز) {
        attribs[i++] = GLX_ACCUM_GREEN_سائز;
        attribs[i++] = _this->gl_config.accum_green_سائز;
    }

    اگر (_this->gl_config.accum_blue_سائز) {
        attribs[i++] = GLX_ACCUM_BLUE_سائز;
        attribs[i++] = _this->gl_config.accum_blue_سائز;
    }

    اگر (_this->gl_config.accum_alpha_سائز) {
        attribs[i++] = GLX_ACCUM_ALPHA_سائز;
        attribs[i++] = _this->gl_config.accum_alpha_سائز;
    }

    اگر (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        اگر (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    اگر (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    اگر (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    اگر (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    اگر (_this->gl_ڈیٹا->HAS_GLX_ARB_framebuffer_sRGB) {
        ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        اگر (srgbhint && *srgbhint) {
            اگر (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ورنہ {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } ورنہ اگر (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    اگر (_this->gl_config.accelerated >= 0 &&
        _this->gl_ڈیٹا->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    اگر (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        اگر (X11_Use_براہ_راست_Color_Visuals() && _this->gl_ڈیٹا->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_براہ_راست_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_اوصاف);

    اگر (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    واپس i;
}

//get the first transparent Visual
ساکن XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, صحیح screen)
{
    XVisualInfo *visualinfo = تہی;
    XVisualInfo vi_اندر;
    صحیح برآمد_گنتی = 0;

    vi_اندر.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب, &vi_اندر, &برآمد_گنتی);
    اگر (visualinfo != تہی) {
        صحیح i = 0;
        برائے (i = 0; i < برآمد_گنتی; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            اگر (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_اندر.screen = screen;
                vi_اندر.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &vi_اندر, &برآمد_گنتی);
                توڑو;
            }
        }
    }
    واپس visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, صحیح screen, bool transparent)
{
    // 64 seems nice.
    صحیح attribs[64];
    XVisualInfo *vinfo = تہی;
    صحیح *pvistypeattr = تہی;

    اگر (!_this->gl_ڈیٹا) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        واپس تہی;
    }

    اگر (_this->gl_ڈیٹا->glXChooseFBConfig &&
        _this->gl_ڈیٹا->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = تہی;
        صحیح fbcount = 0;

        X11_GL_Get_اوصاف(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_ڈیٹا->glXChooseFBConfig(display, screen, attribs, &fbcount);
        اگر (!framebuffer_config && (pvistypeattr != تہی)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_ڈیٹا->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        اگر (transparent) {
            // Return the first transparent Visual
            صحیح i;
            برائے (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_ڈیٹا->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                اگر (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = تہی;
                    توڑو;
                }
                X11_XFree(vinfo);
                vinfo = تہی;
            }
        }

        اگر (framebuffer_config) {
            vinfo = _this->gl_ڈیٹا->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    اگر (!vinfo) {
        X11_GL_Get_اوصاف(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_ڈیٹا->glXChooseVisual(display, screen, attribs);

        اگر (!vinfo && (pvistypeattr != تہی)) {
            *pvistypeattr = None;
            vinfo = _this->gl_ڈیٹا->glXChooseVisual(display, screen, attribs);
        }
    }

    اگر (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        اگر (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            اگر (visualinfo != تہی) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    اگر (!vinfo) {
        SDL_سیٹ_Error("Couldn't find matching GLX visual");
    }
    واپس vinfo;
}

ساکن صحیح (*handler)(Display *, XErrorEvent *) = تہی;
ساکن ثابت حرف *errorHandlerOperation = تہی;
ساکن صحیح error_بنیاد = 0;
ساکن صحیح error_رمز_2 = 0;
ساکن صحیح X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    حرف *x11_error = تہی;
    حرف x11_error_locale[256];

    error_رمز_2 = e->error_رمز;
    اگر (X11_XGet_Error_متن(d, error_رمز_2, x11_error_locale, حجم(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    اگر (x11_error) {
        SDL_سیٹ_Error("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } ورنہ {
        SDL_سیٹ_Error("Could not %s: %i (Base %i)", errorHandlerOperation, error_رمز_2, error_بنیاد);
    }

    واپس 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_ڈیٹا != تہی);
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        واپس true;
    }

    SDL_assert(_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES);
    واپس (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_نسخہ == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_نسخہ > _this->gl_ڈیٹا->es_profile_max_supported_نسخہ.major || (_this->gl_config.major_نسخہ == _this->gl_ڈیٹا->es_profile_max_supported_نسخہ.major && _this->gl_config.minor_نسخہ > _this->gl_ڈیٹا->es_profile_max_supported_نسخہ.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    صحیح screen = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی)->screen;
    XWindow_اوصاف xattr;
    XVisualInfo v, *vinfo;
    صحیح n;
    SDL_GLContext context = تہی;
    GLXContext share_context;
    ثابت صحیح transparent = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) ? true : false;

    اگر (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } ورنہ {
        share_context = تہی;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    error_بنیاد = _this->gl_ڈیٹا->error_بنیاد;
    error_رمز_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGet_کھڑکی_اوصاف(display, ڈیٹا->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &v, &n);
    اگر (vinfo) {
        اگر (_this->gl_config.major_نسخہ < 3 &&
            _this->gl_config.profile_نقاب == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_ڈیٹا->glXCreateContext(display, vinfo, share_context, True);
        } ورنہ {
            // max 14 attributes plus terminator
            صحیح attribs[15] = {
                GLX_CONTEXT_MAJOR_نسخہ_ARB,
                _this->gl_config.major_نسخہ,
                GLX_CONTEXT_MINOR_نسخہ_ARB,
                _this->gl_config.minor_نسخہ,
                0
            };
            صحیح iattr = 4;

            // SDL profile bits match GLX profile bits
            اگر (_this->gl_config.profile_نقاب != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_نقاب_ARB;
                attribs[iattr++] = _this->gl_config.profile_نقاب;
            }

            // SDL flags match GLX flags
            اگر (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            اگر ((_this->gl_ڈیٹا->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            اگر ((_this->gl_ڈیٹا->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            اگر ((_this->gl_ڈیٹا->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            اگر (!_this->gl_ڈیٹا->glXCreateContextAttribsARB) {
                SDL_سیٹ_Error("OpenGL 3.0 and later are not supported by this system");
            } ورنہ {
                صحیح glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = تہی;
                صحیح fbcount = 0;
                صحیح *pvistypeattr = تہی;

                X11_GL_Get_اوصاف(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                اگر (_this->gl_ڈیٹا->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_ڈیٹا->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    اگر (!framebuffer_config && (pvistypeattr != تہی)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_ڈیٹا->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    اگر (transparent && (framebuffer_config != تہی)) {
                        صحیح i;
                        برائے (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_عارضی = _this->gl_ڈیٹا->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            اگر ( vinfo_عارضی != تہی) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_عارضی);
                                اگر (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_ڈیٹا->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = تہی;
                                    X11_XFree(vinfo_عارضی);
                                    توڑو;
                                }
                                X11_XFree(vinfo_عارضی);
                            }
                        }
                    }
                    اگر (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_ڈیٹا->glXCreateContextAttribsARB(display,
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

    اگر (!context) {
        اگر (error_رمز_2 == Success) {
            SDL_سیٹ_Error("Could not create GL context");
        }
        واپس تہی;
    }

    اگر (!X11_GL_MakeCurrent(_this, کھڑکی, context)) {
        X11_GL_DestroyContext(_this, context);
        واپس تہی;
    }

    واپس context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    Display *display = _this->اندرونی_2->display;
    کھڑکی_2 drawable =
        (context ? کھڑکی->اندرونی_2->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    صحیح rc;

    اگر (!_this->gl_ڈیٹا) {
        واپس SDL_سیٹ_Error("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    error_بنیاد = _this->gl_ڈیٹا->error_بنیاد;
    error_رمز_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_ڈیٹا->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    اگر (error_رمز_2 != Success) { // uhoh, an X error was thrown!
        واپس false;              // the error handler called SDL_SetError() already.
    } ورنہ اگر (!rc) {           // glXMakeCurrent() failed without throwing an X error
        واپس SDL_سیٹ_Error("Unable to make GL context current");
    }

    واپس true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

ساکن صحیح swapinterval = 0;
bool X11_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    bool نتیجہ = false;

    اگر ((interval < 0) && (!_this->gl_ڈیٹا->HAS_GLX_EXT_تبادلہ_control_tear)) {
        واپس SDL_سیٹ_Error("Negative swap interval unsupported in this GL");
    } ورنہ اگر (_this->gl_ڈیٹا->glXSwapIntervalEXT) {
        Display *display = _this->اندرونی_2->display;
        ثابت SDL_کھڑکی_ڈیٹا *windowdata = SDL_GL_Get_Current_کھڑکی()->اندرونی_2;

        کھڑکی_2 drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        صحیح currentInterval = 0;
        X11_GL_Get_تبادلہ_Interval(_this, &currentInterval);
        _this->gl_ڈیٹا->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_ڈیٹا->glXSwapIntervalEXT(display, drawable, interval);
        نتیجہ = true;
        swapinterval = interval;
    } ورنہ اگر (_this->gl_ڈیٹا->glXSwapIntervalMESA) {
        ثابت صحیح rc = _this->gl_ڈیٹا->glXSwapIntervalMESA(interval);
        اگر (rc == 0) {
            swapinterval = interval;
            نتیجہ = true;
        } ورنہ {
            نتیجہ = SDL_سیٹ_Error("glXSwapIntervalMESA failed");
        }
    } ورنہ اگر (_this->gl_ڈیٹا->glXSwapIntervalSGI) {
        ثابت صحیح rc = _this->gl_ڈیٹا->glXSwapIntervalSGI(interval);
        اگر (rc == 0) {
            swapinterval = interval;
            نتیجہ = true;
        } ورنہ {
            نتیجہ = SDL_سیٹ_Error("glXSwapIntervalSGI failed");
        }
    } ورنہ {
        واپس SDL_Unsupported();
    }
    واپس نتیجہ;
}

ساکن SDL_GLSwapIntervalTearBehavior Check_تبادلہ_Interval_Tear_Behavior(SDL_VideoDevice *_this, کھڑکی_2 drawable, غیرعلامتی صحیح current_val, غیرعلامتی صحیح current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    اگر (_this->gl_ڈیٹا->تبادلہ_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        اگر (!_this->gl_ڈیٹا->HAS_GLX_EXT_تبادلہ_control_tear) {
            _this->gl_ڈیٹا->تبادلہ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } ورنہ {
            Display *display = _this->اندرونی_2->display;
            غیرعلامتی صحیح allow_late_تبادلہ_tearing = 22;
            صحیح original_val = (صحیح) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_ڈیٹا->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_ڈیٹا->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_ڈیٹا->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_تبادلہ_tearing);

            اگر (allow_late_تبادلہ_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_ڈیٹا->تبادلہ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                اگر (current_allow_late) {
                    original_val = -original_val;
                }
            } ورنہ اگر (allow_late_تبادلہ_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_ڈیٹا->تبادلہ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } ورنہ {  // unexpected outcome!
                _this->gl_ڈیٹا->تبادلہ_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_ڈیٹا->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    واپس _this->gl_ڈیٹا->تبادلہ_interval_tear_behavior;
}


bool X11_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    اگر (_this->gl_ڈیٹا->glXSwapIntervalEXT) {
        Display *display = _this->اندرونی_2->display;
        ثابت SDL_کھڑکی_ڈیٹا *windowdata = SDL_GL_Get_Current_کھڑکی()->اندرونی_2;
        کھڑکی_2 drawable = windowdata->xwindow;
        غیرعلامتی صحیح allow_late_تبادلہ_tearing = 0;
        غیرعلامتی صحیح val = 0;

        اگر (_this->gl_ڈیٹا->HAS_GLX_EXT_تبادلہ_control_tear) {
            allow_late_تبادلہ_tearing = 22;  // set this to nonsense.
            _this->gl_ڈیٹا->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_تبادلہ_tearing);
        }

        _this->gl_ڈیٹا->glXQueryDrawable(display, drawable,
                                         GLX_تبادلہ_INTERVAL_EXT, &val);

        *interval = (صحیح)val;

        انتخاب (Check_تبادلہ_Interval_Tear_Behavior(_this, drawable, val, allow_late_تبادلہ_tearing)) {
            حالت SDL_SWAPINTERVALTEAR_MESA:
                *interval = (صحیح)val;  // unsigned int cast to signed that generates negative value if necessary.
                توڑو;

            حالت SDL_SWAPINTERVALTEAR_NVIDIA:
            طےشدہ:
                اگر ((allow_late_تبادلہ_tearing) && (val > 0)) {
                    *interval = -((صحیح)val);
                }
                توڑو;
        }

        واپس true;
    } ورنہ اگر (_this->gl_ڈیٹا->gl_XGet_تبادلہ_Interval_MESA) {
        صحیح val = _this->gl_ڈیٹا->gl_XGet_تبادلہ_Interval_MESA();
        اگر (val == GLX_BAD_CONTEXT) {
            واپس SDL_سیٹ_Error("GLX_BAD_CONTEXT");
        }
        *interval = val;
        واپس true;
    } ورنہ {
        *interval = swapinterval;
        واپس true;
    }
}

bool X11_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;

    _this->gl_ڈیٹا->glXSwapBuffers(display, ڈیٹا->xwindow);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ڈیٹا->کھڑکی);
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */

    واپس true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->اندرونی_2->display;
    GLXContext glx_context = (GLXContext)context;

    اگر (!_this->gl_ڈیٹا) {
        واپس true;
    }
    _this->gl_ڈیٹا->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    واپس true;
}

#اگر_ختم // SDL_VIDEO_OPENGL_GLX

#اگر_ختم // SDL_VIDEO_DRIVER_X11
