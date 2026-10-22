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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "SDL_windowsopengles.h"
#అన్తర్భావ "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
#అన్తర్భావ <SDL3/SDL_opengl.h>

#నిర్వచించు DEFAULT_OPENGL "OPENGL32.DLL"

#నిర్వచితం_కాకపోతే WGL_ARB_create_context
#నిర్వచించు WGL_ARB_create_context
#నిర్వచించు WGL_CONTEXT_MAJOR_సంస్కరణ_ARB          0x2091
#నిర్వచించు WGL_CONTEXT_MINOR_సంస్కరణ_ARB          0x2092
#నిర్వచించు WGL_CONTEXT_LAYER_PLANE_ARB            0x2093
#నిర్వచించు WGL_CONTEXT_FLAGS_ARB                  0x2094
#నిర్వచించు WGL_CONTEXT_DEBUG_బిట్టు_ARB              0x0001
#నిర్వచించు WGL_CONTEXT_FORWARD_COMPATIBLE_బిట్టు_ARB 0x0002

#నిర్వచితం_కాకపోతే WGL_ARB_create_context_profile
#నిర్వచించు WGL_ARB_create_context_profile
#నిర్వచించు WGL_CONTEXT_PROFILE_ముసుగు_ARB              0x9126
#నిర్వచించు WGL_CONTEXT_CORE_PROFILE_బిట్టు_ARB          0x00000001
#నిర్వచించు WGL_CONTEXT_COMPATIBILITY_PROFILE_బిట్టు_ARB 0x00000002
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_ARB_create_context_robustness
#నిర్వచించు WGL_ARB_create_context_robustness
#నిర్వచించు WGL_CONTEXT_ROBUST_ACCESS_బిట్టు_ARB           0x00000004
#నిర్వచించు WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#నిర్వచించు WGL_NO_RESET_NOTIFICATION_ARB               0x8261
#నిర్వచించు WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8252
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_EXT_create_context_es2_profile
#నిర్వచించు WGL_EXT_create_context_es2_profile
#నిర్వచించు WGL_CONTEXT_ES2_PROFILE_బిట్టు_EXT 0x00000004
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_EXT_create_context_es_profile
#నిర్వచించు WGL_EXT_create_context_es_profile
#నిర్వచించు WGL_CONTEXT_ES_PROFILE_బిట్టు_EXT 0x00000004
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_ARB_framebuffer_sRGB
#నిర్వచించు WGL_ARB_framebuffer_sRGB
#నిర్వచించు WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20A9
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_ARB_pixel_format_float
#నిర్వచించు WGL_ARB_pixel_format_float
#నిర్వచించు WGL_TYPE_RGBA_FLOAT_ARB 0x21A0
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_ARB_context_flush_control
#నిర్వచించు WGL_ARB_context_flush_control
#నిర్వచించు WGL_CONTEXT_RELEASE_BEHAVIOR_ARB       0x2097
#నిర్వచించు WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB  0x0000
#నిర్వచించు WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_ARB_create_context_no_error
#నిర్వచించు WGL_ARB_create_context_no_error
#నిర్వచించు WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3
#అయితే_ముగింపు

రకనిర్వచనం HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           స్థిరరాశి పూర్ణాంకం
                                                               *attribList);

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#నిర్వచించు GetDC(hwnd)          (HDC) hwnd
#నిర్వచించు ReleaseDC(hwnd, hdc) 1
#నిర్వచించు మార్పిడి_Buffers          _this->gl_దత్తాంశం->wgl_మార్పిడి_Buffers
#నిర్వచించు DescribePixelFormat  _this->gl_దత్తాంశం->wglDescribePixelFormat
#నిర్వచించు ఎంచుకో_Pixel_Format    _this->gl_దత్తాంశం->wgl_ఎంచుకో_Pixel_Format
#నిర్వచించు GetPixelFormat       _this->gl_దత్తాంశం->wglGetPixelFormat
#నిర్వచించు సమితి_Pixel_Format       _this->gl_దత్తాంశం->wgl_సమితి_Pixel_Format
#అయితే_ముగింపు

