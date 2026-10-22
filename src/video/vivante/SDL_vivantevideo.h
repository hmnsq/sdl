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

#اگر_تعریف_نشده SDL_vivantevideo_h_
#تعریف_کن SDL_vivantevideo_h_

#ضمن "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ضمن <SDL3/SDL_egl.h>

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
#ضمن <gc_vdk.h>
#وإلا
#ضمن <EGL/egl.h>
#پایان_اگر

بنية SDL_Video_داده
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_خصوصی_2 vdk_خصوصی;
#وإلا
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(فراغ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_شاخص)(صحيح Display_شاخص);
    فراغ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, صحيح *عرض_2, صحيح *ارتفاع_2);
    فراغ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, صحيح *عرض_2, صحيح *ارتفاع_2, بیعلامت دراز *Physical, صحيح *Stride, صحيح *بیتها_در_هر_pixel);
    فراغ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_پنجره_Type(EGLAPIENTRY *fb_Create_پنجره)(EGLNativeDisplayType Display, صحيح X, صحيح Y, صحيح عرض_2, صحيح ارتفاع_2);
    فراغ(EGLAPIENTRY *fb_Get_پنجره_Geometry)(EGLNative_پنجره_Type پنجره_2, صحيح *X, صحيح *Y, صحيح *عرض_2, صحيح *ارتفاع_2);
    فراغ(EGLAPIENTRY *fb_Get_پنجره_Info)(EGLNative_پنجره_Type پنجره_2, صحيح *X, صحيح *Y, صحيح *عرض_2, صحيح *ارتفاع_2, صحيح *بیتها_در_هر_pixel, بیعلامت صحيح *جابه_جایی);
    فراغ(EGLAPIENTRY *fb_Destroy_پنجره)(EGLNative_پنجره_Type پنجره_2);
#پایان_اگر
};

بنية SDL_Display_داده
{
    EGLNativeDisplayType native_display;
};

بنية SDL_پنجره_داده
{
    EGLNative_پنجره_Type native_پنجره;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);
bool VIVANTE_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
فراغ VIVANTE_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
bool VIVANTE_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
فراغ VIVANTE_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
فراغ VIVANTE_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
فراغ VIVANTE_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
فراغ VIVANTE_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

// Event functions
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#پایان_اگر // SDL_vivantevideo_h_
