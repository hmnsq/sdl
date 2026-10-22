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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowsopengles.h"
#ضمن "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL
#ضمن <SDL3/SDL_opengl.h>

#وصف_ڪريو DEFAULT_OPENGL "OPENGL32.DLL"

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_create_context
#وصف_ڪريو WGL_ARB_create_context
#وصف_ڪريو WGL_CONTEXT_MAJOR_نسخو_ARB          0x2091
#وصف_ڪريو WGL_CONTEXT_MINOR_نسخو_ARB          0x2092
#وصف_ڪريو WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#وصف_ڪريو WGL_CONTEXT_FLAGS_ARB                  0x2094
#وصف_ڪريو WGL_CONTEXT_DEBUG_ٻٽو_انگ_ARB              0x0001
#وصف_ڪريو WGL_CONTEXT_FORWARD_COMPATIBLE_ٻٽو_انگ_ARB 0x0002

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_create_context_profile
#وصف_ڪريو WGL_ARB_create_context_profile
#وصف_ڪريو WGL_CONTEXT_PROFILE_نقاب_ARB              0x9126
#وصف_ڪريو WGL_CONTEXT_CORE_PROFILE_ٻٽو_انگ_ARB          0x00000001
#وصف_ڪريو WGL_CONTEXT_COMPATIBILITY_PROFILE_ٻٽو_انگ_ARB 0x00000002
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_create_context_robustness
#وصف_ڪريو WGL_ARB_create_context_robustness
#وصف_ڪريو WGL_CONTEXT_ROBUST_ACCESS_ٻٽو_انگ_ARB           0x00000004
#وصف_ڪريو WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#وصف_ڪريو WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#وصف_ڪريو WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_EXT_create_context_es2_profile
#وصف_ڪريو WGL_EXT_create_context_es2_profile
#وصف_ڪريو WGL_CONTEXT_ES2_PROFILE_ٻٽو_انگ_EXT 0x00000004
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_EXT_create_context_es_profile
#وصف_ڪريو WGL_EXT_create_context_es_profile
#وصف_ڪريو WGL_CONTEXT_ES_PROFILE_ٻٽو_انگ_EXT 0x00000004
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_framebuffer_sRGB
#وصف_ڪريو WGL_ARB_framebuffer_sRGB
#وصف_ڪريو WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_pixel_format_float
#وصف_ڪريو WGL_ARB_pixel_format_float
#وصف_ڪريو WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_context_flush_control
#وصف_ڪريو WGL_ARB_context_flush_control
#وصف_ڪريو WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#وصف_ڪريو WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#وصف_ڪريو WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_create_context_no_error
#وصف_ڪريو WGL_ARB_create_context_no_error
#وصف_ڪريو WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#جيڪڏهن_پورو

تعريفنوع HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           ثابت صحيح
                                                               *attribList);

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#وصف_ڪريو GetDC(hwnd)          (HDC) hwnd
#وصف_ڪريو ReleaseDC(hwnd, hdc) 1
#وصف_ڪريو مٽا_سٽا_Buffers          _this->gl_معلومات->wgl_مٽا_سٽا_Buffers
#وصف_ڪريو DescribePixelFormat  _this->gl_معلومات->wglDescribePixelFormat
#وصف_ڪريو چونڊيو_Pixel_Format    _this->gl_معلومات->wgl_چونڊيو_Pixel_Format
#وصف_ڪريو GetPixelFormat       _this->gl_معلومات->wglGetPixelFormat
#وصف_ڪريو سيٽ_Pixel_Format       _this->gl_معلومات->wgl_سيٽ_Pixel_Format
#جيڪڏهن_پورو

ساكن bool WIN_GL_ڀريو_Library_EGLFallback(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_ڀريو_Library = WIN_GLES_ڀريو_Library;
    _this->GL_Get_Proc_پتو = WIN_GLES_Get_Proc_پتو;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_سيٽ_مٽا_سٽا_Interval = WIN_GLES_سيٽ_مٽا_سٽا_Interval;
    _this->GL_Get_مٽا_سٽا_Interval = WIN_GLES_Get_مٽا_سٽا_Interval;
    _this->GL_مٽا_سٽا_دري = WIN_GLES_مٽا_سٽا_دري;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    أرجع WIN_GLES_ڀريو_Library(_this, رستو);
#وإلا
    أرجع SDL_سيٽ_Error("SDL not configured with EGL support");
#جيڪڏهن_پورو
}

bool WIN_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    فراغ *handle;

    إذا ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        أرجع WIN_GL_ڀريو_Library_EGLFallback(_this, رستو);
    }

    إذا (رستو == عدم) {
        رستو = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    إذا (رستو == عدم) {
        رستو = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ڀريو_Object(رستو);
    إذا (!_this->gl_config.dll_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_رستو, رستو,
                SDL_arraysize(_this->gl_config.driver_رستو));

    // Allocate OpenGL memory
    _this->gl_معلومات = (بنية SDL_GLDriver_معلومات *)SDL_calloc(1, حجم(بنية SDL_GLDriver_معلومات));
    إذا (!_this->gl_معلومات) {
        أرجع false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_معلومات->wgl_Get_Proc_پتو = (PROC (WINAPI *)(ثابت حرف *))
        SDL_ڀريو_Function(handle, "wglGetProcAddress");
    _this->gl_معلومات->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_ڀريو_Function(handle, "wglCreateContext");
    _this->gl_معلومات->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_ڀريو_Function(handle, "wglDeleteContext");
    _this->gl_معلومات->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_ڀريو_Function(handle, "wglMakeCurrent");
    _this->gl_معلومات->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_ڀريو_Function(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_معلومات->wgl_مٽا_سٽا_Buffers = (BOOL(WINAPI *)(HDC))
        SDL_ڀريو_Function(handle, "wglSwapBuffers");
    _this->gl_معلومات->wglDescribePixelFormat = (صحيح(WINAPI *)(HDC, صحيح, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_ڀريو_Function(handle, "wglDescribePixelFormat");
    _this->gl_معلومات->wgl_چونڊيو_Pixel_Format = (صحيح(WINAPI *)(HDC, ثابت PIXELFORMATDESCRIPTOR *))
        SDL_ڀريو_Function(handle, "wglChoosePixelFormat");
    _this->gl_معلومات->wgl_سيٽ_Pixel_Format = (BOOL(WINAPI *)(HDC, صحيح, ثابت PIXELFORMATDESCRIPTOR *))
        SDL_ڀريو_Function(handle, "wglSetPixelFormat");
    _this->gl_معلومات->wglGetPixelFormat = (صحيح(WINAPI *)(HDC hdc))
        SDL_ڀريو_Function(handle, "wglGetPixelFormat");
#جيڪڏهن_پورو

    إذا (!_this->gl_معلومات->wgl_Get_Proc_پتو ||
        !_this->gl_معلومات->wglCreateContext ||
        !_this->gl_معلومات->wglDeleteContext ||
        !_this->gl_معلومات->wglMakeCurrent
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_معلومات->wgl_مٽا_سٽا_Buffers ||
        !_this->gl_معلومات->wglDescribePixelFormat ||
        !_this->gl_معلومات->wgl_چونڊيو_Pixel_Format ||
        !_this->gl_معلومات->wglGetPixelFormat ||
        !_this->gl_معلومات->wgl_سيٽ_Pixel_Format
#جيڪڏهن_پورو
    ) {
        أرجع SDL_سيٽ_Error("Could not retrieve OpenGL functions");
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

SDL_Function_اشارو WIN_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشارو func;

    // This is to pick up extensions
    func = (SDL_Function_اشارو)_this->gl_معلومات->wgl_Get_Proc_پتو(proc);
    إذا (!func) {
        // This is probably a normal GL function
        func = (SDL_Function_اشارو)Get_Proc_پتو((HMODULE)_this->gl_config.dll_handle, proc);
    }
    أرجع func;
}

فراغ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = عدم;

    // Free OpenGL memory
    SDL_free(_this->gl_معلومات);
    _this->gl_معلومات = عدم;
}

ساكن فراغ WIN_GL_تياري_Pixel_Format(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_سائيز = حجم(*pfd);
    pfd->n_نسخو = 1;
    pfd->dwFlags = (PFD_DRAW_منزل_دري | PFD_SUPPORT_OPENGL);
    إذا (_this->gl_config.double_بفر) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    إذا (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->c_Red_بٽ = (BYTE)_this->gl_config.red_سائيز;
    pfd->c_Green_بٽ = (BYTE)_this->gl_config.green_سائيز;
    pfd->c_Blue_بٽ = (BYTE)_this->gl_config.blue_سائيز;
    pfd->c_Alpha_بٽ = (BYTE)_this->gl_config.alpha_سائيز;
    إذا (_this->gl_config.بفر_سائيز) {
        pfd->c_Color_بٽ = (BYTE)(_this->gl_config.بفر_سائيز - _this->gl_config.alpha_سائيز);
    } وإلا {
        pfd->c_Color_بٽ = (pfd->c_Red_بٽ + pfd->c_Green_بٽ + pfd->c_Blue_بٽ);
    }
    pfd->c_Accum_Red_بٽ = (BYTE)_this->gl_config.accum_red_سائيز;
    pfd->c_Accum_Green_بٽ = (BYTE)_this->gl_config.accum_green_سائيز;
    pfd->c_Accum_Blue_بٽ = (BYTE)_this->gl_config.accum_blue_سائيز;
    pfd->c_Accum_Alpha_بٽ = (BYTE)_this->gl_config.accum_alpha_سائيز;
    pfd->c_Accum_بٽ =
        (pfd->c_Accum_Red_بٽ + pfd->c_Accum_Green_بٽ + pfd->c_Accum_Blue_بٽ +
         pfd->c_Accum_Alpha_بٽ);
    pfd->c_اونهائي_بٽ = (BYTE)_this->gl_config.اونهائي_سائيز;
    pfd->c_Stencil_بٽ = (BYTE)_this->gl_config.stencil_سائيز;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
ساكن bool WIN_GL_چونڊيو_Pixel_Format(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *هدف)
{
    PIXELFORMATDESCRIPTOR pfd;
    صحيح ڳڻپ, اشاريو, بهترين = 0;
    بنانشان صحيح dist, بهترين_dist = ~0U;

    ڳڻپ = DescribePixelFormat(hdc, 1, حجم(pfd), عدم);

    لكل (اشاريو = 1; اشاريو <= ڳڻپ; اشاريو++) {

        إذا (!DescribePixelFormat(hdc, اشاريو, حجم(pfd), &pfd)) {
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

        إذا (pfd.c_Color_بٽ < هدف->c_Color_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Color_بٽ - هدف->c_Color_بٽ);
        }
        إذا (pfd.c_Red_بٽ < هدف->c_Red_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Red_بٽ - هدف->c_Red_بٽ);
        }
        إذا (pfd.c_Green_بٽ < هدف->c_Green_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Green_بٽ - هدف->c_Green_بٽ);
        }
        إذا (pfd.c_Blue_بٽ < هدف->c_Blue_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Blue_بٽ - هدف->c_Blue_بٽ);
        }
        إذا (pfd.c_Alpha_بٽ < هدف->c_Alpha_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Alpha_بٽ - هدف->c_Alpha_بٽ);
        }
        إذا (pfd.c_Accum_بٽ < هدف->c_Accum_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_بٽ - هدف->c_Accum_بٽ);
        }
        إذا (pfd.c_Accum_Red_بٽ < هدف->c_Accum_Red_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Red_بٽ - هدف->c_Accum_Red_بٽ);
        }
        إذا (pfd.c_Accum_Green_بٽ < هدف->c_Accum_Green_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Green_بٽ - هدف->c_Accum_Green_بٽ);
        }
        إذا (pfd.c_Accum_Blue_بٽ < هدف->c_Accum_Blue_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Blue_بٽ - هدف->c_Accum_Blue_بٽ);
        }
        إذا (pfd.c_Accum_Alpha_بٽ < هدف->c_Accum_Alpha_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Accum_Alpha_بٽ - هدف->c_Accum_Alpha_بٽ);
        }
        إذا (pfd.c_اونهائي_بٽ < هدف->c_اونهائي_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_اونهائي_بٽ - هدف->c_اونهائي_بٽ);
        }
        إذا (pfd.c_Stencil_بٽ < هدف->c_Stencil_بٽ) {
            استمر;
        } وإلا {
            dist += (pfd.c_Stencil_بٽ - هدف->c_Stencil_بٽ);
        }

        إذا (dist < بهترين_dist) {
            بهترين = اشاريو;
            بهترين_dist = dist;
        }
    }

    أرجع بهترين;
}

ساكن bool HasExtension(ثابت حرف *extension, ثابت حرف *extensions)
{
    ثابت حرف *شروعات;
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

    شروعات = extensions;

    لكل (;;) {
        where = SDL_strstr(شروعات, extension);
        إذا (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        إذا (where == شروعات || *(where - 1) == ' ') {
            إذا (*terminator == ' ' || *terminator == '\0') {
                أرجع true;
            }
        }

        شروعات = terminator;
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

    إذا (!_this->gl_معلومات) {
        أرجع;
    }

    hwnd =
        Create_دري(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, عدم, عدم, SDL_Instance, عدم);
    إذا (!hwnd) {
        أرجع;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_تياري_Pixel_Format(_this, &pfd);

    سيٽ_Pixel_Format(hdc, چونڊيو_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_معلومات->wglCreateContext(hdc);
    إذا (!hglrc) {
        أرجع;
    }
    _this->gl_معلومات->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (ثابت حرف *(WINAPI *)(HDC))
        _this->gl_معلومات->wgl_Get_Proc_پتو("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    إذا (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } وإلا {
        extensions = عدم;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_معلومات->HAS_WGL_ARB_pixel_format = false;
    إذا (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_معلومات->wgl_چونڊيو_Pixel_Format_ARB =
            (BOOL (WINAPI *)(HDC, ثابت صحيح *, ثابت FLOAT *, UINT, صحيح *, UINT *))
            WIN_GL_Get_Proc_پتو(_this, "wglChoosePixelFormatARB");
        _this->gl_معلومات->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, صحيح, صحيح, UINT, ثابت صحيح *, صحيح *))
            WIN_GL_Get_Proc_پتو(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        إذا ((_this->gl_معلومات->wgl_چونڊيو_Pixel_Format_ARB != عدم) &&
            (_this->gl_معلومات->wglGetPixelFormatAttribivARB != عدم)) {
            _this->gl_معلومات->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_معلومات->HAS_WGL_EXT_مٽا_سٽا_control_tear = false;
    إذا (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_معلومات->wgl_مٽا_سٽا_Interval_EXT =
            (BOOL (WINAPI *)(صحيح))
            WIN_GL_Get_Proc_پتو(_this, "wglSwapIntervalEXT");
        _this->gl_معلومات->wgl_Get_مٽا_سٽا_Interval_EXT =
            (صحيح (WINAPI *)(فراغ))
            WIN_GL_Get_Proc_پتو(_this, "wglGetSwapIntervalEXT");
        إذا (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_معلومات->HAS_WGL_EXT_مٽا_سٽا_control_tear = true;
        }
    } وإلا {
        _this->gl_معلومات->wgl_مٽا_سٽا_Interval_EXT = عدم;
        _this->gl_معلومات->wgl_Get_مٽا_سٽا_Interval_EXT = عدم;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_معلومات->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    إذا (_this->gl_معلومات->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_معلومات->es_profile_max_supported_نسخو.major,
            &_this->gl_معلومات->es_profile_max_supported_نسخو.minor);
    }

    // Check for WGL_ARB_context_flush_control
    إذا (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_معلومات->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    إذا (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_معلومات->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    إذا (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_معلومات->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    إذا (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_معلومات->HAS_WGL_ARB_framebuffer_sRGB = true;
    } وإلا إذا (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_معلومات->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_معلومات->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_معلومات->wglMakeCurrent(hdc, عدم);
    _this->gl_معلومات->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    Destroy_دري(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

ساكن صحيح WIN_GL_چونڊيو_Pixel_Format_ARB(SDL_VideoDevice *_this, صحيح *iAttribs, عائم *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    صحيح pixel_format = 0;
    بنانشان صحيح matching;

    hwnd =
        Create_دري(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, عدم, عدم, SDL_Instance, عدم);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_تياري_Pixel_Format(_this, &pfd);

    سيٽ_Pixel_Format(hdc, چونڊيو_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_معلومات->wglCreateContext(hdc);
    إذا (hglrc) {
        _this->gl_معلومات->wglMakeCurrent(hdc, hglrc);

        إذا (_this->gl_معلومات->HAS_WGL_ARB_pixel_format) {
            _this->gl_معلومات->wgl_چونڊيو_Pixel_Format_ARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            صحيح srgb = 0;
            إذا (_this->gl_معلومات->HAS_WGL_ARB_framebuffer_sRGB) {
                صحيح qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_معلومات->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_معلومات->wglMakeCurrent(hdc, عدم);
        _this->gl_معلومات->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    Destroy_دري(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    أرجع pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
ساكن bool WIN_GL_تياري_دري_اندروني(SDL_VideoDevice *_this, SDL_دري *دري)
{
    HDC hdc = دري->اندروني->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    صحيح pixel_format = 0;
    صحيح iAttribs[64];
    صحيح *iAttr;
    صحيح *iAccelAttr;
    عائم fAttribs[1] = { 0 };

    WIN_GL_تياري_Pixel_Format(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_منزل_دري_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_بٽ_ARB;
    *iAttr++ = _this->gl_config.red_سائيز;
    *iAttr++ = WGL_GREEN_بٽ_ARB;
    *iAttr++ = _this->gl_config.green_سائيز;
    *iAttr++ = WGL_BLUE_بٽ_ARB;
    *iAttr++ = _this->gl_config.blue_سائيز;

    إذا (_this->gl_config.alpha_سائيز) {
        *iAttr++ = WGL_ALPHA_بٽ_ARB;
        *iAttr++ = _this->gl_config.alpha_سائيز;
    }

    *iAttr++ = WGL_DOUBLE_بفر_ARB;
    *iAttr++ = _this->gl_config.double_بفر;

    *iAttr++ = WGL_اونهائي_بٽ_ARB;
    *iAttr++ = _this->gl_config.اونهائي_سائيز;

    إذا (_this->gl_config.stencil_سائيز) {
        *iAttr++ = WGL_STENCIL_بٽ_ARB;
        *iAttr++ = _this->gl_config.stencil_سائيز;
    }

    إذا (_this->gl_config.accum_red_سائيز) {
        *iAttr++ = WGL_ACCUM_RED_بٽ_ARB;
        *iAttr++ = _this->gl_config.accum_red_سائيز;
    }

    إذا (_this->gl_config.accum_green_سائيز) {
        *iAttr++ = WGL_ACCUM_GREEN_بٽ_ARB;
        *iAttr++ = _this->gl_config.accum_green_سائيز;
    }

    إذا (_this->gl_config.accum_blue_سائيز) {
        *iAttr++ = WGL_ACCUM_BLUE_بٽ_ARB;
        *iAttr++ = _this->gl_config.accum_blue_سائيز;
    }

    إذا (_this->gl_config.accum_alpha_سائيز) {
        *iAttr++ = WGL_ACCUM_ALPHA_بٽ_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_سائيز;
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

    إذا (_this->gl_معلومات->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    إذا (_this->gl_معلومات->HAS_WGL_ARB_framebuffer_sRGB) {
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
        *iAttr++ = WGL_ڀريل_ACCELERATION_ARB;
    } وإلا {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_چونڊيو_Pixel_Format_ARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    إذا ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_چونڊيو_Pixel_Format_ARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_ڀريل_ACCELERATION_ARB; // if we try again.
    }
    إذا (!pixel_format) {
        pixel_format = WIN_GL_چونڊيو_Pixel_Format(_this, hdc, &pfd);
    }
    إذا (!pixel_format) {
        أرجع SDL_سيٽ_Error("No matching GL pixel format available");
    }
    إذا (!سيٽ_Pixel_Format(hdc, pixel_format, &pfd)) {
        أرجع WIN_سيٽ_Error("SetPixelFormat()");
    }
    أرجع true;
}

bool WIN_GL_تياري_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // The current context is lost in here; save it and reset it.
    SDL_دري *current_win = SDL_GL_Get_Current_دري();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    ثابت صحيح نتيجو = WIN_GL_تياري_دري_اندروني(_this, دري);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    أرجع نتيجو;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_معلومات != عدم);
    SDL_assert(_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    أرجع !_this->gl_معلومات->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_نسخو > _this->gl_معلومات->es_profile_max_supported_نسخو.major ||
           (_this->gl_config.major_نسخو == _this->gl_معلومات->es_profile_max_supported_نسخو.major && _this->gl_config.minor_نسخو > _this->gl_معلومات->es_profile_max_supported_نسخو.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري)
{
    HDC hdc = دري->اندروني->hdc;
    HGLRC context, share_context;

    إذا (_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        إذا (!WIN_GL_ڀريو_Library_EGLFallback(_this, عدم)) {
            أرجع عدم;
        }

        أرجع WIN_GLES_CreateContext(_this, دري);
#وإلا
        SDL_سيٽ_Error("SDL not configured with EGL support");
        أرجع عدم;
#جيڪڏهن_پورو
    }

    إذا (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } وإلا {
        share_context = 0;
    }

    إذا (_this->gl_config.major_نسخو < 3 &&
        _this->gl_config.profile_نقاب == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_معلومات->wglCreateContext(hdc);
        إذا (share_context != 0) {
            _this->gl_معلومات->wglShareLists(share_context, context);
        }
    } وإلا {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC عارضي_context = _this->gl_معلومات->wglCreateContext(hdc);
        إذا (!عارضي_context) {
            SDL_سيٽ_Error("Could not create GL context");
            أرجع عدم;
        }

        // Make the context current
        إذا (!WIN_GL_MakeCurrent(_this, دري, (SDL_GLContext)عارضي_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)عارضي_context);
            أرجع عدم;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_معلومات->wgl_Get_Proc_پتو("wglCreateContextAttribsARB");
        إذا (!wglCreateContextAttribsARB) {
            SDL_سيٽ_Error("GL 3.x is not supported");
            context = عارضي_context;
        } وإلا {
            صحيح attribs[15]; // max 14 attributes plus terminator
            صحيح iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_نسخو_ARB;
            attribs[iattr++] = _this->gl_config.major_نسخو;
            attribs[iattr++] = WGL_CONTEXT_MINOR_نسخو_ARB;
            attribs[iattr++] = _this->gl_config.minor_نسخو;

            // SDL profile bits match WGL profile bits
            إذا (_this->gl_config.profile_نقاب != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_نقاب_ARB;
                attribs[iattr++] = _this->gl_config.profile_نقاب;
            }

            // SDL flags match WGL flags
            إذا (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            إذا ((_this->gl_معلومات->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            إذا ((_this->gl_معلومات->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            إذا ((_this->gl_معلومات->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_معلومات->wglDeleteContext(عارضي_context);
        }
    }

    إذا (!context) {
        WIN_سيٽ_Error("Could not create GL context");
        أرجع عدم;
    }

    إذا (!WIN_GL_MakeCurrent(_this, دري, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        أرجع عدم;
    }

    _this->gl_config.HAS_GL_ARB_color_بفر_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    أرجع (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context)
{
    HDC hdc;

    إذا (!_this->gl_معلومات) {
        أرجع SDL_سيٽ_Error("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(دري || (دري == عدم && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    إذا (!دري) {
        دري = SDL_GL_Get_Current_دري();
        إذا (!دري) {
            SDL_assert(SDL_GL_GetCurrentContext() == عدم);
            أرجع true; // already done.
        }
    }

    hdc = دري->اندروني->hdc;
    إذا (!_this->gl_معلومات->wglMakeCurrent(hdc, (HGLRC)context)) {
        أرجع WIN_سيٽ_Error("wglMakeCurrent()");
    }
    أرجع true;
}

bool WIN_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    إذا ((interval < 0) && (!_this->gl_معلومات->HAS_WGL_EXT_مٽا_سٽا_control_tear)) {
        أرجع SDL_سيٽ_Error("Negative swap interval unsupported in this GL");
    } وإلا إذا (_this->gl_معلومات->wgl_مٽا_سٽا_Interval_EXT) {
        إذا (!_this->gl_معلومات->wgl_مٽا_سٽا_Interval_EXT(interval)) {
            أرجع WIN_سيٽ_Error("wglSwapIntervalEXT()");
        }
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

bool WIN_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    إذا (_this->gl_معلومات->wgl_Get_مٽا_سٽا_Interval_EXT) {
        *interval = _this->gl_معلومات->wgl_Get_مٽا_سٽا_Interval_EXT();
        أرجع true;
    } وإلا {
        أرجع SDL_Unsupported();
    }
}

bool WIN_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    HDC hdc = دري->اندروني->hdc;

    إذا (!مٽا_سٽا_Buffers(hdc)) {
        أرجع WIN_سيٽ_Error("SwapBuffers()");
    }
    أرجع true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    إذا (!_this->gl_معلومات) {
        أرجع true;
    }
    _this->gl_معلومات->wglDeleteContext((HGLRC)context);
    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_WGL

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS
