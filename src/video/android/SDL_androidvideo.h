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

#اگر_غیر_تعریف_شدہ SDL_androidvideo_h_
#تعریف_کرو SDL_androidvideo_h_

#شامل "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
خارجی خالی Android_سیٹ_Screen_Resolution(صحیح surface_چوڑائی, صحیح surface_اونچائی, صحیح device_چوڑائی, صحیح device_اونچائی, اعشاری density, اعشاری شرح);
خارجی خالی Android_سیٹ_Screen_HDRHeadroom(اعشاری headroom);
خارجی خالی Android_سیٹ_Format(صحیح format_wanted, صحیح format_got);
خارجی خالی Android_سیٹ_Orientation(SDL_DisplayOrientation orientation);
خارجی خالی Android_SendResize(SDL_کھڑکی *کھڑکی);
خارجی خالی Android_سیٹ_کھڑکی_محفوظ_Area_Insets(صحیح بایاں, صحیح دایاں, صحیح چوٹی, صحیح bottom);
خارجی خالی Android_سیٹ_Dark_منوال(bool enabled);

// Private display data

ساخت SDL_Video_ڈیٹا
{
    صحیح isPaused;
    صحیح isPausing;
};

خارجی صحیح Android_Surface_چوڑائی;
خارجی صحیح Android_Surface_اونچائی;
خارجی اعشاری Android_ScreenDensity;
خارجی صحیح Android_محفوظ_Inset_بایاں;
خارجی صحیح Android_محفوظ_Inset_دایاں;
خارجی صحیح Android_محفوظ_Inset_چوٹی;
خارجی صحیح Android_محفوظ_Inset_Bottom;

#اگر_ختم // SDL_androidvideo_h_
