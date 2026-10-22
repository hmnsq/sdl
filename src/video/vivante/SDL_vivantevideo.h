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

#جيڪڏهن_وصف_نه_ٿيل SDL_vivantevideo_h_
#وصف_ڪريو SDL_vivantevideo_h_

#ضمن "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ضمن <SDL3/SDL_egl.h>

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
#ضمن <gc_vdk.h>
#وإلا
#ضمن <EGL/egl.h>
#جيڪڏهن_پورو

بنية SDL_Video_معلومات
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_ذاتي_2 vdk_ذاتي;
#وإلا
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(فراغ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_اشاريو)(صحيح Display_اشاريو);
    فراغ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, صحيح *ويڪر_2, صحيح *اوچائي_2);
    فراغ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, صحيح *ويڪر_2, صحيح *اوچائي_2, بنانشان ڊگهو *Physical, صحيح *Stride, صحيح *بٽ_في_pixel);
    فراغ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_دري_Type(EGLAPIENTRY *fb_Create_دري)(EGLNativeDisplayType Display, صحيح X, صحيح Y, صحيح ويڪر_2, صحيح اوچائي_2);
    فراغ(EGLAPIENTRY *fb_Get_دري_Geometry)(EGLNative_دري_Type دري_2, صحيح *X, صحيح *Y, صحيح *ويڪر_2, صحيح *اوچائي_2);
    فراغ(EGLAPIENTRY *fb_Get_دري_Info)(EGLNative_دري_Type دري_2, صحيح *X, صحيح *Y, صحيح *ويڪر_2, صحيح *اوچائي_2, صحيح *بٽ_في_pixel, بنانشان صحيح *وٿي);
    فراغ(EGLAPIENTRY *fb_Destroy_دري)(EGLNative_دري_Type دري_2);
#جيڪڏهن_پورو
};

بنية SDL_Display_معلومات
{
    EGLNativeDisplayType native_display;
};

بنية SDL_دري_معلومات
{
    EGLNative_دري_Type native_دري;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي);
bool VIVANTE_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
فراغ VIVANTE_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري);
bool VIVANTE_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري);
فراغ VIVANTE_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
فراغ VIVANTE_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري);
فراغ VIVANTE_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري);
فراغ VIVANTE_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);

// Event functions
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#جيڪڏهن_پورو // SDL_vivantevideo_h_
