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

#اگر_تعریف_نشده SDL_rpivideo_h
#تعریف_کن SDL_rpivideo_h

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"

#ضمن <bcm_host.h>
#ضمن <SDL3/SDL_egl.h>

بنية SDL_Video_داده
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

بنية SDL_Display_داده
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

بنية SDL_پنجره_داده
{
    EGL_DISPMANX_پنجره_T dispman_پنجره;
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#پایان_اگر

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_میانگیر;
};

#تعریف_کن SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#تعریف_کن SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool RPI_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ RPI_VideoQuit(SDL_VideoDevice *_this);
خارجي bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool RPI_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);
خارجي bool RPI_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
خارجي فراغ RPI_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool RPI_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ RPI_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

// OpenGL/OpenGL ES functions
خارجي bool RPI_GLES_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر);
خارجي SDL_Function_اشاره_گر RPI_GLES_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context);
خارجي bool RPI_GLES_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool RPI_GLES_Get_جابجا_Interval(SDL_VideoDevice *_this);
خارجي bool RPI_GLES_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#پایان_اگر // SDL_rpivideo_h
