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

#నిర్వచితం_కాకపోతే SDL_vitavideo_h
#నిర్వచించు SDL_vitavideo_h

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_egl_c.h"

#అన్తర్భావ <psp2/types.h>
#అన్తర్భావ <psp2/display.h>
#అన్తర్భావ <psp2/ime_dialog.h>
#అన్తర్భావ <psp2/sysmodule.h>

#నిర్వచితమైతే SDL_VIDEO_VITA_PIB
#అన్తర్భావ <psp2/gxm.h>
#అన్తర్భావ <psp2/display.h>
#అన్తర్భావ <pib.h>
#అన్తర్భావ <EGL/egl.h>
#అన్తర్భావ <EGL/eglext.h>
#అన్తర్భావ <GLES2/gl2.h>
#అన్తర్భావ <GLES2/gl2ext.h>
రకనిర్వచనం నిర్మాణం SDL_GLDriver_దత్తాంశం
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_దత్తాంశం;
#అయితే_ముగింపు

నిర్మాణం SDL_Video_దత్తాంశం
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_బఫరు[SCE_IME_DIALOG_MAX_పాఠ్యం_నిడివి];
    bool ime_చురుకైన;
};

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    bool ఉపయోగిస్తుంది_gles;
    SceUID బఫరు_uid;
    శూన్య *బఫరు_2;
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#అయితే_ముగింపు
};

బాహ్య SDL_కిటికీ *Vita_కిటికీ;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
బాహ్య bool VITA_VideoInit(SDL_VideoDevice *_this);
బాహ్య శూన్య VITA_VideoQuit(SDL_VideoDevice *_this);
బాహ్య bool VITA_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య VITA_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool VITA_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య VITA_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య VITA_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య VITA_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య VITA_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య VITA_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య VITA_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య VITA_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool VITA_సమితి_కిటికీ_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య శూన్య VITA_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
బాహ్య bool VITA_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_Function_సూచిక VITA_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
#అయితే_ముగింపు

// OpenGLES functions
బాహ్య bool VITA_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_Function_సూచిక VITA_GLES_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య శూన్య VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context);
బాహ్య bool VITA_GLES_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool VITA_GLES_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
బాహ్య bool VITA_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#అయితే_ముగింపు

// VITA on screen keyboard
బాహ్య bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
బాహ్య శూన్య VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
బాహ్య శూన్య VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

బాహ్య శూన్య VITA_PumpEvents(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_vitavideo_h
