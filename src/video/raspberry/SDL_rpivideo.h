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

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "../SDL_sysvideo.h"

#অন্তর্ভাব <bcm_host.h>
#অন্তর্ভাব <SDL3/SDL_egl.h>

কাঠামো SDL_Video_তথ্য
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

কাঠামো SDL_Display_তথ্য
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

কাঠামো SDL_Window_তথ্য
{
    EGL_DISPMANX_WINDOW_T dispman_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_বাফার;
};

#define SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#define SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
বাহ্যিক bool RPI_VideoInit(SDL_VideoDevice *_this);
বাহ্যিক শূন্য RPI_VideoQuit(SDL_VideoDevice *_this);
বাহ্যিক bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
বাহ্যিক bool RPI_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
বাহ্যিক bool RPI_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্যিক শূন্য RPI_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool RPI_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য RPI_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// OpenGL/OpenGL ES functions
বাহ্যিক bool RPI_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path);
বাহ্যিক SDL_FunctionPointer RPI_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc);
বাহ্যিক শূন্য RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
বাহ্যিক SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
বাহ্যিক bool RPI_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval);
বাহ্যিক bool RPI_GLES_GetSwapInterval(SDL_VideoDevice *_this);
বাহ্যিক bool RPI_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#endif // SDL_rpivideo_h
