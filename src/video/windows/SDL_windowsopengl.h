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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_windowsopengl_h_
#define SDL_windowsopengl_h_

#ifdef SDL_VIDEO_OPENGL_WGL

#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
வகைவரை கட்டமைப்பு tagPIXELFORMATDESCRIPTOR
{
    WORD nSize;
    WORD nVersion;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE cColorBits;
    BYTE cRedBits;
    BYTE cRedShift;
    BYTE cGreenBits;
    BYTE cGreenShift;
    BYTE cBlueBits;
    BYTE cBlueShift;
    BYTE cAlphaBits;
    BYTE cAlphaShift;
    BYTE cAccumBits;
    BYTE cAccumRedBits;
    BYTE cAccumGreenBits;
    BYTE cAccumBlueBits;
    BYTE cAccumAlphaBits;
    BYTE cDepthBits;
    BYTE cStencilBits;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dwLayerMask;
    DWORD dwVisibleMask;
    DWORD dwDamageMask;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#endif

கட்டமைப்பு SDL_GLDriverData
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_swap_control_tear;
    bool HAS_WGL_ARB_context_flush_control;
    bool HAS_WGL_ARB_create_context_robustness;
    bool HAS_WGL_ARB_create_context_no_error;
    bool HAS_WGL_ARB_pixel_format_float;
    bool HAS_WGL_EXT_create_context_es2_profile;
    bool HAS_WGL_ARB_framebuffer_sRGB;

    /* Max version of OpenGL ES context that can be created if the
       implementation supports WGL_EXT_create_context_es2_profile.
       major = minor = 0 when unsupported.
     */
    கட்டமைப்பு
    {
        முழு major;
        முழு minor;
    } es_profile_max_supported_version;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wglGetProcAddress)(மாறிலி எழுத்து *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wglChoosePixelFormatARB)(HDC hdc, மாறிலி முழு *piAttribIList, மாறிலி FLOAT * pfAttribFList, UINT nMaxFormats, முழு *piFormats, UINT * n_இலக்கம்_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, முழு iPixelFormat, முழு iLayerPlane, UINT nAttributes, மாறிலி முழு *piAttributes, முழு *pi_மதிப்புகள்);
    BOOL (WINAPI *wglSwapIntervalEXT)(முழு interval);
    முழு (WINAPI *wglGetSwapIntervalEXT)(வெறுமை);
#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wglSwapBuffers)(HDC hdc);
    முழு (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         முழு iPixelFormat,
                                         UINT nBytes,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    முழு (WINAPI *wglChoosePixelFormat)(HDC hdc,
                                       மாறிலி PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wglSetPixelFormat)(HDC hdc,
                                     முழு format,
                                     மாறிலி PIXELFORMATDESCRIPTOR *ppfd);
    முழு (WINAPI *wglGetPixelFormat)(HDC hdc);
#endif
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
வெளி bool WIN_GL_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path);
வெளி SDL_FunctionPointer WIN_GL_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc);
வெளி வெறுமை WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
வெளி bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
வெளி bool WIN_GL_SetupWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                              SDL_GLContext context);
வெளி bool WIN_GL_SetSwapInterval(SDL_VideoDevice *_this, முழு interval);
வெளி bool WIN_GL_GetSwapInterval(SDL_VideoDevice *_this, முழு *interval);
வெளி bool WIN_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
வெளி வெறுமை WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#ifndef WGL_ARB_pixel_format
#define WGL_எண்_PIXEL_FORMATS_ARB    0x2000
#define WGL_DRAW_TO_WINDOW_ARB          0x2001
#define WGL_DRAW_TO_BITMAP_ARB          0x2002
#define WGL_ACCELERATION_ARB            0x2003
#define WGL_NEED_PALETTE_ARB            0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB      0x2006
#define WGL_SWAP_METHOD_ARB             0x2007
#define WGL_எண்_OVERLAYS_ARB         0x2008
#define WGL_எண்_UNDERLAYS_ARB        0x2009
#define WGL_TRANSPARENT_ARB             0x200A
#define WGL_TRANSPARENT_RED_மதிப்பு_ARB   0x2037
#define WGL_TRANSPARENT_GREEN_மதிப்பு_ARB 0x2038
#define WGL_TRANSPARENT_BLUE_மதிப்பு_ARB  0x2039
#define WGL_TRANSPARENT_ALPHA_மதிப்பு_ARB 0x203A
#define WGL_TRANSPARENT_INDEX_மதிப்பு_ARB 0x203B
#define WGL_SHARE_DEPTH_ARB             0x200C
#define WGL_SHARE_STENCIL_ARB           0x200D
#define WGL_SHARE_ACCUM_ARB             0x200E
#define WGL_SUPPORT_GDI_ARB             0x200F
#define WGL_SUPPORT_OPENGL_ARB          0x2010
#define WGL_DOUBLE_BUFFER_ARB           0x2011
#define WGL_STEREO_ARB                  0x2012
#define WGL_PIXEL_TYPE_ARB              0x2013
#define WGL_COLOR_BITS_ARB              0x2014
#define WGL_RED_BITS_ARB                0x2015
#define WGL_RED_SHIFT_ARB               0x2016
#define WGL_GREEN_BITS_ARB              0x2017
#define WGL_GREEN_SHIFT_ARB             0x2018
#define WGL_BLUE_BITS_ARB               0x2019
#define WGL_BLUE_SHIFT_ARB              0x201A
#define WGL_ALPHA_BITS_ARB              0x201B
#define WGL_ALPHA_SHIFT_ARB             0x201C
#define WGL_ACCUM_BITS_ARB              0x201D
#define WGL_ACCUM_RED_BITS_ARB          0x201E
#define WGL_ACCUM_GREEN_BITS_ARB        0x201F
#define WGL_ACCUM_BLUE_BITS_ARB         0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB        0x2021
#define WGL_DEPTH_BITS_ARB              0x2022
#define WGL_STENCIL_BITS_ARB            0x2023
#define WGL_AUX_BUFFERS_ARB             0x2024
#define WGL_NO_ACCELERATION_ARB         0x2025
#define WGL_GENERIC_ACCELERATION_ARB    0x2026
#define WGL_FULL_ACCELERATION_ARB       0x2027
#define WGL_SWAP_EXCHANGE_ARB           0x2028
#define WGL_SWAP_COPY_ARB               0x2029
#define WGL_SWAP_UNDEFINED_ARB          0x202A
#define WGL_TYPE_RGBA_ARB               0x202B
#define WGL_TYPE_COLORINDEX_ARB         0x202C
#endif

#ifndef WGL_ARB_multisample
#define WGL_SAMPLE_BUFFERS_ARB 0x2041
#define WGL_SAMPLES_ARB        0x2042
#endif

#endif // SDL_VIDEO_OPENGL_WGL

#endif // SDL_windowsopengl_h_
