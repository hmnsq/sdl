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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengl.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OPENGL "OPENGL32.DLL"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_create_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ARB_create_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_MAJOR_ਸੰਸਕਰਣ_ARB          0x2091
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_MINOR_ਸੰਸਕਰਣ_ARB          0x2092
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_FLAGS_ARB                  0x2094
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_DEBUG_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB              0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_FORWARD_COMPATIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB 0x0002

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_create_context_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ARB_create_context_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_PROFILE_ਨਕਾਬ_ARB              0x9126
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_CORE_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB          0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_COMPATIBILITY_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB 0x00000002
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_create_context_robustness
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ARB_create_context_robustness
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_ROBUST_ACCESS_ਦੋਆਧਾਰੀ_ਅੰਕ_ARB           0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_EXT_create_context_es2_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_EXT_create_context_es2_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_ES2_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT 0x00000004
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_EXT_create_context_es_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_EXT_create_context_es_profile
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_ES_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT 0x00000004
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_framebuffer_sRGB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ARB_framebuffer_sRGB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_pixel_format_float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ARB_pixel_format_float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_context_flush_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ARB_context_flush_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_create_context_no_error
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ARB_create_context_no_error
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           ਅਚਲ ਪੂਰਨ
                                                               *attribList);

#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GetDC(hwnd)          (HDC) hwnd
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ReleaseDC(hwnd, hdc) 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅਦਲਾ_ਬਦਲੀ_Buffers          _this->gl_ਅੰਕੜੇ->wgl_ਅਦਲਾ_ਬਦਲੀ_Buffers
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DescribePixelFormat  _this->gl_ਅੰਕੜੇ->wglDescribePixelFormat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਚੁਣੋ_Pixel_Format    _this->gl_ਅੰਕੜੇ->wgl_ਚੁਣੋ_Pixel_Format
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GetPixelFormat       _this->gl_ਅੰਕੜੇ->wglGetPixelFormat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੈੱਟ_Pixel_Format       _this->gl_ਅੰਕੜੇ->wgl_ਸੈੱਟ_Pixel_Format
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool WIN_GL_ਲੱਦੋ_Library_EGLFallback(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_ਲੱਦੋ_Library = WIN_GLES_ਲੱਦੋ_Library;
    _this->GL_Get_Proc_ਪਤਾ = WIN_GLES_Get_Proc_ਪਤਾ;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    _this->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    _this->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = WIN_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    ਵਾਪਸ WIN_GLES_ਲੱਦੋ_Library(_this, ਰਸਤਾ);
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not configured with EGL support");
#ਜੇ_ਅੰਤ
}

