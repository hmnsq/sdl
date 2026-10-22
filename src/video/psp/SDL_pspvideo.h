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

#অন্তর্ভাব <GLES/egl.h>

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "../SDL_sysvideo.h"

কাঠামো SDL_Video_তথ্য
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

কাঠামো SDL_Window_তথ্য
{
    bool uses_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
বাহ্যিক bool PSP_VideoInit(SDL_VideoDevice *_this);
বাহ্যিক শূন্য PSP_VideoQuit(SDL_VideoDevice *_this);
বাহ্যিক bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
বাহ্যিক bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
বাহ্যিক bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্যিক শূন্য PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

// OpenGL/OpenGL ES functions
বাহ্যিক bool PSP_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path);
বাহ্যিক SDL_FunctionPointer PSP_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc);
বাহ্যিক শূন্য PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
বাহ্যিক SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
বাহ্যিক bool PSP_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval);
বাহ্যিক bool PSP_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval);
বাহ্যিক bool PSP_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
বাহ্যিক bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
বাহ্যিক শূন্য PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
বাহ্যিক শূন্য PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window);

#endif // SDL_pspvideo_h_
