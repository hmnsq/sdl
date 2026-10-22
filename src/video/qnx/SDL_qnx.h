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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __SDL_QNX_H__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __SDL_QNX_H__

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <screen/screen.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/egl.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    screen_display_t screen_display;
} SDL_Display_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ
{
    ਪੂਰਨ                   screen_format;
    screen_display_ਬਹੁਲਕ_t screen_display_ਬਹੁਲਕ;
} SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    screen_ਖਿੜਕੀ_t ਖਿੜਕੀ;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_ਖਿੜਕੀ_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    screen_session_t session;
    ਪੂਰਨ              realized_shape;
    bool             is_visible;
} SDL_Cursor_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Mouse_ਅੰਕੜੇ
{
    ਪੂਰਨ      x_prev;
    ਪੂਰਨ      y_prev;
} SDL_Mouse_ਅੰਕੜੇ;

ਬਾਹਰੀ screen_context_t * getContext();
ਬਾਹਰੀ screen_event_t * getEvent();

ਬਾਹਰੀ ਖਾਲੀ handleKeyboardEvent(screen_event_t event);
ਬਾਹਰੀ ਖਾਲੀ handle_ਸੂਚਕ_Event(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
ਬਾਹਰੀ bool QNX_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *egl_ਰਸਤਾ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ QNX_GLES_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool QNX_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool QNX_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
ਬਾਹਰੀ bool QNX_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, SDL_GLContext context);
ਬਾਹਰੀ bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
ਬਾਹਰੀ ਖਾਲੀ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

ਬਾਹਰੀ SDL_PixelFormat screen_ਮੰਜ਼ਿਲ_Pixel_Format(ਪੂਰਨ screen_format);
ਬਾਹਰੀ bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ਬਾਹਰੀ bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ਬਾਹਰੀ bool QNX_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);

ਬਾਹਰੀ ਖਾਲੀ initMouse(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ quitMouse(SDL_VideoDevice *_this);

ਬਾਹਰੀ ਪੂਰਨ QNX_ਚੁਣੋ_Format(SDL_VideoDevice *_this, EGLConfig egl_conf);

#ਜੇ_ਅੰਤ
