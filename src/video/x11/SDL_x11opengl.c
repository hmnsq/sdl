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
#ضمن "SDL_internal.h"

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xsync.h"
#ضمن "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
#ضمن "SDL_x11opengles.h"

#إذا defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#تعریف_کرو DEFAULT_OPENGL "libGL.so"
#وإلاإذا defined(SDL_PLATFORM_MACOS)
#تعریف_کرو DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#وإلا
#تعریف_کرو DEFAULT_OPENGL "libGL.so.1"
#جے_انت

#جے_بنا_تعریف GLX_NONE_EXT
#تعریف_کرو GLX_NONE_EXT 0x8000
#جے_انت

#جے_بنا_تعریف GLX_ARB_multisample
#تعریف_کرو GLX_ARB_multisample
#تعریف_کرو GLX_SAMPLE_BUFFERS_ARB 100000
#تعریف_کرو GLX_SAMPLES_ARB        100001
#جے_انت

#جے_بنا_تعریف GLX_EXT_visual_rating
#تعریف_کرو GLX_EXT_visual_rating
#تعریف_کرو GLX_VISUAL_CAVEAT_EXT         0x20
#تعریف_کرو GLX_NONE_EXT                  0x8000
#تعریف_کرو GLX_SLOW_VISUAL_EXT           0x8001
#تعریف_کرو GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#جے_انت

#جے_بنا_تعریف GLX_EXT_visual_info
#تعریف_کرو GLX_EXT_visual_info
#تعریف_کرو GLX_X_VISUAL_TYPE_EXT 0x22
#تعریف_کرو GLX_سدھا_COLOR_EXT  0x8003
#جے_انت

#جے_بنا_تعریف GLX_ARB_create_context
#تعریف_کرو GLX_ARB_create_context
#تعریف_کرو GLX_CONTEXT_MAJOR_نسخہ_ARB          0x2091
#تعریف_کرو GLX_CONTEXT_MINOR_نسخہ_ARB          0x2092
#تعریف_کرو GLX_CONTEXT_FLAGS_ARB                  0x2094
#تعریف_کرو GLX_CONTEXT_DEBUG_ثنائی_ہندسہ_ARB              0x0001
#تعریف_کرو GLX_CONTEXT_FORWARD_COMPATIBLE_ثنائی_ہندسہ_ARB 0x0002

// Typedef for the GL 3.0 context creation function
تعريفنوع GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool سدھا,
                                                        ثابت صحيح
                                                            *attrib_list);
#جے_انت

#جے_بنا_تعریف GLX_ARB_create_context_profile
#تعریف_کرو GLX_ARB_create_context_profile
#تعریف_کرو GLX_CONTEXT_PROFILE_نقاب_ARB              0x9126
#تعریف_کرو GLX_CONTEXT_CORE_PROFILE_ثنائی_ہندسہ_ARB          0x00000001
#تعریف_کرو GLX_CONTEXT_COMPATIBILITY_PROFILE_ثنائی_ہندسہ_ARB 0x00000002
#جے_انت

#جے_بنا_تعریف GLX_ARB_create_context_robustness
#تعریف_کرو GLX_ARB_create_context_robustness
#تعریف_کرو GLX_CONTEXT_ROBUST_ACCESS_ثنائی_ہندسہ_ARB           0x00000004
#تعریف_کرو GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#تعریف_کرو GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#تعریف_کرو GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#جے_انت

#جے_بنا_تعریف GLX_EXT_create_context_es2_profile
#تعریف_کرو GLX_EXT_create_context_es2_profile
#جے_بنا_تعریف GLX_CONTEXT_ES2_PROFILE_ثنائی_ہندسہ_EXT
#تعریف_کرو GLX_CONTEXT_ES2_PROFILE_ثنائی_ہندسہ_EXT 0x00000002
#جے_انت
#جے_انت

