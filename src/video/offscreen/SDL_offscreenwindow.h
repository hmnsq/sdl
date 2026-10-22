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

#که_نه_تعریف_شوی SDL_offscreenwindow_h
#تعریف_کړه SDL_offscreenwindow_h

#ضمن "SDL_offscreenvideo.h"

بنية SDL_کړکۍ_معلومات
{
    SDL_کړکۍ *sdl_کړکۍ;
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#د_که_پای
};

خارجي bool OFFSCREEN_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي فراغ OFFSCREEN_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ OFFSCREEN_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

#د_که_پای // SDL_offscreenwindow_h
