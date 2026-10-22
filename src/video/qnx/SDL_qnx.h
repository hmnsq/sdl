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

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব <screen/screen.h>
#অন্তর্ভাব <EGL/egl.h>

প্রকারনির্দেশ সংরচনা SDL_DisplayData
{
    screen_display_t screen_display;
} SDL_DisplayData;

প্রকারনির্দেশ সংরচনা SDL_DisplayModeData
{
    পূর্ণাঙ্ক                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_DisplayModeData;

প্রকারনির্দেশ সংরচনা SDL_WindowData
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_WindowData;

প্রকারনির্দেশ সংরচনা SDL_CursorData
{
    screen_session_t session;
    পূর্ণাঙ্ক              realized_shape;
    bool             is_visible;
} SDL_CursorData;

প্রকারনির্দেশ সংরচনা SDL_MouseData
{
    পূর্ণাঙ্ক      x_prev;
    পূর্ণাঙ্ক      y_prev;
} SDL_MouseData;

বাহ্য screen_context_t * getContext();
বাহ্য screen_event_t * getEvent();

বাহ্য শূন্য handleKeyboardEvent(screen_event_t event);
বাহ্য শূন্য handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
বাহ্য bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *egl_path);
বাহ্য SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুব বর্ণ *proc);
বাহ্য SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval);
বাহ্য bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval);
বাহ্য bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
বাহ্য bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
বাহ্য শূন্য QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

বাহ্য SDL_PixelFormat screenToPixelFormat(পূর্ণাঙ্ক screen_format);
বাহ্য bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
বাহ্য bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
বাহ্য bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

বাহ্য শূন্য initMouse(SDL_VideoDevice *_this);
বাহ্য শূন্য quitMouse(SDL_VideoDevice *_this);

বাহ্য পূর্ণাঙ্ক QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
