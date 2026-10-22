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

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ <screen/screen.h>
#அந்தர்பாவ <EGL/egl.h>

வகைவரை கட்டமைப்பு SDL_DisplayData
{
    screen_display_t screen_display;
} SDL_DisplayData;

வகைவரை கட்டமைப்பு SDL_DisplayModeData
{
    முழு                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_DisplayModeData;

வகைவரை கட்டமைப்பு SDL_WindowData
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_WindowData;

வகைவரை கட்டமைப்பு SDL_CursorData
{
    screen_session_t session;
    முழு              realized_shape;
    bool             is_visible;
} SDL_CursorData;

வகைவரை கட்டமைப்பு SDL_MouseData
{
    முழு      x_prev;
    முழு      y_prev;
} SDL_MouseData;

வெளி screen_context_t * getContext();
வெளி screen_event_t * getEvent();

வெளி வெறுமை handleKeyboardEvent(screen_event_t event);
வெளி வெறுமை handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
வெளி bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *egl_path);
வெளி SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc);
வெளி SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, முழு interval);
வெளி bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, முழு *interval);
வெளி bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
வெளி bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
வெளி வெறுமை QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

வெளி SDL_PixelFormat screenToPixelFormat(முழு screen_format);
வெளி bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
வெளி bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
வெளி bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

வெளி வெறுமை initMouse(SDL_VideoDevice *_this);
வெளி வெறுமை quitMouse(SDL_VideoDevice *_this);

வெளி முழு QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
