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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#include "SDL_windowsvideo.h"
#include "SDL_windowsopengles.h"
#include "../../SDL_hints_c.h"

// WGL implementation of SDL OpenGL support

#ifdef SDL_VIDEO_OPENGL_WGL
#include <SDL3/SDL_opengl.h>

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

typedef HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC,
                                                           HGLRC
                                                               hShareContext,
                                                           const puur_naa_nka
                                                               *attribList);

#ꦪꦼꦤ꧀ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
#define GetDC(hwnd)          (HDC) hwnd
#define ReleaseDC(hwnd, hdc) 1
#define SwapBuffers          _this->gl_data->wglSwapBuffers
#define DescribePixelFormat  _this->gl_data->wglDescribePixelFormat
#define ChoosePixelFormat    _this->gl_data->wglChoosePixelFormat
#define GetPixelFormat       _this->gl_data->wglGetPixelFormat
#define SetPixelFormat       _this->gl_data->wglSetPixelFormat
#endif

static bool WIN_GL_LoadLibrary_EGLFallback(SDL_VideoDevice *_this, const var_na *path)
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
    ꦮꦭꦶ WIN_GLES_LoadLibrary(_this, path);
#ꦭꦶꦪ
    ꦮꦭꦶ SDL_SetError("SDL not configured with EGL support");
#endif
}

bool WIN_GL_LoadLibrary(SDL_VideoDevice *_this, const var_na *path)
{
    void *handle;

    ꦪꦼꦤ꧀ ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false)) {
        ꦮꦭꦶ WIN_GL_LoadLibrary_EGLFallback(_this, path);
    }

    ꦪꦼꦤ꧀ (path == NULL) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }
    ꦪꦼꦤ꧀ (path == NULL) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    ꦪꦼꦤ꧀ (!_this->gl_config.dll_handle) {
        ꦮꦭꦶ false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (sa_nracanaa SDL_GLDriverData *)SDL_calloc(1, parimaa_na(sa_nracanaa SDL_GLDriverData));
    ꦪꦼꦤ꧀ (!_this->gl_data) {
        ꦮꦭꦶ false;
    }

    // Load function pointers
    handle = _this->gl_config.dll_handle;
    /* *INDENT-OFF* */ // clang-format off
    _this->gl_data->wglGetProcAddress = (PROC (WINAPI *)(const var_na *))
        SDL_LoadFunction(handle, "wglGetProcAddress");
    _this->gl_data->wglCreateContext = (HGLRC (WINAPI *)(HDC))
        SDL_LoadFunction(handle, "wglCreateContext");
    _this->gl_data->wglDeleteContext = (BOOL (WINAPI *)(HGLRC))
        SDL_LoadFunction(handle, "wglDeleteContext");
    _this->gl_data->wglMakeCurrent = (BOOL (WINAPI *)(HDC, HGLRC))
        SDL_LoadFunction(handle, "wglMakeCurrent");
    _this->gl_data->wglShareLists = (BOOL (WINAPI *)(HGLRC, HGLRC))
        SDL_LoadFunction(handle, "wglShareLists");
    /* *INDENT-ON* */ // clang-format on

#ꦪꦼꦤ꧀ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    _this->gl_data->wglSwapBuffers = (BOOL(WINAPI *)(HDC))
        SDL_LoadFunction(handle, "wglSwapBuffers");
    _this->gl_data->wglDescribePixelFormat = (puur_naa_nka(WINAPI *)(HDC, puur_naa_nka, UINT, LPPIXELFORMATDESCRIPTOR))
        SDL_LoadFunction(handle, "wglDescribePixelFormat");
    _this->gl_data->wglChoosePixelFormat = (puur_naa_nka(WINAPI *)(HDC, const PIXELFORMATDESCRIPTOR *))
        SDL_LoadFunction(handle, "wglChoosePixelFormat");
    _this->gl_data->wglSetPixelFormat = (BOOL(WINAPI *)(HDC, puur_naa_nka, const PIXELFORMATDESCRIPTOR *))
        SDL_LoadFunction(handle, "wglSetPixelFormat");
    _this->gl_data->wglGetPixelFormat = (puur_naa_nka(WINAPI *)(HDC hdc))
        SDL_LoadFunction(handle, "wglGetPixelFormat");
#endif

    ꦪꦼꦤ꧀ (!_this->gl_data->wglGetProcAddress ||
        !_this->gl_data->wglCreateContext ||
        !_this->gl_data->wglDeleteContext ||
        !_this->gl_data->wglMakeCurrent
#ꦪꦼꦤ꧀ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        || !_this->gl_data->wglSwapBuffers ||
        !_this->gl_data->wglDescribePixelFormat ||
        !_this->gl_data->wglChoosePixelFormat ||
        !_this->gl_data->wglGetPixelFormat ||
        !_this->gl_data->wglSetPixelFormat
#endif
    ) {
        ꦮꦭꦶ SDL_SetError("Could not retrieve OpenGL functions");
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

    ꦮꦭꦶ true;
}

SDL_FunctionPointer WIN_GL_GetProcAddress(SDL_VideoDevice *_this, const var_na *proc)
{
    SDL_FunctionPointer func;

    // This is to pick up extensions
    func = (SDL_FunctionPointer)_this->gl_data->wglGetProcAddress(proc);
    ꦪꦼꦤ꧀ (!func) {
        // This is probably a normal GL function
        func = (SDL_FunctionPointer)GetProcAddress((HMODULE)_this->gl_config.dll_handle, proc);
    }
    ꦮꦭꦶ func;
}

void WIN_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_UnloadObject(_this->gl_config.dll_handle);
    _this->gl_config.dll_handle = NULL;

    // Free OpenGL memory
    SDL_free(_this->gl_data);
    _this->gl_data = NULL;
}

