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

#నిర్వచితం_కాకపోతే SDL_windowsopengl_h_
#నిర్వచించు SDL_windowsopengl_h_

#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
రకనిర్వచనం నిర్మాణం ట్యాగ్_PIXELFORMATDESCRIPTOR
{
    మాట n_కొలత;
    మాట n_సంస్కరణ;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_బిట్లు;
    BYTE c_Red_బిట్లు;
    BYTE c_Red_జరుపు;
    BYTE c_Green_బిట్లు;
    BYTE c_Green_జరుపు;
    BYTE c_Blue_బిట్లు;
    BYTE c_Blue_జరుపు;
    BYTE c_Alpha_బిట్లు;
    BYTE c_Alpha_జరుపు;
    BYTE c_Accum_బిట్లు;
    BYTE c_Accum_Red_బిట్లు;
    BYTE c_Accum_Green_బిట్లు;
    BYTE c_Accum_Blue_బిట్లు;
    BYTE c_Accum_Alpha_బిట్లు;
    BYTE c_లోతు_బిట్లు;
    BYTE c_Stencil_బిట్లు;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_ముసుగు;
    DWORD dw_Visible_ముసుగు;
    DWORD dw_Damage_ముసుగు;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#అయితే_ముగింపు

నిర్మాణం SDL_GLDriver_దత్తాంశం
{
    bool HAS_WGL_ARB_pixel_format;
    bool HAS_WGL_EXT_మార్పిడి_control_tear;
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
    నిర్మాణం
    {
        పూర్ణాంకం major;
        పూర్ణాంకం minor;
    } es_profile_max_supported_సంస్కరణ;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wgl_Get_Proc_చిరునామా)(స్థిరరాశి అక్షరం *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_ఎంచుకో_Pixel_Format_ARB)(HDC hdc, స్థిరరాశి పూర్ణాంకం *piAttribIList, స్థిరరాశి FLOAT * pfAttribFList, UINT nMaxFormats, పూర్ణాంకం *piFormats, UINT * n_అంకె_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, పూర్ణాంకం iPixelFormat, పూర్ణాంకం iLayerPlane, UINT n_లక్షణాలు, స్థిరరాశి పూర్ణాంకం *pi_లక్షణాలు, పూర్ణాంకం *pi_విలువలు);
    BOOL (WINAPI *wgl_మార్పిడి_Interval_EXT)(పూర్ణాంకం interval);
    పూర్ణాంకం (WINAPI *wgl_Get_మార్పిడి_Interval_EXT)(శూన్య);
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wgl_మార్పిడి_Buffers)(HDC hdc);
    పూర్ణాంకం (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         పూర్ణాంకం iPixelFormat,
                                         UINT n_బైట్లు,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    పూర్ణాంకం (WINAPI *wgl_ఎంచుకో_Pixel_Format)(HDC hdc,
                                       స్థిరరాశి PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_సమితి_Pixel_Format)(HDC hdc,
                                     పూర్ణాంకం format,
                                     స్థిరరాశి PIXELFORMATDESCRIPTOR *ppfd);
    పూర్ణాంకం (WINAPI *wglGetPixelFormat)(HDC hdc);
#అయితే_ముగింపు
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
బాహ్య bool WIN_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_Function_సూచిక WIN_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య శూన్య WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
బాహ్య bool WIN_GL_అమరిక_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ,
                              SDL_GLContext context);
బాహ్య bool WIN_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool WIN_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
బాహ్య bool WIN_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
బాహ్య శూన్య WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#నిర్వచితం_కాకపోతే WGL_ARB_pixel_format
#నిర్వచించు WGL_సంఖ్య_PIXEL_FORMATS_ARB    0x2000
#నిర్వచించు WGL_DRAW_గమ్యం_కిటికీ_ARB          0x2001
#నిర్వచించు WGL_DRAW_గమ్యం_BITMAP_ARB          0x2002
#నిర్వచించు WGL_ACCELERATION_ARB            0x2003
#నిర్వచించు WGL_NEED_PALETTE_ARB            0x2004
#నిర్వచించు WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#నిర్వచించు WGL_మార్పిడి_LAYER_BUFFERS_ARB      0x2006
#నిర్వచించు WGL_మార్పిడి_పద్ధతి_ARB             0x2007
#నిర్వచించు WGL_సంఖ్య_OVERLAYS_ARB         0x2008
#నిర్వచించు WGL_సంఖ్య_UNDERLAYS_ARB        0x2009
#నిర్వచించు WGL_TRANSPARENT_ARB             0x200A
#నిర్వచించు WGL_TRANSPARENT_RED_విలువ_ARB   0x2037
#నిర్వచించు WGL_TRANSPARENT_GREEN_విలువ_ARB 0x2038
#నిర్వచించు WGL_TRANSPARENT_BLUE_విలువ_ARB  0x2039
#నిర్వచించు WGL_TRANSPARENT_ALPHA_విలువ_ARB 0x203A
#నిర్వచించు WGL_TRANSPARENT_సూచీ_విలువ_ARB 0x203B
#నిర్వచించు WGL_SHARE_లోతు_ARB             0x200C
#నిర్వచించు WGL_SHARE_STENCIL_ARB           0x200D
#నిర్వచించు WGL_SHARE_ACCUM_ARB             0x200E
#నిర్వచించు WGL_SUPPORT_GDI_ARB             0x200F
#నిర్వచించు WGL_SUPPORT_OPENGL_ARB          0x2010
#నిర్వచించు WGL_DOUBLE_బఫరు_ARB           0x2011
#నిర్వచించు WGL_STEREO_ARB                  0x2012
#నిర్వచించు WGL_PIXEL_TYPE_ARB              0x2013
#నిర్వచించు WGL_COLOR_బిట్లు_ARB              0x2014
#నిర్వచించు WGL_RED_బిట్లు_ARB                0x2015
#నిర్వచించు WGL_RED_జరుపు_ARB               0x2016
#నిర్వచించు WGL_GREEN_బిట్లు_ARB              0x2017
#నిర్వచించు WGL_GREEN_జరుపు_ARB             0x2018
#నిర్వచించు WGL_BLUE_బిట్లు_ARB               0x2019
#నిర్వచించు WGL_BLUE_జరుపు_ARB              0x201A
#నిర్వచించు WGL_ALPHA_బిట్లు_ARB              0x201B
#నిర్వచించు WGL_ALPHA_జరుపు_ARB             0x201C
#నిర్వచించు WGL_ACCUM_బిట్లు_ARB              0x201D
#నిర్వచించు WGL_ACCUM_RED_బిట్లు_ARB          0x201E
#నిర్వచించు WGL_ACCUM_GREEN_బిట్లు_ARB        0x201F
#నిర్వచించు WGL_ACCUM_BLUE_బిట్లు_ARB         0x2020
#నిర్వచించు WGL_ACCUM_ALPHA_బిట్లు_ARB        0x2021
#నిర్వచించు WGL_లోతు_బిట్లు_ARB              0x2022
#నిర్వచించు WGL_STENCIL_బిట్లు_ARB            0x2023
#నిర్వచించు WGL_AUX_BUFFERS_ARB             0x2024
#నిర్వచించు WGL_NO_ACCELERATION_ARB         0x2025
#నిర్వచించు WGL_GENERIC_ACCELERATION_ARB    0x2026
#నిర్వచించు WGL_నిండిన_ACCELERATION_ARB       0x2027
#నిర్వచించు WGL_మార్పిడి_EXCHANGE_ARB           0x2028
#నిర్వచించు WGL_మార్పిడి_COPY_ARB               0x2029
#నిర్వచించు WGL_మార్పిడి_UNDEFINED_ARB          0x202A
#నిర్వచించు WGL_TYPE_RGBA_ARB               0x202B
#నిర్వచించు WGL_TYPE_COLORINDEX_ARB         0x202C
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WGL_ARB_multisample
#నిర్వచించు WGL_SAMPLE_BUFFERS_ARB 0x2041
#నిర్వచించు WGL_SAMPLES_ARB        0x2042
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_WGL

#అయితే_ముగింపు // SDL_windowsopengl_h_
