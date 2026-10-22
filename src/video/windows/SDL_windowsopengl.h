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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_windowsopengl_h_
#تعریف_کرو SDL_windowsopengl_h_

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
قسمتعریف ساخت لیبل_PIXELFORMATDESCRIPTOR
{
    لفظ n_سائز;
    لفظ n_نسخہ;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_بٹ;
    BYTE c_Red_بٹ;
    BYTE c_Red_سرکاؤ;
    BYTE c_Green_بٹ;
    BYTE c_Green_سرکاؤ;
    BYTE c_Blue_بٹ;
    BYTE c_Blue_سرکاؤ;
    BYTE c_Alpha_بٹ;
    BYTE c_Alpha_سرکاؤ;
    BYTE c_Accum_بٹ;
    BYTE c_Accum_Red_بٹ;
    BYTE c_Accum_Green_بٹ;
    BYTE c_Accum_Blue_بٹ;
    BYTE c_Accum_Alpha_بٹ;
    BYTE c_گہرائی_بٹ;
    BYTE c_Stencil_بٹ;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_نقاب;
    DWORD dw_Visible_نقاب;
    DWORD dw_Damage_نقاب;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#اگر_ختم

ساخت SDL_GLDriver_ڈیٹا
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_تبادلہ_control_tear;
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
    ساخت
    {
        صحیح major;
        صحیح minor;
    } es_profile_max_supported_نسخہ;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wgl_Get_Proc_پتہ)(ثابت حرف *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_انتخاب_Pixel_Format_ARB)(HDC hdc, ثابت صحیح *piAttribIList, ثابت FLOAT * pfAttribFList, UINT nMaxFormats, صحیح *piFormats, UINT * n_عدد_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, صحیح iPixelFormat, صحیح iLayerPlane, UINT n_اوصاف, ثابت صحیح *pi_اوصاف, صحیح *pi_اقدار);
    BOOL (WINAPI *wgl_تبادلہ_Interval_EXT)(صحیح interval);
    صحیح (WINAPI *wgl_Get_تبادلہ_Interval_EXT)(خالی);
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wgl_تبادلہ_Buffers)(HDC hdc);
    صحیح (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         صحیح iPixelFormat,
                                         UINT n_بائٹیں,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    صحیح (WINAPI *wgl_انتخاب_Pixel_Format)(HDC hdc,
                                       ثابت PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_سیٹ_Pixel_Format)(HDC hdc,
                                     صحیح format,
                                     ثابت PIXELFORMATDESCRIPTOR *ppfd);
    صحیح (WINAPI *wglGetPixelFormat)(HDC hdc);
#اگر_ختم
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
خارجی bool WIN_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_Function_اشارہ_گر WIN_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی خالی WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجی bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
خارجی bool WIN_GL_تیاری_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                              SDL_GLContext context);
خارجی bool WIN_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool WIN_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);
خارجی bool WIN_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجی خالی WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#اگر_غیر_تعریف_شدہ WGL_ARB_pixel_format
#تعریف_کرو WGL_نمبر_PIXEL_FORMATS_ARB    0x2000
#تعریف_کرو WGL_DRAW_مقصد_کھڑکی_ARB          0x2001
#تعریف_کرو WGL_DRAW_مقصد_BITMAP_ARB          0x2002
#تعریف_کرو WGL_ACCELERATION_ARB            0x2003
#تعریف_کرو WGL_NEED_PALETTE_ARB            0x2004
#تعریف_کرو WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#تعریف_کرو WGL_تبادلہ_LAYER_BUFFERS_ARB      0x2006
#تعریف_کرو WGL_تبادلہ_طریقہ_ARB             0x2007
#تعریف_کرو WGL_نمبر_OVERLAYS_ARB         0x2008
#تعریف_کرو WGL_نمبر_UNDERLAYS_ARB        0x2009
#تعریف_کرو WGL_TRANSPARENT_ARB             0x200A
#تعریف_کرو WGL_TRANSPARENT_RED_قدر_ARB   0x2037
#تعریف_کرو WGL_TRANSPARENT_GREEN_قدر_ARB 0x2038
#تعریف_کرو WGL_TRANSPARENT_BLUE_قدر_ARB  0x2039
#تعریف_کرو WGL_TRANSPARENT_ALPHA_قدر_ARB 0x203A
#تعریف_کرو WGL_TRANSPARENT_اشاریہ_قدر_ARB 0x203B
#تعریف_کرو WGL_SHARE_گہرائی_ARB             0x200C
#تعریف_کرو WGL_SHARE_STENCIL_ARB           0x200D
#تعریف_کرو WGL_SHARE_ACCUM_ARB             0x200E
#تعریف_کرو WGL_SUPPORT_GDI_ARB             0x200F
#تعریف_کرو WGL_SUPPORT_OPENGL_ARB          0x2010
#تعریف_کرو WGL_DOUBLE_بفر_ARB           0x2011
#تعریف_کرو WGL_STEREO_ARB                  0x2012
#تعریف_کرو WGL_PIXEL_TYPE_ARB              0x2013
#تعریف_کرو WGL_COLOR_بٹ_ARB              0x2014
#تعریف_کرو WGL_RED_بٹ_ARB                0x2015
#تعریف_کرو WGL_RED_سرکاؤ_ARB               0x2016
#تعریف_کرو WGL_GREEN_بٹ_ARB              0x2017
#تعریف_کرو WGL_GREEN_سرکاؤ_ARB             0x2018
#تعریف_کرو WGL_BLUE_بٹ_ARB               0x2019
#تعریف_کرو WGL_BLUE_سرکاؤ_ARB              0x201A
#تعریف_کرو WGL_ALPHA_بٹ_ARB              0x201B
#تعریف_کرو WGL_ALPHA_سرکاؤ_ARB             0x201C
#تعریف_کرو WGL_ACCUM_بٹ_ARB              0x201D
#تعریف_کرو WGL_ACCUM_RED_بٹ_ARB          0x201E
#تعریف_کرو WGL_ACCUM_GREEN_بٹ_ARB        0x201F
#تعریف_کرو WGL_ACCUM_BLUE_بٹ_ARB         0x2020
#تعریف_کرو WGL_ACCUM_ALPHA_بٹ_ARB        0x2021
#تعریف_کرو WGL_گہرائی_بٹ_ARB              0x2022
#تعریف_کرو WGL_STENCIL_بٹ_ARB            0x2023
#تعریف_کرو WGL_AUX_BUFFERS_ARB             0x2024
#تعریف_کرو WGL_NO_ACCELERATION_ARB         0x2025
#تعریف_کرو WGL_GENERIC_ACCELERATION_ARB    0x2026
#تعریف_کرو WGL_بھرا_ACCELERATION_ARB       0x2027
#تعریف_کرو WGL_تبادلہ_EXCHANGE_ARB           0x2028
#تعریف_کرو WGL_تبادلہ_COPY_ARB               0x2029
#تعریف_کرو WGL_تبادلہ_UNDEFINED_ARB          0x202A
#تعریف_کرو WGL_TYPE_RGBA_ARB               0x202B
#تعریف_کرو WGL_TYPE_COLORINDEX_ARB         0x202C
#اگر_ختم

#اگر_غیر_تعریف_شدہ WGL_ARB_multisample
#تعریف_کرو WGL_SAMPLE_BUFFERS_ARB 0x2041
#تعریف_کرو WGL_SAMPLES_ARB        0x2042
#اگر_ختم

#اگر_ختم // SDL_VIDEO_OPENGL_WGL

#اگر_ختم // SDL_windowsopengl_h_
