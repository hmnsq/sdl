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

প্রকারলেখ কাঠামো SDL_Display_তথ্য
{
    screen_display_t screen_display;
} SDL_Display_তথ্য;

প্রকারলেখ কাঠামো SDL_Display_Mode_তথ্য
{
    পূর্ণসংখ্যা                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_Display_Mode_তথ্য;

প্রকারলেখ কাঠামো SDL_Window_তথ্য
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_Window_তথ্য;

প্রকারলেখ কাঠামো SDL_Cursor_তথ্য
{
    screen_session_t session;
    পূর্ণসংখ্যা              realized_shape;
    bool             is_visible;
} SDL_Cursor_তথ্য;

প্রকারলেখ কাঠামো SDL_Mouse_তথ্য
{
    পূর্ণসংখ্যা      x_পূর্ব;
    পূর্ণসংখ্যা      y_পূর্ব;
} SDL_Mouse_তথ্য;

বাহ্যিক screen_context_t * getContext();
বাহ্যিক screen_event_t * getEvent();

বাহ্যিক শূন্য handleKeyboardEvent(screen_event_t event);
বাহ্যিক শূন্য handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
বাহ্যিক bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *egl_path);
বাহ্যিক SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc);
বাহ্যিক SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval);
বাহ্যিক bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval);
বাহ্যিক bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
বাহ্যিক bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
বাহ্যিক শূন্য QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

বাহ্যিক SDL_PixelFormat screenToPixelFormat(পূর্ণসংখ্যা screen_format);
বাহ্যিক bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
বাহ্যিক bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
বাহ্যিক bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

বাহ্যিক শূন্য initMouse(SDL_VideoDevice *_this);
বাহ্যিক শূন্য quitMouse(SDL_VideoDevice *_this);

বাহ্যিক পূর্ণসংখ্যা QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
