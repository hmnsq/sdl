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

#अगर_अघोषित SDL_vitavideo_h
#घोषणा SDL_vitavideo_h

#समावेश "SDL_internal.h"
#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_egl_c.h"

#समावेश <psp2/types.h>
#समावेश <psp2/display.h>
#समावेश <psp2/ime_dialog.h>
#समावेश <psp2/sysmodule.h>

#अगर_घोषित SDL_VIDEO_VITA_PIB
#समावेश <psp2/gxm.h>
#समावेश <psp2/display.h>
#समावेश <pib.h>
#समावेश <EGL/egl.h>
#समावेश <EGL/eglext.h>
#समावेश <GLES2/gl2.h>
#समावेश <GLES2/gl2ext.h>
प्रकार काष्ठा SDL_GLDriver_तथ्य
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_तथ्य;
#पूर्ण_अगर

काष्ठा SDL_Video_तथ्य
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_बफर[SCE_IME_DIALOG_MAX_TEXT_लंबाई];
    bool ime_active;
};

काष्ठा SDL_Window_तथ्य
{
    bool uses_gles;
    SceUID बफर_uid;
    व्योम *बफर_2;
#अगर_घोषित SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#पूर्ण_अगर
};

बाह्य SDL_Window *Vita_Window;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
बाह्य bool VITA_VideoInit(SDL_VideoDevice *_this);
बाह्य व्योम VITA_VideoQuit(SDL_VideoDevice *_this);
बाह्य bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम VITA_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य व्योम VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#अगर_घोषित SDL_VIDEO_DRIVER_VITA
#अगर_घोषित SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
बाह्य bool VITA_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_FunctionPointer VITA_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
#पूर्ण_अगर

// OpenGLES functions
बाह्य bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य व्योम VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#पूर्ण_अगर

// VITA on screen keyboard
बाह्य bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
बाह्य व्योम VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
बाह्य व्योम VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

बाह्य व्योम VITA_PumpEvents(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_vitavideo_h
