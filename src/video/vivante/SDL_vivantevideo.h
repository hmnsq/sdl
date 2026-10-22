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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_vivantevideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_vivantevideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_egl.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
#ਅਨ੍ਤਰ੍ਭਾਵ <gc_vdk.h>
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/egl.h>
#ਜੇ_ਅੰਤ

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_ਨਿੱਜੀ_2 vdk_ਨਿੱਜੀ;
#ਨਹੀਂਤਾਂ
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(ਖਾਲੀ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_ਸੂਚਕਾਂਕ)(ਪੂਰਨ Display_ਸੂਚਕਾਂਕ);
    ਖਾਲੀ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, ਪੂਰਨ *ਚੌੜਾਈ_2, ਪੂਰਨ *ਉਚਾਈ_2);
    ਖਾਲੀ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, ਪੂਰਨ *ਚੌੜਾਈ_2, ਪੂਰਨ *ਉਚਾਈ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *Physical, ਪੂਰਨ *Stride, ਪੂਰਨ *ਬਿੱਟ_ਪ੍ਰਤੀ_pixel);
    ਖਾਲੀ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_ਖਿੜਕੀ_Type(EGLAPIENTRY *fb_Create_ਖਿੜਕੀ)(EGLNativeDisplayType Display, ਪੂਰਨ X, ਪੂਰਨ Y, ਪੂਰਨ ਚੌੜਾਈ_2, ਪੂਰਨ ਉਚਾਈ_2);
    ਖਾਲੀ(EGLAPIENTRY *fb_Get_ਖਿੜਕੀ_Geometry)(EGLNative_ਖਿੜਕੀ_Type ਖਿੜਕੀ_2, ਪੂਰਨ *X, ਪੂਰਨ *Y, ਪੂਰਨ *ਚੌੜਾਈ_2, ਪੂਰਨ *ਉਚਾਈ_2);
    ਖਾਲੀ(EGLAPIENTRY *fb_Get_ਖਿੜਕੀ_Info)(EGLNative_ਖਿੜਕੀ_Type ਖਿੜਕੀ_2, ਪੂਰਨ *X, ਪੂਰਨ *Y, ਪੂਰਨ *ਚੌੜਾਈ_2, ਪੂਰਨ *ਉਚਾਈ_2, ਪੂਰਨ *ਬਿੱਟ_ਪ੍ਰਤੀ_pixel, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *ਵਿੱਥ);
    ਖਾਲੀ(EGLAPIENTRY *fb_Destroy_ਖਿੜਕੀ)(EGLNative_ਖਿੜਕੀ_Type ਖਿੜਕੀ_2);
#ਜੇ_ਅੰਤ
};

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    EGLNativeDisplayType native_display;
};

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    EGLNative_ਖਿੜਕੀ_Type native_ਖਿੜਕੀ;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
ਖਾਲੀ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
bool VIVANTE_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਖਾਲੀ VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
bool VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਖਾਲੀ VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਖਾਲੀ VIVANTE_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਖਾਲੀ VIVANTE_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਖਾਲੀ VIVANTE_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

// Event functions
ਖਾਲੀ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#ਜੇ_ਅੰਤ // SDL_vivantevideo_h_
