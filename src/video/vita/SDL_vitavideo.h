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

#અન્તર્ભાવ "SDL_internal.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../SDL_egl_c.h"

#અન્તર્ભાવ <psp2/types.h>
#અન્તર્ભાવ <psp2/display.h>
#અન્તર્ભાવ <psp2/ime_dialog.h>
#અન્તર્ભાવ <psp2/sysmodule.h>

#ifdef SDL_VIDEO_VITA_PIB
#અન્તર્ભાવ <psp2/gxm.h>
#અન્તર્ભાવ <psp2/display.h>
#અન્તર્ભાવ <pib.h>
#અન્તર્ભાવ <EGL/egl.h>
#અન્તર્ભાવ <EGL/eglext.h>
#અન્તર્ભાવ <GLES2/gl2.h>
#અન્તર્ભાવ <GLES2/gl2ext.h>
પ્રકારવ્યાખ્યા સંરચના SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;
#endif

સંરચના SDL_VideoData
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_buffer[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
    bool ime_active;
};

સંરચના SDL_WindowData
{
    bool uses_gles;
    SceUID buffer_uid;
    શૂન્ય *buffer;
#ifdef SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#endif
};

બાહ્ય SDL_Window *Vita_Window;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
બાહ્ય bool VITA_VideoInit(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય VITA_VideoQuit(SDL_VideoDevice *_this);
બાહ્ય bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
બાહ્ય શૂન્ય VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય VITA_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
બાહ્ય શૂન્ય VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#ifdef SDL_VIDEO_DRIVER_VITA
#ifdef SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
બાહ્ય bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *path);
બાહ્ય SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, અચલ અક્ષર *proc);
#endif

// OpenGLES functions
બાહ્ય bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *path);
બાહ્ય SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, અચલ અક્ષર *proc);
બાહ્ય શૂન્ય VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
બાહ્ય SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
બાહ્ય bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક interval);
બાહ્ય bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક *interval);
બાહ્ય bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#endif

// VITA on screen keyboard
બાહ્ય bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
બાહ્ય શૂન્ય VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

બાહ્ય શૂન્ય VITA_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vitavideo_h
