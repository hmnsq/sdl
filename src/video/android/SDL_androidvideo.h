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

#اگر_تعریف_نشده SDL_androidvideo_h_
#تعریف_کن SDL_androidvideo_h_

#ضمن "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
خارجي فراغ Android_مجموعه_Screen_Resolution(صحيح surface_عرض, صحيح surface_ارتفاع, صحيح device_عرض, صحيح device_ارتفاع, عائم density, عائم نرخ);
خارجي فراغ Android_مجموعه_Screen_HDRHeadroom(عائم headroom);
خارجي فراغ Android_مجموعه_Format(صحيح format_wanted, صحيح format_got);
خارجي فراغ Android_مجموعه_Orientation(SDL_DisplayOrientation orientation);
خارجي فراغ Android_SendResize(SDL_پنجره *پنجره);
خارجي فراغ Android_مجموعه_پنجره_امن_Area_Insets(صحيح چپ, صحيح راست, صحيح بالاترین, صحيح bottom);
خارجي فراغ Android_مجموعه_Dark_نما(bool enabled);

// Private display data

بنية SDL_Video_داده
{
    صحيح isPaused;
    صحيح isPausing;
};

خارجي صحيح Android_Surface_عرض;
خارجي صحيح Android_Surface_ارتفاع;
خارجي عائم Android_ScreenDensity;
خارجي صحيح Android_امن_Inset_چپ;
خارجي صحيح Android_امن_Inset_راست;
خارجي صحيح Android_امن_Inset_بالاترین;
خارجي صحيح Android_امن_Inset_Bottom;

#پایان_اگر // SDL_androidvideo_h_
