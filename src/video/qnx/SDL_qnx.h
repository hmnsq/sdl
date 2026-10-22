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

#شامل "../SDL_sysvideo.h"
#شامل <screen/screen.h>
#شامل <EGL/egl.h>

تعریفنوع ساختار SDL_DisplayData
{
    screen_display_t screen_display;
} SDL_DisplayData;

تعریفنوع ساختار SDL_DisplayModeData
{
    صحیح                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_DisplayModeData;

تعریفنوع ساختار SDL_WindowData
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_WindowData;

تعریفنوع ساختار SDL_CursorData
{
    screen_session_t session;
    صحیح              realized_shape;
    bool             is_visible;
} SDL_CursorData;

تعریفنوع ساختار SDL_MouseData
{
    صحیح      x_prev;
    صحیح      y_prev;
} SDL_MouseData;

بیرونی screen_context_t * getContext();
بیرونی screen_event_t * getEvent();

بیرونی تهی handleKeyboardEvent(screen_event_t event);
بیرونی تهی handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
بیرونی bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *egl_path);
بیرونی SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ثابت نویسه *proc);
بیرونی SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, صحیح interval);
بیرونی bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, صحیح *interval);
بیرونی bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
بیرونی bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
بیرونی تهی QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

بیرونی SDL_PixelFormat screenToPixelFormat(صحیح screen_format);
بیرونی bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
بیرونی bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
بیرونی bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

بیرونی تهی initMouse(SDL_VideoDevice *_this);
بیرونی تهی quitMouse(SDL_VideoDevice *_this);

بیرونی صحیح QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
