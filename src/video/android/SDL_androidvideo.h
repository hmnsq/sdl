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

#که_نه_تعریف_شوی SDL_androidvideo_h_
#تعریف_کړه SDL_androidvideo_h_

#ضمن "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
خارجي فراغ Android_سېټ_Screen_Resolution(صحيح surface_پلنوالی, صحيح surface_لوړوالی, صحيح device_پلنوالی, صحيح device_لوړوالی, عائم density, عائم شرح);
خارجي فراغ Android_سېټ_Screen_HDRHeadroom(عائم headroom);
خارجي فراغ Android_سېټ_Format(صحيح format_wanted, صحيح format_got);
خارجي فراغ Android_سېټ_Orientation(SDL_DisplayOrientation orientation);
خارجي فراغ Android_SendResize(SDL_کړکۍ *کړکۍ);
خارجي فراغ Android_سېټ_کړکۍ_خوندي_Area_Insets(صحيح کیڼ, صحيح ښی, صحيح سر, صحيح bottom);
خارجي فراغ Android_سېټ_Dark_ډېرپېښ(bool enabled);

// Private display data

بنية SDL_Video_معلومات
{
    صحيح isPaused;
    صحيح isPausing;
};

خارجي صحيح Android_Surface_پلنوالی;
خارجي صحيح Android_Surface_لوړوالی;
خارجي عائم Android_ScreenDensity;
خارجي صحيح Android_خوندي_Inset_کیڼ;
خارجي صحيح Android_خوندي_Inset_ښی;
خارجي صحيح Android_خوندي_Inset_سر;
خارجي صحيح Android_خوندي_Inset_Bottom;

#د_که_پای // SDL_androidvideo_h_
