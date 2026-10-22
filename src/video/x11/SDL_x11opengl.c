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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11xsync.h"
#అన్తర్భావ "../../SDL_hints_c.h"

// GLX implementation of SDL OpenGL support

#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
#అన్తర్భావ "SDL_x11opengles.h"

#ఒకవేళ defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD)
/*
 * IRIX doesn't have a GL library versioning system.
 * NetBSD and OpenBSD have different GL library versions depending on how
 * the library was installed.
 */
#నిర్వచించు DEFAULT_OPENGL "libGL.so"
#లేదావేళ defined(SDL_PLATFORM_MACOS)
#నిర్వచించు DEFAULT_OPENGL "/opt/X11/lib/libGL.1.dylib"
#లేకపోతే
#నిర్వచించు DEFAULT_OPENGL "libGL.so.1"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_NONE_EXT
#నిర్వచించు GLX_NONE_EXT 0x8000
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_multisample
#నిర్వచించు GLX_ARB_multisample
#నిర్వచించు GLX_SAMPLE_BUFFERS_ARB 100000
#నిర్వచించు GLX_SAMPLES_ARB        100001
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_EXT_visual_rating
#నిర్వచించు GLX_EXT_visual_rating
#నిర్వచించు GLX_VISUAL_CAVEAT_EXT         0x20
#నిర్వచించు GLX_NONE_EXT                  0x8000
#నిర్వచించు GLX_SLOW_VISUAL_EXT           0x8001
#నిర్వచించు GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_EXT_visual_info
#నిర్వచించు GLX_EXT_visual_info
#నిర్వచించు GLX_X_VISUAL_TYPE_EXT 0x22
#నిర్వచించు GLX_ప్రత్యక్ష_COLOR_EXT  0x8003
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_create_context
#నిర్వచించు GLX_ARB_create_context
#నిర్వచించు GLX_CONTEXT_MAJOR_సంస్కరణ_ARB          0x2091
#నిర్వచించు GLX_CONTEXT_MINOR_సంస్కరణ_ARB          0x2092
#నిర్వచించు GLX_CONTEXT_FLAGS_ARB                  0x2094
#నిర్వచించు GLX_CONTEXT_DEBUG_బిట్టు_ARB              0x0001
#నిర్వచించు GLX_CONTEXT_FORWARD_COMPATIBLE_బిట్టు_ARB 0x0002

// Typedef for the GL 3.0 context creation function
రకనిర్వచనం GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                        GLXFBConfig config,
                                                        GLXContext
                                                            share_context,
                                                        Bool ప్రత్యక్ష,
                                                        స్థిరరాశి పూర్ణాంకం
                                                            *attrib_list);
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_create_context_profile
#నిర్వచించు GLX_ARB_create_context_profile
#నిర్వచించు GLX_CONTEXT_PROFILE_ముసుగు_ARB              0x9126
#నిర్వచించు GLX_CONTEXT_CORE_PROFILE_బిట్టు_ARB          0x00000001
#నిర్వచించు GLX_CONTEXT_COMPATIBILITY_PROFILE_బిట్టు_ARB 0x00000002
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_create_context_robustness
#నిర్వచించు GLX_ARB_create_context_robustness
#నిర్వచించు GLX_CONTEXT_ROBUST_ACCESS_బిట్టు_ARB           0x00000004
#నిర్వచించు GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#నిర్వచించు GLX_NO_RESET_NOTIFICATION_ARB               0x8261
#నిర్వచించు GLX_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_EXT_create_context_es2_profile
#నిర్వచించు GLX_EXT_create_context_es2_profile
#నిర్వచితం_కాకపోతే GLX_CONTEXT_ES2_PROFILE_బిట్టు_EXT
#నిర్వచించు GLX_CONTEXT_ES2_PROFILE_బిట్టు_EXT 0x00000002
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_framebuffer_sRGB
#నిర్వచించు GLX_ARB_framebuffer_sRGB
#నిర్వచితం_కాకపోతే GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#నిర్వచించు GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_fbconfig_float
#నిర్వచించు GLX_ARB_fbconfig_float
#నిర్వచితం_కాకపోతే GLX_RGBA_FLOAT_TYPE_ARB
#నిర్వచించు GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే GLX_RGBA_FLOAT_బిట్టు_ARB
#నిర్వచించు GLX_RGBA_FLOAT_బిట్టు_ARB 0x00000004
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_create_context_no_error
#నిర్వచించు GLX_ARB_create_context_no_error
#నిర్వచితం_కాకపోతే GLX_CONTEXT_OPENGL_NO_ERROR_ARB
#నిర్వచించు GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_EXT_మార్పిడి_control
#నిర్వచించు GLX_మార్పిడి_INTERVAL_EXT     0x20F1
#నిర్వచించు GLX_MAX_మార్పిడి_INTERVAL_EXT 0x20F2
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_EXT_మార్పిడి_control_tear
#నిర్వచించు GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GLX_ARB_context_flush_control
#నిర్వచించు GLX_ARB_context_flush_control
#నిర్వచించు GLX_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#నిర్వచించు GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#నిర్వచించు GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#అయితే_ముగింపు

#నిర్వచించు OPENGL_REQUIRES_DLOPEN
#ఒకవేళ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
#అన్తర్భావ <dlfcn.h>
#నిర్వచించు GL_ఎక్కించు_Object(X) dlopen(X, (RTLD_NOW | RTLD_GLOBAL))
#నిర్వచించు GL_ఎక్కించు_Function  dlsym
#నిర్వచించు GL_UnloadObject  dlclose
#లేకపోతే
#నిర్వచించు GL_ఎక్కించు_Object   SDL_ఎక్కించు_Object
#నిర్వచించు GL_ఎక్కించు_Function SDL_ఎక్కించు_Function
#నిర్వచించు GL_UnloadObject SDL_UnloadObject
#అయితే_ముగింపు

స్థిర శూన్య X11_GL_InitExtensions(SDL_VideoDevice *_this);

