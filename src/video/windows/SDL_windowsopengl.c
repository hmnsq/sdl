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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowsopengles.h"
#समावेश "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#अगर_घोषित SDL_VIDEO_OPENGL_WGL
#समावेश <SDL3/SDL_opengl.h>

#घोषणा DEFAULT_OPENGL "OPENGL32.DLL"

#अगर_अघोषित WGL_ARB_create_context
#घोषणा WGL_ARB_create_context
#घोषणा WGL_CONTEXT_MAJOR_VERSION_ARB          0x2091
#घोषणा WGL_CONTEXT_MINOR_VERSION_ARB          0x2092
#घोषणा WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#घोषणा WGL_CONTEXT_FLAGS_ARB                  0x2094
#घोषणा WGL_CONTEXT_DEBUG_BIT_ARB              0x0001
#घोषणा WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002

#अगर_अघोषित WGL_ARB_create_context_profile
#घोषणा WGL_ARB_create_context_profile
#घोषणा WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#घोषणा WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#घोषणा WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#पूर्ण_अगर

#अगर_अघोषित WGL_ARB_create_context_robustness
#घोषणा WGL_ARB_create_context_robustness
#घोषणा WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB           0x00000004
#घोषणा WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#घोषणा WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#घोषणा WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित WGL_EXT_create_context_es2_profile
#घोषणा WGL_EXT_create_context_es2_profile
#घोषणा WGL_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000004
#पूर्ण_अगर

#अगर_अघोषित WGL_EXT_create_context_es_profile
#घोषणा WGL_EXT_create_context_es_profile
#घोषणा WGL_CONTEXT_ES_PROFILE_BIT_EXT 0x00000004
#पूर्ण_अगर

#अगर_अघोषित WGL_ARB_framebuffer_sRGB
#घोषणा WGL_ARB_framebuffer_sRGB
#घोषणा WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#पूर्ण_अगर

#अगर_अघोषित WGL_ARB_pixel_format_float
#घोषणा WGL_ARB_pixel_format_float
#घोषणा WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#पूर्ण_अगर

#अगर_अघोषित WGL_ARB_context_flush_control
#घोषणा WGL_ARB_context_flush_control
#घोषणा WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#घोषणा WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#घोषणा WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#पूर्ण_अगर

#अगर_अघोषित WGL_ARB_create_context_no_error
#घोषणा WGL_ARB_create_context_no_error
#घोषणा WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#पूर्ण_अगर

प्रकार HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           स्थिर पूर्णांक
                                                               *attribList);

#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#घोषणा GetDC(hwnd)          (HDC) hwnd
#घोषणा ReleaseDC(hwnd, hdc) 1
#घोषणा SwapBuffers          _this->gl_तथ्य->wglSwapBuffers
#घोषणा DescribePixelFormat  _this->gl_तथ्य->wglDescribePixelFormat
#घोषणा ChoosePixelFormat    _this->gl_तथ्य->wglChoosePixelFormat
#घोषणा GetPixelFormat       _this->gl_तथ्य->wglGetPixelFormat
#घोषणा SetPixelFormat       _this->gl_तथ्य->wglSetPixelFormat
#पूर्ण_अगर

अटल bool WIN_GL_LoadLibrary_EGLFallback(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
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
    वापस WIN_GLES_LoadLibrary(_this, path);
#अन्यथा
    वापस SDL_SetError("SDL not configured with EGL support");
#पूर्ण_अगर
}

