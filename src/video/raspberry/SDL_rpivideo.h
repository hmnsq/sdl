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

#ifndef SDL_rpivideo_h
#define SDL_rpivideo_h

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"

#ضمن <bcm_host.h>
#ضمن <SDL3/SDL_egl.h>

بنية SDL_VideoData
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

بنية SDL_DisplayData
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

بنية SDL_WindowData
{
    EGL_DISPMANX_WINDOW_T dispman_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_buffer;
};

#define SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#define SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool RPI_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ RPI_VideoQuit(SDL_VideoDevice *_this);
خارجي bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool RPI_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
خارجي bool RPI_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
خارجي فراغ RPI_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool RPI_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ RPI_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// OpenGL/OpenGL ES functions
خارجي bool RPI_GLES_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path);
خارجي SDL_FunctionPointer RPI_GLES_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
خارجي bool RPI_GLES_SetSwapInterval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool RPI_GLES_GetSwapInterval(SDL_VideoDevice *_this);
خارجي bool RPI_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#endif // SDL_rpivideo_h
