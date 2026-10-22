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

#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ <screen/screen.h>
#અન્તર્ભાવ <EGL/egl.h>

પ્રકારવ્યાખ્યા સંરચના SDL_DisplayData
{
    screen_display_t screen_display;
} SDL_DisplayData;

પ્રકારવ્યાખ્યા સંરચના SDL_DisplayModeData
{
    પૂર્ણાંક                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_DisplayModeData;

પ્રકારવ્યાખ્યા સંરચના SDL_WindowData
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_WindowData;

પ્રકારવ્યાખ્યા સંરચના SDL_CursorData
{
    screen_session_t session;
    પૂર્ણાંક              realized_shape;
    bool             is_visible;
} SDL_CursorData;

પ્રકારવ્યાખ્યા સંરચના SDL_MouseData
{
    પૂર્ણાંક      x_prev;
    પૂર્ણાંક      y_prev;
} SDL_MouseData;

બાહ્ય screen_context_t * getContext();
બાહ્ય screen_event_t * getEvent();

બાહ્ય શૂન્ય handleKeyboardEvent(screen_event_t event);
બાહ્ય શૂન્ય handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
બાહ્ય bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *egl_path);
બાહ્ય SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, અચલ અક્ષર *proc);
બાહ્ય SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક interval);
બાહ્ય bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક *interval);
બાહ્ય bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
બાહ્ય bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
બાહ્ય શૂન્ય QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

બાહ્ય SDL_PixelFormat screenToPixelFormat(પૂર્ણાંક screen_format);
બાહ્ય bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
બાહ્ય bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
બાહ્ય bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

બાહ્ય શૂન્ય initMouse(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય quitMouse(SDL_VideoDevice *_this);

બાહ્ય પૂર્ણાંક QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