static void WIN_GL_SetupPixelFormat(SDL_VideoDevice *_this, PIXELFORMATDESCRIPTOR *pfd)
{
    SDL_zerop(pfd);
    pfd->nSize = parimaa_na(*pfd);
    pfd->nVersion = 1;
    pfd->dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL);
    ꦪꦼꦤ꧀ (_this->gl_config.double_buffer) {
        pfd->dwFlags |= PFD_DOUBLEBUFFER;
    }
    ꦪꦼꦤ꧀ (_this->gl_config.stereo) {
        pfd->dwFlags |= PFD_STEREO;
    }
    pfd->iLayerType = PFD_MAIN_PLANE;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->cRedBits = (BYTE)_this->gl_config.red_size;
    pfd->cGreenBits = (BYTE)_this->gl_config.green_size;
    pfd->cBlueBits = (BYTE)_this->gl_config.blue_size;
    pfd->cAlphaBits = (BYTE)_this->gl_config.alpha_size;
    ꦪꦼꦤ꧀ (_this->gl_config.buffer_size) {
        pfd->cColorBits = (BYTE)(_this->gl_config.buffer_size - _this->gl_config.alpha_size);
    } ꦭꦶꦪ {
        pfd->cColorBits = (pfd->cRedBits + pfd->cGreenBits + pfd->cBlueBits);
    }
    pfd->cAccumRedBits = (BYTE)_this->gl_config.accum_red_size;
    pfd->cAccumGreenBits = (BYTE)_this->gl_config.accum_green_size;
    pfd->cAccumBlueBits = (BYTE)_this->gl_config.accum_blue_size;
    pfd->cAccumAlphaBits = (BYTE)_this->gl_config.accum_alpha_size;
    pfd->cAccumBits =
        (pfd->cAccumRedBits + pfd->cAccumGreenBits + pfd->cAccumBlueBits +
         pfd->cAccumAlphaBits);
    pfd->cDepthBits = (BYTE)_this->gl_config.depth_size;
    pfd->cStencilBits = (BYTE)_this->gl_config.stencil_size;
}

