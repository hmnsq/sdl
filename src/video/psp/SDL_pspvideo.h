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

#నిర్వచితం_కాకపోతే SDL_pspvideo_h_
#నిర్వచించు SDL_pspvideo_h_

#అన్తర్భావ <GLES/egl.h>

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "../SDL_sysvideo.h"

నిర్మాణం SDL_Video_దత్తాంశం
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    bool ఉపయోగిస్తుంది_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
బాహ్య bool PSP_VideoInit(SDL_VideoDevice *_this);
బాహ్య శూన్య PSP_VideoQuit(SDL_VideoDevice *_this);
బాహ్య bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య bool PSP_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య bool PSP_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య PSP_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool PSP_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య PSP_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

// OpenGL/OpenGL ES functions
బాహ్య bool PSP_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_Function_సూచిక PSP_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య శూన్య PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context);
బాహ్య bool PSP_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool PSP_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
బాహ్య bool PSP_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
బాహ్య bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
బాహ్య శూన్య PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
బాహ్య శూన్య PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

#అయితే_ముగింపు // SDL_pspvideo_h_
