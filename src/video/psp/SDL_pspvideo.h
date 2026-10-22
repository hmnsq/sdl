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

#ifndef SDL_pspvideo_h_
#define SDL_pspvideo_h_

#അന്തര്ഭാവ <GLES/egl.h>

#അന്തര്ഭാവ "SDL_internal.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"

ഘടന SDL_VideoData
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

ഘടന SDL_WindowData
{
    bool uses_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ബാഹ്യ bool PSP_VideoInit(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം PSP_VideoQuit(SDL_VideoDevice *_this);
ബാഹ്യ bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ബാഹ്യ bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
ബാഹ്യ bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ബാഹ്യ ശൂന്യം PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// OpenGL/OpenGL ES functions
ബാഹ്യ bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
ബാഹ്യ SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc);
ബാഹ്യ ശൂന്യം PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
ബാഹ്യ SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
ബാഹ്യ bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval);
ബാഹ്യ bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval);
ബാഹ്യ bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
ബാഹ്യ bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
ബാഹ്യ ശൂന്യം PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

#endif // SDL_pspvideo_h_
