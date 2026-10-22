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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_rpivideo_h
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_rpivideo_h

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <bcm_host.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_egl.h>

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    uint32_t egl_refcount; // OpenGL ES reference count
};

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
};

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    EGL_DISPMANX_ਖਿੜਕੀ_T dispman_ਖਿੜਕੀ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ਜੇ_ਅੰਤ

    // Vsync callback cond and mutex
    SDL_Condition *vsync_cond;
    SDL_Mutex *vsync_cond_mutex;
    bool double_ਬਫਰ;
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_RPI_VIDEOLAYER 10000 // High enough so to occlude everything
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_RPI_MOUSELAYER SDL_RPI_VIDEOLAYER + 1

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ਬਾਹਰੀ bool RPI_VideoInit(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ RPI_VideoQuit(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool RPI_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ਬਾਹਰੀ bool RPI_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ bool RPI_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਖਾਲੀ RPI_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool RPI_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ RPI_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

// OpenGL/OpenGL ES functions
ਬਾਹਰੀ bool RPI_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ RPI_GLES_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ ਖਾਲੀ RPI_GLES_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ SDL_GLContext RPI_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool RPI_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context);
ਬਾਹਰੀ bool RPI_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool RPI_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool RPI_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool RPI_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#ਜੇ_ਅੰਤ // SDL_rpivideo_h
