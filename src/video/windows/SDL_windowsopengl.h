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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_windowsopengl_h_
#परिभाषय SDL_windowsopengl_h_

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL

#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
प्रकारनिर्देश संरचना चिह्नकम्_PIXELFORMATDESCRIPTOR
{
    WORD n_आकार;
    WORD n_संस्करणम्;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE c_Color_द्वयङ्काः;
    BYTE c_Red_द्वयङ्काः;
    BYTE c_Red_सरणम्;
    BYTE c_Green_द्वयङ्काः;
    BYTE c_Green_सरणम्;
    BYTE c_Blue_द्वयङ्काः;
    BYTE c_Blue_सरणम्;
    BYTE c_Alpha_द्वयङ्काः;
    BYTE c_Alpha_सरणम्;
    BYTE c_Accum_द्वयङ्काः;
    BYTE c_Accum_Red_द्वयङ्काः;
    BYTE c_Accum_Green_द्वयङ्काः;
    BYTE c_Accum_Blue_द्वयङ्काः;
    BYTE c_Accum_Alpha_द्वयङ्काः;
    BYTE c_गभीरता_द्वयङ्काः;
    BYTE c_Stencil_द्वयङ्काः;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dw_Layer_आवरणम्;
    DWORD dw_Visible_आवरणम्;
    DWORD dw_Damage_आवरणम्;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;
#यदि_अन्तः

संरचना SDL_GLDriver_दत्त
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
    संरचना
    {
        पूर्णाङ्क major;
        पूर्णाङ्क minor;
    } es_profile_max_supported_संस्करणम्;

    /* *INDENT-OFF* */ // clang-format off
    PROC (WINAPI *wgl_Get_Proc_स्थानाङ्कः)(ध्रुव वर्ण *proc);
    HGLRC (WINAPI *wglCreateContext)(HDC hdc);
    BOOL (WINAPI *wglDeleteContext)(HGLRC hglrc);
    BOOL (WINAPI *wglMakeCurrent)(HDC hdc, HGLRC hglrc);
    BOOL (WINAPI *wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
    BOOL (WINAPI *wgl_वृणु_Pixel_Format_ARB)(HDC hdc, ध्रुव पूर्णाङ्क *piAttribIList, ध्रुव FLOAT * pfAttribFList, UINT nMaxFormats, पूर्णाङ्क *piFormats, UINT * n_अङ्कः_Formats);
    BOOL (WINAPI *wglGetPixelFormatAttribivARB)(HDC hdc, पूर्णाङ्क iPixelFormat, पूर्णाङ्क iLayerPlane, UINT n_गुणाः, ध्रुव पूर्णाङ्क *pi_गुणाः, पूर्णाङ्क *pi_मानानि);
    BOOL (WINAPI *wglSwapIntervalEXT)(पूर्णाङ्क interval);
    पूर्णाङ्क (WINAPI *wglGetSwapIntervalEXT)(शून्य);
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    BOOL (WINAPI *wglSwapBuffers)(HDC hdc);
    पूर्णाङ्क (WINAPI *wglDescribePixelFormat)(HDC hdc,
                                         पूर्णाङ्क iPixelFormat,
                                         UINT n_अष्टकानि,
                                         LPPIXELFORMATDESCRIPTOR ppfd);
    पूर्णाङ्क (WINAPI *wgl_वृणु_Pixel_Format)(HDC hdc,
                                       ध्रुव PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (WINAPI *wgl_समुच्चयः_Pixel_Format)(HDC hdc,
                                     पूर्णाङ्क format,
                                     ध्रुव PIXELFORMATDESCRIPTOR *ppfd);
    पूर्णाङ्क (WINAPI *wglGetPixelFormat)(HDC hdc);
#यदि_अन्तः
    /* *INDENT-ON* */ // clang-format on
};

// OpenGL functions
बाह्य bool WIN_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य SDL_FunctionPointer WIN_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य शून्य WIN_GL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य bool WIN_GL_UseEGL(SDL_VideoDevice *_this);
बाह्य bool WIN_GL_सज्जता_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_GLContext WIN_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool WIN_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः,
                              SDL_GLContext context);
बाह्य bool WIN_GL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval);
बाह्य bool WIN_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
बाह्य bool WIN_GL_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool WIN_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य शून्य WIN_GL_InitExtensions(SDL_VideoDevice *_this);

#यदि_अपरिभाषितम् WGL_ARB_pixel_format
#परिभाषय WGL_सङ्ख्या_PIXEL_FORMATS_ARB    0x2000
#परिभाषय WGL_DRAW_गन्तव्यम्_गवाक्षः_ARB          0x2001
#परिभाषय WGL_DRAW_गन्तव्यम्_BITMAP_ARB          0x2002
#परिभाषय WGL_ACCELERATION_ARB            0x2003
#परिभाषय WGL_NEED_PALETTE_ARB            0x2004
#परिभाषय WGL_NEED_SYSTEM_PALETTE_ARB     0x2005
#परिभाषय WGL_SWAP_LAYER_BUFFERS_ARB      0x2006
#परिभाषय WGL_SWAP_विधानम्_ARB             0x2007
#परिभाषय WGL_सङ्ख्या_OVERLAYS_ARB         0x2008
#परिभाषय WGL_सङ्ख्या_UNDERLAYS_ARB        0x2009
#परिभाषय WGL_TRANSPARENT_ARB             0x200A
#परिभाषय WGL_TRANSPARENT_RED_मानम्_ARB   0x2037
#परिभाषय WGL_TRANSPARENT_GREEN_मानम्_ARB 0x2038
#परिभाषय WGL_TRANSPARENT_BLUE_मानम्_ARB  0x2039
#परिभाषय WGL_TRANSPARENT_ALPHA_मानम्_ARB 0x203A
#परिभाषय WGL_TRANSPARENT_सूचकांक_मानम्_ARB 0x203B
#परिभाषय WGL_SHARE_गभीरता_ARB             0x200C
#परिभाषय WGL_SHARE_STENCIL_ARB           0x200D
#परिभाषय WGL_SHARE_ACCUM_ARB             0x200E
#परिभाषय WGL_SUPPORT_GDI_ARB             0x200F
#परिभाषय WGL_SUPPORT_OPENGL_ARB          0x2010
#परिभाषय WGL_DOUBLE_बफर_ARB           0x2011
#परिभाषय WGL_STEREO_ARB                  0x2012
#परिभाषय WGL_PIXEL_TYPE_ARB              0x2013
#परिभाषय WGL_COLOR_द्वयङ्काः_ARB              0x2014
#परिभाषय WGL_RED_द्वयङ्काः_ARB                0x2015
#परिभाषय WGL_RED_सरणम्_ARB               0x2016
#परिभाषय WGL_GREEN_द्वयङ्काः_ARB              0x2017
#परिभाषय WGL_GREEN_सरणम्_ARB             0x2018
#परिभाषय WGL_BLUE_द्वयङ्काः_ARB               0x2019
#परिभाषय WGL_BLUE_सरणम्_ARB              0x201A
#परिभाषय WGL_ALPHA_द्वयङ्काः_ARB              0x201B
#परिभाषय WGL_ALPHA_सरणम्_ARB             0x201C
#परिभाषय WGL_ACCUM_द्वयङ्काः_ARB              0x201D
#परिभाषय WGL_ACCUM_RED_द्वयङ्काः_ARB          0x201E
#परिभाषय WGL_ACCUM_GREEN_द्वयङ्काः_ARB        0x201F
#परिभाषय WGL_ACCUM_BLUE_द्वयङ्काः_ARB         0x2020
#परिभाषय WGL_ACCUM_ALPHA_द्वयङ्काः_ARB        0x2021
#परिभाषय WGL_गभीरता_द्वयङ्काः_ARB              0x2022
#परिभाषय WGL_STENCIL_द्वयङ्काः_ARB            0x2023
#परिभाषय WGL_AUX_BUFFERS_ARB             0x2024
#परिभाषय WGL_NO_ACCELERATION_ARB         0x2025
#परिभाषय WGL_GENERIC_ACCELERATION_ARB    0x2026
#परिभाषय WGL_पूर्णम्_ACCELERATION_ARB       0x2027
#परिभाषय WGL_SWAP_EXCHANGE_ARB           0x2028
#परिभाषय WGL_SWAP_COPY_ARB               0x2029
#परिभाषय WGL_SWAP_UNDEFINED_ARB          0x202A
#परिभाषय WGL_TYPE_RGBA_ARB               0x202B
#परिभाषय WGL_TYPE_COLORINDEX_ARB         0x202C
#यदि_अन्तः

#यदि_अपरिभाषितम् WGL_ARB_multisample
#परिभाषय WGL_SAMPLE_BUFFERS_ARB 0x2041
#परिभाषय WGL_SAMPLES_ARB        0x2042
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_OPENGL_WGL

#यदि_अन्तः // SDL_windowsopengl_h_
