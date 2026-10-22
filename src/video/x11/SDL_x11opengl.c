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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11xsync.h"
#അന്തര്ഭാവ "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#ifdef SDL_VIDEO_OPENGL_GLX
#അന്തര്ഭാവ "SDL_x11opengles.h"

#എങ്കിൽ defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#define DEFAULT_OPENGL "libGL.so"
#അല്ലെങ്കിലെങ്കിൽ defined(SDL_PLATFORM_MACOS)
#define DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#അല്ലെങ്കിൽ
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
തരനിർവചനം GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool direct,
                                                        സ്ഥിരം പൂർണ്ണസംഖ്യ
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
#എങ്കിൽ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#അന്തര്ഭാവ <dlfcn.h>
#define GL_LoadObject(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#define GL_LoadFunction  dlsym
#define GL_UnloadObject  dlclose
#അല്ലെങ്കിൽ
#define GL_LoadObject   SDL_LoadObject
#define GL_LoadFunction SDL_LoadFunction
#define GL_UnloadObject SDL_UnloadObject
#endif

സ്ഥിതം ശൂന്യം X11_GL_InitExtensions(SDL_VideoDevice *_this);

സ്ഥിതം bool X11_GL_LoadLibrary_EGLFallback(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
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
    തിരികെ X11_GLES_LoadLibrary(_this, path);
#അല്ലെങ്കിൽ
    തിരികെ SDL_SetError("SDL not configured with EGL support");
#endif
}

bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    Display *display;
    SDL_SharedObject *handle;

    എങ്കിൽ (_this->gl_data) {
        തിരികെ SDL_SetError("OpenGL context already created");
    }

    എങ്കിൽ ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        തിരികെ X11_GL_LoadLibrary_EGLFallback(_this, path);
    }

    // Load the OpenGL library
    എങ്കിൽ (path == ശൂന്യ) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    എങ്കിൽ (path == ശൂന്യ) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_LoadObject(path);
    എങ്കിൽ (!_this->gl_config.dll_handle) {
#എങ്കിൽ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_SetError("Failed loading %s: %s", path, dlerror());
#endif
        തിരികെ false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data =
        (ഘടന SDL_GLDriverData *)SDL_calloc(1,
                                              വലുപ്പം(ഘടന
                                                     SDL_GLDriverData));
    എങ്കിൽ (!_this->gl_data) {
        തിരികെ false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_data->glXQueryExtension =
        (Bool(*)(Display *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *))
            GL_LoadFunction(handle, "glXQueryExtension");
    _this->gl_data->glXGetProcAddress =
        (__GLXextFuncPtr (*)(സ്ഥിരം GLubyte *))
            GL_LoadFunction(handle, "glXGetProcAddressARB");
    _this->gl_data->glXChooseVisual =
        (XVisualInfo * (*)(Display *, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ *))
            X11_GL_GetProcAddress(_this, "glXChooseVisual");
    _this->gl_data->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, പൂർണ്ണസംഖ്യ))
            X11_GL_GetProcAddress(_this, "glXCreateContext");
    _this->gl_data->glXDestroyContext =
        (ശൂന്യം (*)(Display *, GLXContext))
            X11_GL_GetProcAddress(_this, "glXDestroyContext");
    _this->gl_data->glXMakeCurrent =
        (പൂർണ്ണസംഖ്യ (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_GetProcAddress(_this, "glXMakeCurrent");
    _this->gl_data->glXSwapBuffers =
        (ശൂന്യം (*)(Display *, GLXDrawable))
            X11_GL_GetProcAddress(_this, "glXSwapBuffers");
    _this->gl_data->glXQueryDrawable =
        (ശൂന്യം (*)(Display *, GLXDrawable, പൂർണ്ണസംഖ്യ, unsigned പൂർണ്ണസംഖ്യ *))
            X11_GL_GetProcAddress(_this, "glXQueryDrawable");

    എങ്കിൽ (!_this->gl_data->glXQueryExtension ||
        !_this->gl_data->glXChooseVisual ||
        !_this->gl_data->glXCreateContext ||
        !_this->gl_data->glXDestroyContext ||
        !_this->gl_data->glXMakeCurrent ||
        !_this->gl_data->glXSwapBuffers) {
        തിരികെ SDL_SetError("Could not retrieve OpenGL functions");
    }

    display = _this->internal->display;
    എങ്കിൽ (!_this->gl_data->glXQueryExtension(display, &_this->gl_data->errorBase, &_this->gl_data->eventBase)) {
        തിരികെ SDL_SetError("GLX is not supported");
    }

    _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    എങ്കിൽ (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        തിരികെ X11_GL_LoadLibrary_EGLFallback(_this, ശൂന്യ);
    }

    തിരികെ true;
}

SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc)
{
    എങ്കിൽ (_this->gl_data->glXGetProcAddress) {
        തിരികെ _this->gl_data->glXGetProcAddress((സ്ഥിരം GLubyte *)proc);
    }
    തിരികെ GL_LoadFunction(_this->gl_config.dll_handle, proc);
}

