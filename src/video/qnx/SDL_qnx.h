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

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ <screen/screen.h>
#ଅନ୍ତର୍ଭାଵ <EGL/egl.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_DisplayData
{
    screen_display_t screen_display;
} SDL_DisplayData;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_DisplayModeData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_DisplayModeData;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_WindowData
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_WindowData;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_CursorData
{
    screen_session_t session;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              realized_shape;
    bool             is_visible;
} SDL_CursorData;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_MouseData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା      x_prev;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା      y_prev;
} SDL_MouseData;

ବାହ୍ୟ screen_context_t * getContext();
ବାହ୍ୟ screen_event_t * getEvent();

ବାହ୍ୟ ଶୂନ୍ୟ handleKeyboardEvent(screen_event_t event);
ବାହ୍ୟ ଶୂନ୍ୟ handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
ବାହ୍ୟ bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *egl_path);
ବାହ୍ୟ SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc);
ବାହ୍ୟ SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval);
ବାହ୍ୟ bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval);
ବାହ୍ୟ bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
ବାହ୍ୟ bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
ବାହ୍ୟ ଶୂନ୍ୟ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

ବାହ୍ୟ SDL_PixelFormat screenToPixelFormat(ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen_format);
ବାହ୍ୟ bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ବାହ୍ୟ bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ବାହ୍ୟ bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

ବାହ୍ୟ ଶୂନ୍ୟ initMouse(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ quitMouse(SDL_VideoDevice *_this);

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
