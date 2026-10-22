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

#اگر_غیر_تعریف_شدہ __SDL_QNX_H__
#تعریف_کرو __SDL_QNX_H__

#شامل "../SDL_sysvideo.h"
#شامل <screen/screen.h>
#شامل <EGL/egl.h>

قسمتعریف ساخت SDL_Display_ڈیٹا
{
    screen_display_t screen_display;
} SDL_Display_ڈیٹا;

قسمتعریف ساخت SDL_Display_منوال_ڈیٹا
{
    صحیح                   screen_format;
    screen_display_منوال_t screen_display_منوال;
} SDL_Display_منوال_ڈیٹا;

قسمتعریف ساخت SDL_کھڑکی_ڈیٹا
{
    screen_کھڑکی_t کھڑکی;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_کھڑکی_ڈیٹا;

قسمتعریف ساخت SDL_Cursor_ڈیٹا
{
    screen_session_t session;
    صحیح              realized_shape;
    bool             is_visible;
} SDL_Cursor_ڈیٹا;

قسمتعریف ساخت SDL_Mouse_ڈیٹا
{
    صحیح      x_پچھلا;
    صحیح      y_پچھلا;
} SDL_Mouse_ڈیٹا;

خارجی screen_context_t * getContext();
خارجی screen_event_t * getEvent();

خارجی خالی handleKeyboardEvent(screen_event_t event);
خارجی خالی handle_اشارہ_گر_Event(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
خارجی bool QNX_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *egl_راستہ);
خارجی SDL_Function_اشارہ_گر QNX_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool QNX_GLES_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool QNX_GLES_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);
خارجی bool QNX_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_GLContext context);
خارجی bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجی خالی QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

خارجی SDL_PixelFormat screen_مقصد_Pixel_Format(صحیح screen_format);
خارجی bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
خارجی bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجی bool QNX_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);

خارجی خالی initMouse(SDL_VideoDevice *_this);
خارجی خالی quitMouse(SDL_VideoDevice *_this);

خارجی صحیح QNX_انتخاب_Format(SDL_VideoDevice *_this, EGLConfig egl_conf);

#اگر_ختم
