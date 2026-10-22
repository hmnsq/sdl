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

#अगर_अघोषित SDL_rpivideo_h
#घोषणा SDL_rpivideo_h

#समावेश "SDL_internal.h"
#समावेश "../SDL_sysvideo.h"

#समावेश <bcm_host.h>
#समावेश <SDL3/SDL_egl.h>

काष्ठा SDL_Video_तथ्य
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

काष्ठा SDL_Display_तथ्य
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

काष्ठा SDL_Window_तथ्य
{
    EGL_DISPMANX_WINDOW_T dispman_window;
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#पूर्ण_अगर

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_बफर;
};

#घोषणा SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#घोषणा SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
बाह्य bool RPI_VideoInit(SDL_VideoDevice *_this);
बाह्य व्योम RPI_VideoQuit(SDL_VideoDevice *_this);
बाह्य bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool RPI_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य bool RPI_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम RPI_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool RPI_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम RPI_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// OpenGL/OpenGL ES functions
बाह्य bool RPI_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_FunctionPointer RPI_GLES_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य व्योम RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य bool RPI_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool RPI_GLES_GetSwapInterval(SDL_VideoDevice *_this);
बाह्य bool RPI_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#पूर्ण_अगर // SDL_rpivideo_h
