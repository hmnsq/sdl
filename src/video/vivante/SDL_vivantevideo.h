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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_vivantevideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_vivantevideo_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_egl.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
#ಅನ್ತರ್ಭಾವ <gc_vdk.h>
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಆದರೆ_ಅಂತ್ಯ

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_ಖಾಸಗಿ_2 vdk_ಖಾಸಗಿ;
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(ಶೂನ್ಯ *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_ಸೂಚ್ಯಂಕ)(ಪೂರ್ಣಾಂಕ Display_ಸೂಚ್ಯಂಕ);
    ಶೂನ್ಯ(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, ಪೂರ್ಣಾಂಕ *ಅಗಲ_2, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ_2);
    ಶೂನ್ಯ(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, ಪೂರ್ಣಾಂಕ *ಅಗಲ_2, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *Physical, ಪೂರ್ಣಾಂಕ *Stride, ಪೂರ್ಣಾಂಕ *ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel);
    ಶೂನ್ಯ(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_ಕಿಟಕಿ_Type(EGLAPIENTRY *fb_Create_ಕಿಟಕಿ)(EGLNativeDisplayType Display, ಪೂರ್ಣಾಂಕ X, ಪೂರ್ಣಾಂಕ Y, ಪೂರ್ಣಾಂಕ ಅಗಲ_2, ಪೂರ್ಣಾಂಕ ಎತ್ತರ_2);
    ಶೂನ್ಯ(EGLAPIENTRY *fb_Get_ಕಿಟಕಿ_Geometry)(EGLNative_ಕಿಟಕಿ_Type ಕಿಟಕಿ_2, ಪೂರ್ಣಾಂಕ *X, ಪೂರ್ಣಾಂಕ *Y, ಪೂರ್ಣಾಂಕ *ಅಗಲ_2, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ_2);
    ಶೂನ್ಯ(EGLAPIENTRY *fb_Get_ಕಿಟಕಿ_Info)(EGLNative_ಕಿಟಕಿ_Type ಕಿಟಕಿ_2, ಪೂರ್ಣಾಂಕ *X, ಪೂರ್ಣಾಂಕ *Y, ಪೂರ್ಣಾಂಕ *ಅಗಲ_2, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ_2, ಪೂರ್ಣಾಂಕ *ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *ಸ್ಥಾನಾಂತರ);
    ಶೂನ್ಯ(EGLAPIENTRY *fb_Destroy_ಕಿಟಕಿ)(EGLNative_ಕಿಟಕಿ_Type ಕಿಟಕಿ_2);
#ಆದರೆ_ಅಂತ್ಯ
};

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    EGLNativeDisplayType native_display;
};

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    EGLNative_ಕಿಟಕಿ_Type native_ಕಿಟಕಿ;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
ಶೂನ್ಯ VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
bool VIVANTE_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಶೂನ್ಯ VIVANTE_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
bool VIVANTE_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಶೂನ್ಯ VIVANTE_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಶೂನ್ಯ VIVANTE_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಶೂನ್ಯ VIVANTE_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಶೂನ್ಯ VIVANTE_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

// Event functions
ಶೂನ್ಯ VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_vivantevideo_h_
