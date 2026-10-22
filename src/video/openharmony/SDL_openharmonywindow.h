/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_openharmonywindow_h_
#تعریف_کرو SDL_openharmonywindow_h_

#شامل "../../core/openharmony/SDL_openharmony.h"
#شامل "../SDL_egl_c.h"

خارجی bool OPENHARMONY_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی OPENHARMONY_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_Fullscreen_نتیجہ OPENHARMONY_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجی خالی OPENHARMONY_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی OPENHARMONY_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);

خارجی خالی OPENHARMONY_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_کھڑکی *OPENHARMONY_کھڑکی;

ساخت SDL_کھڑکی_ڈیٹا
{
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    صحیح has_تبادلہ_interval;  // Save/Restore the swap interval / vsync
    صحیح تبادلہ_interval;
#اگر_ختم
    bool backup_مکمل;
    خالی *native_xcomponent;
    خالی *native_کھڑکی;
};

#اگر_ختم // SDL_openharmonywindow_h_