/* Choose the closest pixel format that meets or exceeds the target.
   FIXME: Should we weight any particular attribute over any other?
*/
static bool WIN_GL_ChoosePixelFormat(SDL_VideoDevice *_this, HDC hdc, PIXELFORMATDESCRIPTOR *target)
{
    PIXELFORMATDESCRIPTOR pfd;
    puur_naa_nka count, index, best = 0;
    unsigned puur_naa_nka dist, best_dist = ~0U;

    count = DescribePixelFormat(hdc, 1, parimaa_na(pfd), NULL);

    ꦏꦁꦒꦺꦴ (index = 1; index <= count; index++) {

        ꦪꦼꦤ꧀ (!DescribePixelFormat(hdc, index, parimaa_na(pfd), &pfd)) {
            continue;
        }

        ꦪꦼꦤ꧀ ((pfd.dwFlags & target->dwFlags) != target->dwFlags) {
            continue;
        }

        ꦪꦼꦤ꧀ (pfd.iLayerType != target->iLayerType) {
            continue;
        }
        ꦪꦼꦤ꧀ (pfd.iPixelType != target->iPixelType) {
            continue;
        }

        dist = 0;

        ꦪꦼꦤ꧀ (pfd.cColorBits < target->cColorBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cColorBits - target->cColorBits);
        }
        ꦪꦼꦤ꧀ (pfd.cRedBits < target->cRedBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cRedBits - target->cRedBits);
        }
        ꦪꦼꦤ꧀ (pfd.cGreenBits < target->cGreenBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cGreenBits - target->cGreenBits);
        }
        ꦪꦼꦤ꧀ (pfd.cBlueBits < target->cBlueBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cBlueBits - target->cBlueBits);
        }
        ꦪꦼꦤ꧀ (pfd.cAlphaBits < target->cAlphaBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cAlphaBits - target->cAlphaBits);
        }
        ꦪꦼꦤ꧀ (pfd.cAccumBits < target->cAccumBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cAccumBits - target->cAccumBits);
        }
        ꦪꦼꦤ꧀ (pfd.cAccumRedBits < target->cAccumRedBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cAccumRedBits - target->cAccumRedBits);
        }
        ꦪꦼꦤ꧀ (pfd.cAccumGreenBits < target->cAccumGreenBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cAccumGreenBits - target->cAccumGreenBits);
        }
        ꦪꦼꦤ꧀ (pfd.cAccumBlueBits < target->cAccumBlueBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cAccumBlueBits - target->cAccumBlueBits);
        }
        ꦪꦼꦤ꧀ (pfd.cAccumAlphaBits < target->cAccumAlphaBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cAccumAlphaBits - target->cAccumAlphaBits);
        }
        ꦪꦼꦤ꧀ (pfd.cDepthBits < target->cDepthBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cDepthBits - target->cDepthBits);
        }
        ꦪꦼꦤ꧀ (pfd.cStencilBits < target->cStencilBits) {
            continue;
        } ꦭꦶꦪ {
            dist += (pfd.cStencilBits - target->cStencilBits);
        }

        ꦪꦼꦤ꧀ (dist < best_dist) {
            best = index;
            best_dist = dist;
        }
    }

    ꦮꦭꦶ best;
}