స్థిర bool X11_GL_ఎక్కించు_Library_EGLFallback(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    X11_GL_UnloadLibrary(_this);
    _this->GL_ఎక్కించు_Library = X11_GLES_ఎక్కించు_Library;
    _this->GL_Get_Proc_చిరునామా = X11_GLES_Get_Proc_చిరునామా;
    _this->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
    _this->GL_CreateContext = X11_GLES_CreateContext;
    _this->GL_MakeCurrent = X11_GLES_MakeCurrent;
    _this->GL_సమితి_మార్పిడి_Interval = X11_GLES_సమితి_మార్పిడి_Interval;
    _this->GL_Get_మార్పిడి_Interval = X11_GLES_Get_మార్పిడి_Interval;
    _this->GL_మార్పిడి_కిటికీ = X11_GLES_మార్పిడి_కిటికీ;
    _this->GL_DestroyContext = X11_GLES_DestroyContext;
    _this->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
    తిరిగి X11_GLES_ఎక్కించు_Library(_this, మార్గం);
#లేకపోతే
    తిరిగి SDL_సమితి_Error("SDL not configured with EGL support");
#అయితే_ముగింపు
}

bool X11_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    Display *display;
    SDL_SharedObject *handle;

    ఒకవేళ (_this->gl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("OpenGL context already created");
    }

    ఒకవేళ ((_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        తిరిగి X11_GL_ఎక్కించు_Library_EGLFallback(_this, మార్గం);
    }

    // Load the OpenGL library
    ఒకవేళ (మార్గం == ఖాళీ) {
        మార్గం = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    ఒకవేళ (మార్గం == ఖాళీ) {
        మార్గం = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = GL_ఎక్కించు_Object(మార్గం);
    ఒకవేళ (!_this->gl_config.dll_handle) {
#ఒకవేళ defined(OPENGL_REQUIRES_DLOPEN) && defined(HAVE_DLOPEN)
        SDL_సమితి_Error("Failed loading %s: %s", మార్గం, dlerror());
#అయితే_ముగింపు
        తిరిగి false;
    }
    SDL_strlcpy(_this->gl_config.driver_మార్గం, మార్గం,
                SDL_arraysize(_this->gl_config.driver_మార్గం));

    // Allocate OpenGL memory
    _this->gl_దత్తాంశం =
        (నిర్మాణం SDL_GLDriver_దత్తాంశం *)SDL_calloc(1,
                                              పరిమాణం(నిర్మాణం
                                                     SDL_GLDriver_దత్తాంశం));
    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    _this->gl_దత్తాంశం->glXQueryExtension =
        (Bool(*)(Display *, పూర్ణాంకం *, పూర్ణాంకం *))
            GL_ఎక్కించు_Function(handle, "glXQueryExtension");
    _this->gl_దత్తాంశం->gl_XGet_Proc_చిరునామా =
        (__GLXextFuncPtr (*)(స్థిరరాశి GLubyte *))
            GL_ఎక్కించు_Function(handle, "glXGetProcAddressARB");
    _this->gl_దత్తాంశం->glXChooseVisual =
        (XVisualInfo * (*)(Display *, పూర్ణాంకం, పూర్ణాంకం *))
            X11_GL_Get_Proc_చిరునామా(_this, "glXChooseVisual");
    _this->gl_దత్తాంశం->glXCreateContext =
        (GLXContext(*)(Display *, XVisualInfo *, GLXContext, పూర్ణాంకం))
            X11_GL_Get_Proc_చిరునామా(_this, "glXCreateContext");
    _this->gl_దత్తాంశం->glXDestroyContext =
        (శూన్య (*)(Display *, GLXContext))
            X11_GL_Get_Proc_చిరునామా(_this, "glXDestroyContext");
    _this->gl_దత్తాంశం->glXMakeCurrent =
        (పూర్ణాంకం (*)(Display *, GLXDrawable, GLXContext))
            X11_GL_Get_Proc_చిరునామా(_this, "glXMakeCurrent");
    _this->gl_దత్తాంశం->glXSwapBuffers =
        (శూన్య (*)(Display *, GLXDrawable))
            X11_GL_Get_Proc_చిరునామా(_this, "glXSwapBuffers");
    _this->gl_దత్తాంశం->glXQueryDrawable =
        (శూన్య (*)(Display *, GLXDrawable, పూర్ణాంకం, గుర్తులేని పూర్ణాంకం *))
            X11_GL_Get_Proc_చిరునామా(_this, "glXQueryDrawable");

    ఒకవేళ (!_this->gl_దత్తాంశం->glXQueryExtension ||
        !_this->gl_దత్తాంశం->glXChooseVisual ||
        !_this->gl_దత్తాంశం->glXCreateContext ||
        !_this->gl_దత్తాంశం->glXDestroyContext ||
        !_this->gl_దత్తాంశం->glXMakeCurrent ||
        !_this->gl_దత్తాంశం->glXSwapBuffers) {
        తిరిగి SDL_సమితి_Error("Could not retrieve OpenGL functions");
    }

    display = _this->అంతర్గత->display;
    ఒకవేళ (!_this->gl_దత్తాంశం->glXQueryExtension(display, &_this->gl_దత్తాంశం->error_పునాది, &_this->gl_దత్తాంశం->event_పునాది)) {
        తిరిగి SDL_సమితి_Error("GLX is not supported");
    }

    _this->gl_దత్తాంశం->మార్పిడి_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNTESTED;

    // Initialize extensions
    /* See lengthy comment about the inc/dec in
       ../windows/SDL_windowsopengl.c. */
    ++_this->gl_config.driver_loaded;
    X11_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    /* If we need a GL ES context and there's no
     * GLX_EXT_create_context_es2_profile extension, switch over to X11_GLES functions
     */
    ఒకవేళ (((_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) &&
        X11_GL_UseEGL(_this)) {
        తిరిగి X11_GL_ఎక్కించు_Library_EGLFallback(_this, ఖాళీ);
    }

    తిరిగి true;
}

SDL_Function_సూచిక X11_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    ఒకవేళ (_this->gl_దత్తాంశం->gl_XGet_Proc_చిరునామా) {
        తిరిగి _this->gl_దత్తాంశం->gl_XGet_Proc_చిరునామా((స్థిరరాశి GLubyte *)proc);
    }
    తిరిగి GL_ఎక్కించు_Function(_this->gl_config.dll_handle, proc);
}

శూన్య X11_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* Don't actually unload the library, since it may have registered
     * X11 shutdown hooks, per the notes at:
     * http://dri.sourceforge.net/doc/DRIuserguide.html
     */
#ఒకవేళ 0
    GL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ఖాళీ;
#అయితే_ముగింపు

    // Free OpenGL memory
    SDL_free(_this->gl_దత్తాంశం);
    _this->gl_దత్తాంశం = ఖాళీ;
}

స్థిర bool HasExtension(స్థిరరాశి అక్షరం *extension, స్థిరరాశి అక్షరం *extensions)
{
    స్థిరరాశి అక్షరం *ప్రారంభం;
    స్థిరరాశి అక్షరం *where, *terminator;

    ఒకవేళ (!extensions) {
        తిరిగి false;
    }

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ఒకవేళ (where || *extension == '\0') {
        తిరిగి false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    ప్రారంభం = extensions;

    కొరకు (;;) {
        where = SDL_strstr(ప్రారంభం, extension);
        ఒకవేళ (!where) {
            ఆపు;
        }

        terminator = where + SDL_strlen(extension);
        ఒకవేళ (where == ప్రారంభం || *(where - 1) == ' ') {
            ఒకవేళ (*terminator == ' ' || *terminator == '\0') {
                తిరిగి true;
            }
        }

        ప్రారంభం = terminator;
    }
    తిరిగి false;
}

స్థిర శూన్య X11_GL_InitExtensions(SDL_VideoDevice *_this)
{
    Display *display = _this->అంతర్గత->display;
    స్థిరరాశి పూర్ణాంకం screen = DefaultScreen(display);
    XVisualInfo *vinfo = ఖాళీ;
    కిటికీ_2 w = 0;
    GLXContext prev_ctx = ఖాళీ;
    GLXDrawable prev_drawable = 0;
    GLXContext context = ఖాళీ;
    స్థిరరాశి అక్షరం *(*glXQueryExtensionsStringFunc)(Display *, పూర్ణాంకం);
    స్థిరరాశి అక్షరం *extensions;

    vinfo = X11_GL_GetVisual(_this, display, screen, false);
    ఒకవేళ (vinfo) {
        GLXContext (*glXGetCurrentContextFunc)(శూన్య) =
            (GLXContext(*)(శూన్య))
                X11_GL_Get_Proc_చిరునామా(_this, "glXGetCurrentContext");

        GLXDrawable (*glXGetCurrentDrawableFunc)(శూన్య) =
            (GLXDrawable(*)(శూన్య))
                X11_GL_Get_Proc_చిరునామా(_this, "glXGetCurrentDrawable");

        ఒకవేళ (glXGetCurrentContextFunc && glXGetCurrentDrawableFunc) {
            XSet_కిటికీ_లక్షణాలు xattr;
            prev_ctx = glXGetCurrentContextFunc();
            prev_drawable = glXGetCurrentDrawableFunc();

            xattr.background_pixel = 0;
            xattr.border_pixel = 0;
            xattr.colormap =
                X11_XCreateColormap(display, మూలం_కిటికీ(display, screen),
                                    vinfo->visual, AllocNone);
            w = X11_XCreate_కిటికీ(display, మూలం_కిటికీ(display, screen), 0, 0,
                                  32, 32, 0, vinfo->లోతు_2, ఆదానం_Output, vinfo->visual,
                                  (CWBackPixel | CWBorderPixel | CWColormap), &xattr);

            context = _this->gl_దత్తాంశం->glXCreateContext(display, vinfo,
                                                       ఖాళీ, True);
            ఒకవేళ (context) {
                _this->gl_దత్తాంశం->glXMakeCurrent(display, w, context);
            }
        }

        X11_XFree(vinfo);
    }

    glXQueryExtensionsStringFunc =
        (స్థిరరాశి అక్షరం *(*)(Display *, పూర్ణాంకం))X11_GL_Get_Proc_చిరునామా(_this,
                                                               "glXQueryExtensionsString");
    ఒకవేళ (glXQueryExtensionsStringFunc) {
        extensions = glXQueryExtensionsStringFunc(display, screen);
    } లేకపోతే {
        extensions = ఖాళీ;
    }

    // Check for GLX_EXT_swap_control(_tear)
    _this->gl_దత్తాంశం->HAS_GLX_EXT_మార్పిడి_control_tear = false;
    ఒకవేళ (HasExtension("GLX_EXT_swap_control", extensions)) {
        _this->gl_దత్తాంశం->glXSwapIntervalEXT =
            (శూన్య (*)(Display *, GLXDrawable, పూర్ణాంకం))
                X11_GL_Get_Proc_చిరునామా(_this, "glXSwapIntervalEXT");
        ఒకవేళ (HasExtension("GLX_EXT_swap_control_tear", extensions)) {
            _this->gl_దత్తాంశం->HAS_GLX_EXT_మార్పిడి_control_tear = true;
        }
    }

    // Check for GLX_MESA_swap_control
    ఒకవేళ (HasExtension("GLX_MESA_swap_control", extensions)) {
        _this->gl_దత్తాంశం->glXSwapIntervalMESA =
            (పూర్ణాంకం (*)(పూర్ణాంకం))X11_GL_Get_Proc_చిరునామా(_this, "glXSwapIntervalMESA");
        _this->gl_దత్తాంశం->gl_XGet_మార్పిడి_Interval_MESA =
            (పూర్ణాంకం (*)(శూన్య))X11_GL_Get_Proc_చిరునామా(_this,
                                                 "glXGetSwapIntervalMESA");
    }

    // Check for GLX_SGI_swap_control
    ఒకవేళ (HasExtension("GLX_SGI_swap_control", extensions)) {
        _this->gl_దత్తాంశం->glXSwapIntervalSGI =
            (పూర్ణాంకం (*)(పూర్ణాంకం))X11_GL_Get_Proc_చిరునామా(_this, "glXSwapIntervalSGI");
    }

    // Check for GLX_ARB_create_context
    ఒకవేళ (HasExtension("GLX_ARB_create_context", extensions)) {
        _this->gl_దత్తాంశం->glXCreateContextAttribsARB =
            (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, స్థిరరాశి పూర్ణాంకం *))
                X11_GL_Get_Proc_చిరునామా(_this, "glXCreateContextAttribsARB");
        _this->gl_దత్తాంశం->glXChooseFBConfig =
            (GLXFBConfig * (*)(Display *, పూర్ణాంకం, స్థిరరాశి పూర్ణాంకం *, పూర్ణాంకం *))
                X11_GL_Get_Proc_చిరునామా(_this, "glXChooseFBConfig");
        _this->gl_దత్తాంశం->glXGetVisualFromFBConfig =
            (XVisualInfo * (*)(Display *, GLXFBConfig))
                X11_GL_Get_Proc_చిరునామా(_this, "glXGetVisualFromFBConfig");
    }

    // Check for GLX_EXT_visual_rating
    ఒకవేళ (HasExtension("GLX_EXT_visual_rating", extensions)) {
        _this->gl_దత్తాంశం->HAS_GLX_EXT_visual_rating = true;
    }

    // Check for GLX_EXT_visual_info
    ఒకవేళ (HasExtension("GLX_EXT_visual_info", extensions)) {
        _this->gl_దత్తాంశం->HAS_GLX_EXT_visual_info = true;
    }

    // Check for GLX_EXT_create_context_es2_profile
    ఒకవేళ (HasExtension("GLX_EXT_create_context_es2_profile", extensions)) {
        // this wants to call glGetString(), so it needs a context.
        // !!! FIXME: it would be nice not to make a context here though!
        ఒకవేళ (context) {
            SDL_GL_DeduceMaxSupportedESProfile(
                &_this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.major,
                &_this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.minor);
        }
    }

    // Check for GLX_ARB_context_flush_control
    ఒకవేళ (HasExtension("GLX_ARB_context_flush_control", extensions)) {
        _this->gl_దత్తాంశం->HAS_GLX_ARB_context_flush_control = true;
    }

    // Check for GLX_ARB_create_context_robustness
    ఒకవేళ (HasExtension("GLX_ARB_create_context_robustness", extensions)) {
        _this->gl_దత్తాంశం->HAS_GLX_ARB_create_context_robustness = true;
    }

    // Check for GLX_ARB_create_context_no_error
    ఒకవేళ (HasExtension("GLX_ARB_create_context_no_error", extensions)) {
        _this->gl_దత్తాంశం->HAS_GLX_ARB_create_context_no_error = true;
    }

    // Check for GLX_ARB_framebuffer_sRGB
    ఒకవేళ (HasExtension("GLX_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_దత్తాంశం->HAS_GLX_ARB_framebuffer_sRGB = true;
    } లేకపోతే ఒకవేళ (HasExtension("GLX_EXT_framebuffer_sRGB", extensions)) {   // same thing.
        _this->gl_దత్తాంశం->HAS_GLX_ARB_framebuffer_sRGB = true;
    }

    ఒకవేళ (context) {
        _this->gl_దత్తాంశం->glXMakeCurrent(display, None, ఖాళీ);
        _this->gl_దత్తాంశం->glXDestroyContext(display, context);
        ఒకవేళ (prev_ctx && prev_drawable) {
            _this->gl_దత్తాంశం->glXMakeCurrent(display, prev_drawable, prev_ctx);
        }
    }

    ఒకవేళ (w) {
        X11_XDestroy_కిటికీ(display, w);
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
స్థిర పూర్ణాంకం X11_GL_Get_లక్షణాలు(SDL_VideoDevice *_this, Display *display, పూర్ణాంకం screen, పూర్ణాంకం *attribs, పూర్ణాంకం కొలత, Bool for_FBConfig, పూర్ణాంకం **_pvistypeattr, bool transparent)
{
    పూర్ణాంకం i = 0;
    స్థిరరాశి పూర్ణాంకం MAX_లక్షణాలు = 64;
    పూర్ణాంకం *pvistypeattr = ఖాళీ;

    // assert buffer is large enough to hold all SDL attributes.
    SDL_assert(కొలత >= MAX_లక్షణాలు);

    // Setup our GLX attributes according to the gl_config.
    ఒకవేళ (for_FBConfig) {
        attribs[i++] = GLX_RENDER_TYPE;
        ఒకవేళ (_this->gl_config.floatbuffers) {
            attribs[i++] = GLX_RGBA_FLOAT_బిట్టు_ARB;
        } లేకపోతే {
            attribs[i++] = GLX_RGBA_బిట్టు;
        }
    } లేకపోతే {
        attribs[i++] = GLX_RGBA;
    }
    attribs[i++] = GLX_RED_కొలత;
    attribs[i++] = _this->gl_config.red_కొలత;
    attribs[i++] = GLX_GREEN_కొలత;
    attribs[i++] = _this->gl_config.green_కొలత;
    attribs[i++] = GLX_BLUE_కొలత;
    attribs[i++] = _this->gl_config.blue_కొలత;

    ఒకవేళ (_this->gl_config.alpha_కొలత) {
        attribs[i++] = GLX_ALPHA_కొలత;
        attribs[i++] = _this->gl_config.alpha_కొలత;
    }

    ఒకవేళ (_this->gl_config.double_బఫరు) {
        attribs[i++] = GLX_DOUBLEBUFFER;
        ఒకవేళ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    attribs[i++] = GLX_లోతు_కొలత;
    attribs[i++] = _this->gl_config.లోతు_కొలత;

    ఒకవేళ (_this->gl_config.stencil_కొలత) {
        attribs[i++] = GLX_STENCIL_కొలత;
        attribs[i++] = _this->gl_config.stencil_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_red_కొలత) {
        attribs[i++] = GLX_ACCUM_RED_కొలత;
        attribs[i++] = _this->gl_config.accum_red_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_green_కొలత) {
        attribs[i++] = GLX_ACCUM_GREEN_కొలత;
        attribs[i++] = _this->gl_config.accum_green_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_blue_కొలత) {
        attribs[i++] = GLX_ACCUM_BLUE_కొలత;
        attribs[i++] = _this->gl_config.accum_blue_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_alpha_కొలత) {
        attribs[i++] = GLX_ACCUM_ALPHA_కొలత;
        attribs[i++] = _this->gl_config.accum_alpha_కొలత;
    }

    ఒకవేళ (_this->gl_config.stereo) {
        attribs[i++] = GLX_STEREO;
        ఒకవేళ (for_FBConfig) {
            attribs[i++] = True;
        }
    }

    ఒకవేళ (_this->gl_config.multisamplebuffers) {
        attribs[i++] = GLX_SAMPLE_BUFFERS_ARB;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    ఒకవేళ (_this->gl_config.multisamplesamples) {
        attribs[i++] = GLX_SAMPLES_ARB;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    ఒకవేళ (_this->gl_config.floatbuffers) {
        attribs[i++] = GLX_RENDER_TYPE;
        attribs[i++] = GLX_RGBA_FLOAT_TYPE_ARB;
    }

    ఒకవేళ (_this->gl_దత్తాంశం->HAS_GLX_ARB_framebuffer_sRGB) {
        స్థిరరాశి అక్షరం *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ఒకవేళ (srgbhint && *srgbhint) {
            ఒకవేళ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } లేకపోతే {
                attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                attribs[i++] = SDL_GetStringBoolean(srgbhint, false) ? True : False;  // always needed, for_FBConfig or not!
            }
        } లేకపోతే ఒకవేళ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            attribs[i++] = GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            attribs[i++] = True; // always needed, for_FBConfig or not!
        }
    }

    ఒకవేళ (_this->gl_config.accelerated >= 0 &&
        _this->gl_దత్తాంశం->HAS_GLX_EXT_visual_rating) {
        attribs[i++] = GLX_VISUAL_CAVEAT_EXT;
        attribs[i++] = _this->gl_config.accelerated ? GLX_NONE_EXT : GLX_SLOW_VISUAL_EXT;
    }

    // Un-wanted when we request a transparent buffer
    ఒకవేళ (!transparent) {
        /* If we're supposed to use DirectColor visuals, and we've got the
           EXT_visual_info extension, then add GLX_X_VISUAL_TYPE_EXT. */
        ఒకవేళ (X11_Use_ప్రత్యక్ష_Color_Visuals() && _this->gl_దత్తాంశం->HAS_GLX_EXT_visual_info) {
            pvistypeattr = &attribs[i];
            attribs[i++] = GLX_X_VISUAL_TYPE_EXT;
            attribs[i++] = GLX_ప్రత్యక్ష_COLOR_EXT;
        }
    }

    attribs[i++] = None;

    SDL_assert(i <= MAX_లక్షణాలు);

    ఒకవేళ (_pvistypeattr) {
        *_pvistypeattr = pvistypeattr;
    }

    తిరిగి i;
}

//get the first transparent Visual
స్థిర XVisualInfo *X11_GL_GetTransparentVisualInfo(Display *display, పూర్ణాంకం screen)
{
    XVisualInfo *visualinfo = ఖాళీ;
    XVisualInfo vi_లోపల;
    పూర్ణాంకం బహిర్గతం_లెక్క = 0;

    vi_లోపల.screen = screen;
    visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ముసుగు, &vi_లోపల, &బహిర్గతం_లెక్క);
    ఒకవేళ (visualinfo != ఖాళీ) {
        పూర్ణాంకం i = 0;
        కొరకు (i = 0; i < బహిర్గతం_లెక్క; i++) {
            XVisualInfo *v = &visualinfo[i];
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
            ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                vi_లోపల.screen = screen;
                vi_లోపల.visualid = v->visualid;
                X11_XFree(visualinfo);
                visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ముసుగు | VisualIDMask, &vi_లోపల, &బహిర్గతం_లెక్క);
                ఆపు;
            }
        }
    }
    తిరిగి visualinfo;
}

XVisualInfo *X11_GL_GetVisual(SDL_VideoDevice *_this, Display *display, పూర్ణాంకం screen, bool transparent)
{
    // 64 seems nice.
    పూర్ణాంకం attribs[64];
    XVisualInfo *vinfo = ఖాళీ;
    పూర్ణాంకం *pvistypeattr = ఖాళీ;

    ఒకవేళ (!_this->gl_దత్తాంశం) {
        // The OpenGL library wasn't loaded, SDL_GetError() should have info
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (_this->gl_దత్తాంశం->glXChooseFBConfig &&
        _this->gl_దత్తాంశం->glXGetVisualFromFBConfig) {
        GLXFBConfig *framebuffer_config = ఖాళీ;
        పూర్ణాంకం fbcount = 0;

        X11_GL_Get_లక్షణాలు(_this, display, screen, attribs, 64, true, &pvistypeattr, transparent);
        framebuffer_config = _this->gl_దత్తాంశం->glXChooseFBConfig(display, screen, attribs, &fbcount);
        ఒకవేళ (!framebuffer_config && (pvistypeattr != ఖాళీ)) {
            *pvistypeattr = None;
            framebuffer_config = _this->gl_దత్తాంశం->glXChooseFBConfig(display, screen, attribs, &fbcount);
        }

        ఒకవేళ (transparent) {
            // Return the first transparent Visual
            పూర్ణాంకం i;
            కొరకు (i = 0; i < fbcount; i++) {
                Uint32 format;
                vinfo = _this->gl_దత్తాంశం->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
                ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    X11_XFree(framebuffer_config);
                    framebuffer_config = ఖాళీ;
                    ఆపు;
                }
                X11_XFree(vinfo);
                vinfo = ఖాళీ;
            }
        }

        ఒకవేళ (framebuffer_config) {
            vinfo = _this->gl_దత్తాంశం->glXGetVisualFromFBConfig(display, framebuffer_config[0]);
        }

        X11_XFree(framebuffer_config);
    }

    ఒకవేళ (!vinfo) {
        X11_GL_Get_లక్షణాలు(_this, display, screen, attribs, 64, false, &pvistypeattr, transparent);
        vinfo = _this->gl_దత్తాంశం->glXChooseVisual(display, screen, attribs);

        ఒకవేళ (!vinfo && (pvistypeattr != ఖాళీ)) {
            *pvistypeattr = None;
            vinfo = _this->gl_దత్తాంశం->glXChooseVisual(display, screen, attribs);
        }
    }

    ఒకవేళ (transparent && vinfo) {
        Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo);
        ఒకవేళ (!SDL_ISPIXELFORMAT_ALPHA(format)) {
            // not transparent!
            XVisualInfo *visualinfo = X11_GL_GetTransparentVisualInfo(display, screen);
            ఒకవేళ (visualinfo != ఖాళీ) {
                X11_XFree(vinfo);
                vinfo = visualinfo;
            }
        }
    }

    ఒకవేళ (!vinfo) {
        SDL_సమితి_Error("Couldn't find matching GLX visual");
    }
    తిరిగి vinfo;
}

స్థిర పూర్ణాంకం (*handler)(Display *, XErrorEvent *) = ఖాళీ;
స్థిర స్థిరరాశి అక్షరం *errorHandlerOperation = ఖాళీ;
స్థిర పూర్ణాంకం error_పునాది = 0;
స్థిర పూర్ణాంకం error_సంకేతం_2 = 0;
స్థిర పూర్ణాంకం X11_GL_ErrorHandler(Display *d, XErrorEvent *e)
{
    అక్షరం *x11_error = ఖాళీ;
    అక్షరం x11_error_locale[256];

    error_సంకేతం_2 = e->error_సంకేతం;
    ఒకవేళ (X11_XGet_Error_పాఠ్యం(d, error_సంకేతం_2, x11_error_locale, పరిమాణం(x11_error_locale)) == Success) {
        x11_error = SDL_iconv_string("UTF-8", "", x11_error_locale, SDL_strlen(x11_error_locale) + 1);
    }

    ఒకవేళ (x11_error) {
        SDL_సమితి_Error("Could not %s: %s", errorHandlerOperation, x11_error);
        SDL_free(x11_error);
    } లేకపోతే {
        SDL_సమితి_Error("Could not %s: %i (Base %i)", errorHandlerOperation, error_సంకేతం_2, error_పునాది);
    }

    తిరిగి 0;
}

bool X11_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_దత్తాంశం != ఖాళీ);
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // use of EGL has been requested, even for desktop GL
        తిరిగి true;
    }

    SDL_assert(_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES);
    తిరిగి (SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) || _this->gl_config.major_సంస్కరణ == 1 // No GLX extension for OpenGL ES 1.x profiles.
            || _this->gl_config.major_సంస్కరణ > _this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.major || (_this->gl_config.major_సంస్కరణ == _this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.major && _this->gl_config.minor_సంస్కరణ > _this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.minor));
}