#جے_بنا_تعریف GLX_ARB_framebuffer_sRGB
#تعریف_کرو GLX_ARB_framebuffer_sRGB
#جے_بنا_تعریف GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#تعریف_کرو GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#جے_انت
#جے_انت

#جے_بنا_تعریف GLX_ARB_fbconfig_float
#تعریف_کرو GLX_ARB_fbconfig_float
#جے_بنا_تعریف GLX_RGBA_FLOAT_TYPE_ARB
#تعریف_کرو GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#جے_انت
#جے_بنا_تعریف GLX_RGBA_FLOAT_ثنائی_ہندسہ_ARB
#تعریف_کرو GLX_RGBA_FLOAT_ثنائی_ہندسہ_ARB 0x00000004
#جے_انت
#جے_انت

#جے_بنا_تعریف GLX_ARB_create_context_no_error
#تعریف_کرو GLX_ARB_create_context_no_error
#جے_بنا_تعریف GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#تعریف_کرو GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#جے_انت
#جے_انت

#جے_بنا_تعریف GLX_EXT_وٹاندرا_control
#تعریف_کرو GLX_وٹاندرا_INTERVAL_EXT     0x20F1
#تعریف_کرو GLX_MAX_وٹاندرا_INTERVAL_EXT 0x20F2
#جے_انت

#جے_بنا_تعریف GLX_EXT_وٹاندرا_control_tear
#تعریف_کرو GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#جے_انت

#جے_بنا_تعریف GLX_ARB_context_flush_control
#تعریف_کرو GLX_ARB_context_flush_control
#تعریف_کرو GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#تعریف_کرو GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#تعریف_کرو GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#جے_انت

#تعریف_کرو OPENGL_REQUIRES_DLOPEN
#إذا defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#ضمن <dlfcn.h>
#تعریف_کرو GL_لدو_Object(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#تعریف_کرو GL_لدو_Function  dlsym
#تعریف_کرو GL_UnloadObject  dlclose
#وإلا
#تعریف_کرو GL_لدو_Object   SDL_لدو_Object
#تعریف_کرو GL_لدو_Function SDL_لدو_Function
#تعریف_کرو GL_UnloadObject SDL_UnloadObject
#جے_انت

ساكن فراغ X11_GL_InitExtensions(SDL_VideoDevice *_this);

ساكن bool X11_GL_لدو_Library_EGLFallback(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    X11_GL_UnloadLibrary(_this);
    _this->GL_لدو_Library = X11_GLES_لدو_Library;
    _this->GL_Get_Proc_پتہ = X11_GLES_Get_Proc_پتہ;
    _this->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
    _this->GL_CreateContext = X11_GLES_CreateContext;
    _this->GL_MakeCurrent = X11_GLES_MakeCurrent;
    _this->GL_سیٹ_وٹاندرا_Interval = X11_GLES_سیٹ_وٹاندرا_Interval;
    _this->GL_Get_وٹاندرا_Interval = X11_GLES_Get_وٹاندرا_Interval;
    _this->GL_وٹاندرا_کھڑکی = X11_GLES_وٹاندرا_کھڑکی;
    _this->GL_DestroyContext = X11_GLES_DestroyContext;
    _this->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
    أرجع X11_GLES_لدو_Library(_this, رستہ);
#وإلا
    أرجع SDL_سیٹ_Error("SDL not configured with EGL support");
#جے_انت
}

