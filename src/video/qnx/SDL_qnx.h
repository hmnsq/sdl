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

#अगर_अघोषित __SDL_QNX_H__
#घोषणा __SDL_QNX_H__

#समावेश "../SDL_sysvideo.h"
#समावेश <screen/screen.h>
#समावेश <EGL/egl.h>

प्रकार काष्ठा SDL_Display_तथ्य
{
    screen_display_t screen_display;
} SDL_Display_तथ्य;

प्रकार काष्ठा SDL_Display_Mode_तथ्य
{
    पूर्णांक                   screen_format;
    screen_display_mode_t screen_display_mode;
} SDL_Display_Mode_तथ्य;

प्रकार काष्ठा SDL_Window_तथ्य
{
    screen_window_t window;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_Window_तथ्य;

प्रकार काष्ठा SDL_Cursor_तथ्य
{
    screen_session_t session;
    पूर्णांक              realized_shape;
    bool             is_visible;
} SDL_Cursor_तथ्य;

प्रकार काष्ठा SDL_Mouse_तथ्य
{
    पूर्णांक      x_पूर्व;
    पूर्णांक      y_पूर्व;
} SDL_Mouse_तथ्य;

बाह्य screen_context_t * getContext();
बाह्य screen_event_t * getEvent();

बाह्य व्योम handleKeyboardEvent(screen_event_t event);
बाह्य व्योम handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
बाह्य bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *egl_path);
बाह्य SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context);
बाह्य bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य व्योम QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

बाह्य SDL_PixelFormat screenToPixelFormat(पूर्णांक screen_format);
बाह्य bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
बाह्य bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

बाह्य व्योम initMouse(SDL_VideoDevice *_this);
बाह्य व्योम quitMouse(SDL_VideoDevice *_this);

बाह्य पूर्णांक QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf);

#पूर्ण_अगर
