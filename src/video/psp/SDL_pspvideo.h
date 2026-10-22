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

#अगर_अघोषित SDL_pspvideo_h_
#घोषणा SDL_pspvideo_h_

#समावेश <GLES/egl.h>

#समावेश "SDL_internal.h"
#समावेश "../SDL_sysvideo.h"

काष्ठा SDL_Video_तथ्य
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

काष्ठा SDL_Window_तथ्य
{
    bool uses_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
बाह्य bool PSP_VideoInit(SDL_VideoDevice *_this);
बाह्य व्योम PSP_VideoQuit(SDL_VideoDevice *_this);
बाह्य bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// OpenGL/OpenGL ES functions
बाह्य bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य व्योम PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
बाह्य bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
बाह्य व्योम PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
बाह्य व्योम PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

#पूर्ण_अगर // SDL_pspvideo_h_
