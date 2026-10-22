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

#اگر_تعریف_نشده __SDL_QNX_H__
#تعریف_کن __SDL_QNX_H__

#ضمن "../SDL_sysvideo.h"
#ضمن <screen/screen.h>
#ضمن <EGL/egl.h>

تعريفنوع بنية SDL_Display_داده
{
    screen_display_t screen_display;
} SDL_Display_داده;

تعريفنوع بنية SDL_Display_نما_داده
{
    صحيح                   screen_format;
    screen_display_نما_t screen_display_نما;
} SDL_Display_نما_داده;

تعريفنوع بنية SDL_پنجره_داده
{
    screen_پنجره_t پنجره;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_پنجره_داده;

تعريفنوع بنية SDL_Cursor_داده
{
    screen_session_t session;
    صحيح              realized_shape;
    bool             is_visible;
} SDL_Cursor_داده;

تعريفنوع بنية SDL_Mouse_داده
{
    صحيح      x_prev;
    صحيح      y_prev;
} SDL_Mouse_داده;

خارجي screen_context_t * getContext();
خارجي screen_event_t * getEvent();

خارجي فراغ handleKeyboardEvent(screen_event_t event);
خارجي فراغ handle_اشاره_گر_Event(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
خارجي bool QNX_GLES_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *egl_مسیر);
خارجي SDL_Function_اشاره_گر QNX_GLES_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool QNX_GLES_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool QNX_GLES_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool QNX_GLES_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره * پنجره, SDL_GLContext context);
خارجي bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي فراغ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

خارجي SDL_PixelFormat screen_مقصد_Pixel_Format(صحيح screen_format);
خارجي bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
خارجي bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool QNX_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);

خارجي فراغ initMouse(SDL_VideoDevice *_this);
خارجي فراغ quitMouse(SDL_VideoDevice *_this);

خارجي صحيح QNX_انتخاب_Format(SDL_VideoDevice *_this, EGLConfig egl_conf);

#پایان_اگر
