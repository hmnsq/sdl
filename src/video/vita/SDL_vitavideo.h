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

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_egl_c.h"

#अन्तर्भाव <psp2/types.h>
#अन्तर्भाव <psp2/display.h>
#अन्तर्भाव <psp2/ime_dialog.h>
#अन्तर्भाव <psp2/sysmodule.h>

#ifdef SDL_VIDEO_VITA_PIB
#अन्तर्भाव <psp2/gxm.h>
#अन्तर्भाव <psp2/display.h>
#अन्तर्भाव <pib.h>
#अन्तर्भाव <EGL/egl.h>
#अन्तर्भाव <EGL/eglext.h>
#अन्तर्भाव <GLES2/gl2.h>
#अन्तर्भाव <GLES2/gl2ext.h>
प्रकारव्याख्या संरचना SDL_GLDriverData
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriverData;
#endif

संरचना SDL_VideoData
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_buffer[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
    bool ime_active;
};

संरचना SDL_WindowData
{
    bool uses_gles;
    SceUID buffer_uid;
    शून्य *buffer;
#ifdef SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#endif
};

बाह्य SDL_Window *Vita_Window;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
बाह्य bool VITA_VideoInit(SDL_VideoDevice *_this);
बाह्य शून्य VITA_VideoQuit(SDL_VideoDevice *_this);
बाह्य bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य शून्य VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य VITA_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य शून्य VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#ifdef SDL_VIDEO_DRIVER_VITA
#ifdef SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
बाह्य bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path);
बाह्य SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिरांक अक्षर *proc);
#endif

// OpenGLES functions
बाह्य bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path);
बाह्य SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, स्थिरांक अक्षर *proc);
बाह्य शून्य VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#endif

// VITA on screen keyboard
बाह्य bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
बाह्य शून्य VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
बाह्य शून्य VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

बाह्य शून्य VITA_PumpEvents(SDL_VideoDevice *_this);

#endif // SDL_vitavideo_h