bool WIN_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਖਾਲੀ *handle;

    ਜੇ ((_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ਵਾਪਸ WIN_GL_ਲੱਦੋ_Library_EGLFallback(_this, ਰਸਤਾ);
    }

    ਜੇ (ਰਸਤਾ == ਨਿਰਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    ਜੇ (ਰਸਤਾ == ਨਿਰਾ) {
        ਰਸਤਾ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
    ਜੇ (!_this->gl_config.dll_handle) {
        ਵਾਪਸ false;
    }
    SDL_strlcpy(_this->gl_config.driver_ਰਸਤਾ, ਰਸਤਾ,
                SDL_arraysize(_this->gl_config.driver_ਰਸਤਾ));

    // Allocate OpenGL memory
    _this->gl_ਅੰਕੜੇ = (ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ));
    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_ਅੰਕੜੇ->wgl_Get_Proc_ਪਤਾ = (PROC (WINAPI *)(ਅਚਲ ਅੱਖਰ *))
        SDL_ਲੱਦੋ_Function(handle, "wglGetProcAddress");
    _this->gl_ਅੰਕੜੇ->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_ਲੱਦੋ_Function(handle, "wglCreateContext");
    _this->gl_ਅੰਕੜੇ->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_ਲੱਦੋ_Function(handle, "wglDeleteContext");
    _this->gl_ਅੰਕੜੇ->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_ਲੱਦੋ_Function(handle, "wglMakeCurrent");
    _this->gl_ਅੰਕੜੇ->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_ਲੱਦੋ_Function(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_ਅੰਕੜੇ->wgl_ਅਦਲਾ_ਬਦਲੀ_Buffers = (BOOL(WINAPI *)(HDC))
        SDL_ਲੱਦੋ_Function(handle, "wglSwapBuffers");
    _this->gl_ਅੰਕੜੇ->wglDescribePixelFormat = (ਪੂਰਨ(WINAPI *)(HDC, ਪੂਰਨ, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_ਲੱਦੋ_Function(handle, "wglDescribePixelFormat");
    _this->gl_ਅੰਕੜੇ->wgl_ਚੁਣੋ_Pixel_Format = (ਪੂਰਨ(WINAPI *)(HDC, ਅਚਲ PIXELFORMATDESCRIPTOR *))
        SDL_ਲੱਦੋ_Function(handle, "wglChoosePixelFormat");
    _this->gl_ਅੰਕੜੇ->wgl_ਸੈੱਟ_Pixel_Format = (BOOL(WINAPI *)(HDC, ਪੂਰਨ, ਅਚਲ PIXELFORMATDESCRIPTOR *))
        SDL_ਲੱਦੋ_Function(handle, "wglSetPixelFormat");
    _this->gl_ਅੰਕੜੇ->wglGetPixelFormat = (ਪੂਰਨ(WINAPI *)(HDC hdc))
        SDL_ਲੱਦੋ_Function(handle, "wglGetPixelFormat");
#ਜੇ_ਅੰਤ

    ਜੇ (!_this->gl_ਅੰਕੜੇ->wgl_Get_Proc_ਪਤਾ ||
        !_this->gl_ਅੰਕੜੇ->wglCreateContext ||
        !_this->gl_ਅੰਕੜੇ->wglDeleteContext ||
        !_this->gl_ਅੰਕੜੇ->wglMakeCurrent
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_ਅੰਕੜੇ->wgl_ਅਦਲਾ_ਬਦਲੀ_Buffers ||
        !_this->gl_ਅੰਕੜੇ->wglDescribePixelFormat ||
        !_this->gl_ਅੰਕੜੇ->wgl_ਚੁਣੋ_Pixel_Format ||
        !_this->gl_ਅੰਕੜੇ->wglGetPixelFormat ||
        !_this->gl_ਅੰਕੜੇ->wgl_ਸੈੱਟ_Pixel_Format
#ਜੇ_ਅੰਤ
    ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not retrieve OpenGL functions");
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

    ਵਾਪਸ true;
}

SDL_Function_ਸੂਚਕ WIN_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    SDL_Function_ਸੂਚਕ func;

    // This is to pick up extensions
    func = (SDL_Function_ਸੂਚਕ)_this->gl_ਅੰਕੜੇ->wgl_Get_Proc_ਪਤਾ(proc);
    ਜੇ (!func) {
        // This is probably a normal GL function
        func = (SDL_Function_ਸੂਚਕ)Get_Proc_ਪਤਾ((HMODULE)_this->gl_config.dll_handle, proc);
    }
    ਵਾਪਸ func;
}

ਖਾਲੀ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ਨਿਰਾ;

    // Free OpenGL memory
    SDL_free(_this->gl_ਅੰਕੜੇ);
    _this->gl_ਅੰਕੜੇ = ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ WIN_GL_ਤਿਆਰੀ_Pixel_Format(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_ਮਾਪ = ਆਕਾਰ(*pfd);
    pfd->n_ਸੰਸਕਰਣ = 1;
    pfd->dwFlags = (PFD_DRAW_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ | PFD_SUPPORT_OPENGL);
    ਜੇ (_this->gl_config.double_ਬਫਰ) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    ਜੇ (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->c_Red_ਬਿੱਟ = (BYTE)_this->gl_config.red_ਮਾਪ;
    pfd->c_Green_ਬਿੱਟ = (BYTE)_this->gl_config.green_ਮਾਪ;
    pfd->c_Blue_ਬਿੱਟ = (BYTE)_this->gl_config.blue_ਮਾਪ;
    pfd->c_Alpha_ਬਿੱਟ = (BYTE)_this->gl_config.alpha_ਮਾਪ;
    ਜੇ (_this->gl_config.ਬਫਰ_ਮਾਪ) {
        pfd->c_Color_ਬਿੱਟ = (BYTE)(_this->gl_config.ਬਫਰ_ਮਾਪ - _this->gl_config.alpha_ਮਾਪ);
    } ਨਹੀਂਤਾਂ {
        pfd->c_Color_ਬਿੱਟ = (pfd->c_Red_ਬਿੱਟ + pfd->c_Green_ਬਿੱਟ + pfd->c_Blue_ਬਿੱਟ);
    }
    pfd->c_Accum_Red_ਬਿੱਟ = (BYTE)_this->gl_config.accum_red_ਮਾਪ;
    pfd->c_Accum_Green_ਬਿੱਟ = (BYTE)_this->gl_config.accum_green_ਮਾਪ;
    pfd->c_Accum_Blue_ਬਿੱਟ = (BYTE)_this->gl_config.accum_blue_ਮਾਪ;
    pfd->c_Accum_Alpha_ਬਿੱਟ = (BYTE)_this->gl_config.accum_alpha_ਮਾਪ;
    pfd->c_Accum_ਬਿੱਟ =
        (pfd->c_Accum_Red_ਬਿੱਟ + pfd->c_Accum_Green_ਬਿੱਟ + pfd->c_Accum_Blue_ਬਿੱਟ +
         pfd->c_Accum_Alpha_ਬਿੱਟ);
    pfd->c_ਡੂੰਘਾਈ_ਬਿੱਟ = (BYTE)_this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ;
    pfd->c_Stencil_ਬਿੱਟ = (BYTE)_this->gl_config.stencil_ਮਾਪ;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
ਸਥਿਰ bool WIN_GL_ਚੁਣੋ_Pixel_Format(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *ਨਿਸ਼ਾਨਾ)
{
    PIXELFORMATDESCRIPTOR pfd;
    ਪੂਰਨ ਗਿਣਤੀ_2, ਸੂਚਕਾਂਕ, ਉੱਤਮ = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ dist, ਉੱਤਮ_dist = ~0U;

    ਗਿਣਤੀ_2 = DescribePixelFormat(hdc, 1, ਆਕਾਰ(pfd), ਨਿਰਾ);

    ਲਈ (ਸੂਚਕਾਂਕ = 1; ਸੂਚਕਾਂਕ <= ਗਿਣਤੀ_2; ਸੂਚਕਾਂਕ++) {

        ਜੇ (!DescribePixelFormat(hdc, ਸੂਚਕਾਂਕ, ਆਕਾਰ(pfd), &pfd)) {
            ਜਾਰੀ;
        }

        ਜੇ ((pfd.dwFlags & ਨਿਸ਼ਾਨਾ->dwFlags) != ਨਿਸ਼ਾਨਾ->dwFlags) {
            ਜਾਰੀ;
        }

        ਜੇ (pfd.iLayerType != ਨਿਸ਼ਾਨਾ->iLayerType) {
            ਜਾਰੀ;
        }
        ਜੇ (pfd.iPixelType != ਨਿਸ਼ਾਨਾ->iPixelType) {
            ਜਾਰੀ;
        }

        dist = 0;

        ਜੇ (pfd.c_Color_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Color_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Color_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Color_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Red_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Red_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Red_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Red_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Green_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Green_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Green_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Green_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Blue_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Blue_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Blue_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Blue_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Alpha_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Alpha_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Alpha_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Alpha_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Accum_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Accum_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Accum_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Accum_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Accum_Red_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Accum_Red_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Accum_Red_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Accum_Red_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Accum_Green_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Accum_Green_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Accum_Green_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Accum_Green_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Accum_Blue_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Accum_Blue_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Accum_Blue_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Accum_Blue_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Accum_Alpha_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Accum_Alpha_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Accum_Alpha_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Accum_Alpha_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_ਡੂੰਘਾਈ_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_ਡੂੰਘਾਈ_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_ਡੂੰਘਾਈ_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_ਡੂੰਘਾਈ_ਬਿੱਟ);
        }
        ਜੇ (pfd.c_Stencil_ਬਿੱਟ < ਨਿਸ਼ਾਨਾ->c_Stencil_ਬਿੱਟ) {
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            dist += (pfd.c_Stencil_ਬਿੱਟ - ਨਿਸ਼ਾਨਾ->c_Stencil_ਬਿੱਟ);
        }

        ਜੇ (dist < ਉੱਤਮ_dist) {
            ਉੱਤਮ = ਸੂਚਕਾਂਕ;
            ਉੱਤਮ_dist = dist;
        }
    }

    ਵਾਪਸ ਉੱਤਮ;
}

ਸਥਿਰ bool HasExtension(ਅਚਲ ਅੱਖਰ *extension, ਅਚਲ ਅੱਖਰ *extensions)
{
    ਅਚਲ ਅੱਖਰ *ਸ਼ੁਰੂ;
    ਅਚਲ ਅੱਖਰ *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ਜੇ (where || *extension == '\0') {
        ਵਾਪਸ false;
    }

    ਜੇ (!extensions) {
        ਵਾਪਸ false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    ਸ਼ੁਰੂ = extensions;

    ਲਈ (;;) {
        where = SDL_strstr(ਸ਼ੁਰੂ, extension);
        ਜੇ (!where) {
            ਰੋਕੋ;
        }

        terminator = where + SDL_strlen(extension);
        ਜੇ (where == ਸ਼ੁਰੂ || *(where - 1) == ' ') {
            ਜੇ (*terminator == ' ' || *terminator == '\0') {
                ਵਾਪਸ true;
            }
        }

        ਸ਼ੁਰੂ = terminator;
    }
    ਵਾਪਸ false;
}

ਖਾਲੀ WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    ਅਚਲ ਅੱਖਰ *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    ਅਚਲ ਅੱਖਰ *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ;
    }

    hwnd =
        Create_ਖਿੜਕੀ(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ਨਿਰਾ, ਨਿਰਾ, SDL_Instance, ਨਿਰਾ);
    ਜੇ (!hwnd) {
        ਵਾਪਸ;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_ਤਿਆਰੀ_Pixel_Format(_this, &pfd);

    ਸੈੱਟ_Pixel_Format(hdc, ਚੁਣੋ_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_ਅੰਕੜੇ->wglCreateContext(hdc);
    ਜੇ (!hglrc) {
        ਵਾਪਸ;
    }
    _this->gl_ਅੰਕੜੇ->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (ਅਚਲ ਅੱਖਰ *(WINAPI *)(HDC))
        _this->gl_ਅੰਕੜੇ->wgl_Get_Proc_ਪਤਾ("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    ਜੇ (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } ਨਹੀਂਤਾਂ {
        extensions = ਨਿਰਾ;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_pixel_format = false;
    ਜੇ (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_ਅੰਕੜੇ->wgl_ਚੁਣੋ_Pixel_Format_ARB =
            (BOOL (WINAPI *)(HDC, ਅਚਲ ਪੂਰਨ *, ਅਚਲ FLOAT *, UINT, ਪੂਰਨ *, UINT *))
            WIN_GL_Get_Proc_ਪਤਾ(_this, "wglChoosePixelFormatARB");
        _this->gl_ਅੰਕੜੇ->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, ਪੂਰਨ, ਪੂਰਨ, UINT, ਅਚਲ ਪੂਰਨ *, ਪੂਰਨ *))
            WIN_GL_Get_Proc_ਪਤਾ(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        ਜੇ ((_this->gl_ਅੰਕੜੇ->wgl_ਚੁਣੋ_Pixel_Format_ARB != ਨਿਰਾ) &&
            (_this->gl_ਅੰਕੜੇ->wglGetPixelFormatAttribivARB != ਨਿਰਾ)) {
            _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_ਅੰਕੜੇ->HAS_WGL_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear = false;
    ਜੇ (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_ਅੰਕੜੇ->wgl_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT =
            (BOOL (WINAPI *)(ਪੂਰਨ))
            WIN_GL_Get_Proc_ਪਤਾ(_this, "wglSwapIntervalEXT");
        _this->gl_ਅੰਕੜੇ->wgl_Get_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT =
            (ਪੂਰਨ (WINAPI *)(ਖਾਲੀ))
            WIN_GL_Get_Proc_ਪਤਾ(_this, "wglGetSwapIntervalEXT");
        ਜੇ (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_ਅੰਕੜੇ->HAS_WGL_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear = true;
        }
    } ਨਹੀਂਤਾਂ {
        _this->gl_ਅੰਕੜੇ->wgl_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT = ਨਿਰਾ;
        _this->gl_ਅੰਕੜੇ->wgl_Get_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT = ਨਿਰਾ;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_ਅੰਕੜੇ->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    ਜੇ (_this->gl_ਅੰਕੜੇ->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.major,
            &_this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.minor);
    }

    // Check for WGL_ARB_context_flush_control
    ਜੇ (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    ਜੇ (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    ਜੇ (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    ਜੇ (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_framebuffer_sRGB = true;
    } ਨਹੀਂਤਾਂ ਜੇ (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_ਅੰਕੜੇ->wglMakeCurrent(hdc, ਨਿਰਾ);
    _this->gl_ਅੰਕੜੇ->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    Destroy_ਖਿੜਕੀ(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

ਸਥਿਰ ਪੂਰਨ WIN_GL_ਚੁਣੋ_Pixel_Format_ARB(SDL_VideoDevice *_this, ਪੂਰਨ *iAttribs, ਦਸ਼ਮਲਵ *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    ਪੂਰਨ pixel_format = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ matching;

    hwnd =
        Create_ਖਿੜਕੀ(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ਨਿਰਾ, ਨਿਰਾ, SDL_Instance, ਨਿਰਾ);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_ਤਿਆਰੀ_Pixel_Format(_this, &pfd);

    ਸੈੱਟ_Pixel_Format(hdc, ਚੁਣੋ_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_ਅੰਕੜੇ->wglCreateContext(hdc);
    ਜੇ (hglrc) {
        _this->gl_ਅੰਕੜੇ->wglMakeCurrent(hdc, hglrc);

        ਜੇ (_this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_pixel_format) {
            _this->gl_ਅੰਕੜੇ->wgl_ਚੁਣੋ_Pixel_Format_ARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            ਪੂਰਨ srgb = 0;
            ਜੇ (_this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_framebuffer_sRGB) {
                ਪੂਰਨ qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_ਅੰਕੜੇ->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_ਅੰਕੜੇ->wglMakeCurrent(hdc, ਨਿਰਾ);
        _this->gl_ਅੰਕੜੇ->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    Destroy_ਖਿੜਕੀ(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    ਵਾਪਸ pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
ਸਥਿਰ bool WIN_GL_ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਦਰੂਨੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    HDC hdc = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    ਪੂਰਨ pixel_format = 0;
    ਪੂਰਨ iAttribs[64];
    ਪੂਰਨ *iAttr;
    ਪੂਰਨ *iAccelAttr;
    ਦਸ਼ਮਲਵ fAttribs[1] = { 0 };

    WIN_GL_ਤਿਆਰੀ_Pixel_Format(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_ਬਿੱਟ_ARB;
    *iAttr++ = _this->gl_config.red_ਮਾਪ;
    *iAttr++ = WGL_GREEN_ਬਿੱਟ_ARB;
    *iAttr++ = _this->gl_config.green_ਮਾਪ;
    *iAttr++ = WGL_BLUE_ਬਿੱਟ_ARB;
    *iAttr++ = _this->gl_config.blue_ਮਾਪ;

    ਜੇ (_this->gl_config.alpha_ਮਾਪ) {
        *iAttr++ = WGL_ALPHA_ਬਿੱਟ_ARB;
        *iAttr++ = _this->gl_config.alpha_ਮਾਪ;
    }

    *iAttr++ = WGL_DOUBLE_ਬਫਰ_ARB;
    *iAttr++ = _this->gl_config.double_ਬਫਰ;

    *iAttr++ = WGL_ਡੂੰਘਾਈ_ਬਿੱਟ_ARB;
    *iAttr++ = _this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ;

    ਜੇ (_this->gl_config.stencil_ਮਾਪ) {
        *iAttr++ = WGL_STENCIL_ਬਿੱਟ_ARB;
        *iAttr++ = _this->gl_config.stencil_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_red_ਮਾਪ) {
        *iAttr++ = WGL_ACCUM_RED_ਬਿੱਟ_ARB;
        *iAttr++ = _this->gl_config.accum_red_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_green_ਮਾਪ) {
        *iAttr++ = WGL_ACCUM_GREEN_ਬਿੱਟ_ARB;
        *iAttr++ = _this->gl_config.accum_green_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_blue_ਮਾਪ) {
        *iAttr++ = WGL_ACCUM_BLUE_ਬਿੱਟ_ARB;
        *iAttr++ = _this->gl_config.accum_blue_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.accum_alpha_ਮਾਪ) {
        *iAttr++ = WGL_ACCUM_ALPHA_ਬਿੱਟ_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    ਜੇ (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    ਜੇ (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    ਜੇ (_this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    ਜੇ (_this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_framebuffer_sRGB) {
        ਅਚਲ ਅੱਖਰ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ਜੇ (srgbhint && *srgbhint) {
            ਜੇ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ਨਹੀਂਤਾਂ {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    ਜੇ (_this->gl_config.accelerated) {
        *iAttr++ = WGL_ਭਰਿਆ_ACCELERATION_ARB;
    } ਨਹੀਂਤਾਂ {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_ਚੁਣੋ_Pixel_Format_ARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    ਜੇ ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_ਚੁਣੋ_Pixel_Format_ARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_ਭਰਿਆ_ACCELERATION_ARB; // if we try again.
    }
    ਜੇ (!pixel_format) {
        pixel_format = WIN_GL_ਚੁਣੋ_Pixel_Format(_this, hdc, &pfd);
    }
    ਜੇ (!pixel_format) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No matching GL pixel format available");
    }
    ਜੇ (!ਸੈੱਟ_Pixel_Format(hdc, pixel_format, &pfd)) {
        ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetPixelFormat()");
    }
    ਵਾਪਸ true;
}

bool WIN_GL_ਤਿਆਰੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // The current context is lost in here; save it and reset it.
    SDL_ਖਿੜਕੀ *current_win = SDL_GL_Get_Current_ਖਿੜਕੀ();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    ਅਚਲ ਪੂਰਨ ਨਤੀਜਾ = WIN_GL_ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਦਰੂਨੀ(_this, ਖਿੜਕੀ);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_ਅੰਕੜੇ != ਨਿਰਾ);
    SDL_assert(_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    ਵਾਪਸ !_this->gl_ਅੰਕੜੇ->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_ਸੰਸਕਰਣ > _this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.major ||
           (_this->gl_config.major_ਸੰਸਕਰਣ == _this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.major && _this->gl_config.minor_ਸੰਸਕਰਣ > _this->gl_ਅੰਕੜੇ->es_profile_max_supported_ਸੰਸਕਰਣ.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    HDC hdc = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hdc;
    HGLRC context, share_context;

    ਜੇ (_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        ਜੇ (!WIN_GL_ਲੱਦੋ_Library_EGLFallback(_this, ਨਿਰਾ)) {
            ਵਾਪਸ ਨਿਰਾ;
        }

        ਵਾਪਸ WIN_GLES_CreateContext(_this, ਖਿੜਕੀ);
#ਨਹੀਂਤਾਂ
        SDL_ਸੈੱਟ_Error("SDL not configured with EGL support");
        ਵਾਪਸ ਨਿਰਾ;
#ਜੇ_ਅੰਤ
    }

    ਜੇ (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } ਨਹੀਂਤਾਂ {
        share_context = 0;
    }

    ਜੇ (_this->gl_config.major_ਸੰਸਕਰਣ < 3 &&
        _this->gl_config.profile_ਨਕਾਬ == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_ਅੰਕੜੇ->wglCreateContext(hdc);
        ਜੇ (share_context != 0) {
            _this->gl_ਅੰਕੜੇ->wglShareLists(share_context, context);
        }
    } ਨਹੀਂਤਾਂ {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC ਆਰਜ਼ੀ_context = _this->gl_ਅੰਕੜੇ->wglCreateContext(hdc);
        ਜੇ (!ਆਰਜ਼ੀ_context) {
            SDL_ਸੈੱਟ_Error("Could not create GL context");
            ਵਾਪਸ ਨਿਰਾ;
        }

        // Make the context current
        ਜੇ (!WIN_GL_MakeCurrent(_this, ਖਿੜਕੀ, (SDL_GLContext)ਆਰਜ਼ੀ_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)ਆਰਜ਼ੀ_context);
            ਵਾਪਸ ਨਿਰਾ;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_ਅੰਕੜੇ->wgl_Get_Proc_ਪਤਾ("wglCreateContextAttribsARB");
        ਜੇ (!wglCreateContextAttribsARB) {
            SDL_ਸੈੱਟ_Error("GL 3.x is not supported");
            context = ਆਰਜ਼ੀ_context;
        } ਨਹੀਂਤਾਂ {
            ਪੂਰਨ attribs[15]; // max 14 attributes plus terminator
            ਪੂਰਨ iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_ਸੰਸਕਰਣ_ARB;
            attribs[iattr++] = _this->gl_config.major_ਸੰਸਕਰਣ;
            attribs[iattr++] = WGL_CONTEXT_MINOR_ਸੰਸਕਰਣ_ARB;
            attribs[iattr++] = _this->gl_config.minor_ਸੰਸਕਰਣ;

            // SDL profile bits match WGL profile bits
            ਜੇ (_this->gl_config.profile_ਨਕਾਬ != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_ਨਕਾਬ_ARB;
                attribs[iattr++] = _this->gl_config.profile_ਨਕਾਬ;
            }

            // SDL flags match WGL flags
            ਜੇ (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            ਜੇ ((_this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ਜੇ ((_this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ਜੇ ((_this->gl_ਅੰਕੜੇ->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_ਅੰਕੜੇ->wglDeleteContext(ਆਰਜ਼ੀ_context);
        }
    }

    ਜੇ (!context) {
        WIN_ਸੈੱਟ_Error("Could not create GL context");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!WIN_GL_MakeCurrent(_this, ਖਿੜਕੀ, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        ਵਾਪਸ ਨਿਰਾ;
    }

    _this->gl_config.HAS_GL_ARB_color_ਬਫਰ_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    ਵਾਪਸ (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    HDC hdc;

    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(ਖਿੜਕੀ || (ਖਿੜਕੀ == ਨਿਰਾ && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    ਜੇ (!ਖਿੜਕੀ) {
        ਖਿੜਕੀ = SDL_GL_Get_Current_ਖਿੜਕੀ();
        ਜੇ (!ਖਿੜਕੀ) {
            SDL_assert(SDL_GL_GetCurrentContext() == ਨਿਰਾ);
            ਵਾਪਸ true; // already done.
        }
    }

    hdc = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hdc;
    ਜੇ (!_this->gl_ਅੰਕੜੇ->wglMakeCurrent(hdc, (HGLRC)context)) {
        ਵਾਪਸ WIN_ਸੈੱਟ_Error("wglMakeCurrent()");
    }
    ਵਾਪਸ true;
}

bool WIN_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    ਜੇ ((interval < 0) && (!_this->gl_ਅੰਕੜੇ->HAS_WGL_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Negative swap interval unsupported in this GL");
    } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_ਅੰਕੜੇ->wgl_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT) {
        ਜੇ (!_this->gl_ਅੰਕੜੇ->wgl_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT(interval)) {
            ਵਾਪਸ WIN_ਸੈੱਟ_Error("wglSwapIntervalEXT()");
        }
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Unsupported();
    }
    ਵਾਪਸ true;
}

bool WIN_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    ਜੇ (_this->gl_ਅੰਕੜੇ->wgl_Get_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT) {
        *interval = _this->gl_ਅੰਕੜੇ->wgl_Get_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT();
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Unsupported();
    }
}

bool WIN_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    HDC hdc = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hdc;

    ਜੇ (!ਅਦਲਾ_ਬਦਲੀ_Buffers(hdc)) {
        ਵਾਪਸ WIN_ਸੈੱਟ_Error("SwapBuffers()");
    }
    ਵਾਪਸ true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ true;
    }
    _this->gl_ਅੰਕੜੇ->wglDeleteContext((HGLRC)context);
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_WGL

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS
