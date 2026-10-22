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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11xsync.h"
#অন্তর্ভাব "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#ifdef SDL_VIDEO_OPENGL_GLX
#অন্তর্ভাব "SDL_x11opengles.h"

#যদি defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#define DEFAULT_OPENGL "libGL.so"
#নতুবা_যদি defined(SDL_PLATFORM_MACOS)
#define DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#অন্যথা
#define DEFAULT_OPENGL "libGL.so.1"
#endif

#ifndef GLX_NONE_EXT
#define GLX_NONE_EXT 0x8000
#endif

#ifndef GLX_ARB_multisample
#define GLX_ARB_multisample
#define GLX_SAMPLE_BUFFERS_ARB 100000
#define GLX_SAMPLES_ARB        100001
#endif

#ifndef GLX_EXT_visual_rating
#define GLX_EXT_visual_rating
#define GLX_VISUAL_CAVEAT_EXT         0x20
#define GLX_NONE_EXT                  0x8000
#define GLX_SLOW_VISUAL_EXT           0x8001
#define GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#endif

#ifndef GLX_EXT_visual_info
#define GLX_EXT_visual_info
#define GLX_X_VISUAL_TYPE_EXT 0x22
#define GLX_DIRECT_COLOR_EXT  0x8003
#endif

#ifndef GLX_ARB_create_context
#define GLX_ARB_create_context
#define GLX_CONTEXT_MAJOR_VERSION_ARB          0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB          0x2092
#define GLX_CONTEXT_FLAGS_ARB                  0x2094
#define GLX_CONTEXT_DEBUG_BIT_ARB              0x0001
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002

// Typedef for the GL 3.0 context creation function
প্রকারলেখ GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool direct,
                                                        ধ্রুবক পূর্ণসংখ্যা
                                                            *attrib_list);
#endif

#ifndef GLX_ARB_create_context_profile
#define GLX_ARB_create_context_profile
#define GLX_CONTEXT_PROFILE_MASK_ARB              0x9126
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#endif

#ifndef GLX_ARB_create_context_robustness
#define GLX_ARB_create_context_robustness
#define GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB           0x00000004
#define GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#define GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#endif

#ifndef GLX_EXT_create_context_es2_profile
#define GLX_EXT_create_context_es2_profile
#ifndef GLX_CONTEXT_ES2_PROFILE_BIT_EXT
#define GLX_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000002
#endif
#endif

#ifndef GLX_ARB_framebuffer_sRGB
#define GLX_ARB_framebuffer_sRGB
#ifndef GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#define GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#endif
#endif

#ifndef GLX_ARB_fbconfig_float
#define GLX_ARB_fbconfig_float
#ifndef GLX_RGBA_FLOAT_TYPE_ARB
#define GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#endif
#ifndef GLX_RGBA_FLOAT_BIT_ARB
#define GLX_RGBA_FLOAT_BIT_ARB 0x00000004
#endif
#endif

#ifndef GLX_ARB_create_context_no_error
#define GLX_ARB_create_context_no_error
#ifndef GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#define GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#endif
#endif

#ifndef GLX_EXT_swap_control
#define GLX_SWAP_INTERVAL_EXT     0x20F1
#define GLX_MAX_SWAP_INTERVAL_EXT 0x20F2
#endif

#ifndef GLX_EXT_swap_control_tear
#define GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#endif

#ifndef GLX_ARB_context_flush_control
#define GLX_ARB_context_flush_control
#define GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#define GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#define GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#endif

#define OPENGL_REQUIRES_DLOPEN
#যদি defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#অন্তর্ভাব <dlfcn.h>
#define GL_LoadObject(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#define GL_LoadFunction  dlsym
#define GL_UnloadObject  dlclose
#অন্যথা
#define GL_LoadObject   SDL_LoadObject
#define GL_LoadFunction SDL_LoadFunction
#define GL_UnloadObject SDL_UnloadObject
#endif

স্থির শূন্য X11_GL_InitExtensions(SDL_VideoDevice *_this);

