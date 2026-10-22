/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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

#ifndef __SDL_QNX_H__
#define __SDL_QNX_H__

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ <screen/screen.h>
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_DisplayData
{
    screen_display_t screen_display;
} SDL_DisplayData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_DisplayModeData
{
    ಪೂರ್ಣಾಙ್ಕ                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_DisplayModeData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WindowData
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_WindowData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_CursorData
{
    screen_session_t session;
    ಪೂರ್ಣಾಙ್ಕ              realized_shape;
    bool             is_visible;
} SDL_CursorData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_MouseData
{
    ಪೂರ್ಣಾಙ್ಕ      x_prev;
    ಪೂರ್ಣಾಙ್ಕ      y_prev;
} SDL_MouseData;

ಬಾಹ್ಯ screen_context_t * getContext();
ಬಾಹ್ಯ screen_event_t * getEvent();

ಬಾಹ್ಯ ಶೂನ್ಯ handleKeyboardEvent(screen_event_t event);
ಬಾಹ್ಯ ಶೂನ್ಯ handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
ಬಾಹ್ಯ bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *egl_path);
ಬಾಹ್ಯ SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc);
ಬಾಹ್ಯ SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval);
ಬಾಹ್ಯ bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval);
ಬಾಹ್ಯ bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
ಬಾಹ್ಯ bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
ಬಾಹ್ಯ ಶೂನ್ಯ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

ಬಾಹ್ಯ SDL_PixelFormat screenToPixelFormat(ಪೂರ್ಣಾಙ್ಕ screen_format);
ಬಾಹ್ಯ bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ಬಾಹ್ಯ bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ಬಾಹ್ಯ bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

ಬಾಹ್ಯ ಶೂನ್ಯ initMouse(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ quitMouse(SDL_VideoDevice *_this);

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
