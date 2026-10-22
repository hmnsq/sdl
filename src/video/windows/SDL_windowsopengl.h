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

#که_نه_تعریف_شوی SDL_windowsopengl_h_
#تعریف_کړه SDL_windowsopengl_h_

#که_تعریف_شوی SDL_VIDEO_OPENGL_WGL

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
تعريفنوع بنية نښان_PIXELFORMATDESCRIPTOR
{
    کلمه n_اندازه;
    کلمه n_نسخه;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_بټونه;
    BYTE c_Red_بټونه;
    BYTE c_Red_ښويدنه;
    BYTE c_Green_بټونه;
    BYTE c_Green_ښويدنه;
    BYTE c_Blue_بټونه;
    BYTE c_Blue_ښويدنه;
    BYTE c_Alpha_بټونه;
    BYTE c_Alpha_ښويدنه;
    BYTE c_Accum_بټونه;
    BYTE c_Accum_Red_بټونه;
    BYTE c_Accum_Green_بټونه;
    BYTE c_Accum_Blue_بټونه;
    BYTE c_Accum_Alpha_بټونه;
    BYTE c_ژوروالی_بټونه;
    BYTE c_Stencil_بټونه;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_ماسک;
    DWORD dw_Visible_ماسک;
    DWORD dw_Damage_ماسک;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#د_که_پای

بنية SDL_GLDriver_معلومات
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_بدلون_control_tear;
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
    PROC (WINAPI *wgl_Get_Proc_پته)(ثابت حرف *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_ټاکنه_Pixel_Format_ARB)(HDC hdc, ثابت صحيح *piAttribIList, ثابت FLOAT * pfAttribFList, UINT nMaxFormats, صحيح *piFormats, UINT * n_عدد_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, صحيح iPixelFormat, صحيح iLayerPlane, UINT n_ځانګړتیاوې, ثابت صحيح *pi_ځانګړتیاوې, صحيح *pi_ارزښتونه);
    BOOL (WINAPI *wgl_بدلون_Interval_EXT)(صحيح interval);
    صحيح (WINAPI *wgl_Get_بدلون_Interval_EXT)(فراغ);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wgl_بدلون_Buffers)(HDC hdc);
    صحيح (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         صحيح iPixelFormat,
                                         UINT n_بایټونه,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    صحيح (WINAPI *wgl_ټاکنه_Pixel_Format)(HDC hdc,
                                       ثابت PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_سېټ_Pixel_Format)(HDC hdc,
                                     صحيح format,
                                     ثابت PIXELFORMATDESCRIPTOR *ppfd);
    صحيح (WINAPI *wglGetPixelFormat)(HDC hdc);
#د_که_پای
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
خارجي bool WIN_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي SDL_Function_اشاره_ګر WIN_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
خارجي bool WIN_GL_تیاری_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ,
                              SDL_GLContext context);
خارجي bool WIN_GL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool WIN_GL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool WIN_GL_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي فراغ WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#که_نه_تعریف_شوی WGL_ARB_pixel_format
#تعریف_کړه WGL_شمېره_PIXEL_FORMATS_ARB    0x2000
#تعریف_کړه WGL_DRAW_منزل_کړکۍ_ARB          0x2001
#تعریف_کړه WGL_DRAW_منزل_BITMAP_ARB          0x2002
#تعریف_کړه WGL_ACCELERATION_ARB            0x2003
#تعریف_کړه WGL_NEED_PALETTE_ARB            0x2004
#تعریف_کړه WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#تعریف_کړه WGL_بدلون_LAYER_BUFFERS_ARB      0x2006
#تعریف_کړه WGL_بدلون_لاره_ARB             0x2007
#تعریف_کړه WGL_شمېره_OVERLAYS_ARB         0x2008
#تعریف_کړه WGL_شمېره_UNDERLAYS_ARB        0x2009
#تعریف_کړه WGL_TRANSPARENT_ARB             0x200A
#تعریف_کړه WGL_TRANSPARENT_RED_ارزښت_ARB   0x2037
#تعریف_کړه WGL_TRANSPARENT_GREEN_ارزښت_ARB 0x2038
#تعریف_کړه WGL_TRANSPARENT_BLUE_ارزښت_ARB  0x2039
#تعریف_کړه WGL_TRANSPARENT_ALPHA_ارزښت_ARB 0x203A
#تعریف_کړه WGL_TRANSPARENT_شاخص_ارزښت_ARB 0x203B
#تعریف_کړه WGL_SHARE_ژوروالی_ARB             0x200C
#تعریف_کړه WGL_SHARE_STENCIL_ARB           0x200D
#تعریف_کړه WGL_SHARE_ACCUM_ARB             0x200E
#تعریف_کړه WGL_SUPPORT_GDI_ARB             0x200F
#تعریف_کړه WGL_SUPPORT_OPENGL_ARB          0x2010
#تعریف_کړه WGL_DOUBLE_بفر_ARB           0x2011
#تعریف_کړه WGL_STEREO_ARB                  0x2012
#تعریف_کړه WGL_PIXEL_TYPE_ARB              0x2013
#تعریف_کړه WGL_COLOR_بټونه_ARB              0x2014
#تعریف_کړه WGL_RED_بټونه_ARB                0x2015
#تعریف_کړه WGL_RED_ښويدنه_ARB               0x2016
#تعریف_کړه WGL_GREEN_بټونه_ARB              0x2017
#تعریف_کړه WGL_GREEN_ښويدنه_ARB             0x2018
#تعریف_کړه WGL_BLUE_بټونه_ARB               0x2019
#تعریف_کړه WGL_BLUE_ښويدنه_ARB              0x201A
#تعریف_کړه WGL_ALPHA_بټونه_ARB              0x201B
#تعریف_کړه WGL_ALPHA_ښويدنه_ARB             0x201C
#تعریف_کړه WGL_ACCUM_بټونه_ARB              0x201D
#تعریف_کړه WGL_ACCUM_RED_بټونه_ARB          0x201E
#تعریف_کړه WGL_ACCUM_GREEN_بټونه_ARB        0x201F
#تعریف_کړه WGL_ACCUM_BLUE_بټونه_ARB         0x2020
#تعریف_کړه WGL_ACCUM_ALPHA_بټونه_ARB        0x2021
#تعریف_کړه WGL_ژوروالی_بټونه_ARB              0x2022
#تعریف_کړه WGL_STENCIL_بټونه_ARB            0x2023
#تعریف_کړه WGL_AUX_BUFFERS_ARB             0x2024
#تعریف_کړه WGL_NO_ACCELERATION_ARB         0x2025
#تعریف_کړه WGL_GENERIC_ACCELERATION_ARB    0x2026
#تعریف_کړه WGL_ډک_ACCELERATION_ARB       0x2027
#تعریف_کړه WGL_بدلون_EXCHANGE_ARB           0x2028
#تعریف_کړه WGL_بدلون_COPY_ARB               0x2029
#تعریف_کړه WGL_بدلون_UNDEFINED_ARB          0x202A
#تعریف_کړه WGL_TYPE_RGBA_ARB               0x202B
#تعریف_کړه WGL_TYPE_COLORINDEX_ARB         0x202C
#د_که_پای

#که_نه_تعریف_شوی WGL_ARB_multisample
#تعریف_کړه WGL_SAMPLE_BUFFERS_ARB 0x2041
#تعریف_کړه WGL_SAMPLES_ARB        0x2042
#د_که_پای

#د_که_پای // SDL_VIDEO_OPENGL_WGL

#د_که_پای // SDL_windowsopengl_h_
