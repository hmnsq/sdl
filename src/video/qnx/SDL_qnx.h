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

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव <screen/screen.h>
#अन्तर्भाव <EGL/egl.h>

प्रकारनिर्देश संरचना SDL_DisplayData
{
    screen_display_t screen_display;
} SDL_DisplayData;

प्रकारनिर्देश संरचना SDL_DisplayModeData
{
    पूर्णाङ्क                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_DisplayModeData;

प्रकारनिर्देश संरचना SDL_WindowData
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_WindowData;

प्रकारनिर्देश संरचना SDL_CursorData
{
    screen_session_t session;
    पूर्णाङ्क              realized_shape;
    bool             is_visible;
} SDL_CursorData;

प्रकारनिर्देश संरचना SDL_MouseData
{
    पूर्णाङ्क      x_prev;
    पूर्णाङ्क      y_prev;
} SDL_MouseData;

बाह्य screen_context_t * getContext();
बाह्य screen_event_t * getEvent();

बाह्य शून्य handleKeyboardEvent(screen_event_t event);
बाह्य शून्य handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
बाह्य bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ध्रुव वर्ण *egl_path);
बाह्य SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क interval);
बाह्य bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
बाह्य bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
बाह्य bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य शून्य QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

बाह्य SDL_PixelFormat screenToPixelFormat(पूर्णाङ्क screen_format);
बाह्य bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
बाह्य bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

बाह्य शून्य initMouse(SDL_VideoDevice *_this);
बाह्य शून्य quitMouse(SDL_VideoDevice *_this);

बाह्य पूर्णाङ्क QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#endif
