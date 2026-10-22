/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#অন্তর্ভাব "SDL_windowsvideo.h"
#অন্তর্ভাব "SDL_windowsopengles.h"
#অন্তর্ভাব "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#ifdef SDL_VIDEO_OPENGL_WGL
#অন্তর্ভাব <SDL3/SDL_opengl.h>

#define DEFAULT_OPENGL "OPENGL32.DLL"

#ifndef WGL_ARB_create_context
#define WGL_ARB_create_context
#define WGL_CONTEXT_MAJOR_VERSION_ARB          0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB          0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#define WGL_CONTEXT_FLAGS_ARB                  0x2094
#define WGL_CONTEXT_DEBUG_BIT_ARB              0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002

#ifndef WGL_ARB_create_context_profile
#define WGL_ARB_create_context_profile
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#endif

#ifndef WGL_ARB_create_context_robustness
#define WGL_ARB_create_context_robustness
#define WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB           0x00000004
#define WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#define WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#endif
#endif

#ifndef WGL_EXT_create_context_es2_profile
#define WGL_EXT_create_context_es2_profile
#define WGL_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000004
#endif

#ifndef WGL_EXT_create_context_es_profile
#define WGL_EXT_create_context_es_profile
#define WGL_CONTEXT_ES_PROFILE_BIT_EXT 0x00000004
#endif

#ifndef WGL_ARB_framebuffer_sRGB
#define WGL_ARB_framebuffer_sRGB
#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#endif

#ifndef WGL_ARB_pixel_format_float
#define WGL_ARB_pixel_format_float
#define WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#endif

#ifndef WGL_ARB_context_flush_control
#define WGL_ARB_context_flush_control
#define WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#define WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#define WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#endif

#ifndef WGL_ARB_create_context_no_error
#define WGL_ARB_create_context_no_error
#define WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#endif

প্রকারলেখ HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           ধ্রুবক পূর্ণসংখ্যা
                                                               *attribList);

#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#define GetDC(hwnd)          (HDC) hwnd
#define ReleaseDC(hwnd, hdc) 1
#define SwapBuffers          _this->gl_তথ্য->wglSwapBuffers
#define DescribePixelFormat  _this->gl_তথ্য->wglDescribePixelFormat
#define ChoosePixelFormat    _this->gl_তথ্য->wglChoosePixelFormat
#define GetPixelFormat       _this->gl_তথ্য->wglGetPixelFormat
#define SetPixelFormat       _this->gl_তথ্য->wglSetPixelFormat
#endif

স্থির bool WIN_GL_LoadLibrary_EGLFallback(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_LoadLibrary = WIN_GLES_LoadLibrary;
    _this->GL_GetProcAddress = WIN_GLES_GetProcAddress;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_SetSwapInterval = WIN_GLES_SetSwapInterval;
    _this->GL_GetSwapInterval = WIN_GLES_GetSwapInterval;
    _this->GL_SwapWindow = WIN_GLES_SwapWindow;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    ফেরত WIN_GLES_LoadLibrary(_this, path);
#অন্যথা
    ফেরত SDL_SetError("SDL not configured with EGL support");
#endif
}

