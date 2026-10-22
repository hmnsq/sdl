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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_windowsopengl_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_windowsopengl_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL

#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਟੈਗ_PIXELFORMATDESCRIPTOR
{
    ਸ਼ਬਦ_2 n_ਮਾਪ;
    ਸ਼ਬਦ_2 n_ਸੰਸਕਰਣ;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_ਬਿੱਟ;
    BYTE c_Red_ਬਿੱਟ;
    BYTE c_Red_ਖਿਸਕਾਓ;
    BYTE c_Green_ਬਿੱਟ;
    BYTE c_Green_ਖਿਸਕਾਓ;
    BYTE c_Blue_ਬਿੱਟ;
    BYTE c_Blue_ਖਿਸਕਾਓ;
    BYTE c_Alpha_ਬਿੱਟ;
    BYTE c_Alpha_ਖਿਸਕਾਓ;
    BYTE c_Accum_ਬਿੱਟ;
    BYTE c_Accum_Red_ਬਿੱਟ;
    BYTE c_Accum_Green_ਬਿੱਟ;
    BYTE c_Accum_Blue_ਬਿੱਟ;
    BYTE c_Accum_Alpha_ਬਿੱਟ;
    BYTE c_ਡੂੰਘਾਈ_ਬਿੱਟ;
    BYTE c_Stencil_ਬਿੱਟ;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_ਨਕਾਬ;
    DWORD dw_Visible_ਨਕਾਬ;
    DWORD dw_Damage_ਨਕਾਬ;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#ਜੇ_ਅੰਤ

ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_ਅਦਲਾ_ਬਦਲੀ_control_tear;
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
    ਬਣਤਰ
    {
        ਪੂਰਨ major;
        ਪੂਰਨ minor;
    } es_profile_max_supported_ਸੰਸਕਰਣ;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wgl_Get_Proc_ਪਤਾ)(ਅਚਲ ਅੱਖਰ *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_ਚੁਣੋ_Pixel_Format_ARB)(HDC hdc, ਅਚਲ ਪੂਰਨ *piAttribIList, ਅਚਲ FLOAT * pfAttribFList, UINT nMaxFormats, ਪੂਰਨ *piFormats, UINT * n_ਅੰਕ_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, ਪੂਰਨ iPixelFormat, ਪੂਰਨ iLayerPlane, UINT n_ਗੁਣ, ਅਚਲ ਪੂਰਨ *pi_ਗੁਣ, ਪੂਰਨ *pi_ਮੁੱਲਾਂ);
    BOOL (WINAPI *wgl_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT)(ਪੂਰਨ interval);
    ਪੂਰਨ (WINAPI *wgl_Get_ਅਦਲਾ_ਬਦਲੀ_Interval_EXT)(ਖਾਲੀ);
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wgl_ਅਦਲਾ_ਬਦਲੀ_Buffers)(HDC hdc);
    ਪੂਰਨ (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         ਪੂਰਨ iPixelFormat,
                                         UINT n_ਬਾਈਟਾਂ,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    ਪੂਰਨ (WINAPI *wgl_ਚੁਣੋ_Pixel_Format)(HDC hdc,
                                       ਅਚਲ PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_ਸੈੱਟ_Pixel_Format)(HDC hdc,
                                     ਪੂਰਨ format,
                                     ਅਚਲ PIXELFORMATDESCRIPTOR *ppfd);
    ਪੂਰਨ (WINAPI *wglGetPixelFormat)(HDC hdc);
#ਜੇ_ਅੰਤ
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
ਬਾਹਰੀ bool WIN_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ WIN_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ ਖਾਲੀ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool WIN_GL_ਤਿਆਰੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                              SDL_GLContext context);
ਬਾਹਰੀ bool WIN_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool WIN_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
ਬਾਹਰੀ bool WIN_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ਬਾਹਰੀ ਖਾਲੀ WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_pixel_format
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਸੰਖਿਆ_PIXEL_FORMATS_ARB    0x2000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_DRAW_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ_ARB          0x2001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_DRAW_ਮੰਜ਼ਿਲ_BITMAP_ARB          0x2002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ACCELERATION_ARB            0x2003
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_NEED_PALETTE_ARB            0x2004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਅਦਲਾ_ਬਦਲੀ_LAYER_BUFFERS_ARB      0x2006
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਅਦਲਾ_ਬਦਲੀ_ਵਿਧੀ_ARB             0x2007
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਸੰਖਿਆ_OVERLAYS_ARB         0x2008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਸੰਖਿਆ_UNDERLAYS_ARB        0x2009
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TRANSPARENT_ARB             0x200A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TRANSPARENT_RED_ਮੁੱਲ_ARB   0x2037
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TRANSPARENT_GREEN_ਮੁੱਲ_ARB 0x2038
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TRANSPARENT_BLUE_ਮੁੱਲ_ARB  0x2039
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TRANSPARENT_ALPHA_ਮੁੱਲ_ARB 0x203A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TRANSPARENT_ਸੂਚਕਾਂਕ_ਮੁੱਲ_ARB 0x203B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_SHARE_ਡੂੰਘਾਈ_ARB             0x200C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_SHARE_STENCIL_ARB           0x200D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_SHARE_ACCUM_ARB             0x200E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_SUPPORT_GDI_ARB             0x200F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_SUPPORT_OPENGL_ARB          0x2010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_DOUBLE_ਬਫਰ_ARB           0x2011
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_STEREO_ARB                  0x2012
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_PIXEL_TYPE_ARB              0x2013
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_COLOR_ਬਿੱਟ_ARB              0x2014
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_RED_ਬਿੱਟ_ARB                0x2015
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_RED_ਖਿਸਕਾਓ_ARB               0x2016
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_GREEN_ਬਿੱਟ_ARB              0x2017
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_GREEN_ਖਿਸਕਾਓ_ARB             0x2018
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_BLUE_ਬਿੱਟ_ARB               0x2019
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_BLUE_ਖਿਸਕਾਓ_ARB              0x201A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ALPHA_ਬਿੱਟ_ARB              0x201B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ALPHA_ਖਿਸਕਾਓ_ARB             0x201C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ACCUM_ਬਿੱਟ_ARB              0x201D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ACCUM_RED_ਬਿੱਟ_ARB          0x201E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ACCUM_GREEN_ਬਿੱਟ_ARB        0x201F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ACCUM_BLUE_ਬਿੱਟ_ARB         0x2020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ACCUM_ALPHA_ਬਿੱਟ_ARB        0x2021
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਡੂੰਘਾਈ_ਬਿੱਟ_ARB              0x2022
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_STENCIL_ਬਿੱਟ_ARB            0x2023
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_AUX_BUFFERS_ARB             0x2024
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_NO_ACCELERATION_ARB         0x2025
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_GENERIC_ACCELERATION_ARB    0x2026
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਭਰਿਆ_ACCELERATION_ARB       0x2027
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਅਦਲਾ_ਬਦਲੀ_EXCHANGE_ARB           0x2028
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਅਦਲਾ_ਬਦਲੀ_COPY_ARB               0x2029
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_ਅਦਲਾ_ਬਦਲੀ_UNDEFINED_ARB          0x202A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TYPE_RGBA_ARB               0x202B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_TYPE_COLORINDEX_ARB         0x202C
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WGL_ARB_multisample
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_SAMPLE_BUFFERS_ARB 0x2041
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WGL_SAMPLES_ARB        0x2042
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_WGL

#ਜੇ_ਅੰਤ // SDL_windowsopengl_h_
