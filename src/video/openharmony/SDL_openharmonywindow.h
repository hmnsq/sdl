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
#ضمن "SDL_internal.h"

#جے_بنا_تعریف SDL_openharmonywindow_h_
#تعریف_کرو SDL_openharmonywindow_h_

#ضمن "../../core/openharmony/SDL_openharmony.h"
#ضمن "../SDL_egl_c.h"

خارجي bool OPENHARMONY_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي فراغ OPENHARMONY_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي SDL_Fullscreen_نتیجہ OPENHARMONY_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ OPENHARMONY_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ OPENHARMONY_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);

خارجي فراغ OPENHARMONY_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي SDL_کھڑکی *OPENHARMONY_کھڑکی;

بنية SDL_کھڑکی_انکڑے
{
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    صحيح has_وٹاندرا_interval;  // Save/Restore the swap interval / vsync
    صحيح وٹاندرا_interval;
#جے_انت
    bool backup_پورا;
    فراغ *native_xcomponent;
    فراغ *native_کھڑکی;
};

#جے_انت // SDL_openharmonywindow_h_
