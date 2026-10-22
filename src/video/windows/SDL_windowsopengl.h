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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_windowsopengl_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_windowsopengl_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಟ್ಯಾಗ್_PIXELFORMATDESCRIPTOR
{
    ಶಬ್ದ n_ಗಾತ್ರ;
    ಶಬ್ದ n_ಆವೃತ್ತಿ;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_ಬಿಟ್ಟುಗಳು;
    BYTE c_Red_ಬಿಟ್ಟುಗಳು;
    BYTE c_Red_ಸರಿಸು;
    BYTE c_Green_ಬಿಟ್ಟುಗಳು;
    BYTE c_Green_ಸರಿಸು;
    BYTE c_Blue_ಬಿಟ್ಟುಗಳು;
    BYTE c_Blue_ಸರಿಸು;
    BYTE c_Alpha_ಬಿಟ್ಟುಗಳು;
    BYTE c_Alpha_ಸರಿಸು;
    BYTE c_Accum_ಬಿಟ್ಟುಗಳು;
    BYTE c_Accum_Red_ಬಿಟ್ಟುಗಳು;
    BYTE c_Accum_Green_ಬಿಟ್ಟುಗಳು;
    BYTE c_Accum_Blue_ಬಿಟ್ಟುಗಳು;
    BYTE c_Accum_Alpha_ಬಿಟ್ಟುಗಳು;
    BYTE c_ಆಳ_ಬಿಟ್ಟುಗಳು;
    BYTE c_Stencil_ಬಿಟ್ಟುಗಳು;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_ಮುಖವಾಡ;
    DWORD dw_Visible_ಮುಖವಾಡ;
    DWORD dw_Damage_ಮುಖವಾಡ;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#ಆದರೆ_ಅಂತ್ಯ

ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_ಅದಲುಬದಲು_control_tear;
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
    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ major;
        ಪೂರ್ಣಾಂಕ minor;
    } es_profile_max_supported_ಆವೃತ್ತಿ;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wgl_Get_Proc_ವಿಳಾಸ)(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_ಆರಿಸು_Pixel_Format_ARB)(HDC hdc, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *piAttribIList, ಸ್ಥಿರಾಂಕ FLOAT * pfAttribFList, UINT nMaxFormats, ಪೂರ್ಣಾಂಕ *piFormats, UINT * n_ಅಂಕೆ_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, ಪೂರ್ಣಾಂಕ iPixelFormat, ಪೂರ್ಣಾಂಕ iLayerPlane, UINT n_ಗುಣಲಕ್ಷಣಗಳು, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *pi_ಗುಣಲಕ್ಷಣಗಳು, ಪೂರ್ಣಾಂಕ *pi_ಮೌಲ್ಯಗಳು);
    BOOL (WINAPI *wgl_ಅದಲುಬದಲು_Interval_EXT)(ಪೂರ್ಣಾಂಕ interval);
    ಪೂರ್ಣಾಂಕ (WINAPI *wgl_Get_ಅದಲುಬದಲು_Interval_EXT)(ಶೂನ್ಯ);
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wgl_ಅದಲುಬದಲು_Buffers)(HDC hdc);
    ಪೂರ್ಣಾಂಕ (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         ಪೂರ್ಣಾಂಕ iPixelFormat,
                                         UINT n_ಬೈಟುಗಳು,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    ಪೂರ್ಣಾಂಕ (WINAPI *wgl_ಆರಿಸು_Pixel_Format)(HDC hdc,
                                       ಸ್ಥಿರಾಂಕ PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_ಗಣ_Pixel_Format)(HDC hdc,
                                     ಪೂರ್ಣಾಂಕ format,
                                     ಸ್ಥಿರಾಂಕ PIXELFORMATDESCRIPTOR *ppfd);
    ಪೂರ್ಣಾಂಕ (WINAPI *wglGetPixelFormat)(HDC hdc);
#ಆದರೆ_ಅಂತ್ಯ
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
ಬಾಹ್ಯ bool WIN_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ WIN_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool WIN_GL_ಸಿದ್ಧತೆ_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                              SDL_GLContext context);
ಬಾಹ್ಯ bool WIN_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
ಬಾಹ್ಯ bool WIN_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);
ಬಾಹ್ಯ bool WIN_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_pixel_format
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಸಂಖ್ಯೆ_PIXEL_FORMATS_ARB    0x2000
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_DRAW_ಗಮ್ಯ_ಕಿಟಕಿ_ARB          0x2001
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_DRAW_ಗಮ್ಯ_BITMAP_ARB          0x2002
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ACCELERATION_ARB            0x2003
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_NEED_PALETTE_ARB            0x2004
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಅದಲುಬದಲು_LAYER_BUFFERS_ARB      0x2006
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಅದಲುಬದಲು_ವಿಧಾನ_ARB             0x2007
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಸಂಖ್ಯೆ_OVERLAYS_ARB         0x2008
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಸಂಖ್ಯೆ_UNDERLAYS_ARB        0x2009
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TRANSPARENT_ARB             0x200A
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TRANSPARENT_RED_ಮೌಲ್ಯ_ARB   0x2037
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TRANSPARENT_GREEN_ಮೌಲ್ಯ_ARB 0x2038
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TRANSPARENT_BLUE_ಮೌಲ್ಯ_ARB  0x2039
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TRANSPARENT_ALPHA_ಮೌಲ್ಯ_ARB 0x203A
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TRANSPARENT_ಸೂಚ್ಯಂಕ_ಮೌಲ್ಯ_ARB 0x203B
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_SHARE_ಆಳ_ARB             0x200C
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_SHARE_STENCIL_ARB           0x200D
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_SHARE_ACCUM_ARB             0x200E
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_SUPPORT_GDI_ARB             0x200F
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_SUPPORT_OPENGL_ARB          0x2010
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_DOUBLE_ಬಫರ್_ARB           0x2011
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_STEREO_ARB                  0x2012
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_PIXEL_TYPE_ARB              0x2013
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_COLOR_ಬಿಟ್ಟುಗಳು_ARB              0x2014
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_RED_ಬಿಟ್ಟುಗಳು_ARB                0x2015
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_RED_ಸರಿಸು_ARB               0x2016
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_GREEN_ಬಿಟ್ಟುಗಳು_ARB              0x2017
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_GREEN_ಸರಿಸು_ARB             0x2018
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_BLUE_ಬಿಟ್ಟುಗಳು_ARB               0x2019
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_BLUE_ಸರಿಸು_ARB              0x201A
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ALPHA_ಬಿಟ್ಟುಗಳು_ARB              0x201B
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ALPHA_ಸರಿಸು_ARB             0x201C
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ACCUM_ಬಿಟ್ಟುಗಳು_ARB              0x201D
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ACCUM_RED_ಬಿಟ್ಟುಗಳು_ARB          0x201E
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ACCUM_GREEN_ಬಿಟ್ಟುಗಳು_ARB        0x201F
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ACCUM_BLUE_ಬಿಟ್ಟುಗಳು_ARB         0x2020
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ACCUM_ALPHA_ಬಿಟ್ಟುಗಳು_ARB        0x2021
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಆಳ_ಬಿಟ್ಟುಗಳು_ARB              0x2022
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_STENCIL_ಬಿಟ್ಟುಗಳು_ARB            0x2023
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_AUX_BUFFERS_ARB             0x2024
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_NO_ACCELERATION_ARB         0x2025
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_GENERIC_ACCELERATION_ARB    0x2026
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ತುಂಬಿದ_ACCELERATION_ARB       0x2027
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಅದಲುಬದಲು_EXCHANGE_ARB           0x2028
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಅದಲುಬದಲು_COPY_ARB               0x2029
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_ಅದಲುಬದಲು_UNDEFINED_ARB          0x202A
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TYPE_RGBA_ARB               0x202B
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_TYPE_COLORINDEX_ARB         0x202C
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WGL_ARB_multisample
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_SAMPLE_BUFFERS_ARB 0x2041
#ವ್ಯಾಖ್ಯಾನಿಸು WGL_SAMPLES_ARB        0x2042
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_WGL

#ಆದರೆ_ಅಂತ್ಯ // SDL_windowsopengl_h_
