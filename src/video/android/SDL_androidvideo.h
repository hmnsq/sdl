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

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#ضمن "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
خارجي فراغ Android_SetScreenResolution(صحيح surfaceWidth, صحيح surfaceHeight, صحيح deviceWidth, صحيح deviceHeight, عائم density, عائم rate);
خارجي فراغ Android_SetScreenHDRHeadroom(عائم headroom);
خارجي فراغ Android_SetFormat(صحيح format_wanted, صحيح format_got);
خارجي فراغ Android_SetOrientation(SDL_DisplayOrientation orientation);
خارجي فراغ Android_SendResize(SDL_Window *window);
خارجي فراغ Android_SetWindowSafeAreaInsets(صحيح بایاں, صحيح دایاں, صحيح چوٹی, صحيح bottom);
خارجي فراغ Android_SetDarkMode(bool enabled);

// Private display data

بنية SDL_VideoData
{
    صحيح isPaused;
    صحيح isPausing;
};

خارجي صحيح Android_SurfaceWidth;
خارجي صحيح Android_SurfaceHeight;
خارجي عائم Android_ScreenDensity;
خارجي صحيح Android_Safe_Inset_بایاں;
خارجي صحيح Android_Safe_Inset_دایاں;
خارجي صحيح Android_Safe_Inset_چوٹی;
خارجي صحيح Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
