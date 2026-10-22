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

#अगर_अघोषित SDL_BWINDOW_H
#घोषणा SDL_BWINDOW_H

#समावेश "../SDL_sysvideo.h"

बाह्य bool HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_Set_Window_Minimum_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य व्योम HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
बाह्य SDL_Fullscreen_परिणाम HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य bool HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य bool HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
बाह्य bool HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
बाह्य व्योम HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

#पूर्ण_अगर
