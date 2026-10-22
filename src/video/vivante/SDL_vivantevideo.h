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

#यदि_अपरिभाषितम् SDL_vivantevideo_h_
#परिभाषय SDL_vivantevideo_h_

#अन्तर्भाव "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#अन्तर्भाव <SDL3/SDL_egl.h>

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
#अन्तर्भाव <gc_vdk.h>
#अन्यथा
#अन्तर्भाव <EGL/egl.h>
#यदि_अन्तः

संरचना SDL_Video_दत्त
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_वैयक्तिकम्_2 vdk_वैयक्तिकम्;
#अन्यथा
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(शून्य *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_सूचकांक)(पूर्णाङ्क Display_सूचकांक);
    शून्य(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, पूर्णाङ्क *विस्तारः_2, पूर्णाङ्क *Height);
    शून्य(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, पूर्णाङ्क *विस्तारः_2, पूर्णाङ्क *Height, अचिह्नित दीर्घ *Physical, पूर्णाङ्क *Stride, पूर्णाङ्क *द्वयङ्काः_प्रत्येकम्_pixel);
    शून्य(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_गवाक्षः_Type(EGLAPIENTRY *fb_Create_गवाक्षः)(EGLNativeDisplayType Display, पूर्णाङ्क X, पूर्णाङ्क Y, पूर्णाङ्क विस्तारः_2, पूर्णाङ्क Height);
    शून्य(EGLAPIENTRY *fb_Get_गवाक्षः_Geometry)(EGLNative_गवाक्षः_Type गवाक्षः_2, पूर्णाङ्क *X, पूर्णाङ्क *Y, पूर्णाङ्क *विस्तारः_2, पूर्णाङ्क *Height);
    शून्य(EGLAPIENTRY *fb_Get_गवाक्षः_Info)(EGLNative_गवाक्षः_Type गवाक्षः_2, पूर्णाङ्क *X, पूर्णाङ्क *Y, पूर्णाङ्क *विस्तारः_2, पूर्णाङ्क *Height, पूर्णाङ्क *द्वयङ्काः_प्रत्येकम्_pixel, अचिह्नित पूर्णाङ्क *विस्थापनम्);
    शून्य(EGLAPIENTRY *fb_Destroy_गवाक्षः)(EGLNative_गवाक्षः_Type गवाक्षः_2);
#यदि_अन्तः
};

संरचना SDL_Display_दत्त
{
    EGLNativeDisplayType native_display;
};

संरचना SDL_गवाक्षः_दत्त
{
    EGLNative_गवाक्षः_Type native_गवाक्षः;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
शून्य VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
bool VIVANTE_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
शून्य VIVANTE_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
bool VIVANTE_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
शून्य VIVANTE_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
शून्य VIVANTE_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
शून्य VIVANTE_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
शून्य VIVANTE_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

// Event functions
शून्य VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#यदि_अन्तः // SDL_vivantevideo_h_
