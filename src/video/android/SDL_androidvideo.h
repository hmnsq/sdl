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

#جيڪڏهن_وصف_نه_ٿيل SDL_androidvideo_h_
#وصف_ڪريو SDL_androidvideo_h_

#ضمن "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
خارجي فراغ Android_سيٽ_Screen_Resolution(صحيح surface_ويڪر, صحيح surface_اوچائي, صحيح device_ويڪر, صحيح device_اوچائي, عائم density, عائم شرح);
خارجي فراغ Android_سيٽ_Screen_HDRHeadroom(عائم headroom);
خارجي فراغ Android_سيٽ_Format(صحيح format_wanted, صحيح format_got);
خارجي فراغ Android_سيٽ_Orientation(SDL_DisplayOrientation orientation);
خارجي فراغ Android_SendResize(SDL_دري *دري);
خارجي فراغ Android_سيٽ_دري_محفوظ_Area_Insets(صحيح کاٻو, صحيح ساڄو, صحيح چوٽي, صحيح bottom);
خارجي فراغ Android_سيٽ_Dark_گهڻائي(bool enabled);

// Private display data

بنية SDL_Video_معلومات
{
    صحيح isPaused;
    صحيح isPausing;
};

خارجي صحيح Android_Surface_ويڪر;
خارجي صحيح Android_Surface_اوچائي;
خارجي عائم Android_ScreenDensity;
خارجي صحيح Android_محفوظ_Inset_کاٻو;
خارجي صحيح Android_محفوظ_Inset_ساڄو;
خارجي صحيح Android_محفوظ_Inset_چوٽي;
خارجي صحيح Android_محفوظ_Inset_Bottom;

#جيڪڏهن_پورو // SDL_androidvideo_h_
