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

#اگر_غیر_تعریف_شدہ SDL_vivantevideo_h_
#تعریف_کرو SDL_vivantevideo_h_

#شامل "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#شامل <SDL3/SDL_egl.h>

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
#شامل <gc_vdk.h>
#ورنہ
#شامل <EGL/egl.h>
#اگر_ختم

ساخت SDL_Video_ڈیٹا
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_نجی_2 vdk_نجی;
#ورنہ
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(خالی *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_اشاریہ)(صحیح Display_اشاریہ);
    خالی(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, صحیح *چوڑائی_2, صحیح *اونچائی_2);
    خالی(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, صحیح *چوڑائی_2, صحیح *اونچائی_2, غیرعلامتی طویل *Physical, صحیح *Stride, صحیح *بٹ_فی_pixel);
    خالی(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_کھڑکی_Type(EGLAPIENTRY *fb_Create_کھڑکی)(EGLNativeDisplayType Display, صحیح X, صحیح Y, صحیح چوڑائی_2, صحیح اونچائی_2);
    خالی(EGLAPIENTRY *fb_Get_کھڑکی_Geometry)(EGLNative_کھڑکی_Type کھڑکی_2, صحیح *X, صحیح *Y, صحیح *چوڑائی_2, صحیح *اونچائی_2);
    خالی(EGLAPIENTRY *fb_Get_کھڑکی_Info)(EGLNative_کھڑکی_Type کھڑکی_2, صحیح *X, صحیح *Y, صحیح *چوڑائی_2, صحیح *اونچائی_2, صحیح *بٹ_فی_pixel, غیرعلامتی صحیح *انحراف);
    خالی(EGLAPIENTRY *fb_Destroy_کھڑکی)(EGLNative_کھڑکی_Type کھڑکی_2);
#اگر_ختم
};

ساخت SDL_Display_ڈیٹا
{
    EGLNativeDisplayType native_display;
};

ساخت SDL_کھڑکی_ڈیٹا
{
    EGLNative_کھڑکی_Type native_کھڑکی;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
خالی VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
bool VIVANTE_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خالی VIVANTE_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
bool VIVANTE_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خالی VIVANTE_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خالی VIVANTE_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خالی VIVANTE_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خالی VIVANTE_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

// Event functions
خالی VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#اگر_ختم // SDL_vivantevideo_h_
