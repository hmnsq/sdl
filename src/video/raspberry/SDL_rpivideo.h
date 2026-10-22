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

#اگر_غیر_تعریف_شدہ SDL_rpivideo_h
#تعریف_کرو SDL_rpivideo_h

#شامل "SDL_internal.h"
#شامل "../SDL_sysvideo.h"

#شامل <bcm_host.h>
#شامل <SDL3/SDL_egl.h>

ساخت SDL_Video_ڈیٹا
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

ساخت SDL_Display_ڈیٹا
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

ساخت SDL_کھڑکی_ڈیٹا
{
    EGL_DISPMANX_کھڑکی_T dispman_کھڑکی;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#اگر_ختم

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
خارجی bool RPI_VideoInit(SDL_VideoDevice *_this);
خارجی خالی RPI_VideoQuit(SDL_VideoDevice *_this);
خارجی bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجی bool RPI_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجی bool RPI_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی RPI_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool RPI_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی RPI_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

// OpenGL/OpenGL ES functions
خارجی bool RPI_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_Function_اشارہ_گر RPI_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی خالی RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجی SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجی bool RPI_GLES_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool RPI_GLES_Get_تبادلہ_Interval(SDL_VideoDevice *_this);
خارجی bool RPI_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#اگر_ختم // SDL_rpivideo_h
