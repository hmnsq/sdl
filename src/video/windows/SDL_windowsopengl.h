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

#अगर_अघोषित SDL_windowsopengl_h_
#घोषणा SDL_windowsopengl_h_

#अगर_घोषित SDL_VIDEO_OPENGL_WGL

#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
प्रकार काष्ठा tagPIXELFORMATDESCRIPTOR
{
    WORD n_आकार;
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
#पूर्ण_अगर

काष्ठा SDL_GLDriver_तथ्य
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
    काष्ठा
    {
        पूर्णांक major;
        पूर्णांक minor;
    } es_profile_max_supported_version;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wglGetProcAddress)(स्थिर अक्षर *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wglChoosePixelFormatARB)(HDC hdc, स्थिर पूर्णांक *piAttribIList, स्थिर FLOAT * pfAttribFList, UINT nMaxFormats, पूर्णांक *piFormats, UINT * n_अंक_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, पूर्णांक iPixelFormat, पूर्णांक iLayerPlane, UINT nAttributes, स्थिर पूर्णांक *piAttributes, पूर्णांक *pi_मूल्यावली);
    BOOL (WINAPI *wglSwapIntervalEXT)(पूर्णांक interval);
    पूर्णांक (WINAPI *wglGetSwapIntervalEXT)(व्योम);
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wglSwapBuffers)(HDC hdc);
    पूर्णांक (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         पूर्णांक iPixelFormat,
                                         UINT nBytes,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    पूर्णांक (WINAPI *wglChoosePixelFormat)(HDC hdc,
                                       स्थिर PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wglSetPixelFormat)(HDC hdc,
                                     पूर्णांक format,
                                     स्थिर PIXELFORMATDESCRIPTOR *ppfd);
    पूर्णांक (WINAPI *wglGetPixelFormat)(HDC hdc);
#पूर्ण_अगर
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
बाह्य bool WIN_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_FunctionPointer WIN_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य व्योम WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
बाह्य bool WIN_GL_SetupWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window,
                              SDL_GLContext context);
बाह्य bool WIN_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool WIN_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool WIN_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य व्योम WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#अगर_अघोषित WGL_ARB_pixel_format
#घोषणा WGL_संख्या_PIXEL_FORMATS_ARB    0x2000
#घोषणा WGL_DRAW_TO_WINDOW_ARB          0x2001
#घोषणा WGL_DRAW_TO_BITMAP_ARB          0x2002
#घोषणा WGL_ACCELERATION_ARB            0x2003
#घोषणा WGL_NEED_PALETTE_ARB            0x2004
#घोषणा WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#घोषणा WGL_SWAP_LAYER_BUFFERS_ARB      0x2006
#घोषणा WGL_SWAP_METHOD_ARB             0x2007
#घोषणा WGL_संख्या_OVERLAYS_ARB         0x2008
#घोषणा WGL_संख्या_UNDERLAYS_ARB        0x2009
#घोषणा WGL_TRANSPARENT_ARB             0x200A
#घोषणा WGL_TRANSPARENT_RED_मूल्य_ARB   0x2037
#घोषणा WGL_TRANSPARENT_GREEN_मूल्य_ARB 0x2038
#घोषणा WGL_TRANSPARENT_BLUE_मूल्य_ARB  0x2039
#घोषणा WGL_TRANSPARENT_ALPHA_मूल्य_ARB 0x203A
#घोषणा WGL_TRANSPARENT_सूचकांक_मूल्य_ARB 0x203B
#घोषणा WGL_SHARE_DEPTH_ARB             0x200C
#घोषणा WGL_SHARE_STENCIL_ARB           0x200D
#घोषणा WGL_SHARE_ACCUM_ARB             0x200E
#घोषणा WGL_SUPPORT_GDI_ARB             0x200F
#घोषणा WGL_SUPPORT_OPENGL_ARB          0x2010
#घोषणा WGL_DOUBLE_बफर_ARB           0x2011
#घोषणा WGL_STEREO_ARB                  0x2012
#घोषणा WGL_PIXEL_TYPE_ARB              0x2013
#घोषणा WGL_COLOR_BITS_ARB              0x2014
#घोषणा WGL_RED_BITS_ARB                0x2015
#घोषणा WGL_RED_SHIFT_ARB               0x2016
#घोषणा WGL_GREEN_BITS_ARB              0x2017
#घोषणा WGL_GREEN_SHIFT_ARB             0x2018
#घोषणा WGL_BLUE_BITS_ARB               0x2019
#घोषणा WGL_BLUE_SHIFT_ARB              0x201A
#घोषणा WGL_ALPHA_BITS_ARB              0x201B
#घोषणा WGL_ALPHA_SHIFT_ARB             0x201C
#घोषणा WGL_ACCUM_BITS_ARB              0x201D
#घोषणा WGL_ACCUM_RED_BITS_ARB          0x201E
#घोषणा WGL_ACCUM_GREEN_BITS_ARB        0x201F
#घोषणा WGL_ACCUM_BLUE_BITS_ARB         0x2020
#घोषणा WGL_ACCUM_ALPHA_BITS_ARB        0x2021
#घोषणा WGL_DEPTH_BITS_ARB              0x2022
#घोषणा WGL_STENCIL_BITS_ARB            0x2023
#घोषणा WGL_AUX_BUFFERS_ARB             0x2024
#घोषणा WGL_NO_ACCELERATION_ARB         0x2025
#घोषणा WGL_GENERIC_ACCELERATION_ARB    0x2026
#घोषणा WGL_FULL_ACCELERATION_ARB       0x2027
#घोषणा WGL_SWAP_EXCHANGE_ARB           0x2028
#घोषणा WGL_SWAP_COPY_ARB               0x2029
#घोषणा WGL_SWAP_UNDEFINED_ARB          0x202A
#घोषणा WGL_TYPE_RGBA_ARB               0x202B
#घोषणा WGL_TYPE_COLORINDEX_ARB         0x202C
#पूर्ण_अगर

#अगर_अघोषित WGL_ARB_multisample
#घोषणा WGL_SAMPLE_BUFFERS_ARB 0x2041
#घोषणा WGL_SAMPLES_ARB        0x2042
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_OPENGL_WGL

#पूर्ण_अगर // SDL_windowsopengl_h_
