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

#അന്തര്ഭാവ "SDL_internal.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_egl_c.h"

#അന്തര്ഭാവ <psp2/types.h>
#അന്തര്ഭാവ <psp2/display.h>
#അന്തര്ഭാവ <psp2/ime_dialog.h>
#അന്തര്ഭാവ <psp2/sysmodule.h>

#ifdef SDL_VIDEO_VITA_PIB
#അന്തര്ഭാവ <psp2/gxm.h>
#അന്തര്ഭാവ <psp2/display.h>
#അന്തര്ഭാവ <pib.h>
#അന്തര്ഭാവ <EGL/egl.h>
#അന്തര്ഭാവ <EGL/eglext.h>
#അന്തര്ഭാവ <GLES2/gl2.h>
#അന്തര്ഭാവ <GLES2/gl2ext.h>
തരനിർവചനം ഘടന SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;
#endif

ഘടന SDL_VideoData
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_buffer[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
    bool ime_active;
};

ഘടന SDL_WindowData
{
    bool uses_gles;
    SceUID buffer_uid;
    ശൂന്യം *buffer;
#ifdef SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#endif
};

ബാഹ്യ SDL_Window *Vita_Window;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ബാഹ്യ bool VITA_VideoInit(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം VITA_VideoQuit(SDL_VideoDevice *_this);
ബാഹ്യ bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ബാഹ്യ ശൂന്യം VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം VITA_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ബാഹ്യ ശൂന്യം VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#ifdef SDL_VIDEO_DRIVER_VITA
#ifdef SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
ബാഹ്യ bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
ബാഹ്യ SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc);
#endif

// OpenGLES functions
ബാഹ്യ bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
ബാഹ്യ SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc);
ബാഹ്യ ശൂന്യം VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
ബാഹ്യ SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
ബാഹ്യ bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval);
ബാഹ്യ bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval);
ബാഹ്യ bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#endif

// VITA on screen keyboard
ബാഹ്യ bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
ബാഹ്യ ശൂന്യം VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

ബാഹ്യ ശൂന്യം VITA_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vitavideo_h
