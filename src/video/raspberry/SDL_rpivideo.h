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

#که_نه_تعریف_شوی SDL_rpivideo_h
#تعریف_کړه SDL_rpivideo_h

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"

#ضمن <bcm_host.h>
#ضمن <SDL3/SDL_egl.h>

بنية SDL_Video_معلومات
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

بنية SDL_Display_معلومات
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

بنية SDL_کړکۍ_معلومات
{
    EGL_DISPMANX_کړکۍ_T dispman_کړکۍ;
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#د_که_پای

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_بفر;
};

#تعریف_کړه SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#تعریف_کړه SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool RPI_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ RPI_VideoQuit(SDL_VideoDevice *_this);
خارجي bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool RPI_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ);
خارجي bool RPI_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي فراغ RPI_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool RPI_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ RPI_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

// OpenGL/OpenGL ES functions
خارجي bool RPI_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي SDL_Function_اشاره_ګر RPI_GLES_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context);
خارجي bool RPI_GLES_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool RPI_GLES_Get_بدلون_Interval(SDL_VideoDevice *_this);
خارجي bool RPI_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#د_که_پای // SDL_rpivideo_h