స్థిర bool WIN_GL_ఎక్కించు_Library_EGLFallback(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    WIN_GL_UnloadLibrary(_this);
    _this->GL_ఎక్కించు_Library = WIN_GLES_ఎక్కించు_Library;
    _this->GL_Get_Proc_చిరునామా = WIN_GLES_Get_Proc_చిరునామా;
    _this->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
    _this->GL_CreateContext = WIN_GLES_CreateContext;
    _this->GL_MakeCurrent = WIN_GLES_MakeCurrent;
    _this->GL_సమితి_మార్పిడి_Interval = WIN_GLES_సమితి_మార్పిడి_Interval;
    _this->GL_Get_మార్పిడి_Interval = WIN_GLES_Get_మార్పిడి_Interval;
    _this->GL_మార్పిడి_కిటికీ = WIN_GLES_మార్పిడి_కిటికీ;
    _this->GL_DestroyContext = WIN_GLES_DestroyContext;
    _this->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
    తిరిగి WIN_GLES_ఎక్కించు_Library(_this, మార్గం);
#లేకపోతే
    తిరిగి SDL_సమితి_Error("SDL not configured with EGL support");
#అయితే_ముగింపు
}

bool WIN_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    శూన్య *handle;

    ఒకవేళ ((_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        తిరిగి WIN_GL_ఎక్కించు_Library_EGLFallback(_this, మార్గం);
    }

    ఒకవేళ (మార్గం == ఖాళీ) {
        మార్గం = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    ఒకవేళ (మార్గం == ఖాళీ) {
        మార్గం = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ఎక్కించు_Object(మార్గం);
    ఒకవేళ (!_this->gl_config.dll_handle) {
        తిరిగి false;
    }
    SDL_strlcpy(_this->gl_config.driver_మార్గం, మార్గం,
                SDL_arraysize(_this->gl_config.driver_మార్గం));

    // Allocate OpenGL memory
    _this->gl_దత్తాంశం = (నిర్మాణం SDL_GLDriver_దత్తాంశం *)SDL_calloc(1, పరిమాణం(నిర్మాణం SDL_GLDriver_దత్తాంశం));
    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_దత్తాంశం->wgl_Get_Proc_చిరునామా = (PROC (WINAPI *)(స్థిరరాశి అక్షరం *))
        SDL_ఎక్కించు_Function(handle, "wglGetProcAddress");
    _this->gl_దత్తాంశం->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_ఎక్కించు_Function(handle, "wglCreateContext");
    _this->gl_దత్తాంశం->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_ఎక్కించు_Function(handle, "wglDeleteContext");
    _this->gl_దత్తాంశం->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_ఎక్కించు_Function(handle, "wglMakeCurrent");
    _this->gl_దత్తాంశం->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_ఎక్కించు_Function(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_దత్తాంశం->wgl_మార్పిడి_Buffers = (BOOL(WINAPI *)(HDC))
        SDL_ఎక్కించు_Function(handle, "wglSwapBuffers");
    _this->gl_దత్తాంశం->wglDescribePixelFormat = (పూర్ణాంకం(WINAPI *)(HDC, పూర్ణాంకం, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_ఎక్కించు_Function(handle, "wglDescribePixelFormat");
    _this->gl_దత్తాంశం->wgl_ఎంచుకో_Pixel_Format = (పూర్ణాంకం(WINAPI *)(HDC, స్థిరరాశి PIXELFORMATDESCRIPTOR *))
        SDL_ఎక్కించు_Function(handle, "wglChoosePixelFormat");
    _this->gl_దత్తాంశం->wgl_సమితి_Pixel_Format = (BOOL(WINAPI *)(HDC, పూర్ణాంకం, స్థిరరాశి PIXELFORMATDESCRIPTOR *))
        SDL_ఎక్కించు_Function(handle, "wglSetPixelFormat");
    _this->gl_దత్తాంశం->wglGetPixelFormat = (పూర్ణాంకం(WINAPI *)(HDC hdc))
        SDL_ఎక్కించు_Function(handle, "wglGetPixelFormat");
#అయితే_ముగింపు

    ఒకవేళ (!_this->gl_దత్తాంశం->wgl_Get_Proc_చిరునామా ||
        !_this->gl_దత్తాంశం->wglCreateContext ||
        !_this->gl_దత్తాంశం->wglDeleteContext ||
        !_this->gl_దత్తాంశం->wglMakeCurrent
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_దత్తాంశం->wgl_మార్పిడి_Buffers ||
        !_this->gl_దత్తాంశం->wglDescribePixelFormat ||
        !_this->gl_దత్తాంశం->wgl_ఎంచుకో_Pixel_Format ||
        !_this->gl_దత్తాంశం->wglGetPixelFormat ||
        !_this->gl_దత్తాంశం->wgl_సమితి_Pixel_Format
#అయితే_ముగింపు
    ) {
        తిరిగి SDL_సమితి_Error("Could not retrieve OpenGL functions");
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

    తిరిగి true;
}

SDL_Function_సూచిక WIN_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    SDL_Function_సూచిక func;

    // This is to pick up extensions
    func = (SDL_Function_సూచిక)_this->gl_దత్తాంశం->wgl_Get_Proc_చిరునామా(proc);
    ఒకవేళ (!func) {
        // This is probably a normal GL function
        func = (SDL_Function_సూచిక)Get_Proc_చిరునామా((HMODULE)_this->gl_config.dll_handle, proc);
    }
    తిరిగి func;
}

శూన్య WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = ఖాళీ;

    // Free OpenGL memory
    SDL_free(_this->gl_దత్తాంశం);
    _this->gl_దత్తాంశం = ఖాళీ;
}

స్థిర శూన్య WIN_GL_అమరిక_Pixel_Format(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->n_కొలత = పరిమాణం(*pfd);
    pfd->n_సంస్కరణ = 1;
    pfd->dwFlags = (PFD_DRAW_గమ్యం_కిటికీ | PFD_SUPPORT_OPENGL);
    ఒకవేళ (_this->gl_config.double_బఫరు) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    ఒకవేళ (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->c_Red_బిట్లు = (BYTE)_this->gl_config.red_కొలత;
    pfd->c_Green_బిట్లు = (BYTE)_this->gl_config.green_కొలత;
    pfd->c_Blue_బిట్లు = (BYTE)_this->gl_config.blue_కొలత;
    pfd->c_Alpha_బిట్లు = (BYTE)_this->gl_config.alpha_కొలత;
    ఒకవేళ (_this->gl_config.బఫరు_కొలత) {
        pfd->c_Color_బిట్లు = (BYTE)(_this->gl_config.బఫరు_కొలత - _this->gl_config.alpha_కొలత);
    } లేకపోతే {
        pfd->c_Color_బిట్లు = (pfd->c_Red_బిట్లు + pfd->c_Green_బిట్లు + pfd->c_Blue_బిట్లు);
    }
    pfd->c_Accum_Red_బిట్లు = (BYTE)_this->gl_config.accum_red_కొలత;
    pfd->c_Accum_Green_బిట్లు = (BYTE)_this->gl_config.accum_green_కొలత;
    pfd->c_Accum_Blue_బిట్లు = (BYTE)_this->gl_config.accum_blue_కొలత;
    pfd->c_Accum_Alpha_బిట్లు = (BYTE)_this->gl_config.accum_alpha_కొలత;
    pfd->c_Accum_బిట్లు =
        (pfd->c_Accum_Red_బిట్లు + pfd->c_Accum_Green_బిట్లు + pfd->c_Accum_Blue_బిట్లు +
         pfd->c_Accum_Alpha_బిట్లు);
    pfd->c_లోతు_బిట్లు = (BYTE)_this->gl_config.లోతు_కొలత;
    pfd->c_Stencil_బిట్లు = (BYTE)_this->gl_config.stencil_కొలత;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
స్థిర bool WIN_GL_ఎంచుకో_Pixel_Format(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *లక్ష్యం)
{
    PIXELFORMATDESCRIPTOR pfd;
    పూర్ణాంకం లెక్క, సూచీ, ఉత్తమ = 0;
    గుర్తులేని పూర్ణాంకం dist, ఉత్తమ_dist = ~0U;

    లెక్క = DescribePixelFormat(hdc, 1, పరిమాణం(pfd), ఖాళీ);

    కొరకు (సూచీ = 1; సూచీ <= లెక్క; సూచీ++) {

        ఒకవేళ (!DescribePixelFormat(hdc, సూచీ, పరిమాణం(pfd), &pfd)) {
            కొనసాగు;
        }

        ఒకవేళ ((pfd.dwFlags & లక్ష్యం->dwFlags) != లక్ష్యం->dwFlags) {
            కొనసాగు;
        }

        ఒకవేళ (pfd.iLayerType != లక్ష్యం->iLayerType) {
            కొనసాగు;
        }
        ఒకవేళ (pfd.iPixelType != లక్ష్యం->iPixelType) {
            కొనసాగు;
        }

        dist = 0;

        ఒకవేళ (pfd.c_Color_బిట్లు < లక్ష్యం->c_Color_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Color_బిట్లు - లక్ష్యం->c_Color_బిట్లు);
        }
        ఒకవేళ (pfd.c_Red_బిట్లు < లక్ష్యం->c_Red_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Red_బిట్లు - లక్ష్యం->c_Red_బిట్లు);
        }
        ఒకవేళ (pfd.c_Green_బిట్లు < లక్ష్యం->c_Green_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Green_బిట్లు - లక్ష్యం->c_Green_బిట్లు);
        }
        ఒకవేళ (pfd.c_Blue_బిట్లు < లక్ష్యం->c_Blue_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Blue_బిట్లు - లక్ష్యం->c_Blue_బిట్లు);
        }
        ఒకవేళ (pfd.c_Alpha_బిట్లు < లక్ష్యం->c_Alpha_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Alpha_బిట్లు - లక్ష్యం->c_Alpha_బిట్లు);
        }
        ఒకవేళ (pfd.c_Accum_బిట్లు < లక్ష్యం->c_Accum_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Accum_బిట్లు - లక్ష్యం->c_Accum_బిట్లు);
        }
        ఒకవేళ (pfd.c_Accum_Red_బిట్లు < లక్ష్యం->c_Accum_Red_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Accum_Red_బిట్లు - లక్ష్యం->c_Accum_Red_బిట్లు);
        }
        ఒకవేళ (pfd.c_Accum_Green_బిట్లు < లక్ష్యం->c_Accum_Green_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Accum_Green_బిట్లు - లక్ష్యం->c_Accum_Green_బిట్లు);
        }
        ఒకవేళ (pfd.c_Accum_Blue_బిట్లు < లక్ష్యం->c_Accum_Blue_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Accum_Blue_బిట్లు - లక్ష్యం->c_Accum_Blue_బిట్లు);
        }
        ఒకవేళ (pfd.c_Accum_Alpha_బిట్లు < లక్ష్యం->c_Accum_Alpha_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Accum_Alpha_బిట్లు - లక్ష్యం->c_Accum_Alpha_బిట్లు);
        }
        ఒకవేళ (pfd.c_లోతు_బిట్లు < లక్ష్యం->c_లోతు_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_లోతు_బిట్లు - లక్ష్యం->c_లోతు_బిట్లు);
        }
        ఒకవేళ (pfd.c_Stencil_బిట్లు < లక్ష్యం->c_Stencil_బిట్లు) {
            కొనసాగు;
        } లేకపోతే {
            dist += (pfd.c_Stencil_బిట్లు - లక్ష్యం->c_Stencil_బిట్లు);
        }

        ఒకవేళ (dist < ఉత్తమ_dist) {
            ఉత్తమ = సూచీ;
            ఉత్తమ_dist = dist;
        }
    }

    తిరిగి ఉత్తమ;
}

