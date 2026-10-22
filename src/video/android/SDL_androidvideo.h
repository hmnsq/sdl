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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_androidvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_androidvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_Screen_Resolution(ਪੂਰਨ surface_ਚੌੜਾਈ, ਪੂਰਨ surface_ਉਚਾਈ, ਪੂਰਨ device_ਚੌੜਾਈ, ਪੂਰਨ device_ਉਚਾਈ, ਦਸ਼ਮਲਵ density, ਦਸ਼ਮਲਵ ਦਰ);
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_Screen_HDRHeadroom(ਦਸ਼ਮਲਵ headroom);
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_Format(ਪੂਰਨ format_wanted, ਪੂਰਨ format_got);
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_Orientation(SDL_DisplayOrientation orientation);
ਬਾਹਰੀ ਖਾਲੀ Android_SendResize(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_Insets(ਪੂਰਨ ਖੱਬਾ, ਪੂਰਨ ਸੱਜਾ, ਪੂਰਨ ਸਿਖਰ, ਪੂਰਨ bottom);
ਬਾਹਰੀ ਖਾਲੀ Android_ਸੈੱਟ_Dark_ਬਹੁਲਕ(bool enabled);

// Private display data

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    ਪੂਰਨ isPaused;
    ਪੂਰਨ isPausing;
};

ਬਾਹਰੀ ਪੂਰਨ Android_Surface_ਚੌੜਾਈ;
ਬਾਹਰੀ ਪੂਰਨ Android_Surface_ਉਚਾਈ;
ਬਾਹਰੀ ਦਸ਼ਮਲਵ Android_ScreenDensity;
ਬਾਹਰੀ ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_ਖੱਬਾ;
ਬਾਹਰੀ ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_ਸੱਜਾ;
ਬਾਹਰੀ ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_ਸਿਖਰ;
ਬਾਹਰੀ ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_Bottom;

#ਜੇ_ਅੰਤ // SDL_androidvideo_h_
