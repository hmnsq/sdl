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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowsopengles.h"
#ضمن "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
#ضمن <SDL3/SDL_opengl.h>

#تعریف_کن DEFAULT_OPENGL "OPENGL32.DLL"

#اگر_تعریف_نشده WGL_ARB_create_context
#تعریف_کن WGL_ARB_create_context
#تعریف_کن WGL_CONTEXT_MAJOR_نسخه_ARB          0x2091
#تعریف_کن WGL_CONTEXT_MINOR_نسخه_ARB          0x2092
#تعریف_کن WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#تعریف_کن WGL_CONTEXT_FLAGS_ARB                  0x2094
#تعریف_کن WGL_CONTEXT_DEBUG_بیت_ARB              0x0001
#تعریف_کن WGL_CONTEXT_FORWARD_COMPATIBLE_بیت_ARB 0x0002

#اگر_تعریف_نشده WGL_ARB_create_context_profile
#تعریف_کن WGL_ARB_create_context_profile
#تعریف_کن WGL_CONTEXT_PROFILE_ماسک_ARB              0x9126
#تعریف_کن WGL_CONTEXT_CORE_PROFILE_بیت_ARB          0x00000001
#تعریف_کن WGL_CONTEXT_COMPATIBILITY_PROFILE_بیت_ARB 0x00000002
#پایان_اگر

#اگر_تعریف_نشده WGL_ARB_create_context_robustness
#تعریف_کن WGL_ARB_create_context_robustness
#تعریف_کن WGL_CONTEXT_ROBUST_ACCESS_بیت_ARB           0x00000004
#تعریف_کن WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#تعریف_کن WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#تعریف_کن WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#پایان_اگر
#پایان_اگر

#اگر_تعریف_نشده WGL_EXT_create_context_es2_profile
#تعریف_کن WGL_EXT_create_context_es2_profile
#تعریف_کن WGL_CONTEXT_ES2_PROFILE_بیت_EXT 0x00000004
#پایان_اگر

#اگر_تعریف_نشده WGL_EXT_create_context_es_profile
#تعریف_کن WGL_EXT_create_context_es_profile
#تعریف_کن WGL_CONTEXT_ES_PROFILE_بیت_EXT 0x00000004
#پایان_اگر

#اگر_تعریف_نشده WGL_ARB_framebuffer_sRGB
#تعریف_کن WGL_ARB_framebuffer_sRGB
#تعریف_کن WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#پایان_اگر

#اگر_تعریف_نشده WGL_ARB_pixel_format_float
#تعریف_کن WGL_ARB_pixel_format_float
#تعریف_کن WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#پایان_اگر

#اگر_تعریف_نشده WGL_ARB_context_flush_control
#تعریف_کن WGL_ARB_context_flush_control
#تعریف_کن WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#تعریف_کن WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#تعریف_کن WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#پایان_اگر

#اگر_تعریف_نشده WGL_ARB_create_context_no_error
#تعریف_کن WGL_ARB_create_context_no_error
#تعریف_کن WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#پایان_اگر

تعريفنوع HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           ثابت صحيح
                                                               *attribList);

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#تعریف_کن GetDC(hwnd)          (HDC) hwnd
#تعریف_کن ReleaseDC(hwnd, hdc) 1
#تعریف_کن جابجا_Buffers          _this->gl_داده->wgl_جابجا_Buffers
#تعریف_کن DescribePixelFormat  _this->gl_داده->wglDescribePixelFormat
#تعریف_کن انتخاب_Pixel_Format    _this->gl_داده->wgl_انتخاب_Pixel_Format
#تعریف_کن GetPixelFormat       _this->gl_داده->wglGetPixelFormat
#تعریف_کن مجموعه_Pixel_Format       _this->gl_داده->wgl_مجموعه_Pixel_Format
#پایان_اگر

ساكن bool WIN_GL_بارگیری_Library_EGLFallback(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_بارگیری_Library = WIN_GLES_بارگیری_Library;
    _this->GL_Get_Proc_آدرس = WIN_GLES_Get_Proc_آدرس;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_مجموعه_جابجا_Interval = WIN_GLES_مجموعه_جابجا_Interval;
    _this->GL_Get_جابجا_Interval = WIN_GLES_Get_جابجا_Interval;
    _this->GL_جابجا_پنجره = WIN_GLES_جابجا_پنجره;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    أرجع WIN_GLES_بارگیری_Library(_this, مسیر);
#وإلا
    أرجع SDL_مجموعه_Error("SDL not configured with EGL support");
#پایان_اگر
}

bool WIN_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
    فراغ *handle;

    إذا ((_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        أرجع WIN_GL_بارگیری_Library_EGLFallback(_this, مسیر);
    }

    إذا (مسیر == عدم) {
        مسیر = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    إذا (مسیر == عدم) {
        مسیر = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_بارگیری_Object(مسیر);
    إذا (!_this->gl_config.dll_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_مسیر, مسیر,
                SDL_arraysize(_this->gl_config.driver_مسیر));

    // Allocate OpenGL memory
    _this->gl_داده = (بنية SDL_GLDriver_داده *)SDL_calloc(1, حجم(بنية SDL_GLDriver_داده));
    إذا (!_this->gl_داده) {
        أرجع false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_داده->wgl_Get_Proc_آدرس = (PROC (WINAPI *)(ثابت حرف *))
        SDL_بارگیری_Function(handle, "wglGetProcAddress");
    _this->gl_داده->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_بارگیری_Function(handle, "wglCreateContext");
    _this->gl_داده->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_بارگیری_Function(handle, "wglDeleteContext");
    _this->gl_داده->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_بارگیری_Function(handle, "wglMakeCurrent");
    _this->gl_داده->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_بارگیری_Function(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_داده->wgl_جابجا_Buffers = (BOOL(WINAPI *)(HDC))
        SDL_بارگیری_Function(handle, "wglSwapBuffers");
    _this->gl_داده->wglDescribePixelFormat = (صحيح(WINAPI *)(HDC, صحيح, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_بارگیری_Function(handle, "wglDescribePixelFormat");
    _this->gl_داده->wgl_انتخاب_Pixel_Format = (صحيح(WINAPI *)(HDC, ثابت PIXELFORMATDESCRIPTOR *))
        SDL_بارگیری_Function(handle, "wglChoosePixelFormat");
    _this->gl_داده->wgl_مجموعه_Pixel_Format = (BOOL(WINAPI *)(HDC, صحيح, ثابت PIXELFORMATDESCRIPTOR *))
        SDL_بارگیری_Function(handle, "wglSetPixelFormat");
    _this->gl_داده->wglGetPixelFormat = (صحيح(WINAPI *)(HDC hdc))
        SDL_بارگیری_Function(handle, "wglGetPixelFormat");
#پایان_اگر

    إذا (!_this->gl_داده->wgl_Get_Proc_آدرس ||
        !_this->gl_داده->wglCreateContext ||
        !_this->gl_داده->wglDeleteContext ||
        !_this->gl_داده->wglMakeCurrent
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_داده->wgl_جابجا_Buffers ||
        !_this->gl_داده->wglDescribePixelFormat ||
        !_this->gl_داده->wgl_انتخاب_Pixel_Format ||
        !_this->gl_داده->wglGetPixelFormat ||
        !_this->gl_داده->wgl_مجموعه_Pixel_Format
#پایان_اگر
    ) {
        أرجع SDL_مجموعه_Error("Could not retrieve OpenGL functions");
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

    أرجع true;
}

SDL_Function_اشاره_گر WIN_GL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشاره_گر func;

    // This is to pick up extensions
    func = (SDL_Function_اشاره_گر)_this->gl_داده->wgl_Get_Proc_آدرس(proc);
    إذا (!func) {
        // This is probably a normal GL function
        func = (SDL_Function_اشاره_گر)Get_Proc_آدرس((HMODULE)_this->gl_config.dll_handle, proc);
    }
    أرجع func;
}

فراغ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = عدم;

    // Free OpenGL memory
    SDL_free(_this->gl_داده);
    _this->gl_داده = عدم;
}

ساكن فراغ WIN_GL_راهاندازی_Pixel_Format(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_اندازه = حجم(*pfd);
    pfd->n_نسخه = 1;
    pfd->dwFlags = (PFD_DRAW_مقصد_پنجره | PFD_SUPPORT_OPENGL);
    إذا (_this->gl_config.double_میانگیر) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    إذا (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->c_Red_بیتها = (BYTE)_this->gl_config.red_اندازه;
    pfd->c_Green_بیتها = (BYTE)_this->gl_config.green_اندازه;
    pfd->c_Blue_بیتها = (BYTE)_this->gl_config.blue_اندازه;
    pfd->c_Alpha_بیتها = (BYTE)_this->gl_config.alpha_اندازه;
    إذا (_this->gl_config.میانگیر_اندازه) {
        pfd->c_Color_بیتها = (BYTE)(_this->gl_config.میانگیر_اندازه - _this->gl_config.alpha_اندازه);
    } وإلا {
        pfd->c_Color_بیتها = (pfd->c_Red_بیتها + pfd->c_Green_بیتها + pfd->c_Blue_بیتها);
    }
    pfd->c_Accum_Red_بیتها = (BYTE)_this->gl_config.accum_red_اندازه;
    pfd->c_Accum_Green_بیتها = (BYTE)_this->gl_config.accum_green_اندازه;
    pfd->c_Accum_Blue_بیتها = (BYTE)_this->gl_config.accum_blue_اندازه;
    pfd->c_Accum_Alpha_بیتها = (BYTE)_this->gl_config.accum_alpha_اندازه;
    pfd->c_Accum_بیتها =
        (pfd->c_Accum_Red_بیتها + pfd->c_Accum_Green_بیتها + pfd->c_Accum_Blue_بیتها +
         pfd->c_Accum_Alpha_بیتها);
    pfd->c_عمق_بیتها = (BYTE)_this->gl_config.عمق_اندازه;
    pfd->c_Stencil_بیتها = (BYTE)_this->gl_config.stencil_اندازه;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
ساكن bool WIN_GL_انتخاب_Pixel_Format(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *هدف)
{
    PIXELFORMATDESCRIPTOR pfd;
    صحيح شمار, شاخص, بهترین = 0;
    بیعلامت صحيح dist, بهترین_dist = ~0U;

    شمار = DescribePixelFormat(hdc, 1, حجم(pfd), عدم);

    لكل (شاخص = 1; شاخص <= شمار; شاخص++) {

        إذا (!DescribePixelFormat(hdc, شاخص, حجم(pfd), &pfd)) {
            استمر;
        }

        إذا ((pfd.dwFlags & هدف->dwFlags) != هدف->dwFlags) {
            استمر;
        }

        إذا (pfd.iLayerType != هدف->iLayerType) {
            استمر;
        }
        إذا (pfd.iPixelType != هدف->iPixelType) {
            استمر;
        }

        dist = 0;

        إذا (pfd.c_Color_بیتها < هدف->c_Color_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Color_بیتها - هدف->c_Color_بیتها);
        }
        إذا (pfd.c_Red_بیتها < هدف->c_Red_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Red_بیتها - هدف->c_Red_بیتها);
        }
        إذا (pfd.c_Green_بیتها < هدف->c_Green_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Green_بیتها - هدف->c_Green_بیتها);
        }
        إذا (pfd.c_Blue_بیتها < هدف->c_Blue_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Blue_بیتها - هدف->c_Blue_بیتها);
        }
        إذا (pfd.c_Alpha_بیتها < هدف->c_Alpha_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Alpha_بیتها - هدف->c_Alpha_بیتها);
        }
        إذا (pfd.c_Accum_بیتها < هدف->c_Accum_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_بیتها - هدف->c_Accum_بیتها);
        }
        إذا (pfd.c_Accum_Red_بیتها < هدف->c_Accum_Red_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Red_بیتها - هدف->c_Accum_Red_بیتها);
        }
        إذا (pfd.c_Accum_Green_بیتها < هدف->c_Accum_Green_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Green_بیتها - هدف->c_Accum_Green_بیتها);
        }
        إذا (pfd.c_Accum_Blue_بیتها < هدف->c_Accum_Blue_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Blue_بیتها - هدف->c_Accum_Blue_بیتها);
        }
        إذا (pfd.c_Accum_Alpha_بیتها < هدف->c_Accum_Alpha_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Alpha_بیتها - هدف->c_Accum_Alpha_بیتها);
        }
        إذا (pfd.c_عمق_بیتها < هدف->c_عمق_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_عمق_بیتها - هدف->c_عمق_بیتها);
        }
        إذا (pfd.c_Stencil_بیتها < هدف->c_Stencil_بیتها) {
            استمر;
        } وإلا {
            dist += (pfd.c_Stencil_بیتها - هدف->c_Stencil_بیتها);
        }

        إذا (dist < بهترین_dist) {
            بهترین = شاخص;
            بهترین_dist = dist;
        }
    }

    أرجع بهترین;
}

ساكن bool HasExtension(ثابت حرف *extension, ثابت حرف *extensions)
{
    ثابت حرف *شروع;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    إذا (where || *extension == '\0') {
        أرجع false;
    }

    إذا (!extensions) {
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

فراغ WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    ثابت حرف *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    ثابت حرف *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    إذا (!_this->gl_داده) {
        أرجع;
    }

    hwnd =
        Create_پنجره(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, عدم, عدم, SDL_Instance, عدم);
    إذا (!hwnd) {
        أرجع;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_راهاندازی_Pixel_Format(_this, &pfd);

    مجموعه_Pixel_Format(hdc, انتخاب_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_داده->wglCreateContext(hdc);
    إذا (!hglrc) {
        أرجع;
    }
    _this->gl_داده->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (ثابت حرف *(WINAPI *)(HDC))
        _this->gl_داده->wgl_Get_Proc_آدرس("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    إذا (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } وإلا {
        extensions = عدم;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_داده->HAS_WGL_ARB_pixel_format = false;
    إذا (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_داده->wgl_انتخاب_Pixel_Format_ARB =
            (BOOL (WINAPI *)(HDC, ثابت صحيح *, ثابت FLOAT *, UINT, صحيح *, UINT *))
            WIN_GL_Get_Proc_آدرس(_this, "wglChoosePixelFormatARB");
        _this->gl_داده->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, صحيح, صحيح, UINT, ثابت صحيح *, صحيح *))
            WIN_GL_Get_Proc_آدرس(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        إذا ((_this->gl_داده->wgl_انتخاب_Pixel_Format_ARB != عدم) &&
            (_this->gl_داده->wglGetPixelFormatAttribivARB != عدم)) {
            _this->gl_داده->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_داده->HAS_WGL_EXT_جابجا_control_tear = false;
    إذا (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_داده->wgl_جابجا_Interval_EXT =
            (BOOL (WINAPI *)(صحيح))
            WIN_GL_Get_Proc_آدرس(_this, "wglSwapIntervalEXT");
        _this->gl_داده->wgl_Get_جابجا_Interval_EXT =
            (صحيح (WINAPI *)(فراغ))
            WIN_GL_Get_Proc_آدرس(_this, "wglGetSwapIntervalEXT");
        إذا (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_داده->HAS_WGL_EXT_جابجا_control_tear = true;
        }
    } وإلا {
        _this->gl_داده->wgl_جابجا_Interval_EXT = عدم;
        _this->gl_داده->wgl_Get_جابجا_Interval_EXT = عدم;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_داده->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    إذا (_this->gl_داده->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_داده->es_profile_max_supported_نسخه.major,
            &_this->gl_داده->es_profile_max_supported_نسخه.minor);
    }

    // Check for WGL_ARB_context_flush_control
    إذا (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_داده->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    إذا (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_داده->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    إذا (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_داده->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    إذا (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_داده->HAS_WGL_ARB_framebuffer_sRGB = true;
    } وإلا إذا (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_داده->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_داده->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_داده->wglMakeCurrent(hdc, عدم);
    _this->gl_داده->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    Destroy_پنجره(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

ساكن صحيح WIN_GL_انتخاب_Pixel_Format_ARB(SDL_VideoDevice *_this, صحيح *iAttribs, عائم *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    صحيح pixel_format = 0;
    بیعلامت صحيح matching;

    hwnd =
        Create_پنجره(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, عدم, عدم, SDL_Instance, عدم);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_راهاندازی_Pixel_Format(_this, &pfd);

    مجموعه_Pixel_Format(hdc, انتخاب_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_داده->wglCreateContext(hdc);
    إذا (hglrc) {
        _this->gl_داده->wglMakeCurrent(hdc, hglrc);

        إذا (_this->gl_داده->HAS_WGL_ARB_pixel_format) {
            _this->gl_داده->wgl_انتخاب_Pixel_Format_ARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            صحيح srgb = 0;
            إذا (_this->gl_داده->HAS_WGL_ARB_framebuffer_sRGB) {
                صحيح qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_داده->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_داده->wglMakeCurrent(hdc, عدم);
        _this->gl_داده->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    Destroy_پنجره(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    أرجع pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
ساكن bool WIN_GL_راهاندازی_پنجره_داخلی(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    HDC hdc = پنجره->داخلی->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    صحيح pixel_format = 0;
    صحيح iAttribs[64];
    صحيح *iAttr;
    صحيح *iAccelAttr;
    عائم fAttribs[1] = { 0 };

    WIN_GL_راهاندازی_Pixel_Format(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_مقصد_پنجره_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_بیتها_ARB;
    *iAttr++ = _this->gl_config.red_اندازه;
    *iAttr++ = WGL_GREEN_بیتها_ARB;
    *iAttr++ = _this->gl_config.green_اندازه;
    *iAttr++ = WGL_BLUE_بیتها_ARB;
    *iAttr++ = _this->gl_config.blue_اندازه;

    إذا (_this->gl_config.alpha_اندازه) {
        *iAttr++ = WGL_ALPHA_بیتها_ARB;
        *iAttr++ = _this->gl_config.alpha_اندازه;
    }

    *iAttr++ = WGL_DOUBLE_میانگیر_ARB;
    *iAttr++ = _this->gl_config.double_میانگیر;

    *iAttr++ = WGL_عمق_بیتها_ARB;
    *iAttr++ = _this->gl_config.عمق_اندازه;

    إذا (_this->gl_config.stencil_اندازه) {
        *iAttr++ = WGL_STENCIL_بیتها_ARB;
        *iAttr++ = _this->gl_config.stencil_اندازه;
    }

    إذا (_this->gl_config.accum_red_اندازه) {
        *iAttr++ = WGL_ACCUM_RED_بیتها_ARB;
        *iAttr++ = _this->gl_config.accum_red_اندازه;
    }

    إذا (_this->gl_config.accum_green_اندازه) {
        *iAttr++ = WGL_ACCUM_GREEN_بیتها_ARB;
        *iAttr++ = _this->gl_config.accum_green_اندازه;
    }

    إذا (_this->gl_config.accum_blue_اندازه) {
        *iAttr++ = WGL_ACCUM_BLUE_بیتها_ARB;
        *iAttr++ = _this->gl_config.accum_blue_اندازه;
    }

    إذا (_this->gl_config.accum_alpha_اندازه) {
        *iAttr++ = WGL_ACCUM_ALPHA_بیتها_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_اندازه;
    }

    إذا (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    إذا (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    إذا (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    إذا (_this->gl_داده->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    إذا (_this->gl_داده->HAS_WGL_ARB_framebuffer_sRGB) {
        ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        إذا (srgbhint && *srgbhint) {
            إذا (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } وإلا {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } وإلا إذا (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    إذا (_this->gl_config.accelerated) {
        *iAttr++ = WGL_پر_ACCELERATION_ARB;
    } وإلا {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_انتخاب_Pixel_Format_ARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    إذا ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_انتخاب_Pixel_Format_ARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_پر_ACCELERATION_ARB; // if we try again.
    }
    إذا (!pixel_format) {
        pixel_format = WIN_GL_انتخاب_Pixel_Format(_this, hdc, &pfd);
    }
    إذا (!pixel_format) {
        أرجع SDL_مجموعه_Error("No matching GL pixel format available");
    }
    إذا (!مجموعه_Pixel_Format(hdc, pixel_format, &pfd)) {
        أرجع WIN_مجموعه_Error("SetPixelFormat()");
    }
    أرجع true;
}

bool WIN_GL_راهاندازی_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // The current context is lost in here; save it and reset it.
    SDL_پنجره *current_win = SDL_GL_Get_Current_پنجره();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    ثابت صحيح نتیجه = WIN_GL_راهاندازی_پنجره_داخلی(_this, پنجره);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    أرجع نتیجه;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_داده != عدم);
    SDL_assert(_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    أرجع !_this->gl_داده->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_نسخه > _this->gl_داده->es_profile_max_supported_نسخه.major ||
           (_this->gl_config.major_نسخه == _this->gl_داده->es_profile_max_supported_نسخه.major && _this->gl_config.minor_نسخه > _this->gl_داده->es_profile_max_supported_نسخه.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    HDC hdc = پنجره->داخلی->hdc;
    HGLRC context, share_context;

    إذا (_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        إذا (!WIN_GL_بارگیری_Library_EGLFallback(_this, عدم)) {
            أرجع عدم;
        }

        أرجع WIN_GLES_CreateContext(_this, پنجره);
#وإلا
        SDL_مجموعه_Error("SDL not configured with EGL support");
        أرجع عدم;
#پایان_اگر
    }

    إذا (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } وإلا {
        share_context = 0;
    }

    إذا (_this->gl_config.major_نسخه < 3 &&
        _this->gl_config.profile_ماسک == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_داده->wglCreateContext(hdc);
        إذا (share_context != 0) {
            _this->gl_داده->wglShareLists(share_context, context);
        }
    } وإلا {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC موقت_context = _this->gl_داده->wglCreateContext(hdc);
        إذا (!موقت_context) {
            SDL_مجموعه_Error("Could not create GL context");
            أرجع عدم;
        }

        // Make the context current
        إذا (!WIN_GL_MakeCurrent(_this, پنجره, (SDL_GLContext)موقت_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)موقت_context);
            أرجع عدم;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_داده->wgl_Get_Proc_آدرس("wglCreateContextAttribsARB");
        إذا (!wglCreateContextAttribsARB) {
            SDL_مجموعه_Error("GL 3.x is not supported");
            context = موقت_context;
        } وإلا {
            صحيح attribs[15]; // max 14 attributes plus terminator
            صحيح iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_نسخه_ARB;
            attribs[iattr++] = _this->gl_config.major_نسخه;
            attribs[iattr++] = WGL_CONTEXT_MINOR_نسخه_ARB;
            attribs[iattr++] = _this->gl_config.minor_نسخه;

            // SDL profile bits match WGL profile bits
            إذا (_this->gl_config.profile_ماسک != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_ماسک_ARB;
                attribs[iattr++] = _this->gl_config.profile_ماسک;
            }

            // SDL flags match WGL flags
            إذا (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            إذا ((_this->gl_داده->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            إذا ((_this->gl_داده->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            إذا ((_this->gl_داده->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_داده->wglDeleteContext(موقت_context);
        }
    }

    إذا (!context) {
        WIN_مجموعه_Error("Could not create GL context");
        أرجع عدم;
    }

    إذا (!WIN_GL_MakeCurrent(_this, پنجره, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        أرجع عدم;
    }

    _this->gl_config.HAS_GL_ARB_color_میانگیر_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    أرجع (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context)
{
    HDC hdc;

    إذا (!_this->gl_داده) {
        أرجع SDL_مجموعه_Error("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(پنجره || (پنجره == عدم && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    إذا (!پنجره) {
        پنجره = SDL_GL_Get_Current_پنجره();
        إذا (!پنجره) {
            SDL_assert(SDL_GL_GetCurrentContext() == عدم);
            أرجع true; // already done.
        }
    }

    hdc = پنجره->داخلی->hdc;
    إذا (!_this->gl_داده->wglMakeCurrent(hdc, (HGLRC)context)) {
        أرجع WIN_مجموعه_Error("wglMakeCurrent()");
    }
    أرجع true;
}

bool WIN_GL_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    إذا ((interval < 0) && (!_this->gl_داده->HAS_WGL_EXT_جابجا_control_tear)) {
        أرجع SDL_مجموعه_Error("Negative swap interval unsupported in this GL");
    } وإلا إذا (_this->gl_داده->wgl_جابجا_Interval_EXT) {
        إذا (!_this->gl_داده->wgl_جابجا_Interval_EXT(interval)) {
            أرجع WIN_مجموعه_Error("wglSwapIntervalEXT()");
        }
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

bool WIN_GL_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    إذا (_this->gl_داده->wgl_Get_جابجا_Interval_EXT) {
        *interval = _this->gl_داده->wgl_Get_جابجا_Interval_EXT();
        أرجع true;
    } وإلا {
        أرجع SDL_Unsupported();
    }
}

bool WIN_GL_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    HDC hdc = پنجره->داخلی->hdc;

    إذا (!جابجا_Buffers(hdc)) {
        أرجع WIN_مجموعه_Error("SwapBuffers()");
    }
    أرجع true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    إذا (!_this->gl_داده) {
        أرجع true;
    }
    _this->gl_داده->wglDeleteContext((HGLRC)context);
    أرجع true;
}

#پایان_اگر // SDL_VIDEO_OPENGL_WGL

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS
