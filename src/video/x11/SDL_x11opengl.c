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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "SDL_x11video.h"
#समावेश "SDL_x11xsync.h"
#समावेश "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#अगर_घोषित SDL_VIDEO_OPENGL_GLX
#समावेश "SDL_x11opengles.h"

#अगर defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#घोषणा DEFAULT_OPENGL "libGL.so"
#या_अगर defined(SDL_PLATFORM_MACOS)
#घोषणा DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#अन्यथा
#घोषणा DEFAULT_OPENGL "libGL.so.1"
#पूर्ण_अगर

#अगर_अघोषित GLX_NONE_EXT
#घोषणा GLX_NONE_EXT 0x8000
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_multisample
#घोषणा GLX_ARB_multisample
#घोषणा GLX_SAMPLE_BUFFERS_ARB 100000
#घोषणा GLX_SAMPLES_ARB        100001
#पूर्ण_अगर

#अगर_अघोषित GLX_EXT_visual_rating
#घोषणा GLX_EXT_visual_rating
#घोषणा GLX_VISUAL_CAVEAT_EXT         0x20
#घोषणा GLX_NONE_EXT                  0x8000
#घोषणा GLX_SLOW_VISUAL_EXT           0x8001
#घोषणा GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#पूर्ण_अगर

#अगर_अघोषित GLX_EXT_visual_info
#घोषणा GLX_EXT_visual_info
#घोषणा GLX_X_VISUAL_TYPE_EXT 0x22
#घोषणा GLX_DIRECT_COLOR_EXT  0x8003
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_create_context
#घोषणा GLX_ARB_create_context
#घोषणा GLX_CONTEXT_MAJOR_VERSION_ARB          0x2091
#घोषणा GLX_CONTEXT_MINOR_VERSION_ARB          0x2092
#घोषणा GLX_CONTEXT_FLAGS_ARB                  0x2094
#घोषणा GLX_CONTEXT_DEBUG_BIT_ARB              0x0001
#घोषणा GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002

// Typedef for the GL 3.0 context creation function
प्रकार GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool direct,
                                                        स्थिर पूर्णांक
                                                            *attrib_list);
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_create_context_profile
#घोषणा GLX_ARB_create_context_profile
#घोषणा GLX_CONTEXT_PROFILE_MASK_ARB              0x9126
#घोषणा GLX_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#घोषणा GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_create_context_robustness
#घोषणा GLX_ARB_create_context_robustness
#घोषणा GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB           0x00000004
#घोषणा GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#घोषणा GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#घोषणा GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#पूर्ण_अगर

#अगर_अघोषित GLX_EXT_create_context_es2_profile
#घोषणा GLX_EXT_create_context_es2_profile
#अगर_अघोषित GLX_CONTEXT_ES2_PROFILE_BIT_EXT
#घोषणा GLX_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000002
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_framebuffer_sRGB
#घोषणा GLX_ARB_framebuffer_sRGB
#अगर_अघोषित GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#घोषणा GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_fbconfig_float
#घोषणा GLX_ARB_fbconfig_float
#अगर_अघोषित GLX_RGBA_FLOAT_TYPE_ARB
#घोषणा GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#पूर्ण_अगर
#अगर_अघोषित GLX_RGBA_FLOAT_BIT_ARB
#घोषणा GLX_RGBA_FLOAT_BIT_ARB 0x00000004
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_create_context_no_error
#घोषणा GLX_ARB_create_context_no_error
#अगर_अघोषित GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#घोषणा GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित GLX_EXT_swap_control
#घोषणा GLX_SWAP_INTERVAL_EXT     0x20F1
#घोषणा GLX_MAX_SWAP_INTERVAL_EXT 0x20F2
#पूर्ण_अगर

#अगर_अघोषित GLX_EXT_swap_control_tear
#घोषणा GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#पूर्ण_अगर

#अगर_अघोषित GLX_ARB_context_flush_control
#घोषणा GLX_ARB_context_flush_control
#घोषणा GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#घोषणा GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#घोषणा GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#पूर्ण_अगर

#घोषणा OPENGL_REQUIRES_DLOPEN
#अगर defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#समावेश <dlfcn.h>
#घोषणा GL_LoadObject(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#घोषणा GL_LoadFunction  dlsym
#घोषणा GL_UnloadObject  dlclose
#अन्यथा
#घोषणा GL_LoadObject   SDL_LoadObject
#घोषणा GL_LoadFunction SDL_LoadFunction
#घोषणा GL_UnloadObject SDL_UnloadObject
#पूर्ण_अगर

अटल व्योम X11_GL_InitExtensions(SDL_VideoDevice *_this);

अटल bool X11_GL_LoadLibrary_EGLFallback(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
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
    वापस X11_GLES_LoadLibrary(_this, path);
#अन्यथा
    वापस SDL_SetError("SDL not configured with EGL support");
#पूर्ण_अगर
}

bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    Display *display;
    SDL_SharedObject *handle;

    अगर (_this->gl_तथ्य) {
        वापस SDL_SetError("OpenGL context already created");
    }

    अगर ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        वापस X11_GL_LoadLibrary_EGLFallback(_this, path);
    }

    // Load the OpenGL library
    अगर (path == शून्य) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    अगर (path == शून्य) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_LoadObject(path);
    अगर (!_this->gl_config.dll_handle) {
#अगर defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_SetError("Failed loading %s: %s", path, dlerror());
#पूर्ण_अगर
        वापस false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_तथ्य =
        (काष्ठा SDL_GLDriver_तथ्य *)SDL_calloc(1,
                                              माप(काष्ठा
                                                     SDL_GLDriver_तथ्य));
    अगर (!_this->gl_तथ्य) {
        वापस false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_तथ्य->glXQueryExtension =
        (Bool(*)(Display *, पूर्णांक *, पूर्णांक *))
            GL_LoadFunction(handle, "glXQueryExtension");
    _this->gl_तथ्य->glXGetProcAddress =
        (__GLXextFuncPtr (*)(स्थिर GLubyte *))
            GL_LoadFunction(handle, "glXGetProcAddressARB");
    _this->gl_तथ्य->glXChooseVisual =
        (XVisualInfo * (*)(Display *, पूर्णांक, पूर्णांक *))
            X11_GL_GetProcAddress(_this, "glXChooseVisual");
    _this->gl_तथ्य->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, पूर्णांक))
            X11_GL_GetProcAddress(_this, "glXCreateContext");
    _this->gl_तथ्य->glXDestroyContext =
        (व्योम (*)(Display *, GLXContext))
            X11_GL_GetProcAddress(_this, "glXDestroyContext");
    _this->gl_तथ्य->glXMakeCurrent =
        (पूर्णांक (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_GetProcAddress(_this, "glXMakeCurrent");
    _this->gl_तथ्य->glXSwapBuffers =
        (व्योम (*)(Display *, GLXDrawable))
            X11_GL_GetProcAddress(_this, "glXSwapBuffers");
    _this->gl_तथ्य->glXQueryDrawable =
        (व्योम (*)(Display *, GLXDrawable, पूर्णांक, अचिन्हित पूर्णांक *))
            X11_GL_GetProcAddress(_this, "glXQueryDrawable");

    अगर (!_this->gl_तथ्य->glXQueryExtension ||
        !_this->gl_तथ्य->glXChooseVisual ||
        !_this->gl_तथ्य->glXCreateContext ||
        !_this->gl_तथ्य->glXDestroyContext ||
        !_this->gl_तथ्य->glXMakeCurrent ||
        !_this->gl_तथ्य->glXSwapBuffers) {
        वापस SDL_SetError("Could not retrieve OpenGL functions");
    }

    display = _this->internal->display;
    अगर (!_this->gl_तथ्य->glXQueryExtension(display, &_this->gl_तथ्य->errorBase, &_this->gl_तथ्य->eventBase)) {
        वापस SDL_SetError("GLX is not supported");
    }

    _this->gl_तथ्य->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    अगर (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        वापस X11_GL_LoadLibrary_EGLFallback(_this, शून्य);
    }

    वापस true;
}

SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    अगर (_this->gl_तथ्य->glXGetProcAddress) {
        वापस _this->gl_तथ्य->glXGetProcAddress((स्थिर GLubyte *)proc);
    }
    वापस GL_LoadFunction(_this->gl_config.dll_handle, proc);
}

व्योम X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#अगर 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = शून्य;
#पूर्ण_अगर

    // Free OpenGL memory
    SDL_free(_this->gl_तथ्य);
    _this->gl_तथ्य = शून्य;
}

अटल bool HasExtension(स्थिर अक्षर *extension, स्थिर अक्षर *extensions)
{
    स्थिर अक्षर *start;
    स्थिर अक्षर *where, *terminator;

    अगर (!extensions) {
        वापस false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    अगर (where || *extension == '\0') {
        वापस false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    start = extensions;

    क्रम (;;) {
        where = SDL_strstr(start, extension);
        अगर (!where) {
            अवरोध;
        }

        terminator = where + SDL_strlen(extension);
        अगर (where == start || *(where - 1) == ' ') {
            अगर (*terminator == ' ' || *terminator == '\0') {
                वापस true;
            }
        }

        start = terminator;
    }
    वापस false;
}

अटल व्योम X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->internal->display;
    स्थिर पूर्णांक screen = DefaultScreen(display);
    XVisualInfo *vinfo = शून्य;
    Window w = 0;
    GLXContext पूर्व_ctx = शून्य;
    GLXDrawable पूर्व_drawable = 0;
    GLXContext context = शून्य;
    स्थिर अक्षर *(*glXQueryExtensionsStringFunc)(Display *, पूर्णांक);
    स्थिर अक्षर *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    अगर (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(व्योम) =
            (GLXContext(*)(व्योम))
                X11_GL_GetProcAddress(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(व्योम) =
            (GLXDrawable(*)(व्योम))
                X11_GL_GetProcAddress(_this, "glXGetCurrentDrawable");

        अगर (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSetWindowAttributes xattr;
            पूर्व_ctx = glXGetCurrentContextFunc();
            पूर्व_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, मूल_Window(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreateWindow(display, मूल_Window(display, screen), 0, 0,
                                  32, 32, 0, vinfo->depth, निवेश_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_तथ्य->glXCreateContext(display, vinfo,
                                                       शून्य, True);
            अगर (context) {
                _this->gl_तथ्य->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (स्थिर अक्षर *(*)(Display *, पूर्णांक))X11_GL_GetProcAddress(_this,
                                                               "glXQueryExtensionsString");
    अगर (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } अन्यथा {
        extensions = शून्य;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_तथ्य->HAS_GLX_EXT_swap_control_tear = false;
    अगर (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_तथ्य->glXSwapIntervalEXT =
            (व्योम (*)(Display *, GLXDrawable, पूर्णांक))
                X11_GL_GetProcAddress(_this, "glXSwapIntervalEXT");
        अगर (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_तथ्य->HAS_GLX_EXT_swap_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    अगर (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_तथ्य->glXSwapIntervalMESA =
            (पूर्णांक (*)(पूर्णांक))X11_GL_GetProcAddress(_this, "glXSwapIntervalMESA");
        _this->gl_तथ्य->glXGetSwapIntervalMESA =
            (पूर्णांक (*)(व्योम))X11_GL_GetProcAddress(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    अगर (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_तथ्य->glXSwapIntervalSGI =
            (पूर्णांक (*)(पूर्णांक))X11_GL_GetProcAddress(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    अगर (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_तथ्य->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, स्थिर पूर्णांक *))
                X11_GL_GetProcAddress(_this, "glXCreateContextAttribsARB");
        _this->gl_तथ्य->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, पूर्णांक, स्थिर पूर्णांक *, पूर्णांक *))
                X11_GL_GetProcAddress(_this, "glXChooseFBConfig");
        _this->gl_तथ्य->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_GetProcAddress(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    अगर (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_तथ्य->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    अगर (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_तथ्य->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    अगर (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        अगर (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_तथ्य->es_profile_max_supported_version.major,
                &_this->gl_तथ्य->es_profile_max_supported_version.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    अगर (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_तथ्य->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    अगर (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_तथ्य->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    अगर (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_तथ्य->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    अगर (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_तथ्य->HAS_GLX_ARB_framebuffer_sRGB = true;
    } अन्यथा अगर (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_तथ्य->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    अगर (context) {
        _this->gl_तथ्य->glXMakeCurrent(display, None, शून्य);
        _this->gl_तथ्य->glXDestroyContext(display, context);
        अगर (पूर्व_ctx && पूर्व_drawable) {
            _this->gl_तथ्य->glXMakeCurrent(display, पूर्व_drawable, पूर्व_ctx);
        }
    }

    अगर (w) {
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
अटल पूर्णांक X11_GL_GetAttributes(SDL_VideoDevice *_this, Display *display, पूर्णांक screen, पूर्णांक *attribs, पूर्णांक आकार, Bool for_FBConfig, पूर्णांक **_pvistypeattr, bool transparent)
{
    पूर्णांक i = 0;
    स्थिर पूर्णांक MAX_ATTRIBUTES = 64;
    पूर्णांक *pvistypeattr = शून्य;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(आकार >= MAX_ATTRIBUTES);

    // Setup our GLX attributes according to the gl_config.
    अगर (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        अगर (_this->gl_config.floatbuffers) {
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

    अगर (_this->gl_config.alpha_आकार) {
        attribs[i++] = GLX_ALPHA_आकार;
        attribs[i++] = _this->gl_config.alpha_आकार;
    }

    अगर (_this->gl_config.double_बफर) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        अगर (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_DEPTH_आकार;
    attribs[i++] = _this->gl_config.depth_आकार;

    अगर (_this->gl_config.stencil_आकार) {
        attribs[i++] = GLX_STENCIL_आकार;
        attribs[i++] = _this->gl_config.stencil_आकार;
    }

    अगर (_this->gl_config.accum_red_आकार) {
        attribs[i++] = GLX_ACCUM_RED_आकार;
        attribs[i++] = _this->gl_config.accum_red_आकार;
    }

    अगर (_this->gl_config.accum_green_आकार) {
        attribs[i++] = GLX_ACCUM_GREEN_आकार;
        attribs[i++] = _this->gl_config.accum_green_आकार;
    }

    अगर (_this->gl_config.accum_blue_आकार) {
        attribs[i++] = GLX_ACCUM_BLUE_आकार;
        attribs[i++] = _this->gl_config.accum_blue_आकार;
    }

    अगर (_this->gl_config.accum_alpha_आकार) {
        attribs[i++] = GLX_ACCUM_ALPHA_आकार;
        attribs[i++] = _this->gl_config.accum_alpha_आकार;
    }

    अगर (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        अगर (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    अगर (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    अगर (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    अगर (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    अगर (_this->gl_तथ्य->HAS_GLX_ARB_framebuffer_sRGB) {
        स्थिर अक्षर *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        अगर (srgbhint && *srgbhint) {
            अगर (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } अन्यथा {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } अन्यथा अगर (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    अगर (_this->gl_config.accelerated >= 0 &&
        _this->gl_तथ्य->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    अगर (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        अगर (X11_UseDirectColorVisuals() && _this->gl_तथ्य->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_DIRECT_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_ATTRIBUTES);

    अगर (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    वापस i;
}

//get the first transparent Visual
अटल XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, पूर्णांक screen)
{
    XVisualInfo *visualinfo = शून्य;
    XVisualInfo vi_in;
    पूर्णांक out_गिनती = 0;

    vi_in.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, VisualScreenMask, &vi_in, &out_गिनती);
    अगर (visualinfo != शून्य) {
        पूर्णांक i = 0;
        क्रम (i = 0; i < out_गिनती; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            अगर (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_in.screen = screen;
                vi_in.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_गिनती);
                अवरोध;
            }
        }
    }
    वापस visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, पूर्णांक screen, bool transparent)
{
    // 64 seems nice.
    पूर्णांक attribs[64];
    XVisualInfo *vinfo = शून्य;
    पूर्णांक *pvistypeattr = शून्य;

    अगर (!_this->gl_तथ्य) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        वापस शून्य;
    }

    अगर (_this->gl_तथ्य->glXChooseFBConfig &&
        _this->gl_तथ्य->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = शून्य;
        पूर्णांक fbcount = 0;

        X11_GL_GetAttributes(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_तथ्य->glXChooseFBConfig(display, screen, attribs, &fbcount);
        अगर (!framebuffer_config && (pvistypeattr != शून्य)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_तथ्य->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        अगर (transparent) {
            // Return the first transparent Visual
            पूर्णांक i;
            क्रम (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_तथ्य->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                अगर (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = शून्य;
                    अवरोध;
                }
                X11_XFree(vinfo);
                vinfo = शून्य;
            }
        }

        अगर (framebuffer_config) {
            vinfo = _this->gl_तथ्य->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    अगर (!vinfo) {
        X11_GL_GetAttributes(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_तथ्य->glXChooseVisual(display, screen, attribs);

        अगर (!vinfo && (pvistypeattr != शून्य)) {
            *pvistypeattr = None;
            vinfo = _this->gl_तथ्य->glXChooseVisual(display, screen, attribs);
        }
    }

    अगर (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        अगर (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            अगर (visualinfo != शून्य) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    अगर (!vinfo) {
        SDL_SetError("Couldn't find matching GLX visual");
    }
    वापस vinfo;
}

अटल पूर्णांक (*handler)(Display *, XErrorEvent *) = शून्य;
अटल स्थिर अक्षर *errorHandlerOperation = शून्य;
अटल पूर्णांक errorBase = 0;
अटल पूर्णांक errorCode = 0;
अटल पूर्णांक X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    अक्षर *x11_error = शून्य;
    अक्षर x11_error_locale[256];

    errorCode = e->error_code;
    अगर (X11_XGetErrorText(d, errorCode, x11_error_locale, माप(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    अगर (x11_error) {
        SDL_SetError("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } अन्यथा {
        SDL_SetError("Could not %s: %i (Base %i)", errorHandlerOperation, errorCode, errorBase);
    }

    वापस 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_तथ्य != शून्य);
    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        वापस true;
    }

    SDL_assert(_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES);
    वापस (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_version == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_version > _this->gl_तथ्य->es_profile_max_supported_version.major || (_this->gl_config.major_version == _this->gl_तथ्य->es_profile_max_supported_version.major && _this->gl_config.minor_version > _this->gl_तथ्य->es_profile_max_supported_version.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    पूर्णांक screen = SDL_Get_Display_Driver_तथ्य_For_Window(window)->screen;
    XWindowAttributes xattr;
    XVisualInfo v, *vinfo;
    पूर्णांक n;
    SDL_GLContext context = शून्य;
    GLXContext share_context;
    स्थिर पूर्णांक transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;

    अगर (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } अन्यथा {
        share_context = शून्य;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    errorBase = _this->gl_तथ्य->errorBase;
    errorCode = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGetWindowAttributes(display, तथ्य->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &v, &n);
    अगर (vinfo) {
        अगर (_this->gl_config.major_version < 3 &&
            _this->gl_config.profile_mask == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_तथ्य->glXCreateContext(display, vinfo, share_context, True);
        } अन्यथा {
            // max 14 attributes plus terminator
            पूर्णांक attribs[15] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB,
                _this->gl_config.major_version,
                GLX_CONTEXT_MINOR_VERSION_ARB,
                _this->gl_config.minor_version,
                0
            };
            पूर्णांक iattr = 4;

            // SDL profile bits match GLX profile bits
            अगर (_this->gl_config.profile_mask != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_MASK_ARB;
                attribs[iattr++] = _this->gl_config.profile_mask;
            }

            // SDL flags match GLX flags
            अगर (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            अगर ((_this->gl_तथ्य->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            अगर ((_this->gl_तथ्य->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            अगर ((_this->gl_तथ्य->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            अगर (!_this->gl_तथ्य->glXCreateContextAttribsARB) {
                SDL_SetError("OpenGL 3.0 and later are not supported by this system");
            } अन्यथा {
                पूर्णांक glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = शून्य;
                पूर्णांक fbcount = 0;
                पूर्णांक *pvistypeattr = शून्य;

                X11_GL_GetAttributes(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                अगर (_this->gl_तथ्य->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_तथ्य->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    अगर (!framebuffer_config && (pvistypeattr != शून्य)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_तथ्य->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    अगर (transparent && (framebuffer_config != शून्य)) {
                        पूर्णांक i;
                        क्रम (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_अस्थायी = _this->gl_तथ्य->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            अगर ( vinfo_अस्थायी != शून्य) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_अस्थायी);
                                अगर (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_तथ्य->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = शून्य;
                                    X11_XFree(vinfo_अस्थायी);
                                    अवरोध;
                                }
                                X11_XFree(vinfo_अस्थायी);
                            }
                        }
                    }
                    अगर (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_तथ्य->glXCreateContextAttribsARB(display,
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

    अगर (!context) {
        अगर (errorCode == Success) {
            SDL_SetError("Could not create GL context");
        }
        वापस शून्य;
    }

    अगर (!X11_GL_MakeCurrent(_this, window, context)) {
        X11_GL_DestroyContext(_this, context);
        वापस शून्य;
    }

    वापस context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    Window drawable =
        (context ? window->internal->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    पूर्णांक rc;

    अगर (!_this->gl_तथ्य) {
        वापस SDL_SetError("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    errorBase = _this->gl_तथ्य->errorBase;
    errorCode = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_तथ्य->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    अगर (errorCode != Success) { // uhoh, an X error was thrown!
        वापस false;              // the error handler called SDL_SetError() already.
    } अन्यथा अगर (!rc) {           // glXMakeCurrent() failed without throwing an X error
        वापस SDL_SetError("Unable to make GL context current");
    }

    वापस true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

अटल पूर्णांक swapinterval = 0;
bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    bool परिणाम = false;

    अगर ((interval < 0) && (!_this->gl_तथ्य->HAS_GLX_EXT_swap_control_tear)) {
        वापस SDL_SetError("Negative swap interval unsupported in this GL");
    } अन्यथा अगर (_this->gl_तथ्य->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        स्थिर SDL_Window_तथ्य *windowdata = SDL_GL_GetCurrentWindow()->internal;

        Window drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        पूर्णांक currentInterval = 0;
        X11_GL_GetSwapInterval(_this, &currentInterval);
        _this->gl_तथ्य->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_तथ्य->glXSwapIntervalEXT(display, drawable, interval);
        परिणाम = true;
        swapinterval = interval;
    } अन्यथा अगर (_this->gl_तथ्य->glXSwapIntervalMESA) {
        स्थिर पूर्णांक rc = _this->gl_तथ्य->glXSwapIntervalMESA(interval);
        अगर (rc == 0) {
            swapinterval = interval;
            परिणाम = true;
        } अन्यथा {
            परिणाम = SDL_SetError("glXSwapIntervalMESA failed");
        }
    } अन्यथा अगर (_this->gl_तथ्य->glXSwapIntervalSGI) {
        स्थिर पूर्णांक rc = _this->gl_तथ्य->glXSwapIntervalSGI(interval);
        अगर (rc == 0) {
            swapinterval = interval;
            परिणाम = true;
        } अन्यथा {
            परिणाम = SDL_SetError("glXSwapIntervalSGI failed");
        }
    } अन्यथा {
        वापस SDL_Unsupported();
    }
    वापस परिणाम;
}

अटल SDL_GLSwapIntervalTearBehavior CheckSwapIntervalTearBehavior(SDL_VideoDevice *_this, Window drawable, अचिन्हित पूर्णांक current_val, अचिन्हित पूर्णांक current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    अगर (_this->gl_तथ्य->swap_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        अगर (!_this->gl_तथ्य->HAS_GLX_EXT_swap_control_tear) {
            _this->gl_तथ्य->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } अन्यथा {
            Display *display = _this->internal->display;
            अचिन्हित पूर्णांक allow_late_swap_tearing = 22;
            पूर्णांक original_val = (पूर्णांक) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_तथ्य->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_तथ्य->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_तथ्य->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_swap_tearing);

            अगर (allow_late_swap_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_तथ्य->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                अगर (current_allow_late) {
                    original_val = -original_val;
                }
            } अन्यथा अगर (allow_late_swap_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_तथ्य->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } अन्यथा {  // unexpected outcome!
                _this->gl_तथ्य->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_तथ्य->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    वापस _this->gl_तथ्य->swap_interval_tear_behavior;
}


bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval)
{
    अगर (_this->gl_तथ्य->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        स्थिर SDL_Window_तथ्य *windowdata = SDL_GL_GetCurrentWindow()->internal;
        Window drawable = windowdata->xwindow;
        अचिन्हित पूर्णांक allow_late_swap_tearing = 0;
        अचिन्हित पूर्णांक val = 0;

        अगर (_this->gl_तथ्य->HAS_GLX_EXT_swap_control_tear) {
            allow_late_swap_tearing = 22;  // set this to nonsense.
            _this->gl_तथ्य->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_swap_tearing);
        }

        _this->gl_तथ्य->glXQueryDrawable(display, drawable,
                                         GLX_SWAP_INTERVAL_EXT, &val);

        *interval = (पूर्णांक)val;

        चयन (CheckSwapIntervalTearBehavior(_this, drawable, val, allow_late_swap_tearing)) {
            हाल SDL_SWAPINTERVALTEAR_MESA:
                *interval = (पूर्णांक)val;  // unsigned int cast to signed that generates negative value if necessary.
                अवरोध;

            हाल SDL_SWAPINTERVALTEAR_NVIDIA:
            शेष:
                अगर ((allow_late_swap_tearing) && (val > 0)) {
                    *interval = -((पूर्णांक)val);
                }
                अवरोध;
        }

        वापस true;
    } अन्यथा अगर (_this->gl_तथ्य->glXGetSwapIntervalMESA) {
        पूर्णांक val = _this->gl_तथ्य->glXGetSwapIntervalMESA();
        अगर (val == GLX_BAD_CONTEXT) {
            वापस SDL_SetError("GLX_BAD_CONTEXT");
        }
        *interval = val;
        वापस true;
    } अन्यथा {
        *interval = swapinterval;
        वापस true;
    }
}

bool X11_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;

    _this->gl_तथ्य->glXSwapBuffers(display, तथ्य->xwindow);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(तथ्य->window);
#पूर्ण_अगर /* SDL_VIDEO_DRIVER_X11_XSYNC */

    वापस true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    GLXContext glx_context = (GLXContext)context;

    अगर (!_this->gl_तथ्य) {
        वापस true;
    }
    _this->gl_तथ्य->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_OPENGL_GLX

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
