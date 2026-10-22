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

#اگر_تعریف_نشده SDL_openharmonywindow_h_
#تعریف_کن SDL_openharmonywindow_h_

#ضمن "../../core/openharmony/SDL_openharmony.h"
#ضمن "../SDL_egl_c.h"

خارجي bool OPENHARMONY_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
خارجي فراغ OPENHARMONY_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي SDL_Fullscreen_نتیجه OPENHARMONY_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ OPENHARMONY_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ OPENHARMONY_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable);

خارجي فراغ OPENHARMONY_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي SDL_پنجره *OPENHARMONY_پنجره;

بنية SDL_پنجره_داده
{
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    صحيح has_جابجا_interval;  // Save/Restore the swap interval / vsync
    صحيح جابجا_interval;
#پایان_اگر
    bool backup_انجامشده;
    فراغ *native_xcomponent;
    فراغ *native_پنجره;
};

#پایان_اگر // SDL_openharmonywindow_h_
