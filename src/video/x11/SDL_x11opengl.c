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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include "SDL_x11video.h"
#include "SDL_x11xsync.h"
#include "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#ifdef SDL_VIDEO_OPENGL_GLX
#include "SDL_x11opengles.h"

#གལ་སྲིད defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#define DEFAULT_OPENGL "libGL.so"
#elif defined(SDL_PLATFORM_MACOS)
#define DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#དེ་མིན
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
typedef GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool direct,
                                                        const ཧྲིལ
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
#གལ་སྲིད defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#include <dlfcn.h>
#define GL_LoadObject(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#define GL_LoadFunction  dlsym
#define GL_UnloadObject  dlclose
#དེ་མིན
#define GL_LoadObject   SDL_LoadObject
#define GL_LoadFunction SDL_LoadFunction
#define GL_UnloadObject SDL_UnloadObject
#endif

static void X11_GL_InitExtensions(SDL_VideoDevice *_this);

static bool X11_GL_LoadLibrary_EGLFallback(SDL_VideoDevice *_this, const var_na *path)
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
    ལོག X11_GLES_LoadLibrary(_this, path);
#དེ་མིན
    ལོག SDL_SetError("SDL not configured with EGL support");
#endif
}

bool X11_GL_LoadLibrary(SDL_VideoDevice *_this, const var_na *path)
{
    Display *display;
    SDL_SharedObject *handle;

    གལ་སྲིད (_this->gl_data) {
        ལོག SDL_SetError("OpenGL context already created");
    }

    གལ་སྲིད ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ལོག X11_GL_LoadLibrary_EGLFallback(_this, path);
    }

    // Load the OpenGL library
    གལ་སྲིད (path == NULL) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    གལ་སྲིད (path == NULL) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_LoadObject(path);
    གལ་སྲིད (!_this->gl_config.dll_handle) {
#གལ་སྲིད defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_SetError("Failed loading %s: %s", path, dlerror());
#endif
        ལོག false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data =
        (sa_nracanaa SDL_GLDriverData *)SDL_calloc(1,
                                              parimaa_na(sa_nracanaa
                                                     SDL_GLDriverData));
    གལ་སྲིད (!_this->gl_data) {
        ལོག false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_data->glXQueryExtension =
        (Bool(*)(Display *, ཧྲིལ *, ཧྲིལ *))
            GL_LoadFunction(handle, "glXQueryExtension");
    _this->gl_data->glXGetProcAddress =
        (__GLXextFuncPtr (*)(const GLubyte *))
            GL_LoadFunction(handle, "glXGetProcAddressARB");
    _this->gl_data->glXChooseVisual =
        (XVisualInfo * (*)(Display *, ཧྲིལ, ཧྲིལ *))
            X11_GL_GetProcAddress(_this, "glXChooseVisual");
    _this->gl_data->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, ཧྲིལ))
            X11_GL_GetProcAddress(_this, "glXCreateContext");
    _this->gl_data->glXDestroyContext =
        (void (*)(Display *, GLXContext))
            X11_GL_GetProcAddress(_this, "glXDestroyContext");
    _this->gl_data->glXMakeCurrent =
        (ཧྲིལ (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_GetProcAddress(_this, "glXMakeCurrent");
    _this->gl_data->glXSwapBuffers =
        (void (*)(Display *, GLXDrawable))
            X11_GL_GetProcAddress(_this, "glXSwapBuffers");
    _this->gl_data->glXQueryDrawable =
        (void (*)(Display *, GLXDrawable, ཧྲིལ, unsigned ཧྲིལ *))
            X11_GL_GetProcAddress(_this, "glXQueryDrawable");

    གལ་སྲིད (!_this->gl_data->glXQueryExtension ||
        !_this->gl_data->glXChooseVisual ||
        !_this->gl_data->glXCreateContext ||
        !_this->gl_data->glXDestroyContext ||
        !_this->gl_data->glXMakeCurrent ||
        !_this->gl_data->glXSwapBuffers) {
        ལོག SDL_SetError("Could not retrieve OpenGL functions");
    }

    display = _this->internal->display;
    གལ་སྲིད (!_this->gl_data->glXQueryExtension(display, &_this->gl_data->errorBase, &_this->gl_data->eventBase)) {
        ལོག SDL_SetError("GLX is not supported");
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
    གལ་སྲིད (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        ལོག X11_GL_LoadLibrary_EGLFallback(_this, NULL);
    }

    ལོག true;
}

SDL_FunctionPointer X11_GL_GetProcAddress(SDL_VideoDevice *_this, const var_na *proc)
{
    གལ་སྲིད (_this->gl_data->glXGetProcAddress) {
        ལོག _this->gl_data->glXGetProcAddress((const GLubyte *)proc);
    }
    ལོག GL_LoadFunction(_this->gl_config.dll_handle, proc);
}

void X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#གལ་སྲིད 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = NULL;
#endif

    // Free OpenGL memory
    SDL_free(_this->gl_data);
    _this->gl_data = NULL;
}

static bool HasExtension(const var_na *extension, const var_na *extensions)
{
    const var_na *start;
    const var_na *where, *terminator;

    གལ་སྲིད (!extensions) {
        ལོག false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    གལ་སྲིད (where || *extension == '\0') {
        ལོག false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    start = extensions;

    དོན་ལུ (;;) {
        where = SDL_strstr(start, extension);
        གལ་སྲིད (!where) {
            bha_nga;
        }

        terminator = where + SDL_strlen(extension);
        གལ་སྲིད (where == start || *(where - 1) == ' ') {
            གལ་སྲིད (*terminator == ' ' || *terminator == '\0') {
                ལོག true;
            }
        }

        start = terminator;
    }
    ལོག false;
}

static void X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->internal->display;
    const ཧྲིལ screen = DefaultScreen(display);
    XVisualInfo *vinfo = NULL;
    Window w = 0;
    GLXContext prev_ctx = NULL;
    GLXDrawable prev_drawable = 0;
    GLXContext context = NULL;
    const var_na *(*glXQueryExtensionsStringFunc)(Display *, ཧྲིལ);
    const var_na *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    གལ་སྲིད (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(void) =
            (GLXContext(*)(void))
                X11_GL_GetProcAddress(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(void) =
            (GLXDrawable(*)(void))
                X11_GL_GetProcAddress(_this, "glXGetCurrentDrawable");

        གལ་སྲིད (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSetWindowAttributes xattr;
            prev_ctx = glXGetCurrentContextFunc();
            prev_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, RootWindow(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreateWindow(display, RootWindow(display, screen), 0, 0,
                                  32, 32, 0, vinfo->depth, InputOutput, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_data->glXCreateContext(display, vinfo,
                                                       NULL, True);
            གལ་སྲིད (context) {
                _this->gl_data->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (const var_na *(*)(Display *, ཧྲིལ))X11_GL_GetProcAddress(_this,
                                                               "glXQueryExtensionsString");
    གལ་སྲིད (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } དེ་མིན {
        extensions = NULL;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_data->HAS_GLX_EXT_swap_control_tear = false;
    གལ་སྲིད (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_data->glXSwapIntervalEXT =
            (void (*)(Display *, GLXDrawable, ཧྲིལ))
                X11_GL_GetProcAddress(_this, "glXSwapIntervalEXT");
        གལ་སྲིད (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_data->HAS_GLX_EXT_swap_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    གལ་སྲིད (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_data->glXSwapIntervalMESA =
            (ཧྲིལ (*)(ཧྲིལ))X11_GL_GetProcAddress(_this, "glXSwapIntervalMESA");
        _this->gl_data->glXGetSwapIntervalMESA =
            (ཧྲིལ (*)(void))X11_GL_GetProcAddress(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    གལ་སྲིད (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_data->glXSwapIntervalSGI =
            (ཧྲིལ (*)(ཧྲིལ))X11_GL_GetProcAddress(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    གལ་སྲིད (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_data->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, const ཧྲིལ *))
                X11_GL_GetProcAddress(_this, "glXCreateContextAttribsARB");
        _this->gl_data->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, ཧྲིལ, const ཧྲིལ *, ཧྲིལ *))
                X11_GL_GetProcAddress(_this, "glXChooseFBConfig");
        _this->gl_data->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_GetProcAddress(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    གལ་སྲིད (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_data->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    གལ་སྲིད (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_data->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    གལ་སྲིད (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        གལ་སྲིད (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_data->es_profile_max_supported_version.major,
                &_this->gl_data->es_profile_max_supported_version.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    གལ་སྲིད (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_data->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    གལ་སྲིད (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_data->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    གལ་སྲིད (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_data->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    གལ་སྲིད (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_data->HAS_GLX_ARB_framebuffer_sRGB = true;
    } དེ་མིན གལ་སྲིད (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_data->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    གལ་སྲིད (context) {
        _this->gl_data->glXMakeCurrent(display, None, NULL);
        _this->gl_data->glXDestroyContext(display, context);
        གལ་སྲིད (prev_ctx && prev_drawable) {
            _this->gl_data->glXMakeCurrent(display, prev_drawable, prev_ctx);
        }
    }

    གལ་སྲིད (w) {
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
static ཧྲིལ X11_GL_GetAttributes(SDL_VideoDevice *_this, Display *display, ཧྲིལ screen, ཧྲིལ *attribs, ཧྲིལ size, Bool for_FBConfig, ཧྲིལ **_pvistypeattr, bool transparent)
{
    ཧྲིལ i = 0;
    const ཧྲིལ MAX_ATTRIBUTES = 64;
    ཧྲིལ *pvistypeattr = NULL;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(size >= MAX_ATTRIBUTES);

    // Setup our GLX attributes according to the gl_config.
    གལ་སྲིད (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        གལ་སྲིད (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_BIT_ARB;
        } དེ་མིན {
            attribs[i++] = GLX_RGBA_BIT;
        }
    } དེ་མིན {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_SIZE;
    attribs[i++] = _this->gl_config.red_size;
    attribs[i++] = GLX_GREEN_SIZE;
    attribs[i++] = _this->gl_config.green_size;
    attribs[i++] = GLX_BLUE_SIZE;
    attribs[i++] = _this->gl_config.blue_size;

    གལ་སྲིད (_this->gl_config.alpha_size) {
        attribs[i++] = GLX_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.alpha_size;
    }

    གལ་སྲིད (_this->gl_config.double_buffer) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        གལ་སྲིད (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_DEPTH_SIZE;
    attribs[i++] = _this->gl_config.depth_size;

    གལ་སྲིད (_this->gl_config.stencil_size) {
        attribs[i++] = GLX_STENCIL_SIZE;
        attribs[i++] = _this->gl_config.stencil_size;
    }

    གལ་སྲིད (_this->gl_config.accum_red_size) {
        attribs[i++] = GLX_ACCUM_RED_SIZE;
        attribs[i++] = _this->gl_config.accum_red_size;
    }

    གལ་སྲིད (_this->gl_config.accum_green_size) {
        attribs[i++] = GLX_ACCUM_GREEN_SIZE;
        attribs[i++] = _this->gl_config.accum_green_size;
    }

    གལ་སྲིད (_this->gl_config.accum_blue_size) {
        attribs[i++] = GLX_ACCUM_BLUE_SIZE;
        attribs[i++] = _this->gl_config.accum_blue_size;
    }

    གལ་སྲིད (_this->gl_config.accum_alpha_size) {
        attribs[i++] = GLX_ACCUM_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.accum_alpha_size;
    }

    གལ་སྲིད (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        གལ་སྲིད (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    གལ་སྲིད (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    གལ་སྲིད (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    གལ་སྲིད (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    གལ་སྲིད (_this->gl_data->HAS_GLX_ARB_framebuffer_sRGB) {
        const var_na *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        གལ་སྲིད (srgbhint && *srgbhint) {
            གལ་སྲིད (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } དེ་མིན {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } དེ་མིན གལ་སྲིད (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    གལ་སྲིད (_this->gl_config.accelerated >= 0 &&
        _this->gl_data->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    གལ་སྲིད (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        གལ་སྲིད (X11_UseDirectColorVisuals() && _this->gl_data->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_DIRECT_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_ATTRIBUTES);

    གལ་སྲིད (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    ལོག i;
}

//get the first transparent Visual
static XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, ཧྲིལ screen)
{
    XVisualInfo *visualinfo = NULL;
    XVisualInfo vi_in;
    ཧྲིལ out_count = 0;

    vi_in.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, VisualScreenMask, &vi_in, &out_count);
    གལ་སྲིད (visualinfo != NULL) {
        ཧྲིལ i = 0;
        དོན་ལུ (i = 0; i < out_count; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            གལ་སྲིད (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_in.screen = screen;
                vi_in.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_count);
                bha_nga;
            }
        }
    }
    ལོག visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, ཧྲིལ screen, bool transparent)
{
    // 64 seems nice.
    ཧྲིལ attribs[64];
    XVisualInfo *vinfo = NULL;
    ཧྲིལ *pvistypeattr = NULL;

    གལ་སྲིད (!_this->gl_data) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        ལོག NULL;
    }

    གལ་སྲིད (_this->gl_data->glXChooseFBConfig &&
        _this->gl_data->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = NULL;
        ཧྲིལ fbcount = 0;

        X11_GL_GetAttributes(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_data->glXChooseFBConfig(display, screen, attribs, &fbcount);
        གལ་སྲིད (!framebuffer_config && (pvistypeattr != NULL)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_data->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        གལ་སྲིད (transparent) {
            // Return the first transparent Visual
            ཧྲིལ i;
            དོན་ལུ (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_data->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                གལ་སྲིད (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = NULL;
                    bha_nga;
                }
                X11_XFree(vinfo);
                vinfo = NULL;
            }
        }

        གལ་སྲིད (framebuffer_config) {
            vinfo = _this->gl_data->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    གལ་སྲིད (!vinfo) {
        X11_GL_GetAttributes(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_data->glXChooseVisual(display, screen, attribs);

        གལ་སྲིད (!vinfo && (pvistypeattr != NULL)) {
            *pvistypeattr = None;
            vinfo = _this->gl_data->glXChooseVisual(display, screen, attribs);
        }
    }

    གལ་སྲིད (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        གལ་སྲིད (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            གལ་སྲིད (visualinfo != NULL) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    གལ་སྲིད (!vinfo) {
        SDL_SetError("Couldn't find matching GLX visual");
    }
    ལོག vinfo;
}

static ཧྲིལ (*handler)(Display *, XErrorEvent *) = NULL;
static const var_na *errorHandlerOperation = NULL;
static ཧྲིལ errorBase = 0;
static ཧྲིལ errorCode = 0;
static ཧྲིལ X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    var_na *x11_error = NULL;
    var_na x11_error_locale[256];

    errorCode = e->error_code;
    གལ་སྲིད (X11_XGetErrorText(d, errorCode, x11_error_locale, parimaa_na(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    གལ་སྲིད (x11_error) {
        SDL_SetError("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } དེ་མིན {
        SDL_SetError("Could not %s: %i (Base %i)", errorHandlerOperation, errorCode, errorBase);
    }

    ལོག 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_data != NULL);
    གལ་སྲིད (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        ལོག true;
    }

    SDL_assert(_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES);
    ལོག (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_version == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_version > _this->gl_data->es_profile_max_supported_version.major || (_this->gl_config.major_version == _this->gl_data->es_profile_max_supported_version.major && _this->gl_config.minor_version > _this->gl_data->es_profile_max_supported_version.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    ཧྲིལ screen = SDL_GetDisplayDriverDataForWindow(window)->screen;
    XWindowAttributes xattr;
    XVisualInfo v, *vinfo;
    ཧྲིལ n;
    SDL_GLContext context = NULL;
    GLXContext share_context;
    const ཧྲིལ transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;

    གལ་སྲིད (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } དེ་མིན {
        share_context = NULL;
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
    གལ་སྲིད (vinfo) {
        གལ་སྲིད (_this->gl_config.major_version < 3 &&
            _this->gl_config.profile_mask == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_data->glXCreateContext(display, vinfo, share_context, True);
        } དེ་མིན {
            // max 14 attributes plus terminator
            ཧྲིལ attribs[15] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB,
                _this->gl_config.major_version,
                GLX_CONTEXT_MINOR_VERSION_ARB,
                _this->gl_config.minor_version,
                0
            };
            ཧྲིལ iattr = 4;

            // SDL profile bits match GLX profile bits
            གལ་སྲིད (_this->gl_config.profile_mask != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_MASK_ARB;
                attribs[iattr++] = _this->gl_config.profile_mask;
            }

            // SDL flags match GLX flags
            གལ་སྲིད (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            གལ་སྲིད ((_this->gl_data->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            གལ་སྲིད ((_this->gl_data->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            གལ་སྲིད ((_this->gl_data->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            གལ་སྲིད (!_this->gl_data->glXCreateContextAttribsARB) {
                SDL_SetError("OpenGL 3.0 and later are not supported by this system");
            } དེ་མིན {
                ཧྲིལ glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = NULL;
                ཧྲིལ fbcount = 0;
                ཧྲིལ *pvistypeattr = NULL;

                X11_GL_GetAttributes(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                གལ་སྲིད (_this->gl_data->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_data->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    གལ་སྲིད (!framebuffer_config && (pvistypeattr != NULL)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_data->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    གལ་སྲིད (transparent && (framebuffer_config != NULL)) {
                        ཧྲིལ i;
                        དོན་ལུ (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_temp = _this->gl_data->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            གལ་སྲིད ( vinfo_temp != NULL) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_temp);
                                གལ་སྲིད (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_data->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = NULL;
                                    X11_XFree(vinfo_temp);
                                    bha_nga;
                                }
                                X11_XFree(vinfo_temp);
                            }
                        }
                    }
                    གལ་སྲིད (framebuffer_config) {
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

    གལ་སྲིད (!context) {
        གལ་སྲིད (errorCode == Success) {
            SDL_SetError("Could not create GL context");
        }
        ལོག NULL;
    }

    གལ་སྲིད (!X11_GL_MakeCurrent(_this, window, context)) {
        X11_GL_DestroyContext(_this, context);
        ལོག NULL;
    }

    ལོག context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    Window drawable =
        (context ? window->internal->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    ཧྲིལ rc;

    གལ་སྲིད (!_this->gl_data) {
        ལོག SDL_SetError("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    errorBase = _this->gl_data->errorBase;
    errorCode = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_data->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    གལ་སྲིད (errorCode != Success) { // uhoh, an X error was thrown!
        ལོག false;              // the error handler called SDL_SetError() already.
    } དེ་མིན གལ་སྲིད (!rc) {           // glXMakeCurrent() failed without throwing an X error
        ལོག SDL_SetError("Unable to make GL context current");
    }

    ལོག true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

static ཧྲིལ swapinterval = 0;
bool X11_GL_SetSwapInterval(SDL_VideoDevice *_this, ཧྲིལ interval)
{
    bool result = false;

    གལ་སྲིད ((interval < 0) && (!_this->gl_data->HAS_GLX_EXT_swap_control_tear)) {
        ལོག SDL_SetError("Negative swap interval unsupported in this GL");
    } དེ་མིན གལ་སྲིད (_this->gl_data->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        const SDL_WindowData *windowdata = SDL_GL_GetCurrentWindow()->internal;

        Window drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        ཧྲིལ currentInterval = 0;
        X11_GL_GetSwapInterval(_this, &currentInterval);
        _this->gl_data->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_data->glXSwapIntervalEXT(display, drawable, interval);
        result = true;
        swapinterval = interval;
    } དེ་མིན གལ་སྲིད (_this->gl_data->glXSwapIntervalMESA) {
        const ཧྲིལ rc = _this->gl_data->glXSwapIntervalMESA(interval);
        གལ་སྲིད (rc == 0) {
            swapinterval = interval;
            result = true;
        } དེ་མིན {
            result = SDL_SetError("glXSwapIntervalMESA failed");
        }
    } དེ་མིན གལ་སྲིད (_this->gl_data->glXSwapIntervalSGI) {
        const ཧྲིལ rc = _this->gl_data->glXSwapIntervalSGI(interval);
        གལ་སྲིད (rc == 0) {
            swapinterval = interval;
            result = true;
        } དེ་མིན {
            result = SDL_SetError("glXSwapIntervalSGI failed");
        }
    } དེ་མིན {
        ལོག SDL_Unsupported();
    }
    ལོག result;
}

static SDL_GLSwapIntervalTearBehavior CheckSwapIntervalTearBehavior(SDL_VideoDevice *_this, Window drawable, unsigned ཧྲིལ current_val, unsigned ཧྲིལ current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    གལ་སྲིད (_this->gl_data->swap_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        གལ་སྲིད (!_this->gl_data->HAS_GLX_EXT_swap_control_tear) {
            _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } དེ་མིན {
            Display *display = _this->internal->display;
            unsigned ཧྲིལ allow_late_swap_tearing = 22;
            ཧྲིལ original_val = (ཧྲིལ) current_val;

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

            གལ་སྲིད (allow_late_swap_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                གལ་སྲིད (current_allow_late) {
                    original_val = -original_val;
                }
            } དེ་མིན གལ་སྲིད (allow_late_swap_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } དེ་མིན {  // unexpected outcome!
                _this->gl_data->swap_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_data->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    ལོག _this->gl_data->swap_interval_tear_behavior;
}


bool X11_GL_GetSwapInterval(SDL_VideoDevice *_this, ཧྲིལ *interval)
{
    གལ་སྲིད (_this->gl_data->glXSwapIntervalEXT) {
        Display *display = _this->internal->display;
        const SDL_WindowData *windowdata = SDL_GL_GetCurrentWindow()->internal;
        Window drawable = windowdata->xwindow;
        unsigned ཧྲིལ allow_late_swap_tearing = 0;
        unsigned ཧྲིལ val = 0;

        གལ་སྲིད (_this->gl_data->HAS_GLX_EXT_swap_control_tear) {
            allow_late_swap_tearing = 22;  // set this to nonsense.
            _this->gl_data->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_swap_tearing);
        }

        _this->gl_data->glXQueryDrawable(display, drawable,
                                         GLX_SWAP_INTERVAL_EXT, &val);

        *interval = (ཧྲིལ)val;

        switch (CheckSwapIntervalTearBehavior(_this, drawable, val, allow_late_swap_tearing)) {
            pak_sa SDL_SWAPINTERVALTEAR_MESA:
                *interval = (ཧྲིལ)val;  // unsigned int cast to signed that generates negative value if necessary.
                bha_nga;

            pak_sa SDL_SWAPINTERVALTEAR_NVIDIA:
            default:
                གལ་སྲིད ((allow_late_swap_tearing) && (val > 0)) {
                    *interval = -((ཧྲིལ)val);
                }
                bha_nga;
        }

        ལོག true;
    } དེ་མིན གལ་སྲིད (_this->gl_data->glXGetSwapIntervalMESA) {
        ཧྲིལ val = _this->gl_data->glXGetSwapIntervalMESA();
        གལ་སྲིད (val == GLX_BAD_CONTEXT) {
            ལོག SDL_SetError("GLX_BAD_CONTEXT");
        }
        *interval = val;
        ལོག true;
    } དེ་མིན {
        *interval = swapinterval;
        ལོག true;
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

    ལོག true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->internal->display;
    GLXContext glx_context = (GLXContext)context;

    གལ་སྲིད (!_this->gl_data) {
        ལོག true;
    }
    _this->gl_data->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    ལོག true;
}

#endif // SDL_VIDEO_OPENGL_GLX

#endif // SDL_VIDEO_DRIVER_X11