bool WIN_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    व्योम *handle;

    अगर ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        वापस WIN_GL_LoadLibrary_EGLFallback(_this, path);
    }

    अगर (path == शून्य) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    अगर (path == शून्य) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    अगर (!_this->gl_config.dll_handle) {
        वापस false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_तथ्य = (काष्ठा SDL_GLDriver_तथ्य *)SDL_calloc(1, माप(काष्ठा SDL_GLDriver_तथ्य));
    अगर (!_this->gl_तथ्य) {
        वापस false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_तथ्य->wglGetProcAddress = (PROC (WINAPI *)(स्थिर अक्षर *))
        SDL_LoadFunction(handle, "wglGetProcAddress");
    _this->gl_तथ्य->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_LoadFunction(handle, "wglCreateContext");
    _this->gl_तथ्य->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_LoadFunction(handle, "wglDeleteContext");
    _this->gl_तथ्य->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_LoadFunction(handle, "wglMakeCurrent");
    _this->gl_तथ्य->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_LoadFunction(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_तथ्य->wglSwapBuffers = (BOOL(WINAPI *)(HDC))
        SDL_LoadFunction(handle, "wglSwapBuffers");
    _this->gl_तथ्य->wglDescribePixelFormat = (पूर्णांक(WINAPI *)(HDC, पूर्णांक, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_LoadFunction(handle, "wglDescribePixelFormat");
    _this->gl_तथ्य->wglChoosePixelFormat = (पूर्णांक(WINAPI *)(HDC, स्थिर PIXELFORMATDESCRIPTOR *))
        SDL_LoadFunction(handle, "wglChoosePixelFormat");
    _this->gl_तथ्य->wglSetPixelFormat = (BOOL(WINAPI *)(HDC, पूर्णांक, स्थिर PIXELFORMATDESCRIPTOR *))
        SDL_LoadFunction(handle, "wglSetPixelFormat");
    _this->gl_तथ्य->wglGetPixelFormat = (पूर्णांक(WINAPI *)(HDC hdc))
        SDL_LoadFunction(handle, "wglGetPixelFormat");
#पूर्ण_अगर

    अगर (!_this->gl_तथ्य->wglGetProcAddress ||
        !_this->gl_तथ्य->wglCreateContext ||
        !_this->gl_तथ्य->wglDeleteContext ||
        !_this->gl_तथ्य->wglMakeCurrent
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_तथ्य->wglSwapBuffers ||
        !_this->gl_तथ्य->wglDescribePixelFormat ||
        !_this->gl_तथ्य->wglChoosePixelFormat ||
        !_this->gl_तथ्य->wglGetPixelFormat ||
        !_this->gl_तथ्य->wglSetPixelFormat
#पूर्ण_अगर
    ) {
        वापस SDL_SetError("Could not retrieve OpenGL functions");
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

    वापस true;
}

SDL_FunctionPointer WIN_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    SDL_FunctionPointer func;

    // This is to pick up extensions
    func = (SDL_FunctionPointer)_this->gl_तथ्य->wglGetProcAddress(proc);
    अगर (!func) {
        // This is probably a normal GL function
        func = (SDL_FunctionPointer)GetProcAddress((HMODULE)_this->gl_config.dll_handle, proc);
    }
    वापस func;
}

व्योम WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = शून्य;

    // Free OpenGL memory
    SDL_free(_this->gl_तथ्य);
    _this->gl_तथ्य = शून्य;
}

अटल व्योम WIN_GL_SetupPixelFormat(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_आकार = माप(*pfd);
    pfd->nVersion = 1;
    pfd->dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL);
    अगर (_this->gl_config.double_बफर) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    अगर (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->cRedBits = (BYTE)_this->gl_config.red_आकार;
    pfd->cGreenBits = (BYTE)_this->gl_config.green_आकार;
    pfd->cBlueBits = (BYTE)_this->gl_config.blue_आकार;
    pfd->cAlphaBits = (BYTE)_this->gl_config.alpha_आकार;
    अगर (_this->gl_config.बफर_आकार) {
        pfd->cColorBits = (BYTE)(_this->gl_config.बफर_आकार - _this->gl_config.alpha_आकार);
    } अन्यथा {
        pfd->cColorBits = (pfd->cRedBits + pfd->cGreenBits + pfd->cBlueBits);
    }
    pfd->cAccumRedBits = (BYTE)_this->gl_config.accum_red_आकार;
    pfd->cAccumGreenBits = (BYTE)_this->gl_config.accum_green_आकार;
    pfd->cAccumBlueBits = (BYTE)_this->gl_config.accum_blue_आकार;
    pfd->cAccumAlphaBits = (BYTE)_this->gl_config.accum_alpha_आकार;
    pfd->cAccumBits =
        (pfd->cAccumRedBits + pfd->cAccumGreenBits + pfd->cAccumBlueBits +
         pfd->cAccumAlphaBits);
    pfd->cDepthBits = (BYTE)_this->gl_config.depth_आकार;
    pfd->cStencilBits = (BYTE)_this->gl_config.stencil_आकार;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
अटल bool WIN_GL_ChoosePixelFormat(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *target)
{
    PIXELFORMATDESCRIPTOR pfd;
    पूर्णांक गिनती, सूचकांक, best = 0;
    अचिन्हित पूर्णांक dist, best_dist = ~0U;

    गिनती = DescribePixelFormat(hdc, 1, माप(pfd), शून्य);

    क्रम (सूचकांक = 1; सूचकांक <= गिनती; सूचकांक++) {

        अगर (!DescribePixelFormat(hdc, सूचकांक, माप(pfd), &pfd)) {
            जारी;
        }

        अगर ((pfd.dwFlags & target->dwFlags) != target->dwFlags) {
            जारी;
        }

        अगर (pfd.iLayerType != target->iLayerType) {
            जारी;
        }
        अगर (pfd.iPixelType != target->iPixelType) {
            जारी;
        }

        dist = 0;

        अगर (pfd.cColorBits < target->cColorBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cColorBits - target->cColorBits);
        }
        अगर (pfd.cRedBits < target->cRedBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cRedBits - target->cRedBits);
        }
        अगर (pfd.cGreenBits < target->cGreenBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cGreenBits - target->cGreenBits);
        }
        अगर (pfd.cBlueBits < target->cBlueBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cBlueBits - target->cBlueBits);
        }
        अगर (pfd.cAlphaBits < target->cAlphaBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cAlphaBits - target->cAlphaBits);
        }
        अगर (pfd.cAccumBits < target->cAccumBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cAccumBits - target->cAccumBits);
        }
        अगर (pfd.cAccumRedBits < target->cAccumRedBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cAccumRedBits - target->cAccumRedBits);
        }
        अगर (pfd.cAccumGreenBits < target->cAccumGreenBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cAccumGreenBits - target->cAccumGreenBits);
        }
        अगर (pfd.cAccumBlueBits < target->cAccumBlueBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cAccumBlueBits - target->cAccumBlueBits);
        }
        अगर (pfd.cAccumAlphaBits < target->cAccumAlphaBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cAccumAlphaBits - target->cAccumAlphaBits);
        }
        अगर (pfd.cDepthBits < target->cDepthBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cDepthBits - target->cDepthBits);
        }
        अगर (pfd.cStencilBits < target->cStencilBits) {
            जारी;
        } अन्यथा {
            dist += (pfd.cStencilBits - target->cStencilBits);
        }

        अगर (dist < best_dist) {
            best = सूचकांक;
            best_dist = dist;
        }
    }

    वापस best;
}

