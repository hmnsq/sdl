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

#నిర్వచితం_కాకపోతే SDL_vivantevideo_h_
#నిర్వచించు SDL_vivantevideo_h_

#అన్తర్భావ "../SDL_sysvideo.h"

// Set up definitions for Vivante EGL
#అన్తర్భావ <SDL3/SDL_egl.h>

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
#అన్తర్భావ <gc_vdk.h>
#లేకపోతే
#అన్తర్భావ <EGL/egl.h>
#అయితే_ముగింపు

నిర్మాణం SDL_Video_దత్తాంశం
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    vdk_వ్యక్తిగత_2 vdk_వ్యక్తిగత;
#లేకపోతే
    SDL_SharedObject *egl_handle; // EGL shared library handle
    EGLNativeDisplayType(EGLAPIENTRY *fbGetDisplay)(శూన్య *context);
    EGLNativeDisplayType(EGLAPIENTRY *fb_Get_Display_By_సూచీ)(పూర్ణాంకం Display_సూచీ);
    శూన్య(EGLAPIENTRY *fbGetDisplayGeometry)(EGLNativeDisplayType Display, పూర్ణాంకం *వెడల్పు_2, పూర్ణాంకం *ఎత్తు_2);
    శూన్య(EGLAPIENTRY *fbGetDisplayInfo)(EGLNativeDisplayType Display, పూర్ణాంకం *వెడల్పు_2, పూర్ణాంకం *ఎత్తు_2, గుర్తులేని దీర్ఘ *Physical, పూర్ణాంకం *Stride, పూర్ణాంకం *బిట్లు_చొప్పున_pixel);
    శూన్య(EGLAPIENTRY *fbDestroyDisplay)(EGLNativeDisplayType Display);
    EGLNative_కిటికీ_Type(EGLAPIENTRY *fb_Create_కిటికీ)(EGLNativeDisplayType Display, పూర్ణాంకం X, పూర్ణాంకం Y, పూర్ణాంకం వెడల్పు_2, పూర్ణాంకం ఎత్తు_2);
    శూన్య(EGLAPIENTRY *fb_Get_కిటికీ_Geometry)(EGLNative_కిటికీ_Type కిటికీ_2, పూర్ణాంకం *X, పూర్ణాంకం *Y, పూర్ణాంకం *వెడల్పు_2, పూర్ణాంకం *ఎత్తు_2);
    శూన్య(EGLAPIENTRY *fb_Get_కిటికీ_Info)(EGLNative_కిటికీ_Type కిటికీ_2, పూర్ణాంకం *X, పూర్ణాంకం *Y, పూర్ణాంకం *వెడల్పు_2, పూర్ణాంకం *ఎత్తు_2, పూర్ణాంకం *బిట్లు_చొప్పున_pixel, గుర్తులేని పూర్ణాంకం *స్థానభ్రంశం);
    శూన్య(EGLAPIENTRY *fb_Destroy_కిటికీ)(EGLNative_కిటికీ_Type కిటికీ_2);
#అయితే_ముగింపు
};

నిర్మాణం SDL_Display_దత్తాంశం
{
    EGLNativeDisplayType native_display;
};

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    EGLNative_కిటికీ_Type native_కిటికీ;
    EGLSurface egl_surface;
};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
bool VIVANTE_VideoInit(SDL_VideoDevice *_this);
శూన్య VIVANTE_VideoQuit(SDL_VideoDevice *_this);
bool VIVANTE_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
bool VIVANTE_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
bool VIVANTE_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
శూన్య VIVANTE_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
bool VIVANTE_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
శూన్య VIVANTE_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
శూన్య VIVANTE_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
శూన్య VIVANTE_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
శూన్య VIVANTE_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

// Event functions
శూన్య VIVANTE_PumpEvents(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_vivantevideo_h_