স্থির bool X11_GL_LoadLibrary_EGLFallback(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    X11_GL_UnloadLibrary(_this);
    _this->GL_LoadLibrary = X11_GLES_LoadLibrary;
    _this->GL_GetProcAddress = X11_GLES_GetProcAddress;
    _this->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
    _this->GL_CreateContext = X11_GLES_CreateContext;
    _this->GL_MakeCurrent = X11_GLES_MakeCurrent;
    _this->GL_SetSwapInterval = X11_GLES_SetSwapInterval;
    _this->GL_GetSwapInterval = X11_GLES_GetSwapInterval;
    _this->GL_SwapWindow = X11_GLES_SwapWindow;
    _this->GL_DestroyContext = X11_GLES_DestroyContext;
    _this->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
    ফেরত X11_GLES_LoadLibrary(_this, path);
#অন্যথা
    ফেরত SDL_SetError("SDL not configured with EGL support");
#endif
}

bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    Display *display;
    SDL_SharedObject *handle;

    যদি (_this->gl_তথ্য) {
        ফেরত SDL_SetError("OpenGL context already created");
    }

    যদি ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ফেরত X11_GL_LoadLibrary_EGLFallback(_this, path);
    }

    // Load the OpenGL library
    যদি (path == ফাঁকা) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    যদি (path == ফাঁকা) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_LoadObject(path);
    যদি (!_this->gl_config.dll_handle) {
#যদি defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_SetError("Failed loading %s: %s", path, dlerror());
#endif
        ফেরত false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_তথ্য =
        (কাঠামো SDL_GLDriver_তথ্য *)SDL_calloc(1,
                                              আকার(কাঠামো
                                                     SDL_GLDriver_তথ্য));
    যদি (!_this->gl_তথ্য) {
        ফেরত false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_তথ্য->glXQueryExtension =
        (Bool(*)(Display *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *))
            GL_LoadFunction(handle, "glXQueryExtension");
    _this->gl_তথ্য->glXGetProcAddress =
        (__GLXextFuncPtr (*)(ধ্রুবক GLubyte *))
            GL_LoadFunction(handle, "glXGetProcAddressARB");
    _this->gl_তথ্য->glXChooseVisual =
        (XVisualInfo * (*)(Display *, পূর্ণসংখ্যা, পূর্ণসংখ্যা *))
            X11_GL_GetProcAddress(_this, "glXChooseVisual");
    _this->gl_তথ্য->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, পূর্ণসংখ্যা))
            X11_GL_GetProcAddress(_this, "glXCreateContext");
    _this->gl_তথ্য->glXDestroyContext =
        (শূন্য (*)(Display *, GLXContext))
            X11_GL_GetProcAddress(_this, "glXDestroyContext");
    _this->gl_তথ্য->glXMakeCurrent =
        (পূর্ণসংখ্যা (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_GetProcAddress(_this, "glXMakeCurrent");
    _this->gl_তথ্য->glXSwapBuffers =
        (শূন্য (*)(Display *, GLXDrawable))
            X11_GL_GetProcAddress(_this, "glXSwapBuffers");
    _this->gl_তথ্য->glXQueryDrawable =
        (শূন্য (*)(Display *, GLXDrawable, পূর্ণসংখ্যা, unsigned পূর্ণসংখ্যা *))
            X11_GL_GetProcAddress(_this, "glXQueryDrawable");

    যদি (!_this->gl_তথ্য->glXQueryExtension ||
        !_this->gl_তথ্য->glXChooseVisual ||
        !_this->gl_তথ্য->glXCreateContext ||
        !_this->gl_তথ্য->glXDestroyContext ||
        !_this->gl_তথ্য->glXMakeCurrent ||
        !_this->gl_তথ্য->glXSwapBuffers) {
        ফেরত SDL_SetError("Could not retrieve OpenGL functions");
    }

    display = _this->internal->display;
    যদি (!_this->gl_তথ্য->glXQueryExtension(display, &_this->gl_তথ্য->errorBase, &_this->gl_তথ্য->eventBase)) {
        ফেরত SDL_SetError("GLX is not supported");
    }

    _this->gl_তথ্য->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    যদি (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        ফেরত X11_GL_LoadLibrary_EGLFallback(_this, ফাঁকা);
    }

    ফেরত true;
}

SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    যদি (_this->gl_তথ্য->glXGetProcAddress) {
        ফেরত _this->gl_তথ্য->glXGetProcAddress((ধ্রুবক GLubyte *)proc);
    }
    ফেরত GL_LoadFunction(_this->gl_config.dll_handle, proc);
}

