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

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

#ضمن <psp2/types.h>
#ضمن <psp2/display.h>
#ضمن <psp2/ime_dialog.h>
#ضمن <psp2/sysmodule.h>

#ifdef SDL_VIDEO_VITA_PIB
#ضمن <psp2/gxm.h>
#ضمن <psp2/display.h>
#ضمن <pib.h>
#ضمن <EGL/egl.h>
#ضمن <EGL/eglext.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
تعريفنوع بنية SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;
#endif

بنية SDL_VideoData
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_buffer[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
    bool ime_active;
};

بنية SDL_WindowData
{
    bool uses_gles;
    SceUID buffer_uid;
    فراغ *buffer;
#ifdef SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#endif
};

خارجي SDL_Window *Vita_Window;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool VITA_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ VITA_VideoQuit(SDL_VideoDevice *_this);
خارجي bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
خارجي فراغ VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ VITA_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
خارجي فراغ VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#ifdef SDL_VIDEO_DRIVER_VITA
#ifdef SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
خارجي bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path);
خارجي SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
خارجي SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc);
#endif

// OpenGLES functions
خارجي bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path);
خارجي SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
خارجي bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#endif

// VITA on screen keyboard
خارجي bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجي فراغ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
خارجي فراغ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

خارجي فراغ VITA_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vitavideo_h