ശൂന്യം X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#എങ്കിൽ 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ശൂന്യ;
#endif

    // Free OpenGL memory
    SDL_free(_this->gl_data);
    _this->gl_data = ശൂന്യ;
}

സ്ഥിതം bool HasExtension(സ്ഥിരം അക്ഷരം *extension, സ്ഥിരം അക്ഷരം *extensions)
{
    സ്ഥിരം അക്ഷരം *start;
    സ്ഥിരം അക്ഷരം *where, *terminator;

    എങ്കിൽ (!extensions) {
        തിരികെ false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    എങ്കിൽ (where || *extension == '\0') {
        തിരികെ false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    start = extensions;

    വേണ്ടി (;;) {
        where = SDL_strstr(start, extension);
        എങ്കിൽ (!where) {
            നിർത്തുക;
        }

        terminator = where + SDL_strlen(extension);
        എങ്കിൽ (where == start || *(where - 1) == ' ') {
            എങ്കിൽ (*terminator == ' ' || *terminator == '\0') {
                തിരികെ true;
            }
        }

        start = terminator;
    }
    തിരികെ false;
}

സ്ഥിതം ശൂന്യം X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->internal->display;
    സ്ഥിരം പൂർണ്ണസംഖ്യ screen = DefaultScreen(display);
    XVisualInfo *vinfo = ശൂന്യ;
    Window w = 0;
    GLXContext prev_ctx = ശൂന്യ;
    GLXDrawable prev_drawable = 0;
    GLXContext context = ശൂന്യ;
    സ്ഥിരം അക്ഷരം *(*glXQueryExtensionsStringFunc)(Display *, പൂർണ്ണസംഖ്യ);
    സ്ഥിരം അക്ഷരം *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    എങ്കിൽ (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(ശൂന്യം) =
            (GLXContext(*)(ശൂന്യം))
                X11_GL_GetProcAddress(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(ശൂന്യം) =
            (GLXDrawable(*)(ശൂന്യം))
                X11_GL_GetProcAddress(_this, "glXGetCurrentDrawable");

        എങ്കിൽ (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSetWindowAttributes xattr;
            prev_ctx = glXGetCurrentContextFunc();
            prev_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, വേര്_Window(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreateWindow(display, വേര്_Window(display, screen), 0, 0,
                                  32, 32, 0, vinfo->depth, നിവേശം_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_data->glXCreateContext(display, vinfo,
                                                       ശൂന്യ, True);
            എങ്കിൽ (context) {
                _this->gl_data->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (സ്ഥിരം അക്ഷരം *(*)(Display *, പൂർണ്ണസംഖ്യ))X11_GL_GetProcAddress(_this,
                                                               "glXQueryExtensionsString");
    എങ്കിൽ (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } അല്ലെങ്കിൽ {
        extensions = ശൂന്യ;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_data->HAS_GLX_EXT_swap_control_tear = false;
    എങ്കിൽ (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_data->glXSwapIntervalEXT =
            (ശൂന്യം (*)(Display *, GLXDrawable, പൂർണ്ണസംഖ്യ))
                X11_GL_GetProcAddress(_this, "glXSwapIntervalEXT");
        എങ്കിൽ (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_data->HAS_GLX_EXT_swap_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    എങ്കിൽ (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_data->glXSwapIntervalMESA =
            (പൂർണ്ണസംഖ്യ (*)(പൂർണ്ണസംഖ്യ))X11_GL_GetProcAddress(_this, "glXSwapIntervalMESA");
        _this->gl_data->glXGetSwapIntervalMESA =
            (പൂർണ്ണസംഖ്യ (*)(ശൂന്യം))X11_GL_GetProcAddress(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    എങ്കിൽ (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_data->glXSwapIntervalSGI =
            (പൂർണ്ണസംഖ്യ (*)(പൂർണ്ണസംഖ്യ))X11_GL_GetProcAddress(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    എങ്കിൽ (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_data->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, സ്ഥിരം പൂർണ്ണസംഖ്യ *))
                X11_GL_GetProcAddress(_this, "glXCreateContextAttribsARB");
        _this->gl_data->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, പൂർണ്ണസംഖ്യ, സ്ഥിരം പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *))
                X11_GL_GetProcAddress(_this, "glXChooseFBConfig");
        _this->gl_data->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_GetProcAddress(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    എങ്കിൽ (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_data->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    എങ്കിൽ (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_data->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    എങ്കിൽ (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        എങ്കിൽ (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_data->es_profile_max_supported_version.major,
                &_this->gl_data->es_profile_max_supported_version.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    എങ്കിൽ (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_data->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    എങ്കിൽ (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_data->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    എങ്കിൽ (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_data->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    എങ്കിൽ (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_data->HAS_GLX_ARB_framebuffer_sRGB = true;
    } അല്ലെങ്കിൽ എങ്കിൽ (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_data->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    എങ്കിൽ (context) {
        _this->gl_data->glXMakeCurrent(display, None, ശൂന്യ);
        _this->gl_data->glXDestroyContext(display, context);
        എങ്കിൽ (prev_ctx && prev_drawable) {
            _this->gl_data->glXMakeCurrent(display, prev_drawable, prev_ctx);
        }
    }

    എങ്കിൽ (w) {
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
സ്ഥിതം പൂർണ്ണസംഖ്യ X11_GL_GetAttributes(SDL_VideoDevice *_this, Display *display, പൂർണ്ണസംഖ്യ screen, പൂർണ്ണസംഖ്യ *attribs, പൂർണ്ണസംഖ്യ size, Bool for_FBConfig, പൂർണ്ണസംഖ്യ **_pvistypeattr, bool transparent)
{
    പൂർണ്ണസംഖ്യ i = 0;
    സ്ഥിരം പൂർണ്ണസംഖ്യ MAX_ATTRIBUTES = 64;
    പൂർണ്ണസംഖ്യ *pvistypeattr = ശൂന്യ;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(size >= MAX_ATTRIBUTES);

    // Setup our GLX attributes according to the gl_config.
    എങ്കിൽ (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        എങ്കിൽ (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_BIT_ARB;
        } അല്ലെങ്കിൽ {
            attribs[i++] = GLX_RGBA_BIT;
        }
    } അല്ലെങ്കിൽ {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_SIZE;
    attribs[i++] = _this->gl_config.red_size;
    attribs[i++] = GLX_GREEN_SIZE;
    attribs[i++] = _this->gl_config.green_size;
    attribs[i++] = GLX_BLUE_SIZE;
    attribs[i++] = _this->gl_config.blue_size;

    എങ്കിൽ (_this->gl_config.alpha_size) {
        attribs[i++] = GLX_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.alpha_size;
    }

    എങ്കിൽ (_this->gl_config.double_buffer) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        എങ്കിൽ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_DEPTH_SIZE;
    attribs[i++] = _this->gl_config.depth_size;

    എങ്കിൽ (_this->gl_config.stencil_size) {
        attribs[i++] = GLX_STENCIL_SIZE;
        attribs[i++] = _this->gl_config.stencil_size;
    }

    എങ്കിൽ (_this->gl_config.accum_red_size) {
        attribs[i++] = GLX_ACCUM_RED_SIZE;
        attribs[i++] = _this->gl_config.accum_red_size;
    }

    എങ്കിൽ (_this->gl_config.accum_green_size) {
        attribs[i++] = GLX_ACCUM_GREEN_SIZE;
        attribs[i++] = _this->gl_config.accum_green_size;
    }

    എങ്കിൽ (_this->gl_config.accum_blue_size) {
        attribs[i++] = GLX_ACCUM_BLUE_SIZE;
        attribs[i++] = _this->gl_config.accum_blue_size;
    }

    എങ്കിൽ (_this->gl_config.accum_alpha_size) {
        attribs[i++] = GLX_ACCUM_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.accum_alpha_size;
    }

    എങ്കിൽ (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        എങ്കിൽ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    എങ്കിൽ (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    എങ്കിൽ (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    എങ്കിൽ (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    എങ്കിൽ (_this->gl_data->HAS_GLX_ARB_framebuffer_sRGB) {
        സ്ഥിരം അക്ഷരം *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        എങ്കിൽ (srgbhint && *srgbhint) {
            എങ്കിൽ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } അല്ലെങ്കിൽ {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    എങ്കിൽ (_this->gl_config.accelerated >= 0 &&
        _this->gl_data->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    എങ്കിൽ (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        എങ്കിൽ (X11_UseDirectColorVisuals() && _this->gl_data->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_DIRECT_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_ATTRIBUTES);

    എങ്കിൽ (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    തിരികെ i;
}

//get the first transparent Visual
സ്ഥിതം XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, പൂർണ്ണസംഖ്യ screen)
{
    XVisualInfo *visualinfo = ശൂന്യ;
    XVisualInfo vi_in;
    പൂർണ്ണസംഖ്യ out_എണ്ണം = 0;

    vi_in.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, VisualScreenMask, &vi_in, &out_എണ്ണം);
    എങ്കിൽ (visualinfo != ശൂന്യ) {
        പൂർണ്ണസംഖ്യ i = 0;
        വേണ്ടി (i = 0; i < out_എണ്ണം; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            എങ്കിൽ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_in.screen = screen;
                vi_in.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_എണ്ണം);
                നിർത്തുക;
            }
        }
    }
    തിരികെ visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, പൂർണ്ണസംഖ്യ screen, bool transparent)
{
    // 64 seems nice.
    പൂർണ്ണസംഖ്യ attribs[64];
    XVisualInfo *vinfo = ശൂന്യ;
    പൂർണ്ണസംഖ്യ *pvistypeattr = ശൂന്യ;

    എങ്കിൽ (!_this->gl_data) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (_this->gl_data->glXChooseFBConfig &&
        _this->gl_data->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = ശൂന്യ;
        പൂർണ്ണസംഖ്യ fbcount = 0;

        X11_GL_GetAttributes(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_data->glXChooseFBConfig(display, screen, attribs, &fbcount);
        എങ്കിൽ (!framebuffer_config && (pvistypeattr != ശൂന്യ)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_data->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        എങ്കിൽ (transparent) {
            // Return the first transparent Visual
            പൂർണ്ണസംഖ്യ i;
            വേണ്ടി (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_data->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                എങ്കിൽ (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = ശൂന്യ;
                    നിർത്തുക;
                }
                X11_XFree(vinfo);
                vinfo = ശൂന്യ;
            }
        }

        എങ്കിൽ (framebuffer_config) {
            vinfo = _this->gl_data->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    എങ്കിൽ (!vinfo) {
        X11_GL_GetAttributes(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_data->glXChooseVisual(display, screen, attribs);

        എങ്കിൽ (!vinfo && (pvistypeattr != ശൂന്യ)) {
            *pvistypeattr = None;
            vinfo = _this->gl_data->glXChooseVisual(display, screen, attribs);
        }
    }

    എങ്കിൽ (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        എങ്കിൽ (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            എങ്കിൽ (visualinfo != ശൂന്യ) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    എങ്കിൽ (!vinfo) {
        SDL_SetError("Couldn't find matching GLX visual");
    }
    തിരികെ vinfo;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ (*handler)(Display *, XErrorEvent *) = ശൂന്യ;
സ്ഥിതം സ്ഥിരം അക്ഷരം *errorHandlerOperation = ശൂന്യ;
സ്ഥിതം പൂർണ്ണസംഖ്യ errorBase = 0;
സ്ഥിതം പൂർണ്ണസംഖ്യ errorCode = 0;
സ്ഥിതം പൂർണ്ണസംഖ്യ X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    അക്ഷരം *x11_error = ശൂന്യ;
    അക്ഷരം x11_error_locale[256];

    errorCode = e->error_code;
    എങ്കിൽ (X11_XGetErrorText(d, errorCode, x11_error_locale, വലുപ്പം(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    എങ്കിൽ (x11_error) {
        SDL_SetError("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } അല്ലെങ്കിൽ {
        SDL_SetError("Could not %s: %i (Base %i)", errorHandlerOperation, errorCode, errorBase);
    }

    തിരികെ 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_data != ശൂന്യ);
    എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        തിരികെ true;
    }

    SDL_assert(_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES);
    തിരികെ (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_version == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_version > _this->gl_data->es_profile_max_supported_version.major || (_this->gl_config.major_version == _this->gl_data->es_profile_max_supported_version.major && _this->gl_config.minor_version > _this->gl_data->es_profile_max_supported_version.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    പൂർണ്ണസംഖ്യ screen = SDL_GetDisplayDriverDataForWindow(window)->screen;
    XWindowAttributes xattr;
    XVisualInfo v, *vinfo;
    പൂർണ്ണസംഖ്യ n;
    SDL_GLContext context = ശൂന്യ;
    GLXContext share_context;
    സ്ഥിരം പൂർണ്ണസംഖ്യ transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;

    എങ്കിൽ (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } അല്ലെങ്കിൽ {
        share_context = ശൂന്യ;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    errorBase = _this->gl_data->errorBase;
    errorCode = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGetWindowAttributes(display, data->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &v, &n);
    എങ്കിൽ (vinfo) {
        എങ്കിൽ (_this->gl_config.major_version < 3 &&
            _this->gl_config.profile_mask == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_data->glXCreateContext(display, vinfo, share_context, True);
        } അല്ലെങ്കിൽ {
            // max 14 attributes plus terminator
            പൂർണ്ണസംഖ്യ attribs[15] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB,
                _this->gl_config.major_version,
                GLX_CONTEXT_MINOR_VERSION_ARB,
                _this->gl_config.minor_version,
                0
            };
            പൂർണ്ണസംഖ്യ iattr = 4;

            // SDL profile bits match GLX profile bits
            എങ്കിൽ (_this->gl_config.profile_mask != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_MASK_ARB;
                attribs[iattr++] = _this->gl_config.profile_mask;
            }

            // SDL flags match GLX flags
            എങ്കിൽ (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            എങ്കിൽ ((_this->gl_data->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            എങ്കിൽ ((_this->gl_data->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            എങ്കിൽ ((_this->gl_data->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            എങ്കിൽ (!_this->gl_data->glXCreateContextAttribsARB) {
                SDL_SetError("OpenGL 3.0 and later are not supported by this system");
            } അല്ലെങ്കിൽ {
                പൂർണ്ണസംഖ്യ glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = ശൂന്യ;
                പൂർണ്ണസംഖ്യ fbcount = 0;
                പൂർണ്ണസംഖ്യ *pvistypeattr = ശൂന്യ;

                X11_GL_GetAttributes(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                എങ്കിൽ (_this->gl_data->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_data->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    എങ്കിൽ (!framebuffer_config && (pvistypeattr != ശൂന്യ)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_data->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    എങ്കിൽ (transparent && (framebuffer_config != ശൂന്യ)) {
                        പൂർണ്ണസംഖ്യ i;
                        വേണ്ടി (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_temp = _this->gl_data->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            എങ്കിൽ ( vinfo_temp != ശൂന്യ) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_temp);
                                എങ്കിൽ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_data->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = ശൂന്യ;
                                    X11_XFree(vinfo_temp);
                                    നിർത്തുക;
                                }
                                X11_XFree(vinfo_temp);
                            }
                        }
                    }
                    എങ്കിൽ (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_data->glXCreateContextAttribsARB(display,
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

    എങ്കിൽ (!context) {
        എങ്കിൽ (errorCode == Success) {
            SDL_SetError("Could not create GL context");
        }
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!X11_GL_MakeCurrent(_this, window, context)) {
        X11_GL_DestroyContext(_this, context);
        തിരികെ ശൂന്യ;
    }

    തിരികെ context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    Window drawable =
        (context ? window->internal->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    പൂർണ്ണസംഖ്യ rc;

    എങ്കിൽ (!_this->gl_data) {
        തിരികെ SDL_SetError("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    errorBase = _this->gl_data->errorBase;
    errorCode = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_data->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    എങ്കിൽ (errorCode != Success) { // uhoh, an X error was thrown!
        തിരികെ false;              // the error handler called SDL_SetError() already.
    } അല്ലെങ്കിൽ എങ്കിൽ (!rc) {           // glXMakeCurrent() failed without throwing an X error
        തിരികെ SDL_SetError("Unable to make GL context current");
    }

    തിരികെ true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

സ്ഥിതം പൂർണ്ണസംഖ്യ swapinterval = 0;
bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval)
{
    bool result = false;

    എങ്കിൽ ((interval < 0) && (!_this->gl_data->HAS_GLX_EXT_swap_control_tear)) {
        തിരികെ SDL_SetError("Negative swap interval unsupported in this GL");
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->gl_data->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        സ്ഥിരം SDL_WindowData *windowdata = SDL_GL_GetCurrentWindow()->internal;

        Window drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        പൂർണ്ണസംഖ്യ currentInterval = 0;
        X11_GL_GetSwapInterval(_this, &currentInterval);
        _this->gl_data->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_data->glXSwapIntervalEXT(display, drawable, interval);
        result = true;
        swapinterval = interval;
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->gl_data->glXSwapIntervalMESA) {
        സ്ഥിരം പൂർണ്ണസംഖ്യ rc = _this->gl_data->glXSwapIntervalMESA(interval);
        എങ്കിൽ (rc == 0) {
            swapinterval = interval;
            result = true;
        } അല്ലെങ്കിൽ {
            result = SDL_SetError("glXSwapIntervalMESA failed");
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->gl_data->glXSwapIntervalSGI) {
        സ്ഥിരം പൂർണ്ണസംഖ്യ rc = _this->gl_data->glXSwapIntervalSGI(interval);
        എങ്കിൽ (rc == 0) {
            swapinterval = interval;
            result = true;
        } അല്ലെങ്കിൽ {
            result = SDL_SetError("glXSwapIntervalSGI failed");
        }
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_Unsupported();
    }
    തിരികെ result;
}

സ്ഥിതം SDL_GLSwapIntervalTearBehavior CheckSwapIntervalTearBehavior(SDL_VideoDevice *_this, Window drawable, unsigned പൂർണ്ണസംഖ്യ current_val, unsigned പൂർണ്ണസംഖ്യ current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    എങ്കിൽ (_this->gl_data->swap_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        എങ്കിൽ (!_this->gl_data->HAS_GLX_EXT_swap_control_tear) {
            _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } അല്ലെങ്കിൽ {
            Display *display = _this->internal->display;
            unsigned പൂർണ്ണസംഖ്യ allow_late_swap_tearing = 22;
            പൂർണ്ണസംഖ്യ original_val = (പൂർണ്ണസംഖ്യ) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_data->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_data->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_data->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_swap_tearing);

            എങ്കിൽ (allow_late_swap_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                എങ്കിൽ (current_allow_late) {
                    original_val = -original_val;
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (allow_late_swap_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } അല്ലെങ്കിൽ {  // unexpected outcome!
                _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_data->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    തിരികെ _this->gl_data->swap_interval_tear_behavior;
}


bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval)
{
    എങ്കിൽ (_this->gl_data->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        സ്ഥിരം SDL_WindowData *windowdata = SDL_GL_GetCurrentWindow()->internal;
        Window drawable = windowdata->xwindow;
        unsigned പൂർണ്ണസംഖ്യ allow_late_swap_tearing = 0;
        unsigned പൂർണ്ണസംഖ്യ val = 0;

        എങ്കിൽ (_this->gl_data->HAS_GLX_EXT_swap_control_tear) {
            allow_late_swap_tearing = 22;  // set this to nonsense.
            _this->gl_data->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_swap_tearing);
        }

        _this->gl_data->glXQueryDrawable(display, drawable,
                                         GLX_SWAP_INTERVAL_EXT, &val);

        *interval = (പൂർണ്ണസംഖ്യ)val;

        തിരഞ്ഞെടുപ്പ് (CheckSwapIntervalTearBehavior(_this, drawable, val, allow_late_swap_tearing)) {
            അവസ്ഥ SDL_SWAPINTERVALTEAR_MESA:
                *interval = (പൂർണ്ണസംഖ്യ)val;  // unsigned int cast to signed that generates negative value if necessary.
                നിർത്തുക;

            അവസ്ഥ SDL_SWAPINTERVALTEAR_NVIDIA:
            സ്ഥിരസ്ഥിതി:
                എങ്കിൽ ((allow_late_swap_tearing) && (val > 0)) {
                    *interval = -((പൂർണ്ണസംഖ്യ)val);
                }
                നിർത്തുക;
        }

        തിരികെ true;
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->gl_data->glXGetSwapIntervalMESA) {
        പൂർണ്ണസംഖ്യ val = _this->gl_data->glXGetSwapIntervalMESA();
        എങ്കിൽ (val == GLX_BAD_CONTEXT) {
            തിരികെ SDL_SetError("GLX_BAD_CONTEXT");
        }
        *interval = val;
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        *interval = swapinterval;
        തിരികെ true;
    }
}

bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    _this->gl_data->glXSwapBuffers(display, data->xwindow);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(data->window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

    തിരികെ true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    GLXContext glx_context = (GLXContext)context;

    എങ്കിൽ (!_this->gl_data) {
        തിരികെ true;
    }
    _this->gl_data->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    തിരികെ true;
}

#endif // SDL_VIDEO_OPENGL_GLX

#endif // SDL_VIDEO_DRIVER_X11
