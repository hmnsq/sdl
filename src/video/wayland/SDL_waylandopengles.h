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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_waylandopengles_h_
#define SDL_waylandopengles_h_

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_egl_c.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_PrivateGLESData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy;
} SDL_PrivateGLESData;

// OpenGLES functions
#define Wayland_GLES_GetAttribute   SDL_EGL_GetAttribute
#define Wayland_GLES_GetProcAddress SDL_EGL_GetProcAddressInternal
#define Wayland_GLES_UnloadLibrary  SDL_EGL_UnloadLibrary

ବାହ୍ୟ bool Wayland_GLES_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
ବାହ୍ୟ SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Wayland_GLES_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval);
ବାହ୍ୟ bool Wayland_GLES_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval);
ବାହ୍ୟ bool Wayland_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
ବାହ୍ୟ bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_GLES_SetDefaultProfileConfig(SDL_VideoDevice *_this);
ବାହ୍ୟ SDL_EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window);

#endif // SDL_waylandopengles_h_
