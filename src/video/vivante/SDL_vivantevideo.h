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

#که_نه_تعریف_شوی SDL_vivantevideo_h_
#تعریف_کړه SDL_vivantevideo_h_

#ضمن "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ضمن <SDL3/SDL_egl.h>

#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
#ضمن <gc_vdk.h>
#وإلا
#ضمن <EGL/egl.h>
#د_که_پای

بنية SDL_Video_معلومات
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_شخصي_2 vdk_شخصي;
#وإلا
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(فراغ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_شاخص)(صحيح Display_شاخص);
    فراغ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, صحيح *پلنوالی_2, صحيح *لوړوالی_2);
    فراغ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, صحيح *پلنوالی_2, صحيح *لوړوالی_2, بینښه اوږد *Physical, صحيح *Stride, صحيح *بټونه_فی_pixel);
    فراغ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_کړکۍ_Type(EGLAPIENTRY *fb_Create_کړکۍ)(EGLNativeDisplayType Display, صحيح X, صحيح Y, صحيح پلنوالی_2, صحيح لوړوالی_2);
    فراغ(EGLAPIENTRY *fb_Get_کړکۍ_Geometry)(EGLNative_کړکۍ_Type کړکۍ_2, صحيح *X, صحيح *Y, صحيح *پلنوالی_2, صحيح *لوړوالی_2);
    فراغ(EGLAPIENTRY *fb_Get_کړکۍ_Info)(EGLNative_کړکۍ_Type کړکۍ_2, صحيح *X, صحيح *Y, صحيح *پلنوالی_2, صحيح *لوړوالی_2, صحيح *بټونه_فی_pixel, بینښه صحيح *دننه_واټن);
    فراغ(EGLAPIENTRY *fb_Destroy_کړکۍ)(EGLNative_کړکۍ_Type کړکۍ_2);
#د_که_پای
};

بنية SDL_Display_معلومات
{
    EGLNativeDisplayType native_display;
};

بنية SDL_کړکۍ_معلومات
{
    EGLNative_کړکۍ_Type native_کړکۍ;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ);
bool VIVANTE_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
فراغ VIVANTE_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
bool VIVANTE_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
فراغ VIVANTE_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
فراغ VIVANTE_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
فراغ VIVANTE_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
فراغ VIVANTE_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

// Event functions
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#د_که_پای // SDL_vivantevideo_h_
