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

#ifndef SDL_BWINDOW_H
#define SDL_BWINDOW_H

#அந்தர்பாவ "../SDL_sysvideo.h"

வெளி bool HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
வெளி வெறுமை HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
வெளி வெறுமை HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
வெளி SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
வெளி bool HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
வெளி bool HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
வெளி bool HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
வெளி வெறுமை HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#endif
