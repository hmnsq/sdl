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

#جے_بنا_تعریف SDL_rpivideo_h
#تعریف_کرو SDL_rpivideo_h

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"

#ضمن <bcm_host.h>
#ضمن <SDL3/SDL_egl.h>

بنية SDL_Video_انکڑے
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

بنية SDL_Display_انکڑے
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

بنية SDL_کھڑکی_انکڑے
{
    EGL_DISPMANX_کھڑکی_T dispman_کھڑکی;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#جے_انت

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_بفر;
};

#تعریف_کرو SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#تعریف_کرو SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool RPI_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ RPI_VideoQuit(SDL_VideoDevice *_this);
خارجي bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool RPI_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجي bool RPI_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي فراغ RPI_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool RPI_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ RPI_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

// OpenGL/OpenGL ES functions
خارجي bool RPI_GLES_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ);
خارجي SDL_Function_اشارہ_گر RPI_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجي bool RPI_GLES_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool RPI_GLES_Get_وٹاندرا_Interval(SDL_VideoDevice *_this);
خارجي bool RPI_GLES_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#جے_انت // SDL_rpivideo_h