bool WIN_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    শূন্য *handle;

    যদি ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ফেরত WIN_GL_LoadLibrary_EGLFallback(_this, path);
    }

    যদি (path == ফাঁকা) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    যদি (path == ফাঁকা) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    যদি (!_this->gl_config.dll_handle) {
        ফেরত false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_তথ্য = (কাঠামো SDL_GLDriver_তথ্য *)SDL_calloc(1, আকার(কাঠামো SDL_GLDriver_তথ্য));
    যদি (!_this->gl_তথ্য) {
        ফেরত false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_তথ্য->wglGetProcAddress = (PROC (WINAPI *)(ধ্রুবক অক্ষর *))
        SDL_LoadFunction(handle, "wglGetProcAddress");
    _this->gl_তথ্য->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_LoadFunction(handle, "wglCreateContext");
    _this->gl_তথ্য->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_LoadFunction(handle, "wglDeleteContext");
    _this->gl_তথ্য->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_LoadFunction(handle, "wglMakeCurrent");
    _this->gl_তথ্য->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_LoadFunction(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_তথ্য->wglSwapBuffers = (BOOL(WINAPI *)(HDC))
        SDL_LoadFunction(handle, "wglSwapBuffers");
    _this->gl_তথ্য->wglDescribePixelFormat = (পূর্ণসংখ্যা(WINAPI *)(HDC, পূর্ণসংখ্যা, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_LoadFunction(handle, "wglDescribePixelFormat");
    _this->gl_তথ্য->wglChoosePixelFormat = (পূর্ণসংখ্যা(WINAPI *)(HDC, ধ্রুবক PIXELFORMATDESCRIPTOR *))
        SDL_LoadFunction(handle, "wglChoosePixelFormat");
    _this->gl_তথ্য->wglSetPixelFormat = (BOOL(WINAPI *)(HDC, পূর্ণসংখ্যা, ধ্রুবক PIXELFORMATDESCRIPTOR *))
        SDL_LoadFunction(handle, "wglSetPixelFormat");
    _this->gl_তথ্য->wglGetPixelFormat = (পূর্ণসংখ্যা(WINAPI *)(HDC hdc))
        SDL_LoadFunction(handle, "wglGetPixelFormat");
#endif

    যদি (!_this->gl_তথ্য->wglGetProcAddress ||
        !_this->gl_তথ্য->wglCreateContext ||
        !_this->gl_তথ্য->wglDeleteContext ||
        !_this->gl_তথ্য->wglMakeCurrent
#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_তথ্য->wglSwapBuffers ||
        !_this->gl_তথ্য->wglDescribePixelFormat ||
        !_this->gl_তথ্য->wglChoosePixelFormat ||
        !_this->gl_তথ্য->wglGetPixelFormat ||
        !_this->gl_তথ্য->wglSetPixelFormat
#endif
    ) {
        ফেরত SDL_SetError("Could not retrieve OpenGL functions");
    }

    /* XXX Too sleazy? WIN_GL_InitExtensions looks for certain OpenGL
       extensions via SDL_GL_DeduceMaxSupportedESProfile. This uses
       SDL_GL_ExtensionSupported which in turn calls SDL_GL_GetProcAddress.
       However SDL_GL_GetProcAddress will fail if the library is not
       loaded; it checks for gl_config.driver_loaded > 0. To avoid this
       test failing, increment driver_loaded around the call to
       WIN_GLInitExtensions.

       Successful loading of the library is normally indicated by
       SDL_GL_LoadLibrary incrementing driver_loaded immediately after
       this function returns 0 to it.

       Alternatives to this are:
       - moving SDL_GL_DeduceMaxSupportedESProfile to both the WIN and
         X11 platforms while adding a function equivalent to
         SDL_GL_ExtensionSupported but which directly calls
         glGetProcAddress(). Having 3 copies of the
         SDL_GL_ExtensionSupported makes this alternative unattractive.
       - moving SDL_GL_DeduceMaxSupportedESProfile to a new file shared
         by the WIN and X11 platforms while adding a function equivalent
         to SDL_GL_ExtensionSupported. This is unattractive due to the
         number of project files that will need updating, plus there
         will be 2 copies of the SDL_GL_ExtensionSupported code.
       - Add a private equivalent of SDL_GL_ExtensionSupported to
         SDL_video.c.
       - Move the call to WIN_GL_InitExtensions back to WIN_CreateWindow
         and add a flag to gl_data to avoid multiple calls to this
         expensive function. This is probably the least objectionable
         alternative if this increment/decrement trick is unacceptable.

       Note that the driver_loaded > 0 check needs to remain in
       SDL_GL_ExtensionSupported and SDL_GL_GetProcAddress as they are
       public API functions.
    */
    ++_this->gl_config.driver_loaded;
    WIN_GL_InitExtensions(_this);
    --_this->gl_config.driver_loaded;

    ফেরত true;
}

SDL_FunctionPointer WIN_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    SDL_FunctionPointer func;

    // This is to pick up extensions
    func = (SDL_FunctionPointer)_this->gl_তথ্য->wglGetProcAddress(proc);
    যদি (!func) {
        // This is probably a normal GL function
        func = (SDL_FunctionPointer)GetProcAddress((HMODULE)_this->gl_config.dll_handle, proc);
    }
    ফেরত func;
}

শূন্য WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ফাঁকা;

    // Free OpenGL memory
    SDL_free(_this->gl_তথ্য);
    _this->gl_তথ্য = ফাঁকা;
}

স্থির শূন্য WIN_GL_SetupPixelFormat(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_আকার = আকার(*pfd);
    pfd->nVersion = 1;
    pfd->dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL);
    যদি (_this->gl_config.double_বাফার) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    যদি (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->cRedBits = (BYTE)_this->gl_config.red_আকার;
    pfd->cGreenBits = (BYTE)_this->gl_config.green_আকার;
    pfd->cBlueBits = (BYTE)_this->gl_config.blue_আকার;
    pfd->cAlphaBits = (BYTE)_this->gl_config.alpha_আকার;
    যদি (_this->gl_config.বাফার_আকার) {
        pfd->cColorBits = (BYTE)(_this->gl_config.বাফার_আকার - _this->gl_config.alpha_আকার);
    } অন্যথা {
        pfd->cColorBits = (pfd->cRedBits + pfd->cGreenBits + pfd->cBlueBits);
    }
    pfd->cAccumRedBits = (BYTE)_this->gl_config.accum_red_আকার;
    pfd->cAccumGreenBits = (BYTE)_this->gl_config.accum_green_আকার;
    pfd->cAccumBlueBits = (BYTE)_this->gl_config.accum_blue_আকার;
    pfd->cAccumAlphaBits = (BYTE)_this->gl_config.accum_alpha_আকার;
    pfd->cAccumBits =
        (pfd->cAccumRedBits + pfd->cAccumGreenBits + pfd->cAccumBlueBits +
         pfd->cAccumAlphaBits);
    pfd->cDepthBits = (BYTE)_this->gl_config.depth_আকার;
    pfd->cStencilBits = (BYTE)_this->gl_config.stencil_আকার;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
স্থির bool WIN_GL_ChoosePixelFormat(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *target)
{
    PIXELFORMATDESCRIPTOR pfd;
    পূর্ণসংখ্যা গুনতি, সূচক, best = 0;
    unsigned পূর্ণসংখ্যা dist, best_dist = ~0U;

    গুনতি = DescribePixelFormat(hdc, 1, আকার(pfd), ফাঁকা);

    জন্য (সূচক = 1; সূচক <= গুনতি; সূচক++) {

        যদি (!DescribePixelFormat(hdc, সূচক, আকার(pfd), &pfd)) {
            চালু;
        }

        যদি ((pfd.dwFlags & target->dwFlags) != target->dwFlags) {
            চালু;
        }

        যদি (pfd.iLayerType != target->iLayerType) {
            চালু;
        }
        যদি (pfd.iPixelType != target->iPixelType) {
            চালু;
        }

        dist = 0;

        যদি (pfd.cColorBits < target->cColorBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cColorBits - target->cColorBits);
        }
        যদি (pfd.cRedBits < target->cRedBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cRedBits - target->cRedBits);
        }
        যদি (pfd.cGreenBits < target->cGreenBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cGreenBits - target->cGreenBits);
        }
        যদি (pfd.cBlueBits < target->cBlueBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cBlueBits - target->cBlueBits);
        }
        যদি (pfd.cAlphaBits < target->cAlphaBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cAlphaBits - target->cAlphaBits);
        }
        যদি (pfd.cAccumBits < target->cAccumBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cAccumBits - target->cAccumBits);
        }
        যদি (pfd.cAccumRedBits < target->cAccumRedBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cAccumRedBits - target->cAccumRedBits);
        }
        যদি (pfd.cAccumGreenBits < target->cAccumGreenBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cAccumGreenBits - target->cAccumGreenBits);
        }
        যদি (pfd.cAccumBlueBits < target->cAccumBlueBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cAccumBlueBits - target->cAccumBlueBits);
        }
        যদি (pfd.cAccumAlphaBits < target->cAccumAlphaBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cAccumAlphaBits - target->cAccumAlphaBits);
        }
        যদি (pfd.cDepthBits < target->cDepthBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cDepthBits - target->cDepthBits);
        }
        যদি (pfd.cStencilBits < target->cStencilBits) {
            চালু;
        } অন্যথা {
            dist += (pfd.cStencilBits - target->cStencilBits);
        }

        যদি (dist < best_dist) {
            best = সূচক;
            best_dist = dist;
        }
    }

    ফেরত best;
}