bool X11_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    Display *display;
    SDL_SharedObject *handle;

    إذا (_this->gl_انکڑے) {
        أرجع SDL_سیٹ_Error("OpenGL context already created");
    }

    إذا ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        أرجع X11_GL_لدو_Library_EGLFallback(_this, رستہ);
    }

    // Load the OpenGL library
    إذا (رستہ == عدم) {
        رستہ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    إذا (رستہ == عدم) {
        رستہ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_لدو_Object(رستہ);
    إذا (!_this->gl_config.dll_handle) {
#إذا defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_سیٹ_Error("Failed loading %s: %s", رستہ, dlerror());
#جے_انت
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_رستہ, رستہ,
                SDL_arraysize(_this->gl_config.driver_رستہ));

    // Allocate OpenGL memory
    _this->gl_انکڑے =
        (بنية SDL_GLDriver_انکڑے *)SDL_calloc(1,
                                              حجم(بنية
                                                     SDL_GLDriver_انکڑے));
    إذا (!_this->gl_انکڑے) {
        أرجع false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_انکڑے->glXQueryExtension =
        (Bool(*)(Display *, صحيح *, صحيح *))
            GL_لدو_Function(handle, "glXQueryExtension");
    _this->gl_انکڑے->gl_XGet_Proc_پتہ =
        (__GLXextFuncPtr (*)(ثابت GLubyte *))
            GL_لدو_Function(handle, "glXGetProcAddressARB");
    _this->gl_انکڑے->glXChooseVisual =
        (XVisualInfo * (*)(Display *, صحيح, صحيح *))
            X11_GL_Get_Proc_پتہ(_this, "glXChooseVisual");
    _this->gl_انکڑے->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, صحيح))
            X11_GL_Get_Proc_پتہ(_this, "glXCreateContext");
    _this->gl_انکڑے->glXDestroyContext =
        (فراغ (*)(Display *, GLXContext))
            X11_GL_Get_Proc_پتہ(_this, "glXDestroyContext");
    _this->gl_انکڑے->glXMakeCurrent =
        (صحيح (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_Get_Proc_پتہ(_this, "glXMakeCurrent");
    _this->gl_انکڑے->glXSwapBuffers =
        (فراغ (*)(Display *, GLXDrawable))
            X11_GL_Get_Proc_پتہ(_this, "glXSwapBuffers");
    _this->gl_انکڑے->glXQueryDrawable =
        (فراغ (*)(Display *, GLXDrawable, صحيح, بنانشانی صحيح *))
            X11_GL_Get_Proc_پتہ(_this, "glXQueryDrawable");

    إذا (!_this->gl_انکڑے->glXQueryExtension ||
        !_this->gl_انکڑے->glXChooseVisual ||
        !_this->gl_انکڑے->glXCreateContext ||
        !_this->gl_انکڑے->glXDestroyContext ||
        !_this->gl_انکڑے->glXMakeCurrent ||
        !_this->gl_انکڑے->glXSwapBuffers) {
        أرجع SDL_سیٹ_Error("Could not retrieve OpenGL functions");
    }

    display = _this->اندرونی->display;
    إذا (!_this->gl_انکڑے->glXQueryExtension(display, &_this->gl_انکڑے->error_ادھار, &_this->gl_انکڑے->event_ادھار)) {
        أرجع SDL_سیٹ_Error("GLX is not supported");
    }

    _this->gl_انکڑے->وٹاندرا_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    إذا (((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        أرجع X11_GL_لدو_Library_EGLFallback(_this, عدم);
    }

    أرجع true;
}

SDL_Function_اشارہ_گر X11_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    إذا (_this->gl_انکڑے->gl_XGet_Proc_پتہ) {
        أرجع _this->gl_انکڑے->gl_XGet_Proc_پتہ((ثابت GLubyte *)proc);
    }
    أرجع GL_لدو_Function(_this->gl_config.dll_handle, proc);
}

فراغ X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#إذا 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = عدم;
#جے_انت

    // Free OpenGL memory
    SDL_free(_this->gl_انکڑے);
    _this->gl_انکڑے = عدم;
}

ساكن bool HasExtension(ثابت حرف *extension, ثابت حرف *extensions)
{
    ثابت حرف *شروع;
    ثابت حرف *where, *terminator;

    إذا (!extensions) {
        أرجع false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    إذا (where || *extension == '\0') {
        أرجع false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    شروع = extensions;

    لكل (;;) {
        where = SDL_strstr(شروع, extension);
        إذا (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        إذا (where == شروع || *(where - 1) == ' ') {
            إذا (*terminator == ' ' || *terminator == '\0') {
                أرجع true;
            }
        }

        شروع = terminator;
    }
    أرجع false;
}

ساكن فراغ X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->اندرونی->display;
    ثابت صحيح screen = DefaultScreen(display);
    XVisualInfo *vinfo = عدم;
    کھڑکی_2 w = 0;
    GLXContext prev_ctx = عدم;
    GLXDrawable prev_drawable = 0;
    GLXContext context = عدم;
    ثابت حرف *(*glXQueryExtensionsStringFunc)(Display *, صحيح);
    ثابت حرف *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    إذا (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(فراغ) =
            (GLXContext(*)(فراغ))
                X11_GL_Get_Proc_پتہ(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(فراغ) =
            (GLXDrawable(*)(فراغ))
                X11_GL_Get_Proc_پتہ(_this, "glXGetCurrentDrawable");

        إذا (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSet_کھڑکی_گن xattr;
            prev_ctx = glXGetCurrentContextFunc();
            prev_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, جڑ_کھڑکی(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreate_کھڑکی(display, جڑ_کھڑکی(display, screen), 0, 0,
                                  32, 32, 0, vinfo->ڈونگھائی_2, داخلہ_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_انکڑے->glXCreateContext(display, vinfo,
                                                       عدم, True);
            إذا (context) {
                _this->gl_انکڑے->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (ثابت حرف *(*)(Display *, صحيح))X11_GL_Get_Proc_پتہ(_this,
                                                               "glXQueryExtensionsString");
    إذا (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } وإلا {
        extensions = عدم;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_انکڑے->HAS_GLX_EXT_وٹاندرا_control_tear = false;
    إذا (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_انکڑے->glXSwapIntervalEXT =
            (فراغ (*)(Display *, GLXDrawable, صحيح))
                X11_GL_Get_Proc_پتہ(_this, "glXSwapIntervalEXT");
        إذا (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_انکڑے->HAS_GLX_EXT_وٹاندرا_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    إذا (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_انکڑے->glXSwapIntervalMESA =
            (صحيح (*)(صحيح))X11_GL_Get_Proc_پتہ(_this, "glXSwapIntervalMESA");
        _this->gl_انکڑے->gl_XGet_وٹاندرا_Interval_MESA =
            (صحيح (*)(فراغ))X11_GL_Get_Proc_پتہ(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    إذا (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_انکڑے->glXSwapIntervalSGI =
            (صحيح (*)(صحيح))X11_GL_Get_Proc_پتہ(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    إذا (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_انکڑے->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, ثابت صحيح *))
                X11_GL_Get_Proc_پتہ(_this, "glXCreateContextAttribsARB");
        _this->gl_انکڑے->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, صحيح, ثابت صحيح *, صحيح *))
                X11_GL_Get_Proc_پتہ(_this, "glXChooseFBConfig");
        _this->gl_انکڑے->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_Get_Proc_پتہ(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    إذا (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_انکڑے->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    إذا (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_انکڑے->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    إذا (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        إذا (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_انکڑے->es_profile_max_supported_نسخہ.major,
                &_this->gl_انکڑے->es_profile_max_supported_نسخہ.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    إذا (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_انکڑے->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    إذا (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_انکڑے->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    إذا (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_انکڑے->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    إذا (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_انکڑے->HAS_GLX_ARB_framebuffer_sRGB = true;
    } وإلا إذا (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_انکڑے->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    إذا (context) {
        _this->gl_انکڑے->glXMakeCurrent(display, None, عدم);
        _this->gl_انکڑے->glXDestroyContext(display, context);
        إذا (prev_ctx && prev_drawable) {
            _this->gl_انکڑے->glXMakeCurrent(display, prev_drawable, prev_ctx);
        }
    }

    إذا (w) {
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
ساكن صحيح X11_GL_Get_گن(SDL_VideoDevice *_this, Display *display, صحيح screen, صحيح *attribs, صحيح ناپ, Bool for_FBConfig, صحيح **_pvistypeattr, bool transparent)
{
    صحيح i = 0;
    ثابت صحيح MAX_گن = 64;
    صحيح *pvistypeattr = عدم;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(ناپ >= MAX_گن);

    // Setup our GLX attributes according to the gl_config.
    إذا (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        إذا (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_ثنائی_ہندسہ_ARB;
        } وإلا {
            attribs[i++] = GLX_RGBA_ثنائی_ہندسہ;
        }
    } وإلا {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_ناپ;
    attribs[i++] = _this->gl_config.red_ناپ;
    attribs[i++] = GLX_GREEN_ناپ;
    attribs[i++] = _this->gl_config.green_ناپ;
    attribs[i++] = GLX_BLUE_ناپ;
    attribs[i++] = _this->gl_config.blue_ناپ;

    إذا (_this->gl_config.alpha_ناپ) {
        attribs[i++] = GLX_ALPHA_ناپ;
        attribs[i++] = _this->gl_config.alpha_ناپ;
    }

    إذا (_this->gl_config.double_بفر) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        إذا (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_ڈونگھائی_ناپ;
    attribs[i++] = _this->gl_config.ڈونگھائی_ناپ;

    إذا (_this->gl_config.stencil_ناپ) {
        attribs[i++] = GLX_STENCIL_ناپ;
        attribs[i++] = _this->gl_config.stencil_ناپ;
    }

    إذا (_this->gl_config.accum_red_ناپ) {
        attribs[i++] = GLX_ACCUM_RED_ناپ;
        attribs[i++] = _this->gl_config.accum_red_ناپ;
    }

    إذا (_this->gl_config.accum_green_ناپ) {
        attribs[i++] = GLX_ACCUM_GREEN_ناپ;
        attribs[i++] = _this->gl_config.accum_green_ناپ;
    }

    إذا (_this->gl_config.accum_blue_ناپ) {
        attribs[i++] = GLX_ACCUM_BLUE_ناپ;
        attribs[i++] = _this->gl_config.accum_blue_ناپ;
    }

    إذا (_this->gl_config.accum_alpha_ناپ) {
        attribs[i++] = GLX_ACCUM_ALPHA_ناپ;
        attribs[i++] = _this->gl_config.accum_alpha_ناپ;
    }

    إذا (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        إذا (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    إذا (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    إذا (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    إذا (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    إذا (_this->gl_انکڑے->HAS_GLX_ARB_framebuffer_sRGB) {
        ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        إذا (srgbhint && *srgbhint) {
            إذا (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } وإلا {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } وإلا إذا (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    إذا (_this->gl_config.accelerated >= 0 &&
        _this->gl_انکڑے->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    إذا (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        إذا (X11_Use_سدھا_Color_Visuals() && _this->gl_انکڑے->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_سدھا_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_گن);

    إذا (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    أرجع i;
}

//get the first transparent Visual
ساكن XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, صحيح screen)
{
    XVisualInfo *visualinfo = عدم;
    XVisualInfo vi_وچ;
    صحيح باہرلا_گنتی = 0;

    vi_وچ.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب, &vi_وچ, &باہرلا_گنتی);
    إذا (visualinfo != عدم) {
        صحيح i = 0;
        لكل (i = 0; i < باہرلا_گنتی; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            إذا (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_وچ.screen = screen;
                vi_وچ.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &vi_وچ, &باہرلا_گنتی);
                اكسر;
            }
        }
    }
    أرجع visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, صحيح screen, bool transparent)
{
    // 64 seems nice.
    صحيح attribs[64];
    XVisualInfo *vinfo = عدم;
    صحيح *pvistypeattr = عدم;

    إذا (!_this->gl_انکڑے) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        أرجع عدم;
    }

    إذا (_this->gl_انکڑے->glXChooseFBConfig &&
        _this->gl_انکڑے->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = عدم;
        صحيح fbcount = 0;

        X11_GL_Get_گن(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_انکڑے->glXChooseFBConfig(display, screen, attribs, &fbcount);
        إذا (!framebuffer_config && (pvistypeattr != عدم)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_انکڑے->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        إذا (transparent) {
            // Return the first transparent Visual
            صحيح i;
            لكل (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_انکڑے->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                إذا (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = عدم;
                    اكسر;
                }
                X11_XFree(vinfo);
                vinfo = عدم;
            }
        }

        إذا (framebuffer_config) {
            vinfo = _this->gl_انکڑے->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    إذا (!vinfo) {
        X11_GL_Get_گن(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_انکڑے->glXChooseVisual(display, screen, attribs);

        إذا (!vinfo && (pvistypeattr != عدم)) {
            *pvistypeattr = None;
            vinfo = _this->gl_انکڑے->glXChooseVisual(display, screen, attribs);
        }
    }

    إذا (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        إذا (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            إذا (visualinfo != عدم) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    إذا (!vinfo) {
        SDL_سیٹ_Error("Couldn't find matching GLX visual");
    }
    أرجع vinfo;
}

ساكن صحيح (*handler)(Display *, XErrorEvent *) = عدم;
ساكن ثابت حرف *errorHandlerOperation = عدم;
ساكن صحيح error_ادھار = 0;
ساكن صحيح error_کوڈ_2 = 0;
ساكن صحيح X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    حرف *x11_error = عدم;
    حرف x11_error_locale[256];

    error_کوڈ_2 = e->error_کوڈ;
    إذا (X11_XGet_Error_متن(d, error_کوڈ_2, x11_error_locale, حجم(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    إذا (x11_error) {
        SDL_سیٹ_Error("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } وإلا {
        SDL_سیٹ_Error("Could not %s: %i (Base %i)", errorHandlerOperation, error_کوڈ_2, error_ادھار);
    }

    أرجع 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_انکڑے != عدم);
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        أرجع true;
    }

    SDL_assert(_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES);
    أرجع (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_نسخہ == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_نسخہ > _this->gl_انکڑے->es_profile_max_supported_نسخہ.major || (_this->gl_config.major_نسخہ == _this->gl_انکڑے->es_profile_max_supported_نسخہ.major && _this->gl_config.minor_نسخہ > _this->gl_انکڑے->es_profile_max_supported_نسخہ.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    صحيح screen = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی)->screen;
    XWindow_گن xattr;
    XVisualInfo v, *vinfo;
    صحيح n;
    SDL_GLContext context = عدم;
    GLXContext share_context;
    ثابت صحيح transparent = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) ? true : false;

    إذا (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } وإلا {
        share_context = عدم;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    error_ادھار = _this->gl_انکڑے->error_ادھار;
    error_کوڈ_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGet_کھڑکی_گن(display, انکڑے->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &v, &n);
    إذا (vinfo) {
        إذا (_this->gl_config.major_نسخہ < 3 &&
            _this->gl_config.profile_نقاب == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_انکڑے->glXCreateContext(display, vinfo, share_context, True);
        } وإلا {
            // max 14 attributes plus terminator
            صحيح attribs[15] = {
                GLX_CONTEXT_MAJOR_نسخہ_ARB,
                _this->gl_config.major_نسخہ,
                GLX_CONTEXT_MINOR_نسخہ_ARB,
                _this->gl_config.minor_نسخہ,
                0
            };
            صحيح iattr = 4;

            // SDL profile bits match GLX profile bits
            إذا (_this->gl_config.profile_نقاب != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_نقاب_ARB;
                attribs[iattr++] = _this->gl_config.profile_نقاب;
            }

            // SDL flags match GLX flags
            إذا (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            إذا ((_this->gl_انکڑے->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            إذا ((_this->gl_انکڑے->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            إذا ((_this->gl_انکڑے->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            إذا (!_this->gl_انکڑے->glXCreateContextAttribsARB) {
                SDL_سیٹ_Error("OpenGL 3.0 and later are not supported by this system");
            } وإلا {
                صحيح glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = عدم;
                صحيح fbcount = 0;
                صحيح *pvistypeattr = عدم;

                X11_GL_Get_گن(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                إذا (_this->gl_انکڑے->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_انکڑے->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    إذا (!framebuffer_config && (pvistypeattr != عدم)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_انکڑے->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    إذا (transparent && (framebuffer_config != عدم)) {
                        صحيح i;
                        لكل (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_عارضی = _this->gl_انکڑے->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            إذا ( vinfo_عارضی != عدم) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_عارضی);
                                إذا (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_انکڑے->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = عدم;
                                    X11_XFree(vinfo_عارضی);
                                    اكسر;
                                }
                                X11_XFree(vinfo_عارضی);
                            }
                        }
                    }
                    إذا (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_انکڑے->glXCreateContextAttribsARB(display,
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

    إذا (!context) {
        إذا (error_کوڈ_2 == Success) {
            SDL_سیٹ_Error("Could not create GL context");
        }
        أرجع عدم;
    }

    إذا (!X11_GL_MakeCurrent(_this, کھڑکی, context)) {
        X11_GL_DestroyContext(_this, context);
        أرجع عدم;
    }

    أرجع context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    Display *display = _this->اندرونی->display;
    کھڑکی_2 drawable =
        (context ? کھڑکی->اندرونی->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    صحيح rc;

    إذا (!_this->gl_انکڑے) {
        أرجع SDL_سیٹ_Error("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    error_ادھار = _this->gl_انکڑے->error_ادھار;
    error_کوڈ_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_انکڑے->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    إذا (error_کوڈ_2 != Success) { // uhoh, an X error was thrown!
        أرجع false;              // the error handler called SDL_SetError() already.
    } وإلا إذا (!rc) {           // glXMakeCurrent() failed without throwing an X error
        أرجع SDL_سیٹ_Error("Unable to make GL context current");
    }

    أرجع true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

ساكن صحيح swapinterval = 0;
bool X11_GL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    bool نتیجہ = false;

    إذا ((interval < 0) && (!_this->gl_انکڑے->HAS_GLX_EXT_وٹاندرا_control_tear)) {
        أرجع SDL_سیٹ_Error("Negative swap interval unsupported in this GL");
    } وإلا إذا (_this->gl_انکڑے->glXSwapIntervalEXT) {
        Display *display = _this->اندرونی->display;
        ثابت SDL_کھڑکی_انکڑے *windowdata = SDL_GL_Get_Current_کھڑکی()->اندرونی;

        کھڑکی_2 drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        صحيح currentInterval = 0;
        X11_GL_Get_وٹاندرا_Interval(_this, &currentInterval);
        _this->gl_انکڑے->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_انکڑے->glXSwapIntervalEXT(display, drawable, interval);
        نتیجہ = true;
        swapinterval = interval;
    } وإلا إذا (_this->gl_انکڑے->glXSwapIntervalMESA) {
        ثابت صحيح rc = _this->gl_انکڑے->glXSwapIntervalMESA(interval);
        إذا (rc == 0) {
            swapinterval = interval;
            نتیجہ = true;
        } وإلا {
            نتیجہ = SDL_سیٹ_Error("glXSwapIntervalMESA failed");
        }
    } وإلا إذا (_this->gl_انکڑے->glXSwapIntervalSGI) {
        ثابت صحيح rc = _this->gl_انکڑے->glXSwapIntervalSGI(interval);
        إذا (rc == 0) {
            swapinterval = interval;
            نتیجہ = true;
        } وإلا {
            نتیجہ = SDL_سیٹ_Error("glXSwapIntervalSGI failed");
        }
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع نتیجہ;
}

ساكن SDL_GLSwapIntervalTearBehavior Check_وٹاندرا_Interval_Tear_Behavior(SDL_VideoDevice *_this, کھڑکی_2 drawable, بنانشانی صحيح current_val, بنانشانی صحيح current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    إذا (_this->gl_انکڑے->وٹاندرا_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        إذا (!_this->gl_انکڑے->HAS_GLX_EXT_وٹاندرا_control_tear) {
            _this->gl_انکڑے->وٹاندرا_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } وإلا {
            Display *display = _this->اندرونی->display;
            بنانشانی صحيح allow_late_وٹاندرا_tearing = 22;
            صحيح original_val = (صحيح) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_انکڑے->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_انکڑے->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_انکڑے->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_وٹاندرا_tearing);

            إذا (allow_late_وٹاندرا_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_انکڑے->وٹاندرا_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                إذا (current_allow_late) {
                    original_val = -original_val;
                }
            } وإلا إذا (allow_late_وٹاندرا_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_انکڑے->وٹاندرا_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } وإلا {  // unexpected outcome!
                _this->gl_انکڑے->وٹاندرا_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_انکڑے->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    أرجع _this->gl_انکڑے->وٹاندرا_interval_tear_behavior;
}


bool X11_GL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    إذا (_this->gl_انکڑے->glXSwapIntervalEXT) {
        Display *display = _this->اندرونی->display;
        ثابت SDL_کھڑکی_انکڑے *windowdata = SDL_GL_Get_Current_کھڑکی()->اندرونی;
        کھڑکی_2 drawable = windowdata->xwindow;
        بنانشانی صحيح allow_late_وٹاندرا_tearing = 0;
        بنانشانی صحيح val = 0;

        إذا (_this->gl_انکڑے->HAS_GLX_EXT_وٹاندرا_control_tear) {
            allow_late_وٹاندرا_tearing = 22;  // set this to nonsense.
            _this->gl_انکڑے->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_وٹاندرا_tearing);
        }

        _this->gl_انکڑے->glXQueryDrawable(display, drawable,
                                         GLX_وٹاندرا_INTERVAL_EXT, &val);

        *interval = (صحيح)val;

        بدل (Check_وٹاندرا_Interval_Tear_Behavior(_this, drawable, val, allow_late_وٹاندرا_tearing)) {
            حالة SDL_SWAPINTERVALTEAR_MESA:
                *interval = (صحيح)val;  // unsigned int cast to signed that generates negative value if necessary.
                اكسر;

            حالة SDL_SWAPINTERVALTEAR_NVIDIA:
            افتراضي:
                إذا ((allow_late_وٹاندرا_tearing) && (val > 0)) {
                    *interval = -((صحيح)val);
                }
                اكسر;
        }

        أرجع true;
    } وإلا إذا (_this->gl_انکڑے->gl_XGet_وٹاندرا_Interval_MESA) {
        صحيح val = _this->gl_انکڑے->gl_XGet_وٹاندرا_Interval_MESA();
        إذا (val == GLX_BAD_CONTEXT) {
            أرجع SDL_سیٹ_Error("GLX_BAD_CONTEXT");
        }
        *interval = val;
        أرجع true;
    } وإلا {
        *interval = swapinterval;
        أرجع true;
    }
}

bool X11_GL_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;

    _this->gl_انکڑے->glXSwapBuffers(display, انکڑے->xwindow);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(انکڑے->کھڑکی);
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */

    أرجع true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->اندرونی->display;
    GLXContext glx_context = (GLXContext)context;

    إذا (!_this->gl_انکڑے) {
        أرجع true;
    }
    _this->gl_انکڑے->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    أرجع true;
}

#جے_انت // SDL_VIDEO_OPENGL_GLX

#جے_انت // SDL_VIDEO_DRIVER_X11