స్థిర bool HasExtension(స్థిరరాశి అక్షరం *extension, స్థిరరాశి అక్షరం *extensions)
{
    స్థిరరాశి అక్షరం *ప్రారంభం;
    స్థిరరాశి అక్షరం *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ఒకవేళ (where || *extension == '\0') {
        తిరిగి false;
    }

    ఒకవేళ (!extensions) {
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

శూన్య WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    స్థిరరాశి అక్షరం *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    స్థిరరాశి అక్షరం *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి;
    }

    hwnd =
        Create_కిటికీ(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ఖాళీ, ఖాళీ, SDL_Instance, ఖాళీ);
    ఒకవేళ (!hwnd) {
        తిరిగి;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_అమరిక_Pixel_Format(_this, &pfd);

    సమితి_Pixel_Format(hdc, ఎంచుకో_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_దత్తాంశం->wglCreateContext(hdc);
    ఒకవేళ (!hglrc) {
        తిరిగి;
    }
    _this->gl_దత్తాంశం->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (స్థిరరాశి అక్షరం *(WINAPI *)(HDC))
        _this->gl_దత్తాంశం->wgl_Get_Proc_చిరునామా("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    ఒకవేళ (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } లేకపోతే {
        extensions = ఖాళీ;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_దత్తాంశం->HAS_WGL_ARB_pixel_format = false;
    ఒకవేళ (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_దత్తాంశం->wgl_ఎంచుకో_Pixel_Format_ARB =
            (BOOL (WINAPI *)(HDC, స్థిరరాశి పూర్ణాంకం *, స్థిరరాశి FLOAT *, UINT, పూర్ణాంకం *, UINT *))
            WIN_GL_Get_Proc_చిరునామా(_this, "wglChoosePixelFormatARB");
        _this->gl_దత్తాంశం->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, పూర్ణాంకం, పూర్ణాంకం, UINT, స్థిరరాశి పూర్ణాంకం *, పూర్ణాంకం *))
            WIN_GL_Get_Proc_చిరునామా(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        ఒకవేళ ((_this->gl_దత్తాంశం->wgl_ఎంచుకో_Pixel_Format_ARB != ఖాళీ) &&
            (_this->gl_దత్తాంశం->wglGetPixelFormatAttribivARB != ఖాళీ)) {
            _this->gl_దత్తాంశం->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_దత్తాంశం->HAS_WGL_EXT_మార్పిడి_control_tear = false;
    ఒకవేళ (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_దత్తాంశం->wgl_మార్పిడి_Interval_EXT =
            (BOOL (WINAPI *)(పూర్ణాంకం))
            WIN_GL_Get_Proc_చిరునామా(_this, "wglSwapIntervalEXT");
        _this->gl_దత్తాంశం->wgl_Get_మార్పిడి_Interval_EXT =
            (పూర్ణాంకం (WINAPI *)(శూన్య))
            WIN_GL_Get_Proc_చిరునామా(_this, "wglGetSwapIntervalEXT");
        ఒకవేళ (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_దత్తాంశం->HAS_WGL_EXT_మార్పిడి_control_tear = true;
        }
    } లేకపోతే {
        _this->gl_దత్తాంశం->wgl_మార్పిడి_Interval_EXT = ఖాళీ;
        _this->gl_దత్తాంశం->wgl_Get_మార్పిడి_Interval_EXT = ఖాళీ;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_దత్తాంశం->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    ఒకవేళ (_this->gl_దత్తాంశం->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.major,
            &_this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.minor);
    }

    // Check for WGL_ARB_context_flush_control
    ఒకవేళ (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_దత్తాంశం->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    ఒకవేళ (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_దత్తాంశం->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    ఒకవేళ (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_దత్తాంశం->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    ఒకవేళ (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_దత్తాంశం->HAS_WGL_ARB_framebuffer_sRGB = true;
    } లేకపోతే ఒకవేళ (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_దత్తాంశం->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_దత్తాంశం->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_దత్తాంశం->wglMakeCurrent(hdc, ఖాళీ);
    _this->gl_దత్తాంశం->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    Destroy_కిటికీ(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

స్థిర పూర్ణాంకం WIN_GL_ఎంచుకో_Pixel_Format_ARB(SDL_VideoDevice *_this, పూర్ణాంకం *iAttribs, దశాంశం *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    పూర్ణాంకం pixel_format = 0;
    గుర్తులేని పూర్ణాంకం matching;

    hwnd =
        Create_కిటికీ(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, ఖాళీ, ఖాళీ, SDL_Instance, ఖాళీ);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_అమరిక_Pixel_Format(_this, &pfd);

    సమితి_Pixel_Format(hdc, ఎంచుకో_Pixel_Format(hdc, &pfd), &pfd);

    hglrc = _this->gl_దత్తాంశం->wglCreateContext(hdc);
    ఒకవేళ (hglrc) {
        _this->gl_దత్తాంశం->wglMakeCurrent(hdc, hglrc);

        ఒకవేళ (_this->gl_దత్తాంశం->HAS_WGL_ARB_pixel_format) {
            _this->gl_దత్తాంశం->wgl_ఎంచుకో_Pixel_Format_ARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            పూర్ణాంకం srgb = 0;
            ఒకవేళ (_this->gl_దత్తాంశం->HAS_WGL_ARB_framebuffer_sRGB) {
                పూర్ణాంకం qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_దత్తాంశం->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_దత్తాంశం->wglMakeCurrent(hdc, ఖాళీ);
        _this->gl_దత్తాంశం->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    Destroy_కిటికీ(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    తిరిగి pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
స్థిర bool WIN_GL_అమరిక_కిటికీ_అంతర్గత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    HDC hdc = కిటికీ->అంతర్గత->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    పూర్ణాంకం pixel_format = 0;
    పూర్ణాంకం iAttribs[64];
    పూర్ణాంకం *iAttr;
    పూర్ణాంకం *iAccelAttr;
    దశాంశం fAttribs[1] = { 0 };

    WIN_GL_అమరిక_Pixel_Format(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_గమ్యం_కిటికీ_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_బిట్లు_ARB;
    *iAttr++ = _this->gl_config.red_కొలత;
    *iAttr++ = WGL_GREEN_బిట్లు_ARB;
    *iAttr++ = _this->gl_config.green_కొలత;
    *iAttr++ = WGL_BLUE_బిట్లు_ARB;
    *iAttr++ = _this->gl_config.blue_కొలత;

    ఒకవేళ (_this->gl_config.alpha_కొలత) {
        *iAttr++ = WGL_ALPHA_బిట్లు_ARB;
        *iAttr++ = _this->gl_config.alpha_కొలత;
    }

    *iAttr++ = WGL_DOUBLE_బఫరు_ARB;
    *iAttr++ = _this->gl_config.double_బఫరు;

    *iAttr++ = WGL_లోతు_బిట్లు_ARB;
    *iAttr++ = _this->gl_config.లోతు_కొలత;

    ఒకవేళ (_this->gl_config.stencil_కొలత) {
        *iAttr++ = WGL_STENCIL_బిట్లు_ARB;
        *iAttr++ = _this->gl_config.stencil_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_red_కొలత) {
        *iAttr++ = WGL_ACCUM_RED_బిట్లు_ARB;
        *iAttr++ = _this->gl_config.accum_red_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_green_కొలత) {
        *iAttr++ = WGL_ACCUM_GREEN_బిట్లు_ARB;
        *iAttr++ = _this->gl_config.accum_green_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_blue_కొలత) {
        *iAttr++ = WGL_ACCUM_BLUE_బిట్లు_ARB;
        *iAttr++ = _this->gl_config.accum_blue_కొలత;
    }

    ఒకవేళ (_this->gl_config.accum_alpha_కొలత) {
        *iAttr++ = WGL_ACCUM_ALPHA_బిట్లు_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_కొలత;
    }

    ఒకవేళ (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    ఒకవేళ (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    ఒకవేళ (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    ఒకవేళ (_this->gl_దత్తాంశం->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    ఒకవేళ (_this->gl_దత్తాంశం->HAS_WGL_ARB_framebuffer_sRGB) {
        స్థిరరాశి అక్షరం *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ఒకవేళ (srgbhint && *srgbhint) {
            ఒకవేళ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } లేకపోతే {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } లేకపోతే ఒకవేళ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    ఒకవేళ (_this->gl_config.accelerated) {
        *iAttr++ = WGL_నిండిన_ACCELERATION_ARB;
    } లేకపోతే {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_ఎంచుకో_Pixel_Format_ARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    ఒకవేళ ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_ఎంచుకో_Pixel_Format_ARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_నిండిన_ACCELERATION_ARB; // if we try again.
    }
    ఒకవేళ (!pixel_format) {
        pixel_format = WIN_GL_ఎంచుకో_Pixel_Format(_this, hdc, &pfd);
    }
    ఒకవేళ (!pixel_format) {
        తిరిగి SDL_సమితి_Error("No matching GL pixel format available");
    }
    ఒకవేళ (!సమితి_Pixel_Format(hdc, pixel_format, &pfd)) {
        తిరిగి WIN_సమితి_Error("SetPixelFormat()");
    }
    తిరిగి true;
}

bool WIN_GL_అమరిక_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // The current context is lost in here; save it and reset it.
    SDL_కిటికీ *current_win = SDL_GL_Get_Current_కిటికీ();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    స్థిరరాశి పూర్ణాంకం ఫలితం = WIN_GL_అమరిక_కిటికీ_అంతర్గత(_this, కిటికీ);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    తిరిగి ఫలితం;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_దత్తాంశం != ఖాళీ);
    SDL_assert(_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    తిరిగి !_this->gl_దత్తాంశం->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_సంస్కరణ > _this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.major ||
           (_this->gl_config.major_సంస్కరణ == _this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.major && _this->gl_config.minor_సంస్కరణ > _this->gl_దత్తాంశం->es_profile_max_supported_సంస్కరణ.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    HDC hdc = కిటికీ->అంతర్గత->hdc;
    HGLRC context, share_context;

    ఒకవేళ (_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        ఒకవేళ (!WIN_GL_ఎక్కించు_Library_EGLFallback(_this, ఖాళీ)) {
            తిరిగి ఖాళీ;
        }

        తిరిగి WIN_GLES_CreateContext(_this, కిటికీ);
#లేకపోతే
        SDL_సమితి_Error("SDL not configured with EGL support");
        తిరిగి ఖాళీ;
#అయితే_ముగింపు
    }

    ఒకవేళ (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } లేకపోతే {
        share_context = 0;
    }

    ఒకవేళ (_this->gl_config.major_సంస్కరణ < 3 &&
        _this->gl_config.profile_ముసుగు == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_దత్తాంశం->wglCreateContext(hdc);
        ఒకవేళ (share_context != 0) {
            _this->gl_దత్తాంశం->wglShareLists(share_context, context);
        }
    } లేకపోతే {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC తాత్కాలిక_context = _this->gl_దత్తాంశం->wglCreateContext(hdc);
        ఒకవేళ (!తాత్కాలిక_context) {
            SDL_సమితి_Error("Could not create GL context");
            తిరిగి ఖాళీ;
        }

        // Make the context current
        ఒకవేళ (!WIN_GL_MakeCurrent(_this, కిటికీ, (SDL_GLContext)తాత్కాలిక_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)తాత్కాలిక_context);
            తిరిగి ఖాళీ;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_దత్తాంశం->wgl_Get_Proc_చిరునామా("wglCreateContextAttribsARB");
        ఒకవేళ (!wglCreateContextAttribsARB) {
            SDL_సమితి_Error("GL 3.x is not supported");
            context = తాత్కాలిక_context;
        } లేకపోతే {
            పూర్ణాంకం attribs[15]; // max 14 attributes plus terminator
            పూర్ణాంకం iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_సంస్కరణ_ARB;
            attribs[iattr++] = _this->gl_config.major_సంస్కరణ;
            attribs[iattr++] = WGL_CONTEXT_MINOR_సంస్కరణ_ARB;
            attribs[iattr++] = _this->gl_config.minor_సంస్కరణ;

            // SDL profile bits match WGL profile bits
            ఒకవేళ (_this->gl_config.profile_ముసుగు != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_ముసుగు_ARB;
                attribs[iattr++] = _this->gl_config.profile_ముసుగు;
            }

            // SDL flags match WGL flags
            ఒకవేళ (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            ఒకవేళ ((_this->gl_దత్తాంశం->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ఒకవేళ ((_this->gl_దత్తాంశం->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ఒకవేళ ((_this->gl_దత్తాంశం->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_దత్తాంశం->wglDeleteContext(తాత్కాలిక_context);
        }
    }

    ఒకవేళ (!context) {
        WIN_సమితి_Error("Could not create GL context");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!WIN_GL_MakeCurrent(_this, కిటికీ, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        తిరిగి ఖాళీ;
    }

    _this->gl_config.HAS_GL_ARB_color_బఫరు_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    తిరిగి (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    HDC hdc;

    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(కిటికీ || (కిటికీ == ఖాళీ && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    ఒకవేళ (!కిటికీ) {
        కిటికీ = SDL_GL_Get_Current_కిటికీ();
        ఒకవేళ (!కిటికీ) {
            SDL_assert(SDL_GL_GetCurrentContext() == ఖాళీ);
            తిరిగి true; // already done.
        }
    }

    hdc = కిటికీ->అంతర్గత->hdc;
    ఒకవేళ (!_this->gl_దత్తాంశం->wglMakeCurrent(hdc, (HGLRC)context)) {
        తిరిగి WIN_సమితి_Error("wglMakeCurrent()");
    }
    తిరిగి true;
}

bool WIN_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    ఒకవేళ ((interval < 0) && (!_this->gl_దత్తాంశం->HAS_WGL_EXT_మార్పిడి_control_tear)) {
        తిరిగి SDL_సమితి_Error("Negative swap interval unsupported in this GL");
    } లేకపోతే ఒకవేళ (_this->gl_దత్తాంశం->wgl_మార్పిడి_Interval_EXT) {
        ఒకవేళ (!_this->gl_దత్తాంశం->wgl_మార్పిడి_Interval_EXT(interval)) {
            తిరిగి WIN_సమితి_Error("wglSwapIntervalEXT()");
        }
    } లేకపోతే {
        తిరిగి SDL_Unsupported();
    }
    తిరిగి true;
}

bool WIN_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    ఒకవేళ (_this->gl_దత్తాంశం->wgl_Get_మార్పిడి_Interval_EXT) {
        *interval = _this->gl_దత్తాంశం->wgl_Get_మార్పిడి_Interval_EXT();
        తిరిగి true;
    } లేకపోతే {
        తిరిగి SDL_Unsupported();
    }
}

bool WIN_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    HDC hdc = కిటికీ->అంతర్గత->hdc;

    ఒకవేళ (!మార్పిడి_Buffers(hdc)) {
        తిరిగి WIN_సమితి_Error("SwapBuffers()");
    }
    తిరిగి true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి true;
    }
    _this->gl_దత్తాంశం->wglDeleteContext((HGLRC)context);
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_WGL

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS
