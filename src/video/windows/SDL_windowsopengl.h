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

#اگر_تعریف_نشده SDL_windowsopengl_h_
#تعریف_کن SDL_windowsopengl_h_

#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
تعريفنوع بنية برچسب_PIXELFORMATDESCRIPTOR
{
    کلمه n_اندازه;
    کلمه n_نسخه;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_بیتها;
    BYTE c_Red_بیتها;
    BYTE c_Red_لغزش;
    BYTE c_Green_بیتها;
    BYTE c_Green_لغزش;
    BYTE c_Blue_بیتها;
    BYTE c_Blue_لغزش;
    BYTE c_Alpha_بیتها;
    BYTE c_Alpha_لغزش;
    BYTE c_Accum_بیتها;
    BYTE c_Accum_Red_بیتها;
    BYTE c_Accum_Green_بیتها;
    BYTE c_Accum_Blue_بیتها;
    BYTE c_Accum_Alpha_بیتها;
    BYTE c_عمق_بیتها;
    BYTE c_Stencil_بیتها;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_ماسک;
    DWORD dw_Visible_ماسک;
    DWORD dw_Damage_ماسک;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#پایان_اگر

بنية SDL_GLDriver_داده
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_جابجا_control_tear;
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
    } es_profile_max_supported_نسخه;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wgl_Get_Proc_آدرس)(ثابت حرف *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_انتخاب_Pixel_Format_ARB)(HDC hdc, ثابت صحيح *piAttribIList, ثابت FLOAT * pfAttribFList, UINT nMaxFormats, صحيح *piFormats, UINT * n_رقم_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, صحيح iPixelFormat, صحيح iLayerPlane, UINT n_صفات, ثابت صحيح *pi_صفات, صحيح *pi_مقادیر);
    BOOL (WINAPI *wgl_جابجا_Interval_EXT)(صحيح interval);
    صحيح (WINAPI *wgl_Get_جابجا_Interval_EXT)(فراغ);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wgl_جابجا_Buffers)(HDC hdc);
    صحيح (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         صحيح iPixelFormat,
                                         UINT n_بایتها,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    صحيح (WINAPI *wgl_انتخاب_Pixel_Format)(HDC hdc,
                                       ثابت PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_مجموعه_Pixel_Format)(HDC hdc,
                                     صحيح format,
                                     ثابت PIXELFORMATDESCRIPTOR *ppfd);
    صحيح (WINAPI *wglGetPixelFormat)(HDC hdc);
#پایان_اگر
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
خارجي bool WIN_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر);
خارجي SDL_Function_اشاره_گر WIN_GL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
خارجي bool WIN_GL_راهاندازی_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره,
                              SDL_GLContext context);
خارجي bool WIN_GL_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool WIN_GL_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool WIN_GL_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي فراغ WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#اگر_تعریف_نشده WGL_ARB_pixel_format
#تعریف_کن WGL_عدد_PIXEL_FORMATS_ARB    0x2000
#تعریف_کن WGL_DRAW_مقصد_پنجره_ARB          0x2001
#تعریف_کن WGL_DRAW_مقصد_BITMAP_ARB          0x2002
#تعریف_کن WGL_ACCELERATION_ARB            0x2003
#تعریف_کن WGL_NEED_PALETTE_ARB            0x2004
#تعریف_کن WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#تعریف_کن WGL_جابجا_LAYER_BUFFERS_ARB      0x2006
#تعریف_کن WGL_جابجا_روش_ARB             0x2007
#تعریف_کن WGL_عدد_OVERLAYS_ARB         0x2008
#تعریف_کن WGL_عدد_UNDERLAYS_ARB        0x2009
#تعریف_کن WGL_TRANSPARENT_ARB             0x200A
#تعریف_کن WGL_TRANSPARENT_RED_مقدار_ARB   0x2037
#تعریف_کن WGL_TRANSPARENT_GREEN_مقدار_ARB 0x2038
#تعریف_کن WGL_TRANSPARENT_BLUE_مقدار_ARB  0x2039
#تعریف_کن WGL_TRANSPARENT_ALPHA_مقدار_ARB 0x203A
#تعریف_کن WGL_TRANSPARENT_شاخص_مقدار_ARB 0x203B
#تعریف_کن WGL_SHARE_عمق_ARB             0x200C
#تعریف_کن WGL_SHARE_STENCIL_ARB           0x200D
#تعریف_کن WGL_SHARE_ACCUM_ARB             0x200E
#تعریف_کن WGL_SUPPORT_GDI_ARB             0x200F
#تعریف_کن WGL_SUPPORT_OPENGL_ARB          0x2010
#تعریف_کن WGL_DOUBLE_میانگیر_ARB           0x2011
#تعریف_کن WGL_STEREO_ARB                  0x2012
#تعریف_کن WGL_PIXEL_TYPE_ARB              0x2013
#تعریف_کن WGL_COLOR_بیتها_ARB              0x2014
#تعریف_کن WGL_RED_بیتها_ARB                0x2015
#تعریف_کن WGL_RED_لغزش_ARB               0x2016
#تعریف_کن WGL_GREEN_بیتها_ARB              0x2017
#تعریف_کن WGL_GREEN_لغزش_ARB             0x2018
#تعریف_کن WGL_BLUE_بیتها_ARB               0x2019
#تعریف_کن WGL_BLUE_لغزش_ARB              0x201A
#تعریف_کن WGL_ALPHA_بیتها_ARB              0x201B
#تعریف_کن WGL_ALPHA_لغزش_ARB             0x201C
#تعریف_کن WGL_ACCUM_بیتها_ARB              0x201D
#تعریف_کن WGL_ACCUM_RED_بیتها_ARB          0x201E
#تعریف_کن WGL_ACCUM_GREEN_بیتها_ARB        0x201F
#تعریف_کن WGL_ACCUM_BLUE_بیتها_ARB         0x2020
#تعریف_کن WGL_ACCUM_ALPHA_بیتها_ARB        0x2021
#تعریف_کن WGL_عمق_بیتها_ARB              0x2022
#تعریف_کن WGL_STENCIL_بیتها_ARB            0x2023
#تعریف_کن WGL_AUX_BUFFERS_ARB             0x2024
#تعریف_کن WGL_NO_ACCELERATION_ARB         0x2025
#تعریف_کن WGL_GENERIC_ACCELERATION_ARB    0x2026
#تعریف_کن WGL_پر_ACCELERATION_ARB       0x2027
#تعریف_کن WGL_جابجا_EXCHANGE_ARB           0x2028
#تعریف_کن WGL_جابجا_COPY_ARB               0x2029
#تعریف_کن WGL_جابجا_UNDEFINED_ARB          0x202A
#تعریف_کن WGL_TYPE_RGBA_ARB               0x202B
#تعریف_کن WGL_TYPE_COLORINDEX_ARB         0x202C
#پایان_اگر

#اگر_تعریف_نشده WGL_ARB_multisample
#تعریف_کن WGL_SAMPLE_BUFFERS_ARB 0x2041
#تعریف_کن WGL_SAMPLES_ARB        0x2042
#پایان_اگر

#پایان_اگر // SDL_VIDEO_OPENGL_WGL

#پایان_اگر // SDL_windowsopengl_h_
