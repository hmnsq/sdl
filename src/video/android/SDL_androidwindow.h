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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_androidwindow_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_androidwindow_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/android/SDL_android.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

ਬਾਹਰੀ bool Android_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_Fullscreen_ਨਤੀਜਾ Android_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ਬਾਹਰੀ ਖਾਲੀ Android_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable);

ਬਾਹਰੀ ਖਾਲੀ Android_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_ਖਿੜਕੀ *Android_ਖਿੜਕੀ;

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    ਪੂਰਨ has_ਅਦਲਾ_ਬਦਲੀ_interval;  // Save/Restore the swap interval / vsync
    ਪੂਰਨ ਅਦਲਾ_ਬਦਲੀ_interval;
#ਜੇ_ਅੰਤ
    bool backup_ਪੂਰਾ;
    ANative_ਖਿੜਕੀ *native_ਖਿੜਕੀ;

};

#ਜੇ_ਅੰਤ // SDL_androidwindow_h_