अटल bool HasExtension(स्थिर अक्षर *extension, स्थिर अक्षर *extensions)
{
    स्थिर अक्षर *start;
    स्थिर अक्षर *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    अगर (where || *extension == '\0') {
        वापस false;
    }

    अगर (!extensions) {
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

व्योम WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    स्थिर अक्षर *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    स्थिर अक्षर *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    अगर (!_this->gl_तथ्य) {
        वापस;
    }

    hwnd =
        CreateWindow(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, शून्य, शून्य, SDL_Instance, शून्य);
    अगर (!hwnd) {
        वापस;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_SetupPixelFormat(_this, &pfd);

    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

    hglrc = _this->gl_तथ्य->wglCreateContext(hdc);
    अगर (!hglrc) {
        वापस;
    }
    _this->gl_तथ्य->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (स्थिर अक्षर *(WINAPI *)(HDC))
        _this->gl_तथ्य->wglGetProcAddress("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    अगर (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } अन्यथा {
        extensions = शून्य;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_तथ्य->HAS_WGL_ARB_pixel_format = false;
    अगर (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_तथ्य->wglChoosePixelFormatARB =
            (BOOL (WINAPI *)(HDC, स्थिर पूर्णांक *, स्थिर FLOAT *, UINT, पूर्णांक *, UINT *))
            WIN_GL_GetProcAddress(_this, "wglChoosePixelFormatARB");
        _this->gl_तथ्य->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, पूर्णांक, पूर्णांक, UINT, स्थिर पूर्णांक *, पूर्णांक *))
            WIN_GL_GetProcAddress(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        अगर ((_this->gl_तथ्य->wglChoosePixelFormatARB != शून्य) &&
            (_this->gl_तथ्य->wglGetPixelFormatAttribivARB != शून्य)) {
            _this->gl_तथ्य->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_तथ्य->HAS_WGL_EXT_swap_control_tear = false;
    अगर (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_तथ्य->wglSwapIntervalEXT =
            (BOOL (WINAPI *)(पूर्णांक))
            WIN_GL_GetProcAddress(_this, "wglSwapIntervalEXT");
        _this->gl_तथ्य->wglGetSwapIntervalEXT =
            (पूर्णांक (WINAPI *)(व्योम))
            WIN_GL_GetProcAddress(_this, "wglGetSwapIntervalEXT");
        अगर (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_तथ्य->HAS_WGL_EXT_swap_control_tear = true;
        }
    } अन्यथा {
        _this->gl_तथ्य->wglSwapIntervalEXT = शून्य;
        _this->gl_तथ्य->wglGetSwapIntervalEXT = शून्य;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_तथ्य->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    अगर (_this->gl_तथ्य->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_तथ्य->es_profile_max_supported_version.major,
            &_this->gl_तथ्य->es_profile_max_supported_version.minor);
    }

    // Check for WGL_ARB_context_flush_control
    अगर (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_तथ्य->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    अगर (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_तथ्य->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    अगर (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_तथ्य->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    अगर (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_तथ्य->HAS_WGL_ARB_framebuffer_sRGB = true;
    } अन्यथा अगर (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_तथ्य->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_तथ्य->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_तथ्य->wglMakeCurrent(hdc, शून्य);
    _this->gl_तथ्य->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

अटल पूर्णांक WIN_GL_ChoosePixelFormatARB(SDL_VideoDevice *_this, पूर्णांक *iAttribs, भग्न *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    पूर्णांक pixel_format = 0;
    अचिन्हित पूर्णांक matching;

    hwnd =
        CreateWindow(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, शून्य, शून्य, SDL_Instance, शून्य);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_SetupPixelFormat(_this, &pfd);

    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

    hglrc = _this->gl_तथ्य->wglCreateContext(hdc);
    अगर (hglrc) {
        _this->gl_तथ्य->wglMakeCurrent(hdc, hglrc);

        अगर (_this->gl_तथ्य->HAS_WGL_ARB_pixel_format) {
            _this->gl_तथ्य->wglChoosePixelFormatARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            पूर्णांक srgb = 0;
            अगर (_this->gl_तथ्य->HAS_WGL_ARB_framebuffer_sRGB) {
                पूर्णांक qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_तथ्य->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_तथ्य->wglMakeCurrent(hdc, शून्य);
        _this->gl_तथ्य->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    वापस pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
अटल bool WIN_GL_SetupWindowInternal(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    पूर्णांक pixel_format = 0;
    पूर्णांक iAttribs[64];
    पूर्णांक *iAttr;
    पूर्णांक *iAccelAttr;
    भग्न fAttribs[1] = { 0 };

    WIN_GL_SetupPixelFormat(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_TO_WINDOW_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_BITS_ARB;
    *iAttr++ = _this->gl_config.red_आकार;
    *iAttr++ = WGL_GREEN_BITS_ARB;
    *iAttr++ = _this->gl_config.green_आकार;
    *iAttr++ = WGL_BLUE_BITS_ARB;
    *iAttr++ = _this->gl_config.blue_आकार;

    अगर (_this->gl_config.alpha_आकार) {
        *iAttr++ = WGL_ALPHA_BITS_ARB;
        *iAttr++ = _this->gl_config.alpha_आकार;
    }

    *iAttr++ = WGL_DOUBLE_बफर_ARB;
    *iAttr++ = _this->gl_config.double_बफर;

    *iAttr++ = WGL_DEPTH_BITS_ARB;
    *iAttr++ = _this->gl_config.depth_आकार;

    अगर (_this->gl_config.stencil_आकार) {
        *iAttr++ = WGL_STENCIL_BITS_ARB;
        *iAttr++ = _this->gl_config.stencil_आकार;
    }

    अगर (_this->gl_config.accum_red_आकार) {
        *iAttr++ = WGL_ACCUM_RED_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_red_आकार;
    }

    अगर (_this->gl_config.accum_green_आकार) {
        *iAttr++ = WGL_ACCUM_GREEN_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_green_आकार;
    }

    अगर (_this->gl_config.accum_blue_आकार) {
        *iAttr++ = WGL_ACCUM_BLUE_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_blue_आकार;
    }

    अगर (_this->gl_config.accum_alpha_आकार) {
        *iAttr++ = WGL_ACCUM_ALPHA_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_आकार;
    }

    अगर (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    अगर (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    अगर (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    अगर (_this->gl_तथ्य->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    अगर (_this->gl_तथ्य->HAS_WGL_ARB_framebuffer_sRGB) {
        स्थिर अक्षर *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        अगर (srgbhint && *srgbhint) {
            अगर (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } अन्यथा {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } अन्यथा अगर (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    अगर (_this->gl_config.accelerated) {
        *iAttr++ = WGL_FULL_ACCELERATION_ARB;
    } अन्यथा {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_ChoosePixelFormatARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    अगर ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_ChoosePixelFormatARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_FULL_ACCELERATION_ARB; // if we try again.
    }
    अगर (!pixel_format) {
        pixel_format = WIN_GL_ChoosePixelFormat(_this, hdc, &pfd);
    }
    अगर (!pixel_format) {
        वापस SDL_SetError("No matching GL pixel format available");
    }
    अगर (!SetPixelFormat(hdc, pixel_format, &pfd)) {
        वापस WIN_SetError("SetPixelFormat()");
    }
    वापस true;
}

bool WIN_GL_SetupWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // The current context is lost in here; save it and reset it.
    SDL_Window *current_win = SDL_GL_GetCurrentWindow();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    स्थिर पूर्णांक परिणाम = WIN_GL_SetupWindowInternal(_this, window);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    वापस परिणाम;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_तथ्य != शून्य);
    SDL_assert(_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    वापस !_this->gl_तथ्य->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_version > _this->gl_तथ्य->es_profile_max_supported_version.major ||
           (_this->gl_config.major_version == _this->gl_तथ्य->es_profile_max_supported_version.major && _this->gl_config.minor_version > _this->gl_तथ्य->es_profile_max_supported_version.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;
    HGLRC context, share_context;

    अगर (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        अगर (!WIN_GL_LoadLibrary_EGLFallback(_this, शून्य)) {
            वापस शून्य;
        }

        वापस WIN_GLES_CreateContext(_this, window);
#अन्यथा
        SDL_SetError("SDL not configured with EGL support");
        वापस शून्य;
#पूर्ण_अगर
    }

    अगर (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } अन्यथा {
        share_context = 0;
    }

    अगर (_this->gl_config.major_version < 3 &&
        _this->gl_config.profile_mask == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_तथ्य->wglCreateContext(hdc);
        अगर (share_context != 0) {
            _this->gl_तथ्य->wglShareLists(share_context, context);
        }
    } अन्यथा {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC अस्थायी_context = _this->gl_तथ्य->wglCreateContext(hdc);
        अगर (!अस्थायी_context) {
            SDL_SetError("Could not create GL context");
            वापस शून्य;
        }

        // Make the context current
        अगर (!WIN_GL_MakeCurrent(_this, window, (SDL_GLContext)अस्थायी_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)अस्थायी_context);
            वापस शून्य;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_तथ्य->wglGetProcAddress("wglCreateContextAttribsARB");
        अगर (!wglCreateContextAttribsARB) {
            SDL_SetError("GL 3.x is not supported");
            context = अस्थायी_context;
        } अन्यथा {
            पूर्णांक attribs[15]; // max 14 attributes plus terminator
            पूर्णांक iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
            attribs[iattr++] = _this->gl_config.major_version;
            attribs[iattr++] = WGL_CONTEXT_MINOR_VERSION_ARB;
            attribs[iattr++] = _this->gl_config.minor_version;

            // SDL profile bits match WGL profile bits
            अगर (_this->gl_config.profile_mask != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_MASK_ARB;
                attribs[iattr++] = _this->gl_config.profile_mask;
            }

            // SDL flags match WGL flags
            अगर (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            अगर ((_this->gl_तथ्य->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            अगर ((_this->gl_तथ्य->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            अगर ((_this->gl_तथ्य->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_तथ्य->wglDeleteContext(अस्थायी_context);
        }
    }

    अगर (!context) {
        WIN_SetError("Could not create GL context");
        वापस शून्य;
    }

    अगर (!WIN_GL_MakeCurrent(_this, window, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        वापस शून्य;
    }

    _this->gl_config.HAS_GL_ARB_color_बफर_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    वापस (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    HDC hdc;

    अगर (!_this->gl_तथ्य) {
        वापस SDL_SetError("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(window || (window == शून्य && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    अगर (!window) {
        window = SDL_GL_GetCurrentWindow();
        अगर (!window) {
            SDL_assert(SDL_GL_GetCurrentContext() == शून्य);
            वापस true; // already done.
        }
    }

    hdc = window->internal->hdc;
    अगर (!_this->gl_तथ्य->wglMakeCurrent(hdc, (HGLRC)context)) {
        वापस WIN_SetError("wglMakeCurrent()");
    }
    वापस true;
}

bool WIN_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    अगर ((interval < 0) && (!_this->gl_तथ्य->HAS_WGL_EXT_swap_control_tear)) {
        वापस SDL_SetError("Negative swap interval unsupported in this GL");
    } अन्यथा अगर (_this->gl_तथ्य->wglSwapIntervalEXT) {
        अगर (!_this->gl_तथ्य->wglSwapIntervalEXT(interval)) {
            वापस WIN_SetError("wglSwapIntervalEXT()");
        }
    } अन्यथा {
        वापस SDL_Unsupported();
    }
    वापस true;
}

bool WIN_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval)
{
    अगर (_this->gl_तथ्य->wglGetSwapIntervalEXT) {
        *interval = _this->gl_तथ्य->wglGetSwapIntervalEXT();
        वापस true;
    } अन्यथा {
        वापस SDL_Unsupported();
    }
}

bool WIN_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;

    अगर (!SwapBuffers(hdc)) {
        वापस WIN_SetError("SwapBuffers()");
    }
    वापस true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    अगर (!_this->gl_तथ्य) {
        वापस true;
    }
    _this->gl_तथ्य->wglDeleteContext((HGLRC)context);
    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_OPENGL_WGL

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS
