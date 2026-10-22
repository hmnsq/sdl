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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_نه_ٿيل SDL_windowsopengl_h_
#وصف_ڪريو SDL_windowsopengl_h_

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
تعريفنوع بنية ٽيگ_PIXELFORMATDESCRIPTOR
{
    لفظ_2 n_سائيز;
    لفظ_2 n_نسخو;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_بٽ;
    BYTE c_Red_بٽ;
    BYTE c_Red_سرڪايو;
    BYTE c_Green_بٽ;
    BYTE c_Green_سرڪايو;
    BYTE c_Blue_بٽ;
    BYTE c_Blue_سرڪايو;
    BYTE c_Alpha_بٽ;
    BYTE c_Alpha_سرڪايو;
    BYTE c_Accum_بٽ;
    BYTE c_Accum_Red_بٽ;
    BYTE c_Accum_Green_بٽ;
    BYTE c_Accum_Blue_بٽ;
    BYTE c_Accum_Alpha_بٽ;
    BYTE c_اونهائي_بٽ;
    BYTE c_Stencil_بٽ;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_نقاب;
    DWORD dw_Visible_نقاب;
    DWORD dw_Damage_نقاب;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#جيڪڏهن_پورو

بنية SDL_GLDriver_معلومات
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_مٽا_سٽا_control_tear;
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
    بنية
    {
        صحيح major;
        صحيح minor;
    } es_profile_max_supported_نسخو;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wgl_Get_Proc_پتو)(ثابت حرف *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_چونڊيو_Pixel_Format_ARB)(HDC hdc, ثابت صحيح *piAttribIList, ثابت FLOAT * pfAttribFList, UINT nMaxFormats, صحيح *piFormats, UINT * n_انگ_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, صحيح iPixelFormat, صحيح iLayerPlane, UINT n_خاصيتون, ثابت صحيح *pi_خاصيتون, صحيح *pi_قدرون);
    BOOL (WINAPI *wgl_مٽا_سٽا_Interval_EXT)(صحيح interval);
    صحيح (WINAPI *wgl_Get_مٽا_سٽا_Interval_EXT)(فراغ);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wgl_مٽا_سٽا_Buffers)(HDC hdc);
    صحيح (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         صحيح iPixelFormat,
                                         UINT n_بائيٽون,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    صحيح (WINAPI *wgl_چونڊيو_Pixel_Format)(HDC hdc,
                                       ثابت PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_سيٽ_Pixel_Format)(HDC hdc,
                                     صحيح format,
                                     ثابت PIXELFORMATDESCRIPTOR *ppfd);
    صحيح (WINAPI *wglGetPixelFormat)(HDC hdc);
#جيڪڏهن_پورو
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
خارجي bool WIN_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
خارجي SDL_Function_اشارو WIN_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
خارجي bool WIN_GL_تياري_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري,
                              SDL_GLContext context);
خارجي bool WIN_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool WIN_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool WIN_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي فراغ WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_pixel_format
#وصف_ڪريو WGL_عدد_PIXEL_FORMATS_ARB    0x2000
#وصف_ڪريو WGL_DRAW_منزل_دري_ARB          0x2001
#وصف_ڪريو WGL_DRAW_منزل_BITMAP_ARB          0x2002
#وصف_ڪريو WGL_ACCELERATION_ARB            0x2003
#وصف_ڪريو WGL_NEED_PALETTE_ARB            0x2004
#وصف_ڪريو WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#وصف_ڪريو WGL_مٽا_سٽا_LAYER_BUFFERS_ARB      0x2006
#وصف_ڪريو WGL_مٽا_سٽا_طريقو_ARB             0x2007
#وصف_ڪريو WGL_عدد_OVERLAYS_ARB         0x2008
#وصف_ڪريو WGL_عدد_UNDERLAYS_ARB        0x2009
#وصف_ڪريو WGL_TRANSPARENT_ARB             0x200A
#وصف_ڪريو WGL_TRANSPARENT_RED_قدر_ARB   0x2037
#وصف_ڪريو WGL_TRANSPARENT_GREEN_قدر_ARB 0x2038
#وصف_ڪريو WGL_TRANSPARENT_BLUE_قدر_ARB  0x2039
#وصف_ڪريو WGL_TRANSPARENT_ALPHA_قدر_ARB 0x203A
#وصف_ڪريو WGL_TRANSPARENT_اشاريو_قدر_ARB 0x203B
#وصف_ڪريو WGL_SHARE_اونهائي_ARB             0x200C
#وصف_ڪريو WGL_SHARE_STENCIL_ARB           0x200D
#وصف_ڪريو WGL_SHARE_ACCUM_ARB             0x200E
#وصف_ڪريو WGL_SUPPORT_GDI_ARB             0x200F
#وصف_ڪريو WGL_SUPPORT_OPENGL_ARB          0x2010
#وصف_ڪريو WGL_DOUBLE_بفر_ARB           0x2011
#وصف_ڪريو WGL_STEREO_ARB                  0x2012
#وصف_ڪريو WGL_PIXEL_TYPE_ARB              0x2013
#وصف_ڪريو WGL_COLOR_بٽ_ARB              0x2014
#وصف_ڪريو WGL_RED_بٽ_ARB                0x2015
#وصف_ڪريو WGL_RED_سرڪايو_ARB               0x2016
#وصف_ڪريو WGL_GREEN_بٽ_ARB              0x2017
#وصف_ڪريو WGL_GREEN_سرڪايو_ARB             0x2018
#وصف_ڪريو WGL_BLUE_بٽ_ARB               0x2019
#وصف_ڪريو WGL_BLUE_سرڪايو_ARB              0x201A
#وصف_ڪريو WGL_ALPHA_بٽ_ARB              0x201B
#وصف_ڪريو WGL_ALPHA_سرڪايو_ARB             0x201C
#وصف_ڪريو WGL_ACCUM_بٽ_ARB              0x201D
#وصف_ڪريو WGL_ACCUM_RED_بٽ_ARB          0x201E
#وصف_ڪريو WGL_ACCUM_GREEN_بٽ_ARB        0x201F
#وصف_ڪريو WGL_ACCUM_BLUE_بٽ_ARB         0x2020
#وصف_ڪريو WGL_ACCUM_ALPHA_بٽ_ARB        0x2021
#وصف_ڪريو WGL_اونهائي_بٽ_ARB              0x2022
#وصف_ڪريو WGL_STENCIL_بٽ_ARB            0x2023
#وصف_ڪريو WGL_AUX_BUFFERS_ARB             0x2024
#وصف_ڪريو WGL_NO_ACCELERATION_ARB         0x2025
#وصف_ڪريو WGL_GENERIC_ACCELERATION_ARB    0x2026
#وصف_ڪريو WGL_ڀريل_ACCELERATION_ARB       0x2027
#وصف_ڪريو WGL_مٽا_سٽا_EXCHANGE_ARB           0x2028
#وصف_ڪريو WGL_مٽا_سٽا_COPY_ARB               0x2029
#وصف_ڪريو WGL_مٽا_سٽا_UNDEFINED_ARB          0x202A
#وصف_ڪريو WGL_TYPE_RGBA_ARB               0x202B
#وصف_ڪريو WGL_TYPE_COLORINDEX_ARB         0x202C
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WGL_ARB_multisample
#وصف_ڪريو WGL_SAMPLE_BUFFERS_ARB 0x2041
#وصف_ڪريو WGL_SAMPLES_ARB        0x2042
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_WGL

#جيڪڏهن_پورو // SDL_windowsopengl_h_
