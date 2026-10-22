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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

#شامل "SDL_windowsvideo.h"
#شامل "SDL_windowsopengles.h"
#شامل "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
#شامل <SDL3/SDL_opengl.h>

#تعریف_کرو DEFAULT_OPENGL "OPENGL32.DLL"

#اگر_غیر_تعریف_شدہ WGL_ARB_create_context
#تعریف_کرو WGL_ARB_create_context
#تعریف_کرو WGL_CONTEXT_MAJOR_نسخہ_ARB          0x2091
#تعریف_کرو WGL_CONTEXT_MINOR_نسخہ_ARB          0x2092
#تعریف_کرو WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#تعریف_کرو WGL_CONTEXT_FLAGS_ARB                  0x2094
#تعریف_کرو WGL_CONTEXT_DEBUG_ثنائی_ہندسہ_ARB              0x0001
#تعریف_کرو WGL_CONTEXT_FORWARD_COMPATIBLE_ثنائی_ہندسہ_ARB 0x0002

#اگر_غیر_تعریف_شدہ WGL_ARB_create_context_profile
#تعریف_کرو WGL_ARB_create_context_profile
#تعریف_کرو WGL_CONTEXT_PROFILE_نقاب_ARB              0x9126
#تعریف_کرو WGL_CONTEXT_CORE_PROFILE_ثنائی_ہندسہ_ARB          0x00000001
#تعریف_کرو WGL_CONTEXT_COMPATIBILITY_PROFILE_ثنائی_ہندسہ_ARB 0x00000002
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_ARB_create_context_robustness
#تعریف_کرو WGL_ARB_create_context_robustness
#تعریف_کرو WGL_CONTEXT_ROBUST_ACCESS_ثنائی_ہندسہ_ARB           0x00000004
#تعریف_کرو WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#تعریف_کرو WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#تعریف_کرو WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#اگر_ختم
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_EXT_create_context_es2_profile
#تعریف_کرو WGL_EXT_create_context_es2_profile
#تعریف_کرو WGL_CONTEXT_ES2_PROFILE_ثنائی_ہندسہ_EXT 0x00000004
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_EXT_create_context_es_profile
#تعریف_کرو WGL_EXT_create_context_es_profile
#تعریف_کرو WGL_CONTEXT_ES_PROFILE_ثنائی_ہندسہ_EXT 0x00000004
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_ARB_framebuffer_sRGB
#تعریف_کرو WGL_ARB_framebuffer_sRGB
#تعریف_کرو WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_ARB_pixel_format_float
#تعریف_کرو WGL_ARB_pixel_format_float
#تعریف_کرو WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_ARB_context_flush_control
#تعریف_کرو WGL_ARB_context_flush_control
#تعریف_کرو WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#تعریف_کرو WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#تعریف_کرو WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_ARB_create_context_no_error
#تعریف_کرو WGL_ARB_create_context_no_error
#تعریف_کرو WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#اگر_ختم

قسمتعریف HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           ثابت صحیح
                                                               *attribList);

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#تعریف_کرو GetDC(hwnd)          (HDC) hwnd
#تعریف_کرو ReleaseDC(hwnd, hdc) 1
#تعریف_کرو تبادلہ_Buffers          _this->gl_ڈیٹا->wgl_تبادلہ_Buffers
#تعریف_کرو DescribePixelFormat  _this->gl_ڈیٹا->wglDescribePixelFormat
#تعریف_کرو انتخاب_Pixel_Format    _this->gl_ڈیٹا->wgl_انتخاب_Pixel_Format
#تعریف_کرو GetPixelFormat       _this->gl_ڈیٹا->wglGetPixelFormat
#تعریف_کرو سیٹ_Pixel_Format       _this->gl_ڈیٹا->wgl_سیٹ_Pixel_Format
#اگر_ختم

ساکن bool WIN_GL_بھرو_Library_EGLFallback(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_بھرو_Library = WIN_GLES_بھرو_Library;
    _this->GL_Get_Proc_پتہ = WIN_GLES_Get_Proc_پتہ;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_سیٹ_تبادلہ_Interval = WIN_GLES_سیٹ_تبادلہ_Interval;
    _this->GL_Get_تبادلہ_Interval = WIN_GLES_Get_تبادلہ_Interval;
    _this->GL_تبادلہ_کھڑکی = WIN_GLES_تبادلہ_کھڑکی;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    واپس WIN_GLES_بھرو_Library(_this, راستہ);
#ورنہ
    واپس SDL_سیٹ_Error("SDL not configured with EGL support");
#اگر_ختم
}

bool WIN_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    خالی *handle;

    اگر ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        واپس WIN_GL_بھرو_Library_EGLFallback(_this, راستہ);
    }

    اگر (راستہ == تہی) {
        راستہ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    اگر (راستہ == تہی) {
        راستہ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_بھرو_Object(راستہ);
    اگر (!_this->gl_config.dll_handle) {
        واپس false;
    }
    SDL_strlcpy(_this->gl_config.driver_راستہ, راستہ,
                SDL_arraysize(_this->gl_config.driver_راستہ));

    // Allocate OpenGL memory
    _this->gl_ڈیٹا = (ساخت SDL_GLDriver_ڈیٹا *)SDL_calloc(1, حجم(ساخت SDL_GLDriver_ڈیٹا));
    اگر (!_this->gl_ڈیٹا) {
        واپس false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_ڈیٹا->wgl_Get_Proc_پتہ = (PROC (WINAPI *)(ثابت حرف *))
        SDL_بھرو_Function(handle, "wglGetProcAddress");
    _this->gl_ڈیٹا->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_بھرو_Function(handle, "wglCreateContext");
    _this->gl_ڈیٹا->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_بھرو_Function(handle, "wglDeleteContext");
    _this->gl_ڈیٹا->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_بھرو_Function(handle, "wglMakeCurrent");
    _this->gl_ڈیٹا->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_بھرو_Function(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_ڈیٹا->wgl_تبادلہ_Buffers = (BOOL(WINAPI *)(HDC))
        SDL_بھرو_Function(handle, "wglSwapBuffers");
    _this->gl_ڈیٹا->wglDescribePixelFormat = (صحیح(WINAPI *)(HDC, صحیح, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_بھرو_Function(handle, "wglDescribePixelFormat");
    _this->gl_ڈیٹا->wgl_انتخاب_Pixel_Format = (صحیح(WINAPI *)(HDC, ثابت PIXELFORMATDESCRIPTOR *))
        SDL_بھرو_Function(handle, "wglChoosePixelFormat");
    _this->gl_ڈیٹا->wgl_سیٹ_Pixel_Format = (BOOL(WINAPI *)(HDC, صحیح, ثابت PIXELFORMATDESCRIPTOR *))
        SDL_بھرو_Function(handle, "wglSetPixelFormat");
    _this->gl_ڈیٹا->wglGetPixelFormat = (صحیح(WINAPI *)(HDC hdc))
        SDL_بھرو_Function(handle, "wglGetPixelFormat");
#اگر_ختم

    اگر (!_this->gl_ڈیٹا->wgl_Get_Proc_پتہ ||
        !_this->gl_ڈیٹا->wglCreateContext ||
        !_this->gl_ڈیٹا->wglDeleteContext ||
        !_this->gl_ڈیٹا->wglMakeCurrent
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_ڈیٹا->wgl_تبادلہ_Buffers ||
        !_this->gl_ڈیٹا->wglDescribePixelFormat ||
        !_this->gl_ڈیٹا->wgl_انتخاب_Pixel_Format ||
        !_this->gl_ڈیٹا->wglGetPixelFormat ||
        !_this->gl_ڈیٹا->wgl_سیٹ_Pixel_Format
#اگر_ختم
    ) {
        واپس SDL_سیٹ_Error("Could not retrieve OpenGL functions");
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

    واپس true;
}

SDL_Function_اشارہ_گر WIN_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشارہ_گر func;

    // This is to pick up extensions
    func = (SDL_Function_اشارہ_گر)_this->gl_ڈیٹا->wgl_Get_Proc_پتہ(proc);
    اگر (!func) {
        // This is probably a normal GL function
        func = (SDL_Function_اشارہ_گر)Get_Proc_پتہ((HMODULE)_this->gl_config.dll_handle, proc);
    }
    واپس func;
}

خالی WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = تہی;

    // Free OpenGL memory
    SDL_free(_this->gl_ڈیٹا);
    _this->gl_ڈیٹا = تہی;
}

ساکن خالی WIN_GL_تیاری_Pixel_Format(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_سائز = حجم(*pfd);
    pfd->n_نسخہ = 1;
    pfd->dwFlags = (PFD_DRAW_مقصد_کھڑکی | PFD_SUPPORT_OPENGL);
    اگر (_this->gl_config.double_بفر) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    اگر (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->c_Red_بٹ = (BYTE)_this->gl_config.red_سائز;
    pfd->c_Green_بٹ = (BYTE)_this->gl_config.green_سائز;
    pfd->c_Blue_بٹ = (BYTE)_this->gl_config.blue_سائز;
    pfd->c_Alpha_بٹ = (BYTE)_this->gl_config.alpha_سائز;
    اگر (_this->gl_config.بفر_سائز) {
        pfd->c_Color_بٹ = (BYTE)(_this->gl_config.بفر_سائز - _this->gl_config.alpha_سائز);
    } ورنہ {
        pfd->c_Color_بٹ = (pfd->c_Red_بٹ + pfd->c_Green_بٹ + pfd->c_Blue_بٹ);
    }
    pfd->c_Accum_Red_بٹ = (BYTE)_this->gl_config.accum_red_سائز;
    pfd->c_Accum_Green_بٹ = (BYTE)_this->gl_config.accum_green_سائز;
    pfd->c_Accum_Blue_بٹ = (BYTE)_this->gl_config.accum_blue_سائز;
    pfd->c_Accum_Alpha_بٹ = (BYTE)_this->gl_config.accum_alpha_سائز;
    pfd->c_Accum_بٹ =
        (pfd->c_Accum_Red_بٹ + pfd->c_Accum_Green_بٹ + pfd->c_Accum_Blue_بٹ +
         pfd->c_Accum_Alpha_بٹ);
    pfd->c_گہرائی_بٹ = (BYTE)_this->gl_config.گہرائی_سائز;
    pfd->c_Stencil_بٹ = (BYTE)_this->gl_config.stencil_سائز;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
ساکن bool WIN_GL_انتخاب_Pixel_Format(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *ہدف)
{
    PIXELFORMATDESCRIPTOR pfd;
    صحیح گنتی, اشاریہ, بہترین = 0;
    غیرعلامتی صحیح dist, بہترین_dist = ~0U;

    گنتی = DescribePixelFormat(hdc, 1, حجم(pfd), تہی);

    برائے (اشاریہ = 1; اشاریہ <= گنتی; اشاریہ++) {

        اگر (!DescribePixelFormat(hdc, اشاریہ, حجم(pfd), &pfd)) {
            جاری;
        }

        اگر ((pfd.dwFlags & ہدف->dwFlags) != ہدف->dwFlags) {
            جاری;
        }

        اگر (pfd.iLayerType != ہدف->iLayerType) {
            جاری;
        }
        اگر (pfd.iPixelType != ہدف->iPixelType) {
            جاری;
        }

        dist = 0;

        اگر (pfd.c_Color_بٹ < ہدف->c_Color_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Color_بٹ - ہدف->c_Color_بٹ);
        }
        اگر (pfd.c_Red_بٹ < ہدف->c_Red_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Red_بٹ - ہدف->c_Red_بٹ);
        }
        اگر (pfd.c_Green_بٹ < ہدف->c_Green_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Green_بٹ - ہدف->c_Green_بٹ);
        }
        اگر (pfd.c_Blue_بٹ < ہدف->c_Blue_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Blue_بٹ - ہدف->c_Blue_بٹ);
        }
        اگر (pfd.c_Alpha_بٹ < ہدف->c_Alpha_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Alpha_بٹ - ہدف->c_Alpha_بٹ);
        }
        اگر (pfd.c_Accum_بٹ < ہدف->c_Accum_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Accum_بٹ - ہدف->c_Accum_بٹ);
        }
        اگر (pfd.c_Accum_Red_بٹ < ہدف->c_Accum_Red_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Accum_Red_بٹ - ہدف->c_Accum_Red_بٹ);
        }
        اگر (pfd.c_Accum_Green_بٹ < ہدف->c_Accum_Green_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Accum_Green_بٹ - ہدف->c_Accum_Green_بٹ);
        }
        اگر (pfd.c_Accum_Blue_بٹ < ہدف->c_Accum_Blue_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Accum_Blue_بٹ - ہدف->c_Accum_Blue_بٹ);
        }
        اگر (pfd.c_Accum_Alpha_بٹ < ہدف->c_Accum_Alpha_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Accum_Alpha_بٹ - ہدف->c_Accum_Alpha_بٹ);
        }
        اگر (pfd.c_گہرائی_بٹ < ہدف->c_گہرائی_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_گہرائی_بٹ - ہدف->c_گہرائی_بٹ);
        }
        اگر (pfd.c_Stencil_بٹ < ہدف->c_Stencil_بٹ) {
            جاری;
        } ورنہ {
            dist += (pfd.c_Stencil_بٹ - ہدف->c_Stencil_بٹ);
        }

        اگر (dist < بہترین_dist) {
            بہترین = اشاریہ;
            بہترین_dist = dist;
        }
    }

    واپس بہترین;
}

ساکن bool HasExtension(ثابت حرف *extension, ثابت حرف *extensions)
{
    ثابت حرف *آغاز;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    اگر (where || *extension == '\0') {
        واپس false;
    }

    اگر (!extensions) {
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

خالی WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    ثابت حرف *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    ثابت حرف *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    اگر (!_this->gl_ڈیٹا) {
        واپس;
    }

    hwnd =
        Create_کھڑکی(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, تہی, تہی, SDL_Instance, تہی);
    اگر (!hwnd) {
        واپس;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_تیاری_Pixel_Format(_this, &pfd);

    سیٹ_Pixel_Format(hdc, انتخاب_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_ڈیٹا->wglCreateContext(hdc);
    اگر (!hglrc) {
        واپس;
    }
    _this->gl_ڈیٹا->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (ثابت حرف *(WINAPI *)(HDC))
        _this->gl_ڈیٹا->wgl_Get_Proc_پتہ("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    اگر (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } ورنہ {
        extensions = تہی;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_ڈیٹا->HAS_WGL_ARB_pixel_format = false;
    اگر (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_ڈیٹا->wgl_انتخاب_Pixel_Format_ARB =
            (BOOL (WINAPI *)(HDC, ثابت صحیح *, ثابت FLOAT *, UINT, صحیح *, UINT *))
            WIN_GL_Get_Proc_پتہ(_this, "wglChoosePixelFormatARB");
        _this->gl_ڈیٹا->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, صحیح, صحیح, UINT, ثابت صحیح *, صحیح *))
            WIN_GL_Get_Proc_پتہ(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        اگر ((_this->gl_ڈیٹا->wgl_انتخاب_Pixel_Format_ARB != تہی) &&
            (_this->gl_ڈیٹا->wglGetPixelFormatAttribivARB != تہی)) {
            _this->gl_ڈیٹا->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_ڈیٹا->HAS_WGL_EXT_تبادلہ_control_tear = false;
    اگر (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_ڈیٹا->wgl_تبادلہ_Interval_EXT =
            (BOOL (WINAPI *)(صحیح))
            WIN_GL_Get_Proc_پتہ(_this, "wglSwapIntervalEXT");
        _this->gl_ڈیٹا->wgl_Get_تبادلہ_Interval_EXT =
            (صحیح (WINAPI *)(خالی))
            WIN_GL_Get_Proc_پتہ(_this, "wglGetSwapIntervalEXT");
        اگر (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_ڈیٹا->HAS_WGL_EXT_تبادلہ_control_tear = true;
        }
    } ورنہ {
        _this->gl_ڈیٹا->wgl_تبادلہ_Interval_EXT = تہی;
        _this->gl_ڈیٹا->wgl_Get_تبادلہ_Interval_EXT = تہی;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_ڈیٹا->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    اگر (_this->gl_ڈیٹا->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_ڈیٹا->es_profile_max_supported_نسخہ.major,
            &_this->gl_ڈیٹا->es_profile_max_supported_نسخہ.minor);
    }

    // Check for WGL_ARB_context_flush_control
    اگر (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_ڈیٹا->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    اگر (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_ڈیٹا->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    اگر (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_ڈیٹا->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    اگر (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_ڈیٹا->HAS_WGL_ARB_framebuffer_sRGB = true;
    } ورنہ اگر (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_ڈیٹا->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_ڈیٹا->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_ڈیٹا->wglMakeCurrent(hdc, تہی);
    _this->gl_ڈیٹا->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    Destroy_کھڑکی(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

ساکن صحیح WIN_GL_انتخاب_Pixel_Format_ARB(SDL_VideoDevice *_this, صحیح *iAttribs, اعشاری *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    صحیح pixel_format = 0;
    غیرعلامتی صحیح matching;

    hwnd =
        Create_کھڑکی(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, تہی, تہی, SDL_Instance, تہی);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_تیاری_Pixel_Format(_this, &pfd);

    سیٹ_Pixel_Format(hdc, انتخاب_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_ڈیٹا->wglCreateContext(hdc);
    اگر (hglrc) {
        _this->gl_ڈیٹا->wglMakeCurrent(hdc, hglrc);

        اگر (_this->gl_ڈیٹا->HAS_WGL_ARB_pixel_format) {
            _this->gl_ڈیٹا->wgl_انتخاب_Pixel_Format_ARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            صحیح srgb = 0;
            اگر (_this->gl_ڈیٹا->HAS_WGL_ARB_framebuffer_sRGB) {
                صحیح qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_ڈیٹا->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_ڈیٹا->wglMakeCurrent(hdc, تہی);
        _this->gl_ڈیٹا->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    Destroy_کھڑکی(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    واپس pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
ساکن bool WIN_GL_تیاری_کھڑکی_اندرونی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    HDC hdc = کھڑکی->اندرونی_2->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    صحیح pixel_format = 0;
    صحیح iAttribs[64];
    صحیح *iAttr;
    صحیح *iAccelAttr;
    اعشاری fAttribs[1] = { 0 };

    WIN_GL_تیاری_Pixel_Format(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_مقصد_کھڑکی_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_بٹ_ARB;
    *iAttr++ = _this->gl_config.red_سائز;
    *iAttr++ = WGL_GREEN_بٹ_ARB;
    *iAttr++ = _this->gl_config.green_سائز;
    *iAttr++ = WGL_BLUE_بٹ_ARB;
    *iAttr++ = _this->gl_config.blue_سائز;

    اگر (_this->gl_config.alpha_سائز) {
        *iAttr++ = WGL_ALPHA_بٹ_ARB;
        *iAttr++ = _this->gl_config.alpha_سائز;
    }

    *iAttr++ = WGL_DOUBLE_بفر_ARB;
    *iAttr++ = _this->gl_config.double_بفر;

    *iAttr++ = WGL_گہرائی_بٹ_ARB;
    *iAttr++ = _this->gl_config.گہرائی_سائز;

    اگر (_this->gl_config.stencil_سائز) {
        *iAttr++ = WGL_STENCIL_بٹ_ARB;
        *iAttr++ = _this->gl_config.stencil_سائز;
    }

    اگر (_this->gl_config.accum_red_سائز) {
        *iAttr++ = WGL_ACCUM_RED_بٹ_ARB;
        *iAttr++ = _this->gl_config.accum_red_سائز;
    }

    اگر (_this->gl_config.accum_green_سائز) {
        *iAttr++ = WGL_ACCUM_GREEN_بٹ_ARB;
        *iAttr++ = _this->gl_config.accum_green_سائز;
    }

    اگر (_this->gl_config.accum_blue_سائز) {
        *iAttr++ = WGL_ACCUM_BLUE_بٹ_ARB;
        *iAttr++ = _this->gl_config.accum_blue_سائز;
    }

    اگر (_this->gl_config.accum_alpha_سائز) {
        *iAttr++ = WGL_ACCUM_ALPHA_بٹ_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_سائز;
    }

    اگر (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    اگر (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    اگر (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    اگر (_this->gl_ڈیٹا->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    اگر (_this->gl_ڈیٹا->HAS_WGL_ARB_framebuffer_sRGB) {
        ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        اگر (srgbhint && *srgbhint) {
            اگر (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ورنہ {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } ورنہ اگر (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    اگر (_this->gl_config.accelerated) {
        *iAttr++ = WGL_بھرا_ACCELERATION_ARB;
    } ورنہ {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_انتخاب_Pixel_Format_ARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    اگر ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_انتخاب_Pixel_Format_ARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_بھرا_ACCELERATION_ARB; // if we try again.
    }
    اگر (!pixel_format) {
        pixel_format = WIN_GL_انتخاب_Pixel_Format(_this, hdc, &pfd);
    }
    اگر (!pixel_format) {
        واپس SDL_سیٹ_Error("No matching GL pixel format available");
    }
    اگر (!سیٹ_Pixel_Format(hdc, pixel_format, &pfd)) {
        واپس WIN_سیٹ_Error("SetPixelFormat()");
    }
    واپس true;
}

bool WIN_GL_تیاری_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // The current context is lost in here; save it and reset it.
    SDL_کھڑکی *current_win = SDL_GL_Get_Current_کھڑکی();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    ثابت صحیح نتیجہ = WIN_GL_تیاری_کھڑکی_اندرونی(_this, کھڑکی);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    واپس نتیجہ;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_ڈیٹا != تہی);
    SDL_assert(_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    واپس !_this->gl_ڈیٹا->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_نسخہ > _this->gl_ڈیٹا->es_profile_max_supported_نسخہ.major ||
           (_this->gl_config.major_نسخہ == _this->gl_ڈیٹا->es_profile_max_supported_نسخہ.major && _this->gl_config.minor_نسخہ > _this->gl_ڈیٹا->es_profile_max_supported_نسخہ.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    HDC hdc = کھڑکی->اندرونی_2->hdc;
    HGLRC context, share_context;

    اگر (_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        اگر (!WIN_GL_بھرو_Library_EGLFallback(_this, تہی)) {
            واپس تہی;
        }

        واپس WIN_GLES_CreateContext(_this, کھڑکی);
#ورنہ
        SDL_سیٹ_Error("SDL not configured with EGL support");
        واپس تہی;
#اگر_ختم
    }

    اگر (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } ورنہ {
        share_context = 0;
    }

    اگر (_this->gl_config.major_نسخہ < 3 &&
        _this->gl_config.profile_نقاب == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_ڈیٹا->wglCreateContext(hdc);
        اگر (share_context != 0) {
            _this->gl_ڈیٹا->wglShareLists(share_context, context);
        }
    } ورنہ {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC عارضی_context = _this->gl_ڈیٹا->wglCreateContext(hdc);
        اگر (!عارضی_context) {
            SDL_سیٹ_Error("Could not create GL context");
            واپس تہی;
        }

        // Make the context current
        اگر (!WIN_GL_MakeCurrent(_this, کھڑکی, (SDL_GLContext)عارضی_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)عارضی_context);
            واپس تہی;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_ڈیٹا->wgl_Get_Proc_پتہ("wglCreateContextAttribsARB");
        اگر (!wglCreateContextAttribsARB) {
            SDL_سیٹ_Error("GL 3.x is not supported");
            context = عارضی_context;
        } ورنہ {
            صحیح attribs[15]; // max 14 attributes plus terminator
            صحیح iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_نسخہ_ARB;
            attribs[iattr++] = _this->gl_config.major_نسخہ;
            attribs[iattr++] = WGL_CONTEXT_MINOR_نسخہ_ARB;
            attribs[iattr++] = _this->gl_config.minor_نسخہ;

            // SDL profile bits match WGL profile bits
            اگر (_this->gl_config.profile_نقاب != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_نقاب_ARB;
                attribs[iattr++] = _this->gl_config.profile_نقاب;
            }

            // SDL flags match WGL flags
            اگر (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            اگر ((_this->gl_ڈیٹا->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            اگر ((_this->gl_ڈیٹا->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            اگر ((_this->gl_ڈیٹا->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_ڈیٹا->wglDeleteContext(عارضی_context);
        }
    }

    اگر (!context) {
        WIN_سیٹ_Error("Could not create GL context");
        واپس تہی;
    }

    اگر (!WIN_GL_MakeCurrent(_this, کھڑکی, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        واپس تہی;
    }

    _this->gl_config.HAS_GL_ARB_color_بفر_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    واپس (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    HDC hdc;

    اگر (!_this->gl_ڈیٹا) {
        واپس SDL_سیٹ_Error("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(کھڑکی || (کھڑکی == تہی && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    اگر (!کھڑکی) {
        کھڑکی = SDL_GL_Get_Current_کھڑکی();
        اگر (!کھڑکی) {
            SDL_assert(SDL_GL_GetCurrentContext() == تہی);
            واپس true; // already done.
        }
    }

    hdc = کھڑکی->اندرونی_2->hdc;
    اگر (!_this->gl_ڈیٹا->wglMakeCurrent(hdc, (HGLRC)context)) {
        واپس WIN_سیٹ_Error("wglMakeCurrent()");
    }
    واپس true;
}

bool WIN_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    اگر ((interval < 0) && (!_this->gl_ڈیٹا->HAS_WGL_EXT_تبادلہ_control_tear)) {
        واپس SDL_سیٹ_Error("Negative swap interval unsupported in this GL");
    } ورنہ اگر (_this->gl_ڈیٹا->wgl_تبادلہ_Interval_EXT) {
        اگر (!_this->gl_ڈیٹا->wgl_تبادلہ_Interval_EXT(interval)) {
            واپس WIN_سیٹ_Error("wglSwapIntervalEXT()");
        }
    } ورنہ {
        واپس SDL_Unsupported();
    }
    واپس true;
}

bool WIN_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    اگر (_this->gl_ڈیٹا->wgl_Get_تبادلہ_Interval_EXT) {
        *interval = _this->gl_ڈیٹا->wgl_Get_تبادلہ_Interval_EXT();
        واپس true;
    } ورنہ {
        واپس SDL_Unsupported();
    }
}

bool WIN_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    HDC hdc = کھڑکی->اندرونی_2->hdc;

    اگر (!تبادلہ_Buffers(hdc)) {
        واپس WIN_سیٹ_Error("SwapBuffers()");
    }
    واپس true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    اگر (!_this->gl_ڈیٹا) {
        واپس true;
    }
    _this->gl_ڈیٹا->wglDeleteContext((HGLRC)context);
    واپس true;
}

#اگر_ختم // SDL_VIDEO_OPENGL_WGL

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS
