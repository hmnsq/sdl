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

#నిర్వచితం_కాకపోతే SDL_rpivideo_h
#నిర్వచించు SDL_rpivideo_h

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ <bcm_host.h>
#అన్తర్భావ <SDL3/SDL_egl.h>

నిర్మాణం SDL_Video_దత్తాంశం
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

నిర్మాణం SDL_Display_దత్తాంశం
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    EGL_DISPMANX_కిటికీ_T dispman_కిటికీ;
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#అయితే_ముగింపు

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_బఫరు;
};

#నిర్వచించు SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#నిర్వచించు SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
బాహ్య bool RPI_VideoInit(SDL_VideoDevice *_this);
బాహ్య శూన్య RPI_VideoQuit(SDL_VideoDevice *_this);
బాహ్య bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య bool RPI_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య bool RPI_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య RPI_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool RPI_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య RPI_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

// OpenGL/OpenGL ES functions
బాహ్య bool RPI_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_Function_సూచిక RPI_GLES_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య శూన్య RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context);
బాహ్య bool RPI_GLES_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool RPI_GLES_Get_మార్పిడి_Interval(SDL_VideoDevice *_this);
బాహ్య bool RPI_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#అయితే_ముగింపు // SDL_rpivideo_h