SDL_GLContext X11_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    పూర్ణాంకం screen = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ)->screen;
    XWindow_లక్షణాలు xattr;
    XVisualInfo v, *vinfo;
    పూర్ణాంకం n;
    SDL_GLContext context = ఖాళీ;
    GLXContext share_context;
    స్థిరరాశి పూర్ణాంకం transparent = (కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) ? true : false;

    ఒకవేళ (_this->gl_config.share_with_current_context) {
        share_context = (GLXContext)SDL_GL_GetCurrentContext();
    } లేకపోతే {
        share_context = ఖాళీ;
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "create GL context";
    error_పునాది = _this->gl_దత్తాంశం->error_పునాది;
    error_సంకేతం_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    X11_XGet_కిటికీ_లక్షణాలు(display, దత్తాంశం->xwindow, &xattr);
    v.screen = screen;
    v.visualid = X11_XVisualIDFromVisual(xattr.visual);
    vinfo = X11_XGetVisualInfo(display, Visual_Screen_ముసుగు | VisualIDMask, &v, &n);
    ఒకవేళ (vinfo) {
        ఒకవేళ (_this->gl_config.major_సంస్కరణ < 3 &&
            _this->gl_config.profile_ముసుగు == 0 &&
            _this->gl_config.flags == 0 && !transparent) {
            // Create legacy context
            context =
                (SDL_GLContext)_this->gl_దత్తాంశం->glXCreateContext(display, vinfo, share_context, True);
        } లేకపోతే {
            // max 14 attributes plus terminator
            పూర్ణాంకం attribs[15] = {
                GLX_CONTEXT_MAJOR_సంస్కరణ_ARB,
                _this->gl_config.major_సంస్కరణ,
                GLX_CONTEXT_MINOR_సంస్కరణ_ARB,
                _this->gl_config.minor_సంస్కరణ,
                0
            };
            పూర్ణాంకం iattr = 4;

            // SDL profile bits match GLX profile bits
            ఒకవేళ (_this->gl_config.profile_ముసుగు != 0) {
                attribs[iattr++] = GLX_CONTEXT_PROFILE_ముసుగు_ARB;
                attribs[iattr++] = _this->gl_config.profile_ముసుగు;
            }

            // SDL flags match GLX flags
            ఒకవేళ (_this->gl_config.flags != 0) {
                attribs[iattr++] = GLX_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if glx extension is available and not the default setting
            ఒకవేళ ((_this->gl_దత్తాంశం->HAS_GLX_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] =
                    _this->gl_config.release_behavior ? GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if glx extension is available and not the default setting
            ఒకవేళ ((_this->gl_దత్తాంశం->HAS_GLX_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] =
                    _this->gl_config.reset_notification ? GLX_LOSE_CONTEXT_ON_RESET_ARB : GLX_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if glx extension is available and not the default setting
            ఒకవేళ ((_this->gl_దత్తాంశం->HAS_GLX_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = GLX_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Get a pointer to the context creation function for GL 3.0
            ఒకవేళ (!_this->gl_దత్తాంశం->glXCreateContextAttribsARB) {
                SDL_సమితి_Error("OpenGL 3.0 and later are not supported by this system");
            } లేకపోతే {
                పూర్ణాంకం glxAttribs[64];

                // Create a GL 3.x context
                GLXFBConfig *framebuffer_config = ఖాళీ;
                పూర్ణాంకం fbcount = 0;
                పూర్ణాంకం *pvistypeattr = ఖాళీ;

                X11_GL_Get_లక్షణాలు(_this, display, screen, glxAttribs, 64, true, &pvistypeattr, transparent);

                ఒకవేళ (_this->gl_దత్తాంశం->glXChooseFBConfig) {
                    framebuffer_config = _this->gl_దత్తాంశం->glXChooseFBConfig(display,
                                                                           DefaultScreen(display), glxAttribs,
                                                                           &fbcount);

                    ఒకవేళ (!framebuffer_config && (pvistypeattr != ఖాళీ)) {
                        *pvistypeattr = None;
                        framebuffer_config = _this->gl_దత్తాంశం->glXChooseFBConfig(display,
                                                                               DefaultScreen(display), glxAttribs,
                                                                               &fbcount);
                    }

                    ఒకవేళ (transparent && (framebuffer_config != ఖాళీ)) {
                        పూర్ణాంకం i;
                        కొరకు (i = 0; i < fbcount; i++) {
                            XVisualInfo *vinfo_తాత్కాలిక = _this->gl_దత్తాంశం->glXGetVisualFromFBConfig(display, framebuffer_config[i]);
                            ఒకవేళ ( vinfo_తాత్కాలిక != ఖాళీ) {
                                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, vinfo_తాత్కాలిక);
                                ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(format)) {
                                    // found!
                                    context = (SDL_GLContext)_this->gl_దత్తాంశం->glXCreateContextAttribsARB(display,
                                                                                                        framebuffer_config[i],
                                                                                                        share_context, True, attribs);
                                    X11_XFree(framebuffer_config);
                                    framebuffer_config = ఖాళీ;
                                    X11_XFree(vinfo_తాత్కాలిక);
                                    ఆపు;
                                }
                                X11_XFree(vinfo_తాత్కాలిక);
                            }
                        }
                    }
                    ఒకవేళ (framebuffer_config) {
                        context = (SDL_GLContext)_this->gl_దత్తాంశం->glXCreateContextAttribsARB(display,
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

    ఒకవేళ (!context) {
        ఒకవేళ (error_సంకేతం_2 == Success) {
            SDL_సమితి_Error("Could not create GL context");
        }
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!X11_GL_MakeCurrent(_this, కిటికీ, context)) {
        X11_GL_DestroyContext(_this, context);
        తిరిగి ఖాళీ;
    }

    తిరిగి context;
}

bool X11_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    Display *display = _this->అంతర్గత->display;
    కిటికీ_2 drawable =
        (context ? కిటికీ->అంతర్గత->xwindow : None);
    GLXContext glx_context = (GLXContext)context;
    పూర్ణాంకం rc;

    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("OpenGL not initialized");
    }

    // We do this to create a clean separation between X and GLX errors.
    X11_XSync(display, False);
    errorHandlerOperation = "make GL context current";
    error_పునాది = _this->gl_దత్తాంశం->error_పునాది;
    error_సంకేతం_2 = Success;
    handler = X11_XSetErrorHandler(X11_GL_ErrorHandler);
    rc = _this->gl_దత్తాంశం->glXMakeCurrent(display, drawable, glx_context);
    X11_XSetErrorHandler(handler);

    ఒకవేళ (error_సంకేతం_2 != Success) { // uhoh, an X error was thrown!
        తిరిగి false;              // the error handler called SDL_SetError() already.
    } లేకపోతే ఒకవేళ (!rc) {           // glXMakeCurrent() failed without throwing an X error
        తిరిగి SDL_సమితి_Error("Unable to make GL context current");
    }

    తిరిగి true;
}

/*
   0 is a valid argument to glXSwapInterval(MESA|EXT) and setting it to 0
   will undo the effect of a previous call with a value that is greater
   than zero (or at least that is what the docs say). OTOH, 0 is an invalid
   argument to glXSwapIntervalSGI and it returns an error if you call it
   with 0 as an argument.
*/

స్థిర పూర్ణాంకం swapinterval = 0;
bool X11_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    bool ఫలితం = false;

    ఒకవేళ ((interval < 0) && (!_this->gl_దత్తాంశం->HAS_GLX_EXT_మార్పిడి_control_tear)) {
        తిరిగి SDL_సమితి_Error("Negative swap interval unsupported in this GL");
    } లేకపోతే ఒకవేళ (_this->gl_దత్తాంశం->glXSwapIntervalEXT) {
        Display *display = _this->అంతర్గత->display;
        స్థిరరాశి SDL_కిటికీ_దత్తాంశం *windowdata = SDL_GL_Get_Current_కిటికీ()->అంతర్గత;

        కిటికీ_2 drawable = windowdata->xwindow;

        /*
         * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
         * and will be fixed in a future release (probably 319.xx).
         *
         * There's a bug where glXSetSwapIntervalEXT ignores updates because
         * it has the wrong value cached. To work around it, we just run a no-op
         * update to the current value.
         */
        పూర్ణాంకం currentInterval = 0;
        X11_GL_Get_మార్పిడి_Interval(_this, &currentInterval);
        _this->gl_దత్తాంశం->glXSwapIntervalEXT(display, drawable, currentInterval);
        _this->gl_దత్తాంశం->glXSwapIntervalEXT(display, drawable, interval);
        ఫలితం = true;
        swapinterval = interval;
    } లేకపోతే ఒకవేళ (_this->gl_దత్తాంశం->glXSwapIntervalMESA) {
        స్థిరరాశి పూర్ణాంకం rc = _this->gl_దత్తాంశం->glXSwapIntervalMESA(interval);
        ఒకవేళ (rc == 0) {
            swapinterval = interval;
            ఫలితం = true;
        } లేకపోతే {
            ఫలితం = SDL_సమితి_Error("glXSwapIntervalMESA failed");
        }
    } లేకపోతే ఒకవేళ (_this->gl_దత్తాంశం->glXSwapIntervalSGI) {
        స్థిరరాశి పూర్ణాంకం rc = _this->gl_దత్తాంశం->glXSwapIntervalSGI(interval);
        ఒకవేళ (rc == 0) {
            swapinterval = interval;
            ఫలితం = true;
        } లేకపోతే {
            ఫలితం = SDL_సమితి_Error("glXSwapIntervalSGI failed");
        }
    } లేకపోతే {
        తిరిగి SDL_Unsupported();
    }
    తిరిగి ఫలితం;
}

స్థిర SDL_GLSwapIntervalTearBehavior Check_మార్పిడి_Interval_Tear_Behavior(SDL_VideoDevice *_this, కిటికీ_2 drawable, గుర్తులేని పూర్ణాంకం current_val, గుర్తులేని పూర్ణాంకం current_allow_late)
{
    /* Mesa and Nvidia interpret GLX_EXT_swap_control_tear differently, as of this writing, so
        figure out which behavior we have.
       Technical details: https://github.com/libsdl-org/SDL/issues/8004#issuecomment-1819603282 */
    ఒకవేళ (_this->gl_దత్తాంశం->మార్పిడి_interval_tear_behavior == SDL_SWAPINTERVALTEAR_UNTESTED) {
        ఒకవేళ (!_this->gl_దత్తాంశం->HAS_GLX_EXT_మార్పిడి_control_tear) {
            _this->gl_దత్తాంశం->మార్పిడి_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
        } లేకపోతే {
            Display *display = _this->అంతర్గత->display;
            గుర్తులేని పూర్ణాంకం allow_late_మార్పిడి_tearing = 22;
            పూర్ణాంకం original_val = (పూర్ణాంకం) current_val;

            /*
             * This is a workaround for a bug in NVIDIA drivers. Bug has been reported
             * and will be fixed in a future release (probably 319.xx).
             *
             * There's a bug where glXSetSwapIntervalEXT ignores updates because
             * it has the wrong value cached. To work around it, we just run a no-op
             * update to the current value.
             */
            _this->gl_దత్తాంశం->glXSwapIntervalEXT(display, drawable, current_val);

            // set it to no swap interval and see how it affects GLX_LATE_SWAPS_TEAR_EXT...
            _this->gl_దత్తాంశం->glXSwapIntervalEXT(display, drawable, 0);
            _this->gl_దత్తాంశం->glXQueryDrawable(display, drawable, GLX_LATE_SWAPS_TEAR_EXT, &allow_late_మార్పిడి_tearing);

            ఒకవేళ (allow_late_మార్పిడి_tearing == 0) { // GLX_LATE_SWAPS_TEAR_EXT says whether late swapping is currently in use
                _this->gl_దత్తాంశం->మార్పిడి_interval_tear_behavior = SDL_SWAPINTERVALTEAR_NVIDIA;
                ఒకవేళ (current_allow_late) {
                    original_val = -original_val;
                }
            } లేకపోతే ఒకవేళ (allow_late_మార్పిడి_tearing == 1) {  // GLX_LATE_SWAPS_TEAR_EXT says whether the Drawable can use late swapping at all
                _this->gl_దత్తాంశం->మార్పిడి_interval_tear_behavior = SDL_SWAPINTERVALTEAR_MESA;
            } లేకపోతే {  // unexpected outcome!
                _this->gl_దత్తాంశం->మార్పిడి_interval_tear_behavior = SDL_SWAPINTERVALTEAR_UNKNOWN;
            }

            // set us back to what it was originally...
            _this->gl_దత్తాంశం->glXSwapIntervalEXT(display, drawable, original_val);
        }
    }

    తిరిగి _this->gl_దత్తాంశం->మార్పిడి_interval_tear_behavior;
}


bool X11_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    ఒకవేళ (_this->gl_దత్తాంశం->glXSwapIntervalEXT) {
        Display *display = _this->అంతర్గత->display;
        స్థిరరాశి SDL_కిటికీ_దత్తాంశం *windowdata = SDL_GL_Get_Current_కిటికీ()->అంతర్గత;
        కిటికీ_2 drawable = windowdata->xwindow;
        గుర్తులేని పూర్ణాంకం allow_late_మార్పిడి_tearing = 0;
        గుర్తులేని పూర్ణాంకం val = 0;

        ఒకవేళ (_this->gl_దత్తాంశం->HAS_GLX_EXT_మార్పిడి_control_tear) {
            allow_late_మార్పిడి_tearing = 22;  // set this to nonsense.
            _this->gl_దత్తాంశం->glXQueryDrawable(display, drawable,
                                             GLX_LATE_SWAPS_TEAR_EXT,
                                             &allow_late_మార్పిడి_tearing);
        }

        _this->gl_దత్తాంశం->glXQueryDrawable(display, drawable,
                                         GLX_మార్పిడి_INTERVAL_EXT, &val);

        *interval = (పూర్ణాంకం)val;

        ఎంపిక (Check_మార్పిడి_Interval_Tear_Behavior(_this, drawable, val, allow_late_మార్పిడి_tearing)) {
            స్థితి SDL_SWAPINTERVALTEAR_MESA:
                *interval = (పూర్ణాంకం)val;  // unsigned int cast to signed that generates negative value if necessary.
                ఆపు;

            స్థితి SDL_SWAPINTERVALTEAR_NVIDIA:
            అప్రమేయ:
                ఒకవేళ ((allow_late_మార్పిడి_tearing) && (val > 0)) {
                    *interval = -((పూర్ణాంకం)val);
                }
                ఆపు;
        }

        తిరిగి true;
    } లేకపోతే ఒకవేళ (_this->gl_దత్తాంశం->gl_XGet_మార్పిడి_Interval_MESA) {
        పూర్ణాంకం val = _this->gl_దత్తాంశం->gl_XGet_మార్పిడి_Interval_MESA();
        ఒకవేళ (val == GLX_BAD_CONTEXT) {
            తిరిగి SDL_సమితి_Error("GLX_BAD_CONTEXT");
        }
        *interval = val;
        తిరిగి true;
    } లేకపోతే {
        *interval = swapinterval;
        తిరిగి true;
    }
}

bool X11_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;

    _this->gl_దత్తాంశం->glXSwapBuffers(display, దత్తాంశం->xwindow);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(దత్తాంశం->కిటికీ);
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */

    తిరిగి true;
}

bool X11_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    Display *display = _this->అంతర్గత->display;
    GLXContext glx_context = (GLXContext)context;

    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి true;
    }
    _this->gl_దత్తాంశం->glXDestroyContext(display, glx_context);
    X11_XSync(display, False);
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_GLX

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
