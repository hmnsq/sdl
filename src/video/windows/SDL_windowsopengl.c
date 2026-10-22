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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsopengles.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>

#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OPENGL "OPENGL32.DLL"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_create_context
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ARB_create_context
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_MAJOR_ಆವೃತ್ತಿ_ARB          0x2091
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_MINOR_ಆವೃತ್ತಿ_ARB          0x2092
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_FLAGS_ARB                  0x2094
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_DEBUG_ಬಿಟ್_ARB              0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_FORWARD_COMPATIBLE_ಬಿಟ್_ARB 0x0002

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_create_context_profile
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ARB_create_context_profile
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_PROFILE_ಮುಖವಾಡ_ARB              0x9126
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_CORE_PROFILE_ಬಿಟ್_ARB          0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_COMPATIBILITY_PROFILE_ಬಿಟ್_ARB 0x00000002
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_create_context_robustness
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ARB_create_context_robustness
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_ROBUST_ACCESS_ಬಿಟ್_ARB           0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_EXT_create_context_es2_profile
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_EXT_create_context_es2_profile
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_ES2_PROFILE_ಬಿಟ್_EXT 0x00000004
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_EXT_create_context_es_profile
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_EXT_create_context_es_profile
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_ES_PROFILE_ಬಿಟ್_EXT 0x00000004
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_framebuffer_sRGB
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ARB_framebuffer_sRGB
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_pixel_format_float
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ARB_pixel_format_float
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_context_flush_control
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ARB_context_flush_control
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_create_context_no_error
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ARB_create_context_no_error
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ
                                                               *attribList);

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#ವ್ಯಾಖ್ಯಾನಿಸು GetDC(hwnd)          (HDC) hwnd
#ವ್ಯಾಖ್ಯಾನಿಸು ReleaseDC(hwnd, hdc) 1
#ವ್ಯಾಖ್ಯಾನಿಸು ಅದಲುಬದಲು_Buffers          _this->gl_ದತ್ತಾಂಶ->wgl_ಅದಲುಬದಲು_Buffers
#ವ್ಯಾಖ್ಯಾನಿಸು DescribePixelFormat  _this->gl_ದತ್ತಾಂಶ->wglDescribePixelFormat
#ವ್ಯಾಖ್ಯಾನಿಸು ಆರಿಸು_Pixel_Format    _this->gl_ದತ್ತಾಂಶ->wgl_ಆರಿಸು_Pixel_Format
#ವ್ಯಾಖ್ಯಾನಿಸು GetPixelFormat       _this->gl_ದತ್ತಾಂಶ->wglGetPixelFormat
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಣ_Pixel_Format       _this->gl_ದತ್ತಾಂಶ->wgl_ಗಣ_Pixel_Format
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool WIN_GL_ತುಂಬು_Library_EGLFallback(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_ತುಂಬು_Library = WIN_GLES_ತುಂಬು_Library;
    _this->GL_Get_Proc_ವಿಳಾಸ = WIN_GLES_Get_Proc_ವಿಳಾಸ;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_ಗಣ_ಅದಲುಬದಲು_Interval = WIN_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    _this->GL_Get_ಅದಲುಬದಲು_Interval = WIN_GLES_Get_ಅದಲುಬದಲು_Interval;
    _this->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = WIN_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    ಹಿಂತಿರುಗಿ WIN_GLES_ತುಂಬು_Library(_this, ಮಾರ್ಗ);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not configured with EGL support");
#ಆದರೆ_ಅಂತ್ಯ
}

bool WIN_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಶೂನ್ಯ *handle;

    ಆದರೆ ((_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ಹಿಂತಿರುಗಿ WIN_GL_ತುಂಬು_Library_EGLFallback(_this, ಮಾರ್ಗ);
    }

    ಆದರೆ (ಮಾರ್ಗ == ಖಾಲಿ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    ಆದರೆ (ಮಾರ್ಗ == ಖಾಲಿ) {
        ಮಾರ್ಗ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
    ಆದರೆ (!_this->gl_config.dll_handle) {
        ಹಿಂತಿರುಗಿ false;
    }
    SDL_strlcpy(_this->gl_config.driver_ಮಾರ್ಗ, ಮಾರ್ಗ,
                SDL_arraysize(_this->gl_config.driver_ಮಾರ್ಗ));

    // Allocate OpenGL memory
    _this->gl_ದತ್ತಾಂಶ = (ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ));
    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_ದತ್ತಾಂಶ->wgl_Get_Proc_ವಿಳಾಸ = (PROC (WINAPI *)(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *))
        SDL_ತುಂಬು_Function(handle, "wglGetProcAddress");
    _this->gl_ದತ್ತಾಂಶ->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_ತುಂಬು_Function(handle, "wglCreateContext");
    _this->gl_ದತ್ತಾಂಶ->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_ತುಂಬು_Function(handle, "wglDeleteContext");
    _this->gl_ದತ್ತಾಂಶ->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_ತುಂಬು_Function(handle, "wglMakeCurrent");
    _this->gl_ದತ್ತಾಂಶ->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_ತುಂಬು_Function(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_ದತ್ತಾಂಶ->wgl_ಅದಲುಬದಲು_Buffers = (BOOL(WINAPI *)(HDC))
        SDL_ತುಂಬು_Function(handle, "wglSwapBuffers");
    _this->gl_ದತ್ತಾಂಶ->wglDescribePixelFormat = (ಪೂರ್ಣಾಂಕ(WINAPI *)(HDC, ಪೂರ್ಣಾಂಕ, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_ತುಂಬು_Function(handle, "wglDescribePixelFormat");
    _this->gl_ದತ್ತಾಂಶ->wgl_ಆರಿಸು_Pixel_Format = (ಪೂರ್ಣಾಂಕ(WINAPI *)(HDC, ಸ್ಥಿರಾಂಕ PIXELFORMATDESCRIPTOR *))
        SDL_ತುಂಬು_Function(handle, "wglChoosePixelFormat");
    _this->gl_ದತ್ತಾಂಶ->wgl_ಗಣ_Pixel_Format = (BOOL(WINAPI *)(HDC, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ PIXELFORMATDESCRIPTOR *))
        SDL_ತುಂಬು_Function(handle, "wglSetPixelFormat");
    _this->gl_ದತ್ತಾಂಶ->wglGetPixelFormat = (ಪೂರ್ಣಾಂಕ(WINAPI *)(HDC hdc))
        SDL_ತುಂಬು_Function(handle, "wglGetPixelFormat");
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ->wgl_Get_Proc_ವಿಳಾಸ ||
        !_this->gl_ದತ್ತಾಂಶ->wglCreateContext ||
        !_this->gl_ದತ್ತಾಂಶ->wglDeleteContext ||
        !_this->gl_ದತ್ತಾಂಶ->wglMakeCurrent
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_ದತ್ತಾಂಶ->wgl_ಅದಲುಬದಲು_Buffers ||
        !_this->gl_ದತ್ತಾಂಶ->wglDescribePixelFormat ||
        !_this->gl_ದತ್ತಾಂಶ->wgl_ಆರಿಸು_Pixel_Format ||
        !_this->gl_ದತ್ತಾಂಶ->wglGetPixelFormat ||
        !_this->gl_ದತ್ತಾಂಶ->wgl_ಗಣ_Pixel_Format
#ಆದರೆ_ಅಂತ್ಯ
    ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not retrieve OpenGL functions");
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

    ಹಿಂತಿರುಗಿ true;
}

SDL_Function_ಸೂಚಕ WIN_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    SDL_Function_ಸೂಚಕ func;

    // This is to pick up extensions
    func = (SDL_Function_ಸೂಚಕ)_this->gl_ದತ್ತಾಂಶ->wgl_Get_Proc_ವಿಳಾಸ(proc);
    ಆದರೆ (!func) {
        // This is probably a normal GL function
        func = (SDL_Function_ಸೂಚಕ)Get_Proc_ವಿಳಾಸ((HMODULE)_this->gl_config.dll_handle, proc);
    }
    ಹಿಂತಿರುಗಿ func;
}

ಶೂನ್ಯ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ಖಾಲಿ;

    // Free OpenGL memory
    SDL_free(_this->gl_ದತ್ತಾಂಶ);
    _this->gl_ದತ್ತಾಂಶ = ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_GL_ಸಿದ್ಧತೆ_Pixel_Format(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_ಗಾತ್ರ = ಗಾತ್ರ(*pfd);
    pfd->n_ಆವೃತ್ತಿ = 1;
    pfd->dwFlags = (PFD_DRAW_ಗಮ್ಯ_ಕಿಟಕಿ | PFD_SUPPORT_OPENGL);
    ಆದರೆ (_this->gl_config.double_ಬಫರ್) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    ಆದರೆ (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->c_Red_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.red_ಗಾತ್ರ;
    pfd->c_Green_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.green_ಗಾತ್ರ;
    pfd->c_Blue_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.blue_ಗಾತ್ರ;
    pfd->c_Alpha_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.alpha_ಗಾತ್ರ;
    ಆದರೆ (_this->gl_config.ಬಫರ್_ಗಾತ್ರ) {
        pfd->c_Color_ಬಿಟ್ಟುಗಳು = (BYTE)(_this->gl_config.ಬಫರ್_ಗಾತ್ರ - _this->gl_config.alpha_ಗಾತ್ರ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        pfd->c_Color_ಬಿಟ್ಟುಗಳು = (pfd->c_Red_ಬಿಟ್ಟುಗಳು + pfd->c_Green_ಬಿಟ್ಟುಗಳು + pfd->c_Blue_ಬಿಟ್ಟುಗಳು);
    }
    pfd->c_Accum_Red_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.accum_red_ಗಾತ್ರ;
    pfd->c_Accum_Green_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.accum_green_ಗಾತ್ರ;
    pfd->c_Accum_Blue_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.accum_blue_ಗಾತ್ರ;
    pfd->c_Accum_Alpha_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.accum_alpha_ಗಾತ್ರ;
    pfd->c_Accum_ಬಿಟ್ಟುಗಳು =
        (pfd->c_Accum_Red_ಬಿಟ್ಟುಗಳು + pfd->c_Accum_Green_ಬಿಟ್ಟುಗಳು + pfd->c_Accum_Blue_ಬಿಟ್ಟುಗಳು +
         pfd->c_Accum_Alpha_ಬಿಟ್ಟುಗಳು);
    pfd->c_ಆಳ_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.ಆಳ_ಗಾತ್ರ;
    pfd->c_Stencil_ಬಿಟ್ಟುಗಳು = (BYTE)_this->gl_config.stencil_ಗಾತ್ರ;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
ಸ್ಥಿರ bool WIN_GL_ಆರಿಸು_Pixel_Format(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *ಗುರಿ)
{
    PIXELFORMATDESCRIPTOR pfd;
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, ಸೂಚ್ಯಂಕ, ಉತ್ತಮ = 0;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ dist, ಉತ್ತಮ_dist = ~0U;

    ಎಣಿಕೆ_2 = DescribePixelFormat(hdc, 1, ಗಾತ್ರ(pfd), ಖಾಲಿ);

    ಗಾಗಿ (ಸೂಚ್ಯಂಕ = 1; ಸೂಚ್ಯಂಕ <= ಎಣಿಕೆ_2; ಸೂಚ್ಯಂಕ++) {

        ಆದರೆ (!DescribePixelFormat(hdc, ಸೂಚ್ಯಂಕ, ಗಾತ್ರ(pfd), &pfd)) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ ((pfd.dwFlags & ಗುರಿ->dwFlags) != ಗುರಿ->dwFlags) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ (pfd.iLayerType != ಗುರಿ->iLayerType) {
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (pfd.iPixelType != ಗುರಿ->iPixelType) {
            ಮುಂದುವರಿ;
        }

        dist = 0;

        ಆದರೆ (pfd.c_Color_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Color_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Color_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Color_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Red_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Red_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Red_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Red_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Green_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Green_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Green_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Green_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Blue_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Blue_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Blue_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Blue_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Alpha_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Alpha_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Alpha_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Alpha_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Accum_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Accum_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Accum_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Accum_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Accum_Red_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Accum_Red_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Accum_Red_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Accum_Red_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Accum_Green_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Accum_Green_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Accum_Green_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Accum_Green_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Accum_Blue_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Accum_Blue_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Accum_Blue_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Accum_Blue_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Accum_Alpha_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Accum_Alpha_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Accum_Alpha_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Accum_Alpha_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_ಆಳ_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_ಆಳ_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_ಆಳ_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_ಆಳ_ಬಿಟ್ಟುಗಳು);
        }
        ಆದರೆ (pfd.c_Stencil_ಬಿಟ್ಟುಗಳು < ಗುರಿ->c_Stencil_ಬಿಟ್ಟುಗಳು) {
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dist += (pfd.c_Stencil_ಬಿಟ್ಟುಗಳು - ಗುರಿ->c_Stencil_ಬಿಟ್ಟುಗಳು);
        }

        ಆದರೆ (dist < ಉತ್ತಮ_dist) {
            ಉತ್ತಮ = ಸೂಚ್ಯಂಕ;
            ಉತ್ತಮ_dist = dist;
        }
    }

    ಹಿಂತಿರುಗಿ ಉತ್ತಮ;
}

ಸ್ಥಿರ bool HasExtension(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extension, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extensions)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಆರಂಭ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ಆದರೆ (where || *extension == '\0') {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!extensions) {
        ಹಿಂತಿರುಗಿ false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    ಆರಂಭ = extensions;

    ಗಾಗಿ (;;) {
        where = SDL_strstr(ಆರಂಭ, extension);
        ಆದರೆ (!where) {
            ನಿಲ್ಲಿಸು;
        }

        terminator = where + SDL_strlen(extension);
        ಆದರೆ (where == ಆರಂಭ || *(where - 1) == ' ') {
            ಆದರೆ (*terminator == ' ' || *terminator == '\0') {
                ಹಿಂತಿರುಗಿ true;
            }
        }

        ಆರಂಭ = terminator;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ;
    }

    hwnd =
        Create_ಕಿಟಕಿ(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ಖಾಲಿ, ಖಾಲಿ, SDL_Instance, ಖಾಲಿ);
    ಆದರೆ (!hwnd) {
        ಹಿಂತಿರುಗಿ;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_ಸಿದ್ಧತೆ_Pixel_Format(_this, &pfd);

    ಗಣ_Pixel_Format(hdc, ಆರಿಸು_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_ದತ್ತಾಂಶ->wglCreateContext(hdc);
    ಆದರೆ (!hglrc) {
        ಹಿಂತಿರುಗಿ;
    }
    _this->gl_ದತ್ತಾಂಶ->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(WINAPI *)(HDC))
        _this->gl_ದತ್ತಾಂಶ->wgl_Get_Proc_ವಿಳಾಸ("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    ಆದರೆ (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } ಇಲ್ಲದಿದ್ದರೆ {
        extensions = ಖಾಲಿ;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_pixel_format = false;
    ಆದರೆ (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_ದತ್ತಾಂಶ->wgl_ಆರಿಸು_Pixel_Format_ARB =
            (BOOL (WINAPI *)(HDC, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *, ಸ್ಥಿರಾಂಕ FLOAT *, UINT, ಪೂರ್ಣಾಂಕ *, UINT *))
            WIN_GL_Get_Proc_ವಿಳಾಸ(_this, "wglChoosePixelFormatARB");
        _this->gl_ದತ್ತಾಂಶ->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, UINT, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *))
            WIN_GL_Get_Proc_ವಿಳಾಸ(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        ಆದರೆ ((_this->gl_ದತ್ತಾಂಶ->wgl_ಆರಿಸು_Pixel_Format_ARB != ಖಾಲಿ) &&
            (_this->gl_ದತ್ತಾಂಶ->wglGetPixelFormatAttribivARB != ಖಾಲಿ)) {
            _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_ದತ್ತಾಂಶ->HAS_WGL_EXT_ಅದಲುಬದಲು_control_tear = false;
    ಆದರೆ (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->wgl_ಅದಲುಬದಲು_Interval_EXT =
            (BOOL (WINAPI *)(ಪೂರ್ಣಾಂಕ))
            WIN_GL_Get_Proc_ವಿಳಾಸ(_this, "wglSwapIntervalEXT");
        _this->gl_ದತ್ತಾಂಶ->wgl_Get_ಅದಲುಬದಲು_Interval_EXT =
            (ಪೂರ್ಣಾಂಕ (WINAPI *)(ಶೂನ್ಯ))
            WIN_GL_Get_Proc_ವಿಳಾಸ(_this, "wglGetSwapIntervalEXT");
        ಆದರೆ (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_ದತ್ತಾಂಶ->HAS_WGL_EXT_ಅದಲುಬದಲು_control_tear = true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        _this->gl_ದತ್ತಾಂಶ->wgl_ಅದಲುಬದಲು_Interval_EXT = ಖಾಲಿ;
        _this->gl_ದತ್ತಾಂಶ->wgl_Get_ಅದಲುಬದಲು_Interval_EXT = ಖಾಲಿ;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_ದತ್ತಾಂಶ->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.major,
            &_this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.minor);
    }

    // Check for WGL_ARB_context_flush_control
    ಆದರೆ (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    ಆದರೆ (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    ಆದರೆ (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    ಆದರೆ (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_framebuffer_sRGB = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_ದತ್ತಾಂಶ->wglMakeCurrent(hdc, ಖಾಲಿ);
    _this->gl_ದತ್ತಾಂಶ->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    Destroy_ಕಿಟಕಿ(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ WIN_GL_ಆರಿಸು_Pixel_Format_ARB(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *iAttribs, ದಶಮಾಂಶ *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    ಪೂರ್ಣಾಂಕ pixel_format = 0;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ matching;

    hwnd =
        Create_ಕಿಟಕಿ(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ಖಾಲಿ, ಖಾಲಿ, SDL_Instance, ಖಾಲಿ);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_ಸಿದ್ಧತೆ_Pixel_Format(_this, &pfd);

    ಗಣ_Pixel_Format(hdc, ಆರಿಸು_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_ದತ್ತಾಂಶ->wglCreateContext(hdc);
    ಆದರೆ (hglrc) {
        _this->gl_ದತ್ತಾಂಶ->wglMakeCurrent(hdc, hglrc);

        ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_pixel_format) {
            _this->gl_ದತ್ತಾಂಶ->wgl_ಆರಿಸು_Pixel_Format_ARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            ಪೂರ್ಣಾಂಕ srgb = 0;
            ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_framebuffer_sRGB) {
                ಪೂರ್ಣಾಂಕ qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_ದತ್ತಾಂಶ->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_ದತ್ತಾಂಶ->wglMakeCurrent(hdc, ಖಾಲಿ);
        _this->gl_ದತ್ತಾಂಶ->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    Destroy_ಕಿಟಕಿ(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    ಹಿಂತಿರುಗಿ pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
ಸ್ಥಿರ bool WIN_GL_ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ಆಂತರಿಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    HDC hdc = ಕಿಟಕಿ->ಆಂತರಿಕ->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    ಪೂರ್ಣಾಂಕ pixel_format = 0;
    ಪೂರ್ಣಾಂಕ iAttribs[64];
    ಪೂರ್ಣಾಂಕ *iAttr;
    ಪೂರ್ಣಾಂಕ *iAccelAttr;
    ದಶಮಾಂಶ fAttribs[1] = { 0 };

    WIN_GL_ಸಿದ್ಧತೆ_Pixel_Format(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_ಗಮ್ಯ_ಕಿಟಕಿ_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_ಬಿಟ್ಟುಗಳು_ARB;
    *iAttr++ = _this->gl_config.red_ಗಾತ್ರ;
    *iAttr++ = WGL_GREEN_ಬಿಟ್ಟುಗಳು_ARB;
    *iAttr++ = _this->gl_config.green_ಗಾತ್ರ;
    *iAttr++ = WGL_BLUE_ಬಿಟ್ಟುಗಳು_ARB;
    *iAttr++ = _this->gl_config.blue_ಗಾತ್ರ;

    ಆದರೆ (_this->gl_config.alpha_ಗಾತ್ರ) {
        *iAttr++ = WGL_ALPHA_ಬಿಟ್ಟುಗಳು_ARB;
        *iAttr++ = _this->gl_config.alpha_ಗಾತ್ರ;
    }

    *iAttr++ = WGL_DOUBLE_ಬಫರ್_ARB;
    *iAttr++ = _this->gl_config.double_ಬಫರ್;

    *iAttr++ = WGL_ಆಳ_ಬಿಟ್ಟುಗಳು_ARB;
    *iAttr++ = _this->gl_config.ಆಳ_ಗಾತ್ರ;

    ಆದರೆ (_this->gl_config.stencil_ಗಾತ್ರ) {
        *iAttr++ = WGL_STENCIL_ಬಿಟ್ಟುಗಳು_ARB;
        *iAttr++ = _this->gl_config.stencil_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_red_ಗಾತ್ರ) {
        *iAttr++ = WGL_ACCUM_RED_ಬಿಟ್ಟುಗಳು_ARB;
        *iAttr++ = _this->gl_config.accum_red_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_green_ಗಾತ್ರ) {
        *iAttr++ = WGL_ACCUM_GREEN_ಬಿಟ್ಟುಗಳು_ARB;
        *iAttr++ = _this->gl_config.accum_green_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_blue_ಗಾತ್ರ) {
        *iAttr++ = WGL_ACCUM_BLUE_ಬಿಟ್ಟುಗಳು_ARB;
        *iAttr++ = _this->gl_config.accum_blue_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.accum_alpha_ಗಾತ್ರ) {
        *iAttr++ = WGL_ACCUM_ALPHA_ಬಿಟ್ಟುಗಳು_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    ಆದರೆ (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    ಆದರೆ (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_framebuffer_sRGB) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ಆದರೆ (srgbhint && *srgbhint) {
            ಆದರೆ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ಇಲ್ಲದಿದ್ದರೆ {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    ಆದರೆ (_this->gl_config.accelerated) {
        *iAttr++ = WGL_ತುಂಬಿದ_ACCELERATION_ARB;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_ಆರಿಸು_Pixel_Format_ARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    ಆದರೆ ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_ಆರಿಸು_Pixel_Format_ARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_ತುಂಬಿದ_ACCELERATION_ARB; // if we try again.
    }
    ಆದರೆ (!pixel_format) {
        pixel_format = WIN_GL_ಆರಿಸು_Pixel_Format(_this, hdc, &pfd);
    }
    ಆದರೆ (!pixel_format) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No matching GL pixel format available");
    }
    ಆದರೆ (!ಗಣ_Pixel_Format(hdc, pixel_format, &pfd)) {
        ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetPixelFormat()");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_GL_ಸಿದ್ಧತೆ_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // The current context is lost in here; save it and reset it.
    SDL_ಕಿಟಕಿ *current_win = SDL_GL_Get_Current_ಕಿಟಕಿ();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = WIN_GL_ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ಆಂತರಿಕ(_this, ಕಿಟಕಿ);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_ದತ್ತಾಂಶ != ಖಾಲಿ);
    SDL_assert(_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    ಹಿಂತಿರುಗಿ !_this->gl_ದತ್ತಾಂಶ->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_ಆವೃತ್ತಿ > _this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.major ||
           (_this->gl_config.major_ಆವೃತ್ತಿ == _this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.major && _this->gl_config.minor_ಆವೃತ್ತಿ > _this->gl_ದತ್ತಾಂಶ->es_profile_max_supported_ಆವೃತ್ತಿ.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    HDC hdc = ಕಿಟಕಿ->ಆಂತರಿಕ->hdc;
    HGLRC context, share_context;

    ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        ಆದರೆ (!WIN_GL_ತುಂಬು_Library_EGLFallback(_this, ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ಹಿಂತಿರುಗಿ WIN_GLES_CreateContext(_this, ಕಿಟಕಿ);
#ಇಲ್ಲದಿದ್ದರೆ
        SDL_ಗಣ_Error("SDL not configured with EGL support");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಆದರೆ (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } ಇಲ್ಲದಿದ್ದರೆ {
        share_context = 0;
    }

    ಆದರೆ (_this->gl_config.major_ಆವೃತ್ತಿ < 3 &&
        _this->gl_config.profile_ಮುಖವಾಡ == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_ದತ್ತಾಂಶ->wglCreateContext(hdc);
        ಆದರೆ (share_context != 0) {
            _this->gl_ದತ್ತಾಂಶ->wglShareLists(share_context, context);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC ತಾತ್ಕಾಲಿಕ_context = _this->gl_ದತ್ತಾಂಶ->wglCreateContext(hdc);
        ಆದರೆ (!ತಾತ್ಕಾಲಿಕ_context) {
            SDL_ಗಣ_Error("Could not create GL context");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // Make the context current
        ಆದರೆ (!WIN_GL_MakeCurrent(_this, ಕಿಟಕಿ, (SDL_GLContext)ತಾತ್ಕಾಲಿಕ_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)ತಾತ್ಕಾಲಿಕ_context);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_ದತ್ತಾಂಶ->wgl_Get_Proc_ವಿಳಾಸ("wglCreateContextAttribsARB");
        ಆದರೆ (!wglCreateContextAttribsARB) {
            SDL_ಗಣ_Error("GL 3.x is not supported");
            context = ತಾತ್ಕಾಲಿಕ_context;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಪೂರ್ಣಾಂಕ attribs[15]; // max 14 attributes plus terminator
            ಪೂರ್ಣಾಂಕ iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_ಆವೃತ್ತಿ_ARB;
            attribs[iattr++] = _this->gl_config.major_ಆವೃತ್ತಿ;
            attribs[iattr++] = WGL_CONTEXT_MINOR_ಆವೃತ್ತಿ_ARB;
            attribs[iattr++] = _this->gl_config.minor_ಆವೃತ್ತಿ;

            // SDL profile bits match WGL profile bits
            ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_ಮುಖವಾಡ_ARB;
                attribs[iattr++] = _this->gl_config.profile_ಮುಖವಾಡ;
            }

            // SDL flags match WGL flags
            ಆದರೆ (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            ಆದರೆ ((_this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ಆದರೆ ((_this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ಆದರೆ ((_this->gl_ದತ್ತಾಂಶ->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_ದತ್ತಾಂಶ->wglDeleteContext(ತಾತ್ಕಾಲಿಕ_context);
        }
    }

    ಆದರೆ (!context) {
        WIN_ಗಣ_Error("Could not create GL context");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!WIN_GL_MakeCurrent(_this, ಕಿಟಕಿ, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    _this->gl_config.HAS_GL_ARB_color_ಬಫರ್_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    ಹಿಂತಿರುಗಿ (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    HDC hdc;

    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(ಕಿಟಕಿ || (ಕಿಟಕಿ == ಖಾಲಿ && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಕಿಟಕಿ = SDL_GL_Get_Current_ಕಿಟಕಿ();
        ಆದರೆ (!ಕಿಟಕಿ) {
            SDL_assert(SDL_GL_GetCurrentContext() == ಖಾಲಿ);
            ಹಿಂತಿರುಗಿ true; // already done.
        }
    }

    hdc = ಕಿಟಕಿ->ಆಂತರಿಕ->hdc;
    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ->wglMakeCurrent(hdc, (HGLRC)context)) {
        ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("wglMakeCurrent()");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    ಆದರೆ ((interval < 0) && (!_this->gl_ದತ್ತಾಂಶ->HAS_WGL_EXT_ಅದಲುಬದಲು_control_tear)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Negative swap interval unsupported in this GL");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->wgl_ಅದಲುಬದಲು_Interval_EXT) {
        ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ->wgl_ಅದಲುಬದಲು_Interval_EXT(interval)) {
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("wglSwapIntervalEXT()");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    ಆದರೆ (_this->gl_ದತ್ತಾಂಶ->wgl_Get_ಅದಲುಬದಲು_Interval_EXT) {
        *interval = _this->gl_ದತ್ತಾಂಶ->wgl_Get_ಅದಲುಬದಲು_Interval_EXT();
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }
}

bool WIN_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    HDC hdc = ಕಿಟಕಿ->ಆಂತರಿಕ->hdc;

    ಆದರೆ (!ಅದಲುಬದಲು_Buffers(hdc)) {
        ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SwapBuffers()");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ true;
    }
    _this->gl_ದತ್ತಾಂಶ->wglDeleteContext((HGLRC)context);
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_WGL

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS
