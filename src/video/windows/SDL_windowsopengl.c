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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowsopengles.h"
#अन्तर्भाव "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
#अन्तर्भाव <SDL3/SDL_opengl.h>

#परिभाषय DEFAULT_OPENGL "OPENGL32.DLL"

#यदि_अपरिभाषितम् WGL_ARB_create_context
#परिभाषय WGL_ARB_create_context
#परिभाषय WGL_CONTEXT_MAJOR_संस्करणम्_ARB          0x2091
#परिभाषय WGL_CONTEXT_MINOR_संस्करणम्_ARB          0x2092
#परिभाषय WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#परिभाषय WGL_CONTEXT_FLAGS_ARB                  0x2094
#परिभाषय WGL_CONTEXT_DEBUG_BIT_ARB              0x0001
#परिभाषय WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002

#यदि_अपरिभाषितम् WGL_ARB_create_context_profile
#परिभाषय WGL_ARB_create_context_profile
#परिभाषय WGL_CONTEXT_PROFILE_आवरणम्_ARB              0x9126
#परिभाषय WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#परिभाषय WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_ARB_create_context_robustness
#परिभाषय WGL_ARB_create_context_robustness
#परिभाषय WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB           0x00000004
#परिभाषय WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#परिभाषय WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#परिभाषय WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#यदि_अन्तः
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_EXT_create_context_es2_profile
#परिभाषय WGL_EXT_create_context_es2_profile
#परिभाषय WGL_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000004
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_EXT_create_context_es_profile
#परिभाषय WGL_EXT_create_context_es_profile
#परिभाषय WGL_CONTEXT_ES_PROFILE_BIT_EXT 0x00000004
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_ARB_framebuffer_sRGB
#परिभाषय WGL_ARB_framebuffer_sRGB
#परिभाषय WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_ARB_pixel_format_float
#परिभाषय WGL_ARB_pixel_format_float
#परिभाषय WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_ARB_context_flush_control
#परिभाषय WGL_ARB_context_flush_control
#परिभाषय WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#परिभाषय WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#परिभाषय WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_ARB_create_context_no_error
#परिभाषय WGL_ARB_create_context_no_error
#परिभाषय WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#यदि_अन्तः

प्रकारनिर्देश HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           ध्रुव पूर्णाङ्क
                                                               *attribList);

#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#परिभाषय GetDC(hwnd)          (HDC) hwnd
#परिभाषय ReleaseDC(hwnd, hdc) 1
#परिभाषय SwapBuffers          _this->gl_दत्त->wglSwapBuffers
#परिभाषय DescribePixelFormat  _this->gl_दत्त->wglDescribePixelFormat
#परिभाषय वृणु_Pixel_Format    _this->gl_दत्त->wgl_वृणु_Pixel_Format
#परिभाषय GetPixelFormat       _this->gl_दत्त->wglGetPixelFormat
#परिभाषय समुच्चयः_Pixel_Format       _this->gl_दत्त->wgl_समुच्चयः_Pixel_Format
#यदि_अन्तः

स्थिर bool WIN_GL_आरोपय_Library_EGLFallback(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_आरोपय_Library = WIN_GLES_आरोपय_Library;
    _this->GL_Get_Proc_स्थानाङ्कः = WIN_GLES_Get_Proc_स्थानाङ्कः;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_समुच्चयः_Swap_Interval = WIN_GLES_समुच्चयः_Swap_Interval;
    _this->GL_GetSwapInterval = WIN_GLES_GetSwapInterval;
    _this->GL_Swap_गवाक्षः = WIN_GLES_Swap_गवाक्षः;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    प्रत्यागम WIN_GLES_आरोपय_Library(_this, मार्गः);
#अन्यथा
    प्रत्यागम SDL_समुच्चयः_Error("SDL not configured with EGL support");
#यदि_अन्तः
}

bool WIN_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    शून्य *handle;

    यदि ((_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        प्रत्यागम WIN_GL_आरोपय_Library_EGLFallback(_this, मार्गः);
    }

    यदि (मार्गः == रिक्त) {
        मार्गः = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    यदि (मार्गः == रिक्त) {
        मार्गः = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_आरोपय_Object(मार्गः);
    यदि (!_this->gl_config.dll_handle) {
        प्रत्यागम false;
    }
    SDL_strlcpy(_this->gl_config.driver_मार्गः, मार्गः,
                SDL_arraysize(_this->gl_config.driver_मार्गः));

    // Allocate OpenGL memory
    _this->gl_दत्त = (संरचना SDL_GLDriver_दत्त *)SDL_calloc(1, परिमाण(संरचना SDL_GLDriver_दत्त));
    यदि (!_this->gl_दत्त) {
        प्रत्यागम false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_दत्त->wgl_Get_Proc_स्थानाङ्कः = (PROC (WINAPI *)(ध्रुव वर्ण *))
        SDL_आरोपय_Function(handle, "wglGetProcAddress");
    _this->gl_दत्त->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_आरोपय_Function(handle, "wglCreateContext");
    _this->gl_दत्त->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_आरोपय_Function(handle, "wglDeleteContext");
    _this->gl_दत्त->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_आरोपय_Function(handle, "wglMakeCurrent");
    _this->gl_दत्त->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_आरोपय_Function(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_दत्त->wglSwapBuffers = (BOOL(WINAPI *)(HDC))
        SDL_आरोपय_Function(handle, "wglSwapBuffers");
    _this->gl_दत्त->wglDescribePixelFormat = (पूर्णाङ्क(WINAPI *)(HDC, पूर्णाङ्क, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_आरोपय_Function(handle, "wglDescribePixelFormat");
    _this->gl_दत्त->wgl_वृणु_Pixel_Format = (पूर्णाङ्क(WINAPI *)(HDC, ध्रुव PIXELFORMATDESCRIPTOR *))
        SDL_आरोपय_Function(handle, "wglChoosePixelFormat");
    _this->gl_दत्त->wgl_समुच्चयः_Pixel_Format = (BOOL(WINAPI *)(HDC, पूर्णाङ्क, ध्रुव PIXELFORMATDESCRIPTOR *))
        SDL_आरोपय_Function(handle, "wglSetPixelFormat");
    _this->gl_दत्त->wglGetPixelFormat = (पूर्णाङ्क(WINAPI *)(HDC hdc))
        SDL_आरोपय_Function(handle, "wglGetPixelFormat");
#यदि_अन्तः

    यदि (!_this->gl_दत्त->wgl_Get_Proc_स्थानाङ्कः ||
        !_this->gl_दत्त->wglCreateContext ||
        !_this->gl_दत्त->wglDeleteContext ||
        !_this->gl_दत्त->wglMakeCurrent
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_दत्त->wglSwapBuffers ||
        !_this->gl_दत्त->wglDescribePixelFormat ||
        !_this->gl_दत्त->wgl_वृणु_Pixel_Format ||
        !_this->gl_दत्त->wglGetPixelFormat ||
        !_this->gl_दत्त->wgl_समुच्चयः_Pixel_Format
#यदि_अन्तः
    ) {
        प्रत्यागम SDL_समुच्चयः_Error("Could not retrieve OpenGL functions");
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

    प्रत्यागम true;
}

SDL_FunctionPointer WIN_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    SDL_FunctionPointer func;

    // This is to pick up extensions
    func = (SDL_FunctionPointer)_this->gl_दत्त->wgl_Get_Proc_स्थानाङ्कः(proc);
    यदि (!func) {
        // This is probably a normal GL function
        func = (SDL_FunctionPointer)Get_Proc_स्थानाङ्कः((HMODULE)_this->gl_config.dll_handle, proc);
    }
    प्रत्यागम func;
}

शून्य WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = रिक्त;

    // Free OpenGL memory
    SDL_free(_this->gl_दत्त);
    _this->gl_दत्त = रिक्त;
}

स्थिर शून्य WIN_GL_सज्जता_Pixel_Format(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_आकार = परिमाण(*pfd);
    pfd->n_संस्करणम् = 1;
    pfd->dwFlags = (PFD_DRAW_गन्तव्यम्_गवाक्षः | PFD_SUPPORT_OPENGL);
    यदि (_this->gl_config.double_बफर) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    यदि (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->c_Red_द्वयङ्काः = (BYTE)_this->gl_config.red_आकार;
    pfd->c_Green_द्वयङ्काः = (BYTE)_this->gl_config.green_आकार;
    pfd->c_Blue_द्वयङ्काः = (BYTE)_this->gl_config.blue_आकार;
    pfd->c_Alpha_द्वयङ्काः = (BYTE)_this->gl_config.alpha_आकार;
    यदि (_this->gl_config.बफर_आकार) {
        pfd->c_Color_द्वयङ्काः = (BYTE)(_this->gl_config.बफर_आकार - _this->gl_config.alpha_आकार);
    } अन्यथा {
        pfd->c_Color_द्वयङ्काः = (pfd->c_Red_द्वयङ्काः + pfd->c_Green_द्वयङ्काः + pfd->c_Blue_द्वयङ्काः);
    }
    pfd->c_Accum_Red_द्वयङ्काः = (BYTE)_this->gl_config.accum_red_आकार;
    pfd->c_Accum_Green_द्वयङ्काः = (BYTE)_this->gl_config.accum_green_आकार;
    pfd->c_Accum_Blue_द्वयङ्काः = (BYTE)_this->gl_config.accum_blue_आकार;
    pfd->c_Accum_Alpha_द्वयङ्काः = (BYTE)_this->gl_config.accum_alpha_आकार;
    pfd->c_Accum_द्वयङ्काः =
        (pfd->c_Accum_Red_द्वयङ्काः + pfd->c_Accum_Green_द्वयङ्काः + pfd->c_Accum_Blue_द्वयङ्काः +
         pfd->c_Accum_Alpha_द्वयङ्काः);
    pfd->c_गभीरता_द्वयङ्काः = (BYTE)_this->gl_config.गभीरता_आकार;
    pfd->c_Stencil_द्वयङ्काः = (BYTE)_this->gl_config.stencil_आकार;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
स्थिर bool WIN_GL_वृणु_Pixel_Format(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *target)
{
    PIXELFORMATDESCRIPTOR pfd;
    पूर्णाङ्क गणनम्, सूचकांक, best = 0;
    अचिह्नित पूर्णाङ्क dist, best_dist = ~0U;

    गणनम् = DescribePixelFormat(hdc, 1, परिमाण(pfd), रिक्त);

    प्रति (सूचकांक = 1; सूचकांक <= गणनम्; सूचकांक++) {

        यदि (!DescribePixelFormat(hdc, सूचकांक, परिमाण(pfd), &pfd)) {
            अनुवर्त;
        }

        यदि ((pfd.dwFlags & target->dwFlags) != target->dwFlags) {
            अनुवर्त;
        }

        यदि (pfd.iLayerType != target->iLayerType) {
            अनुवर्त;
        }
        यदि (pfd.iPixelType != target->iPixelType) {
            अनुवर्त;
        }

        dist = 0;

        यदि (pfd.c_Color_द्वयङ्काः < target->c_Color_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Color_द्वयङ्काः - target->c_Color_द्वयङ्काः);
        }
        यदि (pfd.c_Red_द्वयङ्काः < target->c_Red_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Red_द्वयङ्काः - target->c_Red_द्वयङ्काः);
        }
        यदि (pfd.c_Green_द्वयङ्काः < target->c_Green_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Green_द्वयङ्काः - target->c_Green_द्वयङ्काः);
        }
        यदि (pfd.c_Blue_द्वयङ्काः < target->c_Blue_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Blue_द्वयङ्काः - target->c_Blue_द्वयङ्काः);
        }
        यदि (pfd.c_Alpha_द्वयङ्काः < target->c_Alpha_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Alpha_द्वयङ्काः - target->c_Alpha_द्वयङ्काः);
        }
        यदि (pfd.c_Accum_द्वयङ्काः < target->c_Accum_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Accum_द्वयङ्काः - target->c_Accum_द्वयङ्काः);
        }
        यदि (pfd.c_Accum_Red_द्वयङ्काः < target->c_Accum_Red_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Accum_Red_द्वयङ्काः - target->c_Accum_Red_द्वयङ्काः);
        }
        यदि (pfd.c_Accum_Green_द्वयङ्काः < target->c_Accum_Green_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Accum_Green_द्वयङ्काः - target->c_Accum_Green_द्वयङ्काः);
        }
        यदि (pfd.c_Accum_Blue_द्वयङ्काः < target->c_Accum_Blue_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Accum_Blue_द्वयङ्काः - target->c_Accum_Blue_द्वयङ्काः);
        }
        यदि (pfd.c_Accum_Alpha_द्वयङ्काः < target->c_Accum_Alpha_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Accum_Alpha_द्वयङ्काः - target->c_Accum_Alpha_द्वयङ्काः);
        }
        यदि (pfd.c_गभीरता_द्वयङ्काः < target->c_गभीरता_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_गभीरता_द्वयङ्काः - target->c_गभीरता_द्वयङ्काः);
        }
        यदि (pfd.c_Stencil_द्वयङ्काः < target->c_Stencil_द्वयङ्काः) {
            अनुवर्त;
        } अन्यथा {
            dist += (pfd.c_Stencil_द्वयङ्काः - target->c_Stencil_द्वयङ्काः);
        }

        यदि (dist < best_dist) {
            best = सूचकांक;
            best_dist = dist;
        }
    }

    प्रत्यागम best;
}

स्थिर bool HasExtension(ध्रुव वर्ण *extension, ध्रुव वर्ण *extensions)
{
    ध्रुव वर्ण *start;
    ध्रुव वर्ण *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    यदि (where || *extension == '\0') {
        प्रत्यागम false;
    }

    यदि (!extensions) {
        प्रत्यागम false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    start = extensions;

    प्रति (;;) {
        where = SDL_strstr(start, extension);
        यदि (!where) {
            भङ्ग;
        }

        terminator = where + SDL_strlen(extension);
        यदि (where == start || *(where - 1) == ' ') {
            यदि (*terminator == ' ' || *terminator == '\0') {
                प्रत्यागम true;
            }
        }

        start = terminator;
    }
    प्रत्यागम false;
}

शून्य WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    ध्रुव वर्ण *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    ध्रुव वर्ण *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    यदि (!_this->gl_दत्त) {
        प्रत्यागम;
    }

    hwnd =
        Create_गवाक्षः(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, रिक्त, रिक्त, SDL_Instance, रिक्त);
    यदि (!hwnd) {
        प्रत्यागम;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_सज्जता_Pixel_Format(_this, &pfd);

    समुच्चयः_Pixel_Format(hdc, वृणु_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_दत्त->wglCreateContext(hdc);
    यदि (!hglrc) {
        प्रत्यागम;
    }
    _this->gl_दत्त->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (ध्रुव वर्ण *(WINAPI *)(HDC))
        _this->gl_दत्त->wgl_Get_Proc_स्थानाङ्कः("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    यदि (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } अन्यथा {
        extensions = रिक्त;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_दत्त->HAS_WGL_ARB_pixel_format = false;
    यदि (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_दत्त->wgl_वृणु_Pixel_Format_ARB =
            (BOOL (WINAPI *)(HDC, ध्रुव पूर्णाङ्क *, ध्रुव FLOAT *, UINT, पूर्णाङ्क *, UINT *))
            WIN_GL_Get_Proc_स्थानाङ्कः(_this, "wglChoosePixelFormatARB");
        _this->gl_दत्त->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, पूर्णाङ्क, पूर्णाङ्क, UINT, ध्रुव पूर्णाङ्क *, पूर्णाङ्क *))
            WIN_GL_Get_Proc_स्थानाङ्कः(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        यदि ((_this->gl_दत्त->wgl_वृणु_Pixel_Format_ARB != रिक्त) &&
            (_this->gl_दत्त->wglGetPixelFormatAttribivARB != रिक्त)) {
            _this->gl_दत्त->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_दत्त->HAS_WGL_EXT_swap_control_tear = false;
    यदि (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_दत्त->wglSwapIntervalEXT =
            (BOOL (WINAPI *)(पूर्णाङ्क))
            WIN_GL_Get_Proc_स्थानाङ्कः(_this, "wglSwapIntervalEXT");
        _this->gl_दत्त->wglGetSwapIntervalEXT =
            (पूर्णाङ्क (WINAPI *)(शून्य))
            WIN_GL_Get_Proc_स्थानाङ्कः(_this, "wglGetSwapIntervalEXT");
        यदि (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_दत्त->HAS_WGL_EXT_swap_control_tear = true;
        }
    } अन्यथा {
        _this->gl_दत्त->wglSwapIntervalEXT = रिक्त;
        _this->gl_दत्त->wglGetSwapIntervalEXT = रिक्त;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_दत्त->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    यदि (_this->gl_दत्त->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_दत्त->es_profile_max_supported_संस्करणम्.major,
            &_this->gl_दत्त->es_profile_max_supported_संस्करणम्.minor);
    }

    // Check for WGL_ARB_context_flush_control
    यदि (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_दत्त->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    यदि (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_दत्त->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    यदि (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_दत्त->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    यदि (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_दत्त->HAS_WGL_ARB_framebuffer_sRGB = true;
    } अन्यथा यदि (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_दत्त->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_दत्त->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_दत्त->wglMakeCurrent(hdc, रिक्त);
    _this->gl_दत्त->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    Destroy_गवाक्षः(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

स्थिर पूर्णाङ्क WIN_GL_वृणु_Pixel_Format_ARB(SDL_VideoDevice *_this, पूर्णाङ्क *iAttribs, भिन्न *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    पूर्णाङ्क pixel_format = 0;
    अचिह्नित पूर्णाङ्क matching;

    hwnd =
        Create_गवाक्षः(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, रिक्त, रिक्त, SDL_Instance, रिक्त);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_सज्जता_Pixel_Format(_this, &pfd);

    समुच्चयः_Pixel_Format(hdc, वृणु_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_दत्त->wglCreateContext(hdc);
    यदि (hglrc) {
        _this->gl_दत्त->wglMakeCurrent(hdc, hglrc);

        यदि (_this->gl_दत्त->HAS_WGL_ARB_pixel_format) {
            _this->gl_दत्त->wgl_वृणु_Pixel_Format_ARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            पूर्णाङ्क srgb = 0;
            यदि (_this->gl_दत्त->HAS_WGL_ARB_framebuffer_sRGB) {
                पूर्णाङ्क qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_दत्त->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_दत्त->wglMakeCurrent(hdc, रिक्त);
        _this->gl_दत्त->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    Destroy_गवाक्षः(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    प्रत्यागम pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
स्थिर bool WIN_GL_सज्जता_गवाक्षः_आन्तरिकम्(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    HDC hdc = गवाक्षः->आन्तरिकम्->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    पूर्णाङ्क pixel_format = 0;
    पूर्णाङ्क iAttribs[64];
    पूर्णाङ्क *iAttr;
    पूर्णाङ्क *iAccelAttr;
    भिन्न fAttribs[1] = { 0 };

    WIN_GL_सज्जता_Pixel_Format(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_गन्तव्यम्_गवाक्षः_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_द्वयङ्काः_ARB;
    *iAttr++ = _this->gl_config.red_आकार;
    *iAttr++ = WGL_GREEN_द्वयङ्काः_ARB;
    *iAttr++ = _this->gl_config.green_आकार;
    *iAttr++ = WGL_BLUE_द्वयङ्काः_ARB;
    *iAttr++ = _this->gl_config.blue_आकार;

    यदि (_this->gl_config.alpha_आकार) {
        *iAttr++ = WGL_ALPHA_द्वयङ्काः_ARB;
        *iAttr++ = _this->gl_config.alpha_आकार;
    }

    *iAttr++ = WGL_DOUBLE_बफर_ARB;
    *iAttr++ = _this->gl_config.double_बफर;

    *iAttr++ = WGL_गभीरता_द्वयङ्काः_ARB;
    *iAttr++ = _this->gl_config.गभीरता_आकार;

    यदि (_this->gl_config.stencil_आकार) {
        *iAttr++ = WGL_STENCIL_द्वयङ्काः_ARB;
        *iAttr++ = _this->gl_config.stencil_आकार;
    }

    यदि (_this->gl_config.accum_red_आकार) {
        *iAttr++ = WGL_ACCUM_RED_द्वयङ्काः_ARB;
        *iAttr++ = _this->gl_config.accum_red_आकार;
    }

    यदि (_this->gl_config.accum_green_आकार) {
        *iAttr++ = WGL_ACCUM_GREEN_द्वयङ्काः_ARB;
        *iAttr++ = _this->gl_config.accum_green_आकार;
    }

    यदि (_this->gl_config.accum_blue_आकार) {
        *iAttr++ = WGL_ACCUM_BLUE_द्वयङ्काः_ARB;
        *iAttr++ = _this->gl_config.accum_blue_आकार;
    }

    यदि (_this->gl_config.accum_alpha_आकार) {
        *iAttr++ = WGL_ACCUM_ALPHA_द्वयङ्काः_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_आकार;
    }

    यदि (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    यदि (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    यदि (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    यदि (_this->gl_दत्त->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    यदि (_this->gl_दत्त->HAS_WGL_ARB_framebuffer_sRGB) {
        ध्रुव वर्ण *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        यदि (srgbhint && *srgbhint) {
            यदि (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } अन्यथा {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } अन्यथा यदि (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    यदि (_this->gl_config.accelerated) {
        *iAttr++ = WGL_पूर्णम्_ACCELERATION_ARB;
    } अन्यथा {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_वृणु_Pixel_Format_ARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    यदि ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_वृणु_Pixel_Format_ARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_पूर्णम्_ACCELERATION_ARB; // if we try again.
    }
    यदि (!pixel_format) {
        pixel_format = WIN_GL_वृणु_Pixel_Format(_this, hdc, &pfd);
    }
    यदि (!pixel_format) {
        प्रत्यागम SDL_समुच्चयः_Error("No matching GL pixel format available");
    }
    यदि (!समुच्चयः_Pixel_Format(hdc, pixel_format, &pfd)) {
        प्रत्यागम WIN_समुच्चयः_Error("SetPixelFormat()");
    }
    प्रत्यागम true;
}

bool WIN_GL_सज्जता_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // The current context is lost in here; save it and reset it.
    SDL_गवाक्षः *current_win = SDL_GL_Get_Current_गवाक्षः();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    ध्रुव पूर्णाङ्क परिणाम = WIN_GL_सज्जता_गवाक्षः_आन्तरिकम्(_this, गवाक्षः);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    प्रत्यागम परिणाम;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_दत्त != रिक्त);
    SDL_assert(_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    प्रत्यागम !_this->gl_दत्त->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_संस्करणम् > _this->gl_दत्त->es_profile_max_supported_संस्करणम्.major ||
           (_this->gl_config.major_संस्करणम् == _this->gl_दत्त->es_profile_max_supported_संस्करणम्.major && _this->gl_config.minor_संस्करणम् > _this->gl_दत्त->es_profile_max_supported_संस्करणम्.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    HDC hdc = गवाक्षः->आन्तरिकम्->hdc;
    HGLRC context, share_context;

    यदि (_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        यदि (!WIN_GL_आरोपय_Library_EGLFallback(_this, रिक्त)) {
            प्रत्यागम रिक्त;
        }

        प्रत्यागम WIN_GLES_CreateContext(_this, गवाक्षः);
#अन्यथा
        SDL_समुच्चयः_Error("SDL not configured with EGL support");
        प्रत्यागम रिक्त;
#यदि_अन्तः
    }

    यदि (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } अन्यथा {
        share_context = 0;
    }

    यदि (_this->gl_config.major_संस्करणम् < 3 &&
        _this->gl_config.profile_आवरणम् == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_दत्त->wglCreateContext(hdc);
        यदि (share_context != 0) {
            _this->gl_दत्त->wglShareLists(share_context, context);
        }
    } अन्यथा {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC अस्थायी_context = _this->gl_दत्त->wglCreateContext(hdc);
        यदि (!अस्थायी_context) {
            SDL_समुच्चयः_Error("Could not create GL context");
            प्रत्यागम रिक्त;
        }

        // Make the context current
        यदि (!WIN_GL_MakeCurrent(_this, गवाक्षः, (SDL_GLContext)अस्थायी_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)अस्थायी_context);
            प्रत्यागम रिक्त;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_दत्त->wgl_Get_Proc_स्थानाङ्कः("wglCreateContextAttribsARB");
        यदि (!wglCreateContextAttribsARB) {
            SDL_समुच्चयः_Error("GL 3.x is not supported");
            context = अस्थायी_context;
        } अन्यथा {
            पूर्णाङ्क attribs[15]; // max 14 attributes plus terminator
            पूर्णाङ्क iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_संस्करणम्_ARB;
            attribs[iattr++] = _this->gl_config.major_संस्करणम्;
            attribs[iattr++] = WGL_CONTEXT_MINOR_संस्करणम्_ARB;
            attribs[iattr++] = _this->gl_config.minor_संस्करणम्;

            // SDL profile bits match WGL profile bits
            यदि (_this->gl_config.profile_आवरणम् != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_आवरणम्_ARB;
                attribs[iattr++] = _this->gl_config.profile_आवरणम्;
            }

            // SDL flags match WGL flags
            यदि (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            यदि ((_this->gl_दत्त->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            यदि ((_this->gl_दत्त->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            यदि ((_this->gl_दत्त->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_दत्त->wglDeleteContext(अस्थायी_context);
        }
    }

    यदि (!context) {
        WIN_समुच्चयः_Error("Could not create GL context");
        प्रत्यागम रिक्त;
    }

    यदि (!WIN_GL_MakeCurrent(_this, गवाक्षः, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        प्रत्यागम रिक्त;
    }

    _this->gl_config.HAS_GL_ARB_color_बफर_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    प्रत्यागम (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    HDC hdc;

    यदि (!_this->gl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(गवाक्षः || (गवाक्षः == रिक्त && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    यदि (!गवाक्षः) {
        गवाक्षः = SDL_GL_Get_Current_गवाक्षः();
        यदि (!गवाक्षः) {
            SDL_assert(SDL_GL_GetCurrentContext() == रिक्त);
            प्रत्यागम true; // already done.
        }
    }

    hdc = गवाक्षः->आन्तरिकम्->hdc;
    यदि (!_this->gl_दत्त->wglMakeCurrent(hdc, (HGLRC)context)) {
        प्रत्यागम WIN_समुच्चयः_Error("wglMakeCurrent()");
    }
    प्रत्यागम true;
}

bool WIN_GL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    यदि ((interval < 0) && (!_this->gl_दत्त->HAS_WGL_EXT_swap_control_tear)) {
        प्रत्यागम SDL_समुच्चयः_Error("Negative swap interval unsupported in this GL");
    } अन्यथा यदि (_this->gl_दत्त->wglSwapIntervalEXT) {
        यदि (!_this->gl_दत्त->wglSwapIntervalEXT(interval)) {
            प्रत्यागम WIN_समुच्चयः_Error("wglSwapIntervalEXT()");
        }
    } अन्यथा {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम true;
}

bool WIN_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    यदि (_this->gl_दत्त->wglGetSwapIntervalEXT) {
        *interval = _this->gl_दत्त->wglGetSwapIntervalEXT();
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम SDL_Unsupported();
    }
}

bool WIN_GL_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    HDC hdc = गवाक्षः->आन्तरिकम्->hdc;

    यदि (!SwapBuffers(hdc)) {
        प्रत्यागम WIN_समुच्चयः_Error("SwapBuffers()");
    }
    प्रत्यागम true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    यदि (!_this->gl_दत्त) {
        प्रत्यागम true;
    }
    _this->gl_दत्त->wglDeleteContext((HGLRC)context);
    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_OPENGL_WGL

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS
