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

#جے_بنا_تعریف SDL_vivantevideo_h_
#تعریف_کرو SDL_vivantevideo_h_

#ضمن "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ضمن <SDL3/SDL_egl.h>

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
#ضمن <gc_vdk.h>
#وإلا
#ضمن <EGL/egl.h>
#جے_انت

بنية SDL_Video_انکڑے
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_نجی_2 vdk_نجی;
#وإلا
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(فراغ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_اشاریہ)(صحيح Display_اشاریہ);
    فراغ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, صحيح *چوڑائی_2, صحيح *اچائی_2);
    فراغ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, صحيح *چوڑائی_2, صحيح *اچائی_2, بنانشانی لما *Physical, صحيح *Stride, صحيح *بٹ_فی_pixel);
    فراغ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_کھڑکی_Type(EGLAPIENTRY *fb_Create_کھڑکی)(EGLNativeDisplayType Display, صحيح X, صحيح Y, صحيح چوڑائی_2, صحيح اچائی_2);
    فراغ(EGLAPIENTRY *fb_Get_کھڑکی_Geometry)(EGLNative_کھڑکی_Type کھڑکی_2, صحيح *X, صحيح *Y, صحيح *چوڑائی_2, صحيح *اچائی_2);
    فراغ(EGLAPIENTRY *fb_Get_کھڑکی_Info)(EGLNative_کھڑکی_Type کھڑکی_2, صحيح *X, صحيح *Y, صحيح *چوڑائی_2, صحيح *اچائی_2, صحيح *بٹ_فی_pixel, بنانشانی صحيح *وتھ);
    فراغ(EGLAPIENTRY *fb_Destroy_کھڑکی)(EGLNative_کھڑکی_Type کھڑکی_2);
#جے_انت
};

بنية SDL_Display_انکڑے
{
    EGLNativeDisplayType native_display;
};

بنية SDL_کھڑکی_انکڑے
{
    EGLNative_کھڑکی_Type native_کھڑکی;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
bool VIVANTE_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
فراغ VIVANTE_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
bool VIVANTE_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
فراغ VIVANTE_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
فراغ VIVANTE_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
فراغ VIVANTE_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
فراغ VIVANTE_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

// Event functions
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#جے_انت // SDL_vivantevideo_h_
