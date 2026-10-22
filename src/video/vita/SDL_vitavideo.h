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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_vitavideo_h
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_vitavideo_h

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

#ಅನ್ತರ್ಭಾವ <psp2/types.h>
#ಅನ್ತರ್ಭಾವ <psp2/display.h>
#ಅನ್ತರ್ಭಾವ <psp2/ime_dialog.h>
#ಅನ್ತರ್ಭಾವ <psp2/sysmodule.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PIB
#ಅನ್ತರ್ಭಾವ <psp2/gxm.h>
#ಅನ್ತರ್ಭಾವ <psp2/display.h>
#ಅನ್ತರ್ಭಾವ <pib.h>
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಅನ್ತರ್ಭಾವ <EGL/eglext.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2ext.h>
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_ದತ್ತಾಂಶ;
#ಆದರೆ_ಅಂತ್ಯ

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_ಬಫರ್[SCE_IME_DIALOG_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ];
    bool ime_ಸಕ್ರಿಯ;
};

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    bool ಬಳಸುತ್ತದೆ_gles;
    SceUID ಬಫರ್_uid;
    ಶೂನ್ಯ *ಬಫರ್_2;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#ಆದರೆ_ಅಂತ್ಯ
};

ಬಾಹ್ಯ SDL_ಕಿಟಕಿ *Vita_ಕಿಟಕಿ;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ಬಾಹ್ಯ bool VITA_VideoInit(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_VideoQuit(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool VITA_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool VITA_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool VITA_ಗಣ_ಕಿಟಕಿ_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
ಬಾಹ್ಯ bool VITA_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ VITA_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
#ಆದರೆ_ಅಂತ್ಯ

// OpenGLES functions
ಬಾಹ್ಯ bool VITA_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ VITA_GLES_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context);
ಬಾಹ್ಯ bool VITA_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
ಬಾಹ್ಯ bool VITA_GLES_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);
ಬಾಹ್ಯ bool VITA_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#ಆದರೆ_ಅಂತ್ಯ

// VITA on screen keyboard
ಬಾಹ್ಯ bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
ಬಾಹ್ಯ ಶೂನ್ಯ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

ಬಾಹ್ಯ ಶೂನ್ಯ VITA_PumpEvents(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_vitavideo_h
