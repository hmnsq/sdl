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

#شامل "../SDL_sysvideo.h"

بیرونی bool HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
بیرونی تهی HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
بیرونی تهی HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
بیرونی SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
بیرونی bool HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
بیرونی bool HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
بیرونی bool HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
بیرونی تهی HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#endif