স্থির bool HasExtension(ধ্রুবক অক্ষর *extension, ধ্রুবক অক্ষর *extensions)
{
    ধ্রুবক অক্ষর *start;
    ধ্রুবক অক্ষর *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    যদি (where || *extension == '\0') {
        ফেরত false;
    }

    যদি (!extensions) {
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

শূন্য WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    ধ্রুবক অক্ষর *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    ধ্রুবক অক্ষর *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    যদি (!_this->gl_তথ্য) {
        ফেরত;
    }

    hwnd =
        CreateWindow(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ফাঁকা, ফাঁকা, SDL_Instance, ফাঁকা);
    যদি (!hwnd) {
        ফেরত;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_SetupPixelFormat(_this, &pfd);

    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

    hglrc = _this->gl_তথ্য->wglCreateContext(hdc);
    যদি (!hglrc) {
        ফেরত;
    }
    _this->gl_তথ্য->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (ধ্রুবক অক্ষর *(WINAPI *)(HDC))
        _this->gl_তথ্য->wglGetProcAddress("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    যদি (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } অন্যথা {
        extensions = ফাঁকা;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_তথ্য->HAS_WGL_ARB_pixel_format = false;
    যদি (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_তথ্য->wglChoosePixelFormatARB =
            (BOOL (WINAPI *)(HDC, ধ্রুবক পূর্ণসংখ্যা *, ধ্রুবক FLOAT *, UINT, পূর্ণসংখ্যা *, UINT *))
            WIN_GL_GetProcAddress(_this, "wglChoosePixelFormatARB");
        _this->gl_তথ্য->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, পূর্ণসংখ্যা, পূর্ণসংখ্যা, UINT, ধ্রুবক পূর্ণসংখ্যা *, পূর্ণসংখ্যা *))
            WIN_GL_GetProcAddress(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        যদি ((_this->gl_তথ্য->wglChoosePixelFormatARB != ফাঁকা) &&
            (_this->gl_তথ্য->wglGetPixelFormatAttribivARB != ফাঁকা)) {
            _this->gl_তথ্য->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_তথ্য->HAS_WGL_EXT_swap_control_tear = false;
    যদি (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_তথ্য->wglSwapIntervalEXT =
            (BOOL (WINAPI *)(পূর্ণসংখ্যা))
            WIN_GL_GetProcAddress(_this, "wglSwapIntervalEXT");
        _this->gl_তথ্য->wglGetSwapIntervalEXT =
            (পূর্ণসংখ্যা (WINAPI *)(শূন্য))
            WIN_GL_GetProcAddress(_this, "wglGetSwapIntervalEXT");
        যদি (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_তথ্য->HAS_WGL_EXT_swap_control_tear = true;
        }
    } অন্যথা {
        _this->gl_তথ্য->wglSwapIntervalEXT = ফাঁকা;
        _this->gl_তথ্য->wglGetSwapIntervalEXT = ফাঁকা;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_তথ্য->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    যদি (_this->gl_তথ্য->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_তথ্য->es_profile_max_supported_version.major,
            &_this->gl_তথ্য->es_profile_max_supported_version.minor);
    }

    // Check for WGL_ARB_context_flush_control
    যদি (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_তথ্য->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    যদি (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_তথ্য->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    যদি (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_তথ্য->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    যদি (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_তথ্য->HAS_WGL_ARB_framebuffer_sRGB = true;
    } অন্যথা যদি (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_তথ্য->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_তথ্য->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_তথ্য->wglMakeCurrent(hdc, ফাঁকা);
    _this->gl_তথ্য->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

স্থির পূর্ণসংখ্যা WIN_GL_ChoosePixelFormatARB(SDL_VideoDevice *_this, পূর্ণসংখ্যা *iAttribs, দশমিক *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    পূর্ণসংখ্যা pixel_format = 0;
    unsigned পূর্ণসংখ্যা matching;

    hwnd =
        CreateWindow(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ফাঁকা, ফাঁকা, SDL_Instance, ফাঁকা);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_SetupPixelFormat(_this, &pfd);

    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

    hglrc = _this->gl_তথ্য->wglCreateContext(hdc);
    যদি (hglrc) {
        _this->gl_তথ্য->wglMakeCurrent(hdc, hglrc);

        যদি (_this->gl_তথ্য->HAS_WGL_ARB_pixel_format) {
            _this->gl_তথ্য->wglChoosePixelFormatARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            পূর্ণসংখ্যা srgb = 0;
            যদি (_this->gl_তথ্য->HAS_WGL_ARB_framebuffer_sRGB) {
                পূর্ণসংখ্যা qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_তথ্য->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_তথ্য->wglMakeCurrent(hdc, ফাঁকা);
        _this->gl_তথ্য->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    ফেরত pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
স্থির bool WIN_GL_SetupWindowInternal(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    পূর্ণসংখ্যা pixel_format = 0;
    পূর্ণসংখ্যা iAttribs[64];
    পূর্ণসংখ্যা *iAttr;
    পূর্ণসংখ্যা *iAccelAttr;
    দশমিক fAttribs[1] = { 0 };

    WIN_GL_SetupPixelFormat(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_TO_WINDOW_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_BITS_ARB;
    *iAttr++ = _this->gl_config.red_আকার;
    *iAttr++ = WGL_GREEN_BITS_ARB;
    *iAttr++ = _this->gl_config.green_আকার;
    *iAttr++ = WGL_BLUE_BITS_ARB;
    *iAttr++ = _this->gl_config.blue_আকার;

    যদি (_this->gl_config.alpha_আকার) {
        *iAttr++ = WGL_ALPHA_BITS_ARB;
        *iAttr++ = _this->gl_config.alpha_আকার;
    }

    *iAttr++ = WGL_DOUBLE_বাফার_ARB;
    *iAttr++ = _this->gl_config.double_বাফার;

    *iAttr++ = WGL_DEPTH_BITS_ARB;
    *iAttr++ = _this->gl_config.depth_আকার;

    যদি (_this->gl_config.stencil_আকার) {
        *iAttr++ = WGL_STENCIL_BITS_ARB;
        *iAttr++ = _this->gl_config.stencil_আকার;
    }

    যদি (_this->gl_config.accum_red_আকার) {
        *iAttr++ = WGL_ACCUM_RED_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_red_আকার;
    }

    যদি (_this->gl_config.accum_green_আকার) {
        *iAttr++ = WGL_ACCUM_GREEN_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_green_আকার;
    }

    যদি (_this->gl_config.accum_blue_আকার) {
        *iAttr++ = WGL_ACCUM_BLUE_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_blue_আকার;
    }

    যদি (_this->gl_config.accum_alpha_আকার) {
        *iAttr++ = WGL_ACCUM_ALPHA_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_আকার;
    }

    যদি (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    যদি (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    যদি (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    যদি (_this->gl_তথ্য->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    যদি (_this->gl_তথ্য->HAS_WGL_ARB_framebuffer_sRGB) {
        ধ্রুবক অক্ষর *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        যদি (srgbhint && *srgbhint) {
            যদি (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } অন্যথা {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } অন্যথা যদি (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
            *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            *iAttr++ = GL_TRUE;
        }
    }

    /* We always choose either FULL or NO accel on Windows, because of flaky
       drivers. If the app didn't specify, we use FULL, because that's
       probably what they wanted (and if you didn't care and got FULL, that's
       a perfectly valid result in any case). */
    *iAttr++ = WGL_ACCELERATION_ARB;
    iAccelAttr = iAttr;
    যদি (_this->gl_config.accelerated) {
        *iAttr++ = WGL_FULL_ACCELERATION_ARB;
    } অন্যথা {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_ChoosePixelFormatARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    যদি ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_ChoosePixelFormatARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_FULL_ACCELERATION_ARB; // if we try again.
    }
    যদি (!pixel_format) {
        pixel_format = WIN_GL_ChoosePixelFormat(_this, hdc, &pfd);
    }
    যদি (!pixel_format) {
        ফেরত SDL_SetError("No matching GL pixel format available");
    }
    যদি (!SetPixelFormat(hdc, pixel_format, &pfd)) {
        ফেরত WIN_SetError("SetPixelFormat()");
    }
    ফেরত true;
}

bool WIN_GL_SetupWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // The current context is lost in here; save it and reset it.
    SDL_Window *current_win = SDL_GL_GetCurrentWindow();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    ধ্রুবক পূর্ণসংখ্যা ফলাফল = WIN_GL_SetupWindowInternal(_this, window);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    ফেরত ফলাফল;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_তথ্য != ফাঁকা);
    SDL_assert(_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    ফেরত !_this->gl_তথ্য->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_version > _this->gl_তথ্য->es_profile_max_supported_version.major ||
           (_this->gl_config.major_version == _this->gl_তথ্য->es_profile_max_supported_version.major && _this->gl_config.minor_version > _this->gl_তথ্য->es_profile_max_supported_version.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;
    HGLRC context, share_context;

    যদি (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#ifdef SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        যদি (!WIN_GL_LoadLibrary_EGLFallback(_this, ফাঁকা)) {
            ফেরত ফাঁকা;
        }

        ফেরত WIN_GLES_CreateContext(_this, window);
#অন্যথা
        SDL_SetError("SDL not configured with EGL support");
        ফেরত ফাঁকা;
#endif
    }

    যদি (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } অন্যথা {
        share_context = 0;
    }

    যদি (_this->gl_config.major_version < 3 &&
        _this->gl_config.profile_mask == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_তথ্য->wglCreateContext(hdc);
        যদি (share_context != 0) {
            _this->gl_তথ্য->wglShareLists(share_context, context);
        }
    } অন্যথা {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC অস্থায়ী_context = _this->gl_তথ্য->wglCreateContext(hdc);
        যদি (!অস্থায়ী_context) {
            SDL_SetError("Could not create GL context");
            ফেরত ফাঁকা;
        }

        // Make the context current
        যদি (!WIN_GL_MakeCurrent(_this, window, (SDL_GLContext)অস্থায়ী_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)অস্থায়ী_context);
            ফেরত ফাঁকা;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_তথ্য->wglGetProcAddress("wglCreateContextAttribsARB");
        যদি (!wglCreateContextAttribsARB) {
            SDL_SetError("GL 3.x is not supported");
            context = অস্থায়ী_context;
        } অন্যথা {
            পূর্ণসংখ্যা attribs[15]; // max 14 attributes plus terminator
            পূর্ণসংখ্যা iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
            attribs[iattr++] = _this->gl_config.major_version;
            attribs[iattr++] = WGL_CONTEXT_MINOR_VERSION_ARB;
            attribs[iattr++] = _this->gl_config.minor_version;

            // SDL profile bits match WGL profile bits
            যদি (_this->gl_config.profile_mask != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_MASK_ARB;
                attribs[iattr++] = _this->gl_config.profile_mask;
            }

            // SDL flags match WGL flags
            যদি (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            যদি ((_this->gl_তথ্য->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            যদি ((_this->gl_তথ্য->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            যদি ((_this->gl_তথ্য->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_তথ্য->wglDeleteContext(অস্থায়ী_context);
        }
    }

    যদি (!context) {
        WIN_SetError("Could not create GL context");
        ফেরত ফাঁকা;
    }

    যদি (!WIN_GL_MakeCurrent(_this, window, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        ফেরত ফাঁকা;
    }

    _this->gl_config.HAS_GL_ARB_color_বাফার_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    ফেরত (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    HDC hdc;

    যদি (!_this->gl_তথ্য) {
        ফেরত SDL_SetError("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(window || (window == ফাঁকা && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    যদি (!window) {
        window = SDL_GL_GetCurrentWindow();
        যদি (!window) {
            SDL_assert(SDL_GL_GetCurrentContext() == ফাঁকা);
            ফেরত true; // already done.
        }
    }

    hdc = window->internal->hdc;
    যদি (!_this->gl_তথ্য->wglMakeCurrent(hdc, (HGLRC)context)) {
        ফেরত WIN_SetError("wglMakeCurrent()");
    }
    ফেরত true;
}

bool WIN_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    যদি ((interval < 0) && (!_this->gl_তথ্য->HAS_WGL_EXT_swap_control_tear)) {
        ফেরত SDL_SetError("Negative swap interval unsupported in this GL");
    } অন্যথা যদি (_this->gl_তথ্য->wglSwapIntervalEXT) {
        যদি (!_this->gl_তথ্য->wglSwapIntervalEXT(interval)) {
            ফেরত WIN_SetError("wglSwapIntervalEXT()");
        }
    } অন্যথা {
        ফেরত SDL_Unsupported();
    }
    ফেরত true;
}

bool WIN_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval)
{
    যদি (_this->gl_তথ্য->wglGetSwapIntervalEXT) {
        *interval = _this->gl_তথ্য->wglGetSwapIntervalEXT();
        ফেরত true;
    } অন্যথা {
        ফেরত SDL_Unsupported();
    }
}

bool WIN_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;

    যদি (!SwapBuffers(hdc)) {
        ফেরত WIN_SetError("SwapBuffers()");
    }
    ফেরত true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    যদি (!_this->gl_তথ্য) {
        ফেরত true;
    }
    _this->gl_তথ্য->wglDeleteContext((HGLRC)context);
    ফেরত true;
}

#endif // SDL_VIDEO_OPENGL_WGL

#endif // SDL_VIDEO_DRIVER_WINDOWS
