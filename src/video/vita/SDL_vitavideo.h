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

#ifndef SDL_vitavideo_h
#define SDL_vitavideo_h

#அந்தர்பாவ "SDL_internal.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../SDL_egl_c.h"

#அந்தர்பாவ <psp2/types.h>
#அந்தர்பாவ <psp2/display.h>
#அந்தர்பாவ <psp2/ime_dialog.h>
#அந்தர்பாவ <psp2/sysmodule.h>

#ifdef SDL_VIDEO_VITA_PIB
#அந்தர்பாவ <psp2/gxm.h>
#அந்தர்பாவ <psp2/display.h>
#அந்தர்பாவ <pib.h>
#அந்தர்பாவ <EGL/egl.h>
#அந்தர்பாவ <EGL/eglext.h>
#அந்தர்பாவ <GLES2/gl2.h>
#அந்தர்பாவ <GLES2/gl2ext.h>
வகைவரை கட்டமைப்பு SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;
#endif

கட்டமைப்பு SDL_VideoData
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_buffer[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
    bool ime_active;
};

கட்டமைப்பு SDL_WindowData
{
    bool uses_gles;
    SceUID buffer_uid;
    வெறுமை *buffer;
#ifdef SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#endif
};

வெளி SDL_Window *Vita_Window;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
வெளி bool VITA_VideoInit(SDL_VideoDevice *_this);
வெளி வெறுமை VITA_VideoQuit(SDL_VideoDevice *_this);
வெளி bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
வெளி வெறுமை VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை VITA_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
வெளி வெறுமை VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#ifdef SDL_VIDEO_DRIVER_VITA
#ifdef SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
வெளி bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path);
வெளி SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
வெளி SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc);
#endif

// OpenGLES functions
வெளி bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path);
வெளி SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc);
வெளி வெறுமை VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
வெளி SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
வெளி bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, முழு interval);
வெளி bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, முழு *interval);
வெளி bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#endif

// VITA on screen keyboard
வெளி bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
வெளி வெறுமை VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
வெளி வெறுமை VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

வெளி வெறுமை VITA_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vitavideo_h