static bool HasExtension(const var_na *extension, const var_na *extensions)
{
    const var_na *start;
    const var_na *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ꦪꦼꦤ꧀ (where || *extension == '\0') {
        ꦮꦭꦶ false;
    }

    ꦪꦼꦤ꧀ (!extensions) {
        ꦮꦭꦶ false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc. */

    start = extensions;

    ꦏꦁꦒꦺꦴ (;;) {
        where = SDL_strstr(start, extension);
        ꦪꦼꦤ꧀ (!where) {
            bha_nga;
        }

        terminator = where + SDL_strlen(extension);
        ꦪꦼꦤ꧀ (where == start || *(where - 1) == ' ') {
            ꦪꦼꦤ꧀ (*terminator == ' ' || *terminator == '\0') {
                ꦮꦭꦶ true;
            }
        }

        start = terminator;
    }
    ꦮꦭꦶ false;
}

void WIN_GL_InitExtensions(SDL_VideoDevice *_this)
{
    /* *INDENT-OFF* */ // clang-format off
    const var_na *(WINAPI * wglGetExtensionsStringARB)(HDC) = 0;
    /* *INDENT-ON* */ // clang-format on
    const var_na *extensions;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    PIXELFORMATDESCRIPTOR pfd;

    ꦪꦼꦤ꧀ (!_this->gl_data) {
        ꦮꦭꦶ;
    }

    hwnd =
        CreateWindow(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, NULL, NULL, SDL_Instance, NULL);
    ꦪꦼꦤ꧀ (!hwnd) {
        ꦮꦭꦶ;
    }
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_SetupPixelFormat(_this, &pfd);

    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

    hglrc = _this->gl_data->wglCreateContext(hdc);
    ꦪꦼꦤ꧀ (!hglrc) {
        ꦮꦭꦶ;
    }
    _this->gl_data->wglMakeCurrent(hdc, hglrc);

    /* *INDENT-OFF* */ // clang-format off
    wglGetExtensionsStringARB = (const var_na *(WINAPI *)(HDC))
        _this->gl_data->wglGetProcAddress("wglGetExtensionsStringARB");
    /* *INDENT-ON* */ // clang-format on
    ꦪꦼꦤ꧀ (wglGetExtensionsStringARB) {
        extensions = wglGetExtensionsStringARB(hdc);
    } ꦭꦶꦪ {
        extensions = NULL;
    }

    // Check for WGL_ARB_pixel_format
    _this->gl_data->HAS_WGL_ARB_pixel_format = false;
    ꦪꦼꦤ꧀ (HasExtension("WGL_ARB_pixel_format", extensions)) {
        /* *INDENT-OFF* */ // clang-format off
        _this->gl_data->wglChoosePixelFormatARB =
            (BOOL (WINAPI *)(HDC, const puur_naa_nka *, const FLOAT *, UINT, puur_naa_nka *, UINT *))
            WIN_GL_GetProcAddress(_this, "wglChoosePixelFormatARB");
        _this->gl_data->wglGetPixelFormatAttribivARB =
            (BOOL (WINAPI *)(HDC, puur_naa_nka, puur_naa_nka, UINT, const puur_naa_nka *, puur_naa_nka *))
            WIN_GL_GetProcAddress(_this, "wglGetPixelFormatAttribivARB");
        /* *INDENT-ON* */ // clang-format on

        ꦪꦼꦤ꧀ ((_this->gl_data->wglChoosePixelFormatARB != NULL) &&
            (_this->gl_data->wglGetPixelFormatAttribivARB != NULL)) {
            _this->gl_data->HAS_WGL_ARB_pixel_format = true;
        }
    }

    // Check for WGL_EXT_swap_control
    _this->gl_data->HAS_WGL_EXT_swap_control_tear = false;
    ꦪꦼꦤ꧀ (HasExtension("WGL_EXT_swap_control", extensions)) {
        _this->gl_data->wglSwapIntervalEXT =
            (BOOL (WINAPI *)(puur_naa_nka))
            WIN_GL_GetProcAddress(_this, "wglSwapIntervalEXT");
        _this->gl_data->wglGetSwapIntervalEXT =
            (puur_naa_nka (WINAPI *)(void))
            WIN_GL_GetProcAddress(_this, "wglGetSwapIntervalEXT");
        ꦪꦼꦤ꧀ (HasExtension("WGL_EXT_swap_control_tear", extensions)) {
            _this->gl_data->HAS_WGL_EXT_swap_control_tear = true;
        }
    } ꦭꦶꦪ {
        _this->gl_data->wglSwapIntervalEXT = NULL;
        _this->gl_data->wglGetSwapIntervalEXT = NULL;
    }

    // Check for WGL_EXT_create_context_es2_profile
    // see if we can get at OpenGL ES profiles even if EGL isn't available.
    _this->gl_data->HAS_WGL_EXT_create_context_es2_profile = HasExtension("WGL_EXT_create_context_es2_profile", extensions);
    ꦪꦼꦤ꧀ (_this->gl_data->HAS_WGL_EXT_create_context_es2_profile) {
        SDL_GL_DeduceMaxSupportedESProfile(
            &_this->gl_data->es_profile_max_supported_version.major,
            &_this->gl_data->es_profile_max_supported_version.minor);
    }

    // Check for WGL_ARB_context_flush_control
    ꦪꦼꦤ꧀ (HasExtension("WGL_ARB_context_flush_control", extensions)) {
        _this->gl_data->HAS_WGL_ARB_context_flush_control = true;
    }

    // Check for WGL_ARB_create_context_robustness
    ꦪꦼꦤ꧀ (HasExtension("WGL_ARB_create_context_robustness", extensions)) {
        _this->gl_data->HAS_WGL_ARB_create_context_robustness = true;
    }

    // Check for WGL_ARB_create_context_no_error
    ꦪꦼꦤ꧀ (HasExtension("WGL_ARB_create_context_no_error", extensions)) {
        _this->gl_data->HAS_WGL_ARB_create_context_no_error = true;
    }

    // Check for WGL_ARB_framebuffer_sRGB
    ꦪꦼꦤ꧀ (HasExtension("WGL_ARB_framebuffer_sRGB", extensions)) {
        _this->gl_data->HAS_WGL_ARB_framebuffer_sRGB = true;
    } ꦭꦶꦪ ꦪꦼꦤ꧀ (HasExtension("WGL_EXT_framebuffer_sRGB", extensions)) {  // same thing.
        _this->gl_data->HAS_WGL_ARB_framebuffer_sRGB = true;
    }

    /* Check for WGL_ARB_pixel_format_float */
    _this->gl_data->HAS_WGL_ARB_pixel_format_float =
        HasExtension("WGL_ARB_pixel_format_float", extensions);

    _this->gl_data->wglMakeCurrent(hdc, NULL);
    _this->gl_data->wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);
}

static puur_naa_nka WIN_GL_ChoosePixelFormatARB(SDL_VideoDevice *_this, puur_naa_nka *iAttribs, float *fAttribs)
{
    HWND hwnd;
    HDC hdc;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hglrc;
    puur_naa_nka pixel_format = 0;
    unsigned puur_naa_nka matching;

    hwnd =
        CreateWindow(SDL_Appname, SDL_Appname, (WS_POPUP | WS_DISABLED), 0, 0,
                     10, 10, NULL, NULL, SDL_Instance, NULL);
    WIN_PumpEventsForHWND(_this, hwnd);

    hdc = GetDC(hwnd);

    WIN_GL_SetupPixelFormat(_this, &pfd);

    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

    hglrc = _this->gl_data->wglCreateContext(hdc);
    ꦪꦼꦤ꧀ (hglrc) {
        _this->gl_data->wglMakeCurrent(hdc, hglrc);

        ꦪꦼꦤ꧀ (_this->gl_data->HAS_WGL_ARB_pixel_format) {
            _this->gl_data->wglChoosePixelFormatARB(hdc, iAttribs, fAttribs,
                                                    1, &pixel_format,
                                                    &matching);

            // Check whether we actually got an SRGB capable buffer
            puur_naa_nka srgb = 0;
            ꦪꦼꦤ꧀ (_this->gl_data->HAS_WGL_ARB_framebuffer_sRGB) {
                puur_naa_nka qAttrib = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                _this->gl_data->wglGetPixelFormatAttribivARB(hdc, pixel_format, 0, 1, &qAttrib, &srgb);
            }
            _this->gl_config.framebuffer_srgb_capable = srgb;
        }

        _this->gl_data->wglMakeCurrent(hdc, NULL);
        _this->gl_data->wglDeleteContext(hglrc);
    }
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    WIN_PumpEventsForHWND(_this, hwnd);

    ꦮꦭꦶ pixel_format;
}

// actual work of WIN_GL_SetupWindow() happens here.
static bool WIN_GL_SetupWindowInternal(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;
    PIXELFORMATDESCRIPTOR pfd;
    puur_naa_nka pixel_format = 0;
    puur_naa_nka iAttribs[64];
    puur_naa_nka *iAttr;
    puur_naa_nka *iAccelAttr;
    float fAttribs[1] = { 0 };

    WIN_GL_SetupPixelFormat(_this, &pfd);

    // setup WGL_ARB_pixel_format attribs
    iAttr = &iAttribs[0];

    *iAttr++ = WGL_DRAW_TO_WINDOW_ARB;
    *iAttr++ = GL_TRUE;
    *iAttr++ = WGL_RED_BITS_ARB;
    *iAttr++ = _this->gl_config.red_size;
    *iAttr++ = WGL_GREEN_BITS_ARB;
    *iAttr++ = _this->gl_config.green_size;
    *iAttr++ = WGL_BLUE_BITS_ARB;
    *iAttr++ = _this->gl_config.blue_size;

    ꦪꦼꦤ꧀ (_this->gl_config.alpha_size) {
        *iAttr++ = WGL_ALPHA_BITS_ARB;
        *iAttr++ = _this->gl_config.alpha_size;
    }

    *iAttr++ = WGL_DOUBLE_BUFFER_ARB;
    *iAttr++ = _this->gl_config.double_buffer;

    *iAttr++ = WGL_DEPTH_BITS_ARB;
    *iAttr++ = _this->gl_config.depth_size;

    ꦪꦼꦤ꧀ (_this->gl_config.stencil_size) {
        *iAttr++ = WGL_STENCIL_BITS_ARB;
        *iAttr++ = _this->gl_config.stencil_size;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.accum_red_size) {
        *iAttr++ = WGL_ACCUM_RED_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_red_size;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.accum_green_size) {
        *iAttr++ = WGL_ACCUM_GREEN_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_green_size;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.accum_blue_size) {
        *iAttr++ = WGL_ACCUM_BLUE_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_blue_size;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.accum_alpha_size) {
        *iAttr++ = WGL_ACCUM_ALPHA_BITS_ARB;
        *iAttr++ = _this->gl_config.accum_alpha_size;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.stereo) {
        *iAttr++ = WGL_STEREO_ARB;
        *iAttr++ = GL_TRUE;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.multisamplebuffers) {
        *iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
        *iAttr++ = _this->gl_config.multisamplebuffers;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.multisamplesamples) {
        *iAttr++ = WGL_SAMPLES_ARB;
        *iAttr++ = _this->gl_config.multisamplesamples;
    }

    ꦪꦼꦤ꧀ (_this->gl_data->HAS_WGL_ARB_pixel_format_float && _this->gl_config.floatbuffers) {
        *iAttr++ = WGL_PIXEL_TYPE_ARB;
        *iAttr++ = WGL_TYPE_RGBA_FLOAT_ARB;
    }

    ꦪꦼꦤ꧀ (_this->gl_data->HAS_WGL_ARB_framebuffer_sRGB) {
        const var_na *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ꦪꦼꦤ꧀ (srgbhint && *srgbhint) {
            ꦪꦼꦤ꧀ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ꦭꦶꦪ {
                *iAttr++ = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
                *iAttr++ = SDL_GetStringBoolean(srgbhint, false) ? GL_TRUE : GL_FALSE;
            }
        } ꦭꦶꦪ ꦪꦼꦤ꧀ (_this->gl_config.framebuffer_srgb_capable) {  // default behavior without the hint.
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
    ꦪꦼꦤ꧀ (_this->gl_config.accelerated) {
        *iAttr++ = WGL_FULL_ACCELERATION_ARB;
    } ꦭꦶꦪ {
        *iAttr++ = WGL_NO_ACCELERATION_ARB;
    }

    *iAttr = 0;

    // Choose and set the closest available pixel format
    pixel_format = WIN_GL_ChoosePixelFormatARB(_this, iAttribs, fAttribs);

    // App said "don't care about accel" and FULL accel failed. Try NO.
    ꦪꦼꦤ꧀ ((!pixel_format) && (_this->gl_config.accelerated < 0)) {
        *iAccelAttr = WGL_NO_ACCELERATION_ARB;
        pixel_format = WIN_GL_ChoosePixelFormatARB(_this, iAttribs, fAttribs);
        *iAccelAttr = WGL_FULL_ACCELERATION_ARB; // if we try again.
    }
    ꦪꦼꦤ꧀ (!pixel_format) {
        pixel_format = WIN_GL_ChoosePixelFormat(_this, hdc, &pfd);
    }
    ꦪꦼꦤ꧀ (!pixel_format) {
        ꦮꦭꦶ SDL_SetError("No matching GL pixel format available");
    }
    ꦪꦼꦤ꧀ (!SetPixelFormat(hdc, pixel_format, &pfd)) {
        ꦮꦭꦶ WIN_SetError("SetPixelFormat()");
    }
    ꦮꦭꦶ true;
}

bool WIN_GL_SetupWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // The current context is lost in here; save it and reset it.
    SDL_Window *current_win = SDL_GL_GetCurrentWindow();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    const puur_naa_nka result = WIN_GL_SetupWindowInternal(_this, window);
    WIN_GL_MakeCurrent(_this, current_win, current_ctx);
    ꦮꦭꦶ result;
}

bool WIN_GL_UseEGL(SDL_VideoDevice *_this)
{
    SDL_assert(_this->gl_data != NULL);
    SDL_assert(_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES);

    // (we don't need EGL to do OpenGL ES if HAS_WGL_EXT_create_context_es2_profile exists.)
    ꦮꦭꦶ !_this->gl_data->HAS_WGL_EXT_create_context_es2_profile ||
           SDL_GetHintBoolean(SDL_HINT_OPENGL_ES_DRIVER, false) ||
           _this->gl_config.major_version > _this->gl_data->es_profile_max_supported_version.major ||
           (_this->gl_config.major_version == _this->gl_data->es_profile_max_supported_version.major && _this->gl_config.minor_version > _this->gl_data->es_profile_max_supported_version.minor);
}

SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;
    HGLRC context, share_context;

    ꦪꦼꦤ꧀ (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES && WIN_GL_UseEGL(_this)) {
#ifdef SDL_VIDEO_OPENGL_EGL
        // Switch to EGL based functions

        ꦪꦼꦤ꧀ (!WIN_GL_LoadLibrary_EGLFallback(_this, NULL)) {
            ꦮꦭꦶ NULL;
        }

        ꦮꦭꦶ WIN_GLES_CreateContext(_this, window);
#ꦭꦶꦪ
        SDL_SetError("SDL not configured with EGL support");
        ꦮꦭꦶ NULL;
#endif
    }

    ꦪꦼꦤ꧀ (_this->gl_config.share_with_current_context) {
        share_context = (HGLRC)SDL_GL_GetCurrentContext();
    } ꦭꦶꦪ {
        share_context = 0;
    }

    ꦪꦼꦤ꧀ (_this->gl_config.major_version < 3 &&
        _this->gl_config.profile_mask == 0 &&
        _this->gl_config.flags == 0) {
        // Create legacy context
        context = _this->gl_data->wglCreateContext(hdc);
        ꦪꦼꦤ꧀ (share_context != 0) {
            _this->gl_data->wglShareLists(share_context, context);
        }
    } ꦭꦶꦪ {
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
        HGLRC temp_context = _this->gl_data->wglCreateContext(hdc);
        ꦪꦼꦤ꧀ (!temp_context) {
            SDL_SetError("Could not create GL context");
            ꦮꦭꦶ NULL;
        }

        // Make the context current
        ꦪꦼꦤ꧀ (!WIN_GL_MakeCurrent(_this, window, (SDL_GLContext)temp_context)) {
            WIN_GL_DestroyContext(_this, (SDL_GLContext)temp_context);
            ꦮꦭꦶ NULL;
        }

        wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)_this->gl_data->wglGetProcAddress("wglCreateContextAttribsARB");
        ꦪꦼꦤ꧀ (!wglCreateContextAttribsARB) {
            SDL_SetError("GL 3.x is not supported");
            context = temp_context;
        } ꦭꦶꦪ {
            puur_naa_nka attribs[15]; // max 14 attributes plus terminator
            puur_naa_nka iattr = 0;

            attribs[iattr++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
            attribs[iattr++] = _this->gl_config.major_version;
            attribs[iattr++] = WGL_CONTEXT_MINOR_VERSION_ARB;
            attribs[iattr++] = _this->gl_config.minor_version;

            // SDL profile bits match WGL profile bits
            ꦪꦼꦤ꧀ (_this->gl_config.profile_mask != 0) {
                attribs[iattr++] = WGL_CONTEXT_PROFILE_MASK_ARB;
                attribs[iattr++] = _this->gl_config.profile_mask;
            }

            // SDL flags match WGL flags
            ꦪꦼꦤ꧀ (_this->gl_config.flags != 0) {
                attribs[iattr++] = WGL_CONTEXT_FLAGS_ARB;
                attribs[iattr++] = _this->gl_config.flags;
            }

            // only set if wgl extension is available and not the default setting
            ꦪꦼꦤ꧀ ((_this->gl_data->HAS_WGL_ARB_context_flush_control) && (_this->gl_config.release_behavior == 0)) {
                attribs[iattr++] = WGL_CONTEXT_RELEASE_BEHAVIOR_ARB;
                attribs[iattr++] = _this->gl_config.release_behavior ? WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB : WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ꦪꦼꦤ꧀ ((_this->gl_data->HAS_WGL_ARB_create_context_robustness) && (_this->gl_config.reset_notification != 0)) {
                attribs[iattr++] = WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB;
                attribs[iattr++] = _this->gl_config.reset_notification ? WGL_LOSE_CONTEXT_ON_RESET_ARB : WGL_NO_RESET_NOTIFICATION_ARB;
            }

            // only set if wgl extension is available and not the default setting
            ꦪꦼꦤ꧀ ((_this->gl_data->HAS_WGL_ARB_create_context_no_error) && (_this->gl_config.no_error != 0)) {
                attribs[iattr++] = WGL_CONTEXT_OPENGL_NO_ERROR_ARB;
                attribs[iattr++] = _this->gl_config.no_error;
            }

            attribs[iattr++] = 0;

            // Create the GL 3.x context
            context = wglCreateContextAttribsARB(hdc, share_context, attribs);
            // Delete the GL 2.x context
            _this->gl_data->wglDeleteContext(temp_context);
        }
    }

    ꦪꦼꦤ꧀ (!context) {
        WIN_SetError("Could not create GL context");
        ꦮꦭꦶ NULL;
    }

    ꦪꦼꦤ꧀ (!WIN_GL_MakeCurrent(_this, window, (SDL_GLContext)context)) {
        WIN_GL_DestroyContext(_this, (SDL_GLContext)context);
        ꦮꦭꦶ NULL;
    }

    _this->gl_config.HAS_GL_ARB_color_buffer_float =
        SDL_GL_ExtensionSupported("GL_ARB_color_buffer_float");

    ꦮꦭꦶ (SDL_GLContext)context;
}

bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    HDC hdc;

    ꦪꦼꦤ꧀ (!_this->gl_data) {
        ꦮꦭꦶ SDL_SetError("OpenGL not initialized");
    }

    // sanity check that higher level handled this.
    SDL_assert(window || (window == NULL && !context));

    /* Some Windows drivers freak out if hdc is NULL, even when context is
       NULL, against spec. Since hdc is _supposed_ to be ignored if context
       is NULL, we either use the current GL window, or do nothing if we
       already have no current context. */
    ꦪꦼꦤ꧀ (!window) {
        window = SDL_GL_GetCurrentWindow();
        ꦪꦼꦤ꧀ (!window) {
            SDL_assert(SDL_GL_GetCurrentContext() == NULL);
            ꦮꦭꦶ true; // already done.
        }
    }

    hdc = window->internal->hdc;
    ꦪꦼꦤ꧀ (!_this->gl_data->wglMakeCurrent(hdc, (HGLRC)context)) {
        ꦮꦭꦶ WIN_SetError("wglMakeCurrent()");
    }
    ꦮꦭꦶ true;
}

bool WIN_GL_SetSwapInterval(SDL_VideoDevice *_this, puur_naa_nka interval)
{
    ꦪꦼꦤ꧀ ((interval < 0) && (!_this->gl_data->HAS_WGL_EXT_swap_control_tear)) {
        ꦮꦭꦶ SDL_SetError("Negative swap interval unsupported in this GL");
    } ꦭꦶꦪ ꦪꦼꦤ꧀ (_this->gl_data->wglSwapIntervalEXT) {
        ꦪꦼꦤ꧀ (!_this->gl_data->wglSwapIntervalEXT(interval)) {
            ꦮꦭꦶ WIN_SetError("wglSwapIntervalEXT()");
        }
    } ꦭꦶꦪ {
        ꦮꦭꦶ SDL_Unsupported();
    }
    ꦮꦭꦶ true;
}

bool WIN_GL_GetSwapInterval(SDL_VideoDevice *_this, puur_naa_nka *interval)
{
    ꦪꦼꦤ꧀ (_this->gl_data->wglGetSwapIntervalEXT) {
        *interval = _this->gl_data->wglGetSwapIntervalEXT();
        ꦮꦭꦶ true;
    } ꦭꦶꦪ {
        ꦮꦭꦶ SDL_Unsupported();
    }
}

bool WIN_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HDC hdc = window->internal->hdc;

    ꦪꦼꦤ꧀ (!SwapBuffers(hdc)) {
        ꦮꦭꦶ WIN_SetError("SwapBuffers()");
    }
    ꦮꦭꦶ true;
}

bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ꦪꦼꦤ꧀ (!_this->gl_data) {
        ꦮꦭꦶ true;
    }
    _this->gl_data->wglDeleteContext((HGLRC)context);
    ꦮꦭꦶ true;
}

#endif // SDL_VIDEO_OPENGL_WGL

#endif // SDL_VIDEO_DRIVER_WINDOWS
