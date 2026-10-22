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

#جيڪڏهن_وصف_نه_ٿيل __SDL_QNX_H__
#وصف_ڪريو __SDL_QNX_H__

#ضمن "../SDL_sysvideo.h"
#ضمن <screen/screen.h>
#ضمن <EGL/egl.h>

تعريفنوع بنية SDL_Display_معلومات
{
    screen_display_t screen_display;
} SDL_Display_معلومات;

تعريفنوع بنية SDL_Display_گهڻائي_معلومات
{
    صحيح                   screen_format;
    screen_display_گهڻائي_t screen_display_گهڻائي;
} SDL_Display_گهڻائي_معلومات;

تعريفنوع بنية SDL_دري_معلومات
{
    screen_دري_t دري;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_دري_معلومات;

تعريفنوع بنية SDL_Cursor_معلومات
{
    screen_session_t session;
    صحيح              realized_shape;
    bool             is_visible;
} SDL_Cursor_معلومات;

تعريفنوع بنية SDL_Mouse_معلومات
{
    صحيح      x_prev;
    صحيح      y_prev;
} SDL_Mouse_معلومات;

خارجي screen_context_t * getContext();
خارجي screen_event_t * getEvent();

خارجي فراغ handleKeyboardEvent(screen_event_t event);
خارجي فراغ handle_اشارو_Event(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
خارجي bool QNX_GLES_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *egl_رستو);
خارجي SDL_Function_اشارو QNX_GLES_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool QNX_GLES_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool QNX_GLES_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool QNX_GLES_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_دري * دري, SDL_GLContext context);
خارجي bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي فراغ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

خارجي SDL_PixelFormat screen_منزل_Pixel_Format(صحيح screen_format);
خارجي bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
خارجي bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool QNX_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي);

خارجي فراغ initMouse(SDL_VideoDevice *_this);
خارجي فراغ quitMouse(SDL_VideoDevice *_this);

خارجي صحيح QNX_چونڊيو_Format(SDL_VideoDevice *_this, EGLConfig egl_conf);

#جيڪڏهن_پورو