শূন্য X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#যদি 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ফাঁকা;
#endif

    // Free OpenGL memory
    SDL_free(_this->gl_তথ্য);
    _this->gl_তথ্য = ফাঁকা;
}

স্থির bool HasExtension(ধ্রুবক অক্ষর *extension, ধ্রুবক অক্ষর *extensions)
{
    ধ্রুবক অক্ষর *start;
    ধ্রুবক অক্ষর *where, *terminator;

    যদি (!extensions) {
        ফেরত false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    যদি (where || *extension == '\0') {
        ফেরত false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    start = extensions;

    জন্য (;;) {
        where = SDL_strstr(start, extension);
        যদি (!where) {
            বিরতি;
        }

        terminator = where + SDL_strlen(extension);
        যদি (where == start || *(where - 1) == ' ') {
            যদি (*terminator == ' ' || *terminator == '\0') {
                ফেরত true;
            }
        }

        start = terminator;
    }
    ফেরত false;
}

স্থির শূন্য X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->internal->display;
    ধ্রুবক পূর্ণসংখ্যা screen = DefaultScreen(display);
    XVisualInfo *vinfo = ফাঁকা;
    Window w = 0;
    GLXContext পূর্ব_ctx = ফাঁকা;
    GLXDrawable পূর্ব_drawable = 0;
    GLXContext context = ফাঁকা;
    ধ্রুবক অক্ষর *(*glXQueryExtensionsStringFunc)(Display *, পূর্ণসংখ্যা);
    ধ্রুবক অক্ষর *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    যদি (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(শূন্য) =
            (GLXContext(*)(শূন্য))
                X11_GL_GetProcAddress(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(শূন্য) =
            (GLXDrawable(*)(শূন্য))
                X11_GL_GetProcAddress(_this, "glXGetCurrentDrawable");

        যদি (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSetWindowAttributes xattr;
            পূর্ব_ctx = glXGetCurrentContextFunc();
            পূর্ব_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, মূল_Window(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreateWindow(display, মূল_Window(display, screen), 0, 0,
                                  32, 32, 0, vinfo->depth, প্রবেশ_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_তথ্য->glXCreateContext(display, vinfo,
                                                       ফাঁকা, True);
            যদি (context) {
                _this->gl_তথ্য->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (ধ্রুবক অক্ষর *(*)(Display *, পূর্ণসংখ্যা))X11_GL_GetProcAddress(_this,
                                                               "glXQueryExtensionsString");
    যদি (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } অন্যথা {
        extensions = ফাঁকা;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_তথ্য->HAS_GLX_EXT_swap_control_tear = false;
    যদি (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_তথ্য->glXSwapIntervalEXT =
            (শূন্য (*)(Display *, GLXDrawable, পূর্ণসংখ্যা))
                X11_GL_GetProcAddress(_this, "glXSwapIntervalEXT");
        যদি (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_তথ্য->HAS_GLX_EXT_swap_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    যদি (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_তথ্য->glXSwapIntervalMESA =
            (পূর্ণসংখ্যা (*)(পূর্ণসংখ্যা))X11_GL_GetProcAddress(_this, "glXSwapIntervalMESA");
        _this->gl_তথ্য->glXGetSwapIntervalMESA =
            (পূর্ণসংখ্যা (*)(শূন্য))X11_GL_GetProcAddress(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    যদি (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_তথ্য->glXSwapIntervalSGI =
            (পূর্ণসংখ্যা (*)(পূর্ণসংখ্যা))X11_GL_GetProcAddress(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    যদি (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_তথ্য->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, ধ্রুবক পূর্ণসংখ্যা *))
                X11_GL_GetProcAddress(_this, "glXCreateContextAttribsARB");
        _this->gl_তথ্য->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, পূর্ণসংখ্যা, ধ্রুবক পূর্ণসংখ্যা *, পূর্ণসংখ্যা *))
                X11_GL_GetProcAddress(_this, "glXChooseFBConfig");
        _this->gl_তথ্য->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_GetProcAddress(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    যদি (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_তথ্য->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    যদি (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_তথ্য->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    যদি (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        যদি (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_তথ্য->es_profile_max_supported_version.major,
                &_this->gl_তথ্য->es_profile_max_supported_version.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    যদি (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_তথ্য->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    যদি (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_তথ্য->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    যদি (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_তথ্য->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    যদি (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_তথ্য->HAS_GLX_ARB_framebuffer_sRGB = true;
    } অন্যথা যদি (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_তথ্য->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    যদি (context) {
        _this->gl_তথ্য->glXMakeCurrent(display, None, ফাঁকা);
        _this->gl_তথ্য->glXDestroyContext(display, context);
        যদি (পূর্ব_ctx && পূর্ব_drawable) {
            _this->gl_তথ্য->glXMakeCurrent(display, পূর্ব_drawable, পূর্ব_ctx);
        }
    }

    যদি (w) {
        X11_XDestroyWindow(display, w);
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
স্থির পূর্ণসংখ্যা X11_GL_GetAttributes(SDL_VideoDevice *_this, Display *display, পূর্ণসংখ্যা screen, পূর্ণসংখ্যা *attribs, পূর্ণসংখ্যা আকার_2, Bool for_FBConfig, পূর্ণসংখ্যা **_pvistypeattr, bool transparent)
{
    পূর্ণসংখ্যা i = 0;
    ধ্রুবক পূর্ণসংখ্যা MAX_ATTRIBUTES = 64;
    পূর্ণসংখ্যা *pvistypeattr = ফাঁকা;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(আকার_2 >= MAX_ATTRIBUTES);

    // Setup our GLX attributes according to the gl_config.
    যদি (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        যদি (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_BIT_ARB;
        } অন্যথা {
            attribs[i++] = GLX_RGBA_BIT;
        }
    } অন্যথা {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_আকার;
    attribs[i++] = _this->gl_config.red_আকার;
    attribs[i++] = GLX_GREEN_আকার;
    attribs[i++] = _this->gl_config.green_আকার;
    attribs[i++] = GLX_BLUE_আকার;
    attribs[i++] = _this->gl_config.blue_আকার;

    যদি (_this->gl_config.alpha_আকার) {
        attribs[i++] = GLX_ALPHA_আকার;
        attribs[i++] = _this->gl_config.alpha_আকার;
    }

    যদি (_this->gl_config.double_বাফার) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        যদি (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_DEPTH_আকার;
    attribs[i++] = _this->gl_config.depth_আকার;

    যদি (_this->gl_config.stencil_আকার) {
        attribs[i++] = GLX_STENCIL_আকার;
        attribs[i++] = _this->gl_config.stencil_আকার;
    }

    যদি (_this->gl_config.accum_red_আকার) {
        attribs[i++] = GLX_ACCUM_RED_আকার;
        attribs[i++] = _this->gl_config.accum_red_আকার;
    }

    যদি (_this->gl_config.accum_green_আকার) {
        attribs[i++] = GLX_ACCUM_GREEN_আকার;
        attribs[i++] = _this->gl_config.accum_green_আকার;
    }

    যদি (_this->gl_config.accum_blue_আকার) {
        attribs[i++] = GLX_ACCUM_BLUE_আকার;
        attribs[i++] = _this->gl_config.accum_blue_আকার;
    }

    যদি (_this->gl_config.accum_alpha_আকার) {
        attribs[i++] = GLX_ACCUM_ALPHA_আকার;
        attribs[i++] = _this->gl_config.accum_alpha_আকার;
    }

    যদি (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        যদি (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    যদি (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    যদি (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    যদি (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    যদি (_this->gl_তথ্য->HAS_GLX_ARB_framebuffer_sRGB) {
        ধ্রুবক অক্ষর *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        যদি (srgbhint && *srgbhint) {
            যদি (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } অন্যথা {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } অন্যথা যদি (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    যদি (_this->gl_config.accelerated >= 0 &&
        _this->gl_তথ্য->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    যদি (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        যদি (X11_UseDirectColorVisuals() && _this->gl_তথ্য->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_DIRECT_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_ATTRIBUTES);

    যদি (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    ফেরত i;
}

//get the first transparent Visual
স্থির XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, পূর্ণসংখ্যা screen)
{
    XVisualInfo *visualinfo = ফাঁকা;
    XVisualInfo vi_in;
    পূর্ণসংখ্যা out_গুনতি = 0;

    vi_in.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, VisualScreenMask, &vi_in, &out_গুনতি);
    যদি (visualinfo != ফাঁকা) {
        পূর্ণসংখ্যা i = 0;
        জন্য (i = 0; i < out_গুনতি; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            যদি (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_in.screen = screen;
                vi_in.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_গুনতি);
                বিরতি;
            }
        }
    }
    ফেরত visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, পূর্ণসংখ্যা screen, bool transparent)
{
    // 64 seems nice.
    পূর্ণসংখ্যা attribs[64];
    XVisualInfo *vinfo = ফাঁকা;
    পূর্ণসংখ্যা *pvistypeattr = ফাঁকা;

    যদি (!_this->gl_তথ্য) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        ফেরত ফাঁকা;
    }

    যদি (_this->gl_তথ্য->glXChooseFBConfig &&
        _this->gl_তথ্য->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = ফাঁকা;
        পূর্ণসংখ্যা fbcount = 0;

        X11_GL_GetAttributes(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_তথ্য->glXChooseFBConfig(display, screen, attribs, &fbcount);
        যদি (!framebuffer_config && (pvistypeattr != ফাঁকা)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_তথ্য->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        যদি (transparent) {
            // Return the first transparent Visual
            পূর্ণসংখ্যা i;
            জন্য (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_তথ্য->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                যদি (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = ফাঁকা;
                    বিরতি;
                }
                X11_XFree(vinfo);
                vinfo = ফাঁকা;
            }
        }

        যদি (framebuffer_config) {
            vinfo = _this->gl_তথ্য->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    যদি (!vinfo) {
        X11_GL_GetAttributes(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_তথ্য->glXChooseVisual(display, screen, attribs);

        যদি (!vinfo && (pvistypeattr != ফাঁকা)) {
            *pvistypeattr = None;
            vinfo = _this->gl_তথ্য->glXChooseVisual(display, screen, attribs);
        }
    }

    যদি (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        যদি (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            যদি (visualinfo != ফাঁকা) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    যদি (!vinfo) {
        SDL_SetError("Couldn't find matching GLX visual");
    }
    ফেরত vinfo;
}

স্থির পূর্ণসংখ্যা (*handler)(Display *, XErrorEvent *) = ফাঁকা;
স্থির ধ্রুবক অক্ষর *errorHandlerOperation = ফাঁকা;
স্থির পূর্ণসংখ্যা errorBase = 0;
স্থির পূর্ণসংখ্যা errorCode = 0;
স্থির পূর্ণসংখ্যা X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    অক্ষর *x11_error = ফাঁকা;
    অক্ষর x11_error_locale[256];

    errorCode = e->error_code;
    যদি (X11_XGetErrorText(d, errorCode, x11_error_locale, আকার(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    যদি (x11_error) {
        SDL_SetError("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } অন্যথা {
        SDL_SetError("Could not %s: %i (Base %i)", errorHandlerOperation, errorCode, errorBase);
    }

    ফেরত 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_তথ্য != ফাঁকা);
    যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        ফেরত true;
    }

    SDL_assert(_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES);
    ফেরত (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_version == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_version > _this->gl_তথ্য->es_profile_max_supported_version.major || (_this->gl_config.major_version == _this->gl_তথ্য->es_profile_max_supported_version.major && _this->gl_config.minor_version > _this->gl_তথ্য->es_profile_max_supported_version.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    পূর্ণসংখ্যা screen = SDL_Get_Display_Driver_তথ্য_For_Window(window)->screen;
    XWindowAttributes xattr;
    XVisualInfo v, *vinfo;
    পূর্ণসংখ্যা n;
    SDL_GLContext context = ফাঁকা;
    GLXContext share_context;
    ধ্রুবক পূর্ণসংখ্যা transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;

    যদি (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } অন্যথা {
        share_context = ফাঁকা;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    errorBase = _this->gl_তথ্য->errorBase;
    errorCode = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGetWindowAttributes(display, তথ্য->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &v, &n);
    যদি (vinfo) {
        যদি (_this->gl_config.major_version < 3 &&
            _this->gl_config.profile_mask == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_তথ্য->glXCreateContext(display, vinfo, share_context, True);
        } অন্যথা {
            // max 14 attributes plus terminator
            পূর্ণসংখ্যা attribs[15] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB,
                _this->gl_config.major_version,
                GLX_CONTEXT_MINOR_VERSION_ARB,
                _this->gl_config.minor_version,
                0
            };
            পূর্ণসংখ্যা iattr = 4;

            // SDL profile bits match GLX profile bits
            যদি (_this->gl_config.profile_mask != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_MASK_ARB;
                attribs[iattr++] = _this->gl_config.profile_mask;
            }

            // SDL flags match GLX flags
            যদি (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            যদি ((_this->gl_তথ্য->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            যদি ((_this->gl_তথ্য->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            যদি ((_this->gl_তথ্য->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            যদি (!_this->gl_তথ্য->glXCreateContextAttribsARB) {
                SDL_SetError("OpenGL 3.0 and later are not supported by this system");
            } অন্যথা {
                পূর্ণসংখ্যা glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = ফাঁকা;
                পূর্ণসংখ্যা fbcount = 0;
                পূর্ণসংখ্যা *pvistypeattr = ফাঁকা;

                X11_GL_GetAttributes(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                যদি (_this->gl_তথ্য->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_তথ্য->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    যদি (!framebuffer_config && (pvistypeattr != ফাঁকা)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_তথ্য->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    যদি (transparent && (framebuffer_config != ফাঁকা)) {
                        পূর্ণসংখ্যা i;
                        জন্য (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_অস্থায়ী = _this->gl_তথ্য->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            যদি ( vinfo_অস্থায়ী != ফাঁকা) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_অস্থায়ী);
                                যদি (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_তথ্য->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = ফাঁকা;
                                    X11_XFree(vinfo_অস্থায়ী);
                                    বিরতি;
                                }
                                X11_XFree(vinfo_অস্থায়ী);
                            }
                        }
                    }
                    যদি (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_তথ্য->glXCreateContextAttribsARB(display,
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

    যদি (!context) {
        যদি (errorCode == Success) {
            SDL_SetError("Could not create GL context");
        }
        ফেরত ফাঁকা;
    }

    যদি (!X11_GL_MakeCurrent(_this, window, context)) {
        X11_GL_DestroyContext(_this, context);
        ফেরত ফাঁকা;
    }

    ফেরত context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    Window drawable =
        (context ? window->internal->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    পূর্ণসংখ্যা rc;

    যদি (!_this->gl_তথ্য) {
        ফেরত SDL_SetError("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    errorBase = _this->gl_তথ্য->errorBase;
    errorCode = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_তথ্য->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    যদি (errorCode != Success) { // uhoh, an X error was thrown!
        ফেরত false;              // the error handler called SDL_SetError() already.
    } অন্যথা যদি (!rc) {           // glXMakeCurrent() failed without throwing an X error
        ফেরত SDL_SetError("Unable to make GL context current");
    }

    ফেরত true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

স্থির পূর্ণসংখ্যা swapinterval = 0;
bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    bool ফলাফল = false;

    যদি ((interval < 0) && (!_this->gl_তথ্য->HAS_GLX_EXT_swap_control_tear)) {
        ফেরত SDL_SetError("Negative swap interval unsupported in this GL");
    } অন্যথা যদি (_this->gl_তথ্য->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        ধ্রুবক SDL_Window_তথ্য *windowdata = SDL_GL_GetCurrentWindow()->internal;

        Window drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        পূর্ণসংখ্যা currentInterval = 0;
        X11_GL_GetSwapInterval(_this, &currentInterval);
        _this->gl_তথ্য->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_তথ্য->glXSwapIntervalEXT(display, drawable, interval);
        ফলাফল = true;
        swapinterval = interval;
    } অন্যথা যদি (_this->gl_তথ্য->glXSwapIntervalMESA) {
        ধ্রুবক পূর্ণসংখ্যা rc = _this->gl_তথ্য->glXSwapIntervalMESA(interval);
        যদি (rc == 0) {
            swapinterval = interval;
            ফলাফল = true;
        } অন্যথা {
            ফলাফল = SDL_SetError("glXSwapIntervalMESA failed");
        }
    } অন্যথা যদি (_this->gl_তথ্য->glXSwapIntervalSGI) {
        ধ্রুবক পূর্ণসংখ্যা rc = _this->gl_তথ্য->glXSwapIntervalSGI(interval);
        যদি (rc == 0) {
            swapinterval = interval;
            ফলাফল = true;
        } অন্যথা {
            ফলাফল = SDL_SetError("glXSwapIntervalSGI failed");
        }
    } অন্যথা {
        ফেরত SDL_Unsupported();
    }
    ফেরত ফলাফল;
}

স্থির SDL_GLSwapIntervalTearBehavior CheckSwapIntervalTearBehavior(SDL_VideoDevice *_this, Window drawable, unsigned পূর্ণসংখ্যা current_val, unsigned পূর্ণসংখ্যা current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    যদি (_this->gl_তথ্য->swap_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        যদি (!_this->gl_তথ্য->HAS_GLX_EXT_swap_control_tear) {
            _this->gl_তথ্য->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } অন্যথা {
            Display *display = _this->internal->display;
            unsigned পূর্ণসংখ্যা allow_late_swap_tearing = 22;
            পূর্ণসংখ্যা original_val = (পূর্ণসংখ্যা) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_তথ্য->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_তথ্য->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_তথ্য->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_swap_tearing);

            যদি (allow_late_swap_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_তথ্য->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                যদি (current_allow_late) {
                    original_val = -original_val;
                }
            } অন্যথা যদি (allow_late_swap_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_তথ্য->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } অন্যথা {  // unexpected outcome!
                _this->gl_তথ্য->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_তথ্য->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    ফেরত _this->gl_তথ্য->swap_interval_tear_behavior;
}


bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval)
{
    যদি (_this->gl_তথ্য->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        ধ্রুবক SDL_Window_তথ্য *windowdata = SDL_GL_GetCurrentWindow()->internal;
        Window drawable = windowdata->xwindow;
        unsigned পূর্ণসংখ্যা allow_late_swap_tearing = 0;
        unsigned পূর্ণসংখ্যা val = 0;

        যদি (_this->gl_তথ্য->HAS_GLX_EXT_swap_control_tear) {
            allow_late_swap_tearing = 22;  // set this to nonsense.
            _this->gl_তথ্য->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_swap_tearing);
        }

        _this->gl_তথ্য->glXQueryDrawable(display, drawable,
                                         GLX_SWAP_INTERVAL_EXT, &val);

        *interval = (পূর্ণসংখ্যা)val;

        নির্বাচন (CheckSwapIntervalTearBehavior(_this, drawable, val, allow_late_swap_tearing)) {
            ক্ষেত্র SDL_SWAPINTERVALTEAR_MESA:
                *interval = (পূর্ণসংখ্যা)val;  // unsigned int cast to signed that generates negative value if necessary.
                বিরতি;

            ক্ষেত্র SDL_SWAPINTERVALTEAR_NVIDIA:
            পূর্বনির্ধারিত:
                যদি ((allow_late_swap_tearing) && (val > 0)) {
                    *interval = -((পূর্ণসংখ্যা)val);
                }
                বিরতি;
        }

        ফেরত true;
    } অন্যথা যদি (_this->gl_তথ্য->glXGetSwapIntervalMESA) {
        পূর্ণসংখ্যা val = _this->gl_তথ্য->glXGetSwapIntervalMESA();
        যদি (val == GLX_BAD_CONTEXT) {
            ফেরত SDL_SetError("GLX_BAD_CONTEXT");
        }
        *interval = val;
        ফেরত true;
    } অন্যথা {
        *interval = swapinterval;
        ফেরত true;
    }
}

bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;

    _this->gl_তথ্য->glXSwapBuffers(display, তথ্য->xwindow);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(তথ্য->window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

    ফেরত true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    GLXContext glx_context = (GLXContext)context;

    যদি (!_this->gl_তথ্য) {
        ফেরত true;
    }
    _this->gl_তথ্য->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    ফেরত true;
}

#endif // SDL_VIDEO_OPENGL_GLX

#endif // SDL_VIDEO_DRIVER_X11
