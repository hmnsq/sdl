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

#جے_بنا_تعریف SDL_androidvideo_h_
#تعریف_کرو SDL_androidvideo_h_

#ضمن "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
خارجي فراغ Android_سیٹ_Screen_Resolution(صحيح surface_چوڑائی, صحيح surface_اچائی, صحيح device_چوڑائی, صحيح device_اچائی, عائم density, عائم شرح);
خارجي فراغ Android_سیٹ_Screen_HDRHeadroom(عائم headroom);
خارجي فراغ Android_سیٹ_Format(صحيح format_wanted, صحيح format_got);
خارجي فراغ Android_سیٹ_Orientation(SDL_DisplayOrientation orientation);
خارجي فراغ Android_SendResize(SDL_کھڑکی *کھڑکی);
خارجي فراغ Android_سیٹ_کھڑکی_محفوظ_Area_Insets(صحيح بایاں, صحيح دایاں, صحيح چوٹی, صحيح bottom);
خارجي فراغ Android_سیٹ_Dark_منوال(bool enabled);

// Private display data

بنية SDL_Video_انکڑے
{
    صحيح isPaused;
    صحيح isPausing;
};

خارجي صحيح Android_Surface_چوڑائی;
خارجي صحيح Android_Surface_اچائی;
خارجي عائم Android_ScreenDensity;
خارجي صحيح Android_محفوظ_Inset_بایاں;
خارجي صحيح Android_محفوظ_Inset_دایاں;
خارجي صحيح Android_محفوظ_Inset_چوٹی;
خارجي صحيح Android_محفوظ_Inset_Bottom;

#جے_انت // SDL_androidvideo_h_
