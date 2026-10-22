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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_riscosdefs_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_riscosdefs_h_

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ sprite_area
{
    ਪੂਰਨ ਮਾਪ;  // +0
    ਪੂਰਨ ਗਿਣਤੀ_2; // +4
    ਪੂਰਨ ਸ਼ੁਰੂ; // +8
    ਪੂਰਨ ਸਿਰਾ;   // +12
} sprite_area;

SDL_COMPILE_ਸਮਾਂ_ASSERT(sprite_area, ਆਕਾਰ(sprite_area) == 16);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ sprite_ਸਿਰਲੇਖ
{
    ਪੂਰਨ ਅਗਲਾ;         // +0
    ਅੱਖਰ name[12];    // +4
    ਪੂਰਨ ਚੌੜਾਈ;        // +16
    ਪੂਰਨ ਉਚਾਈ;       // +20
    ਪੂਰਨ ਪਹਿਲਾ_ਦੋਆਧਾਰੀ_ਅੰਕ;    // +24
    ਪੂਰਨ ਆਖਰੀ_ਦੋਆਧਾਰੀ_ਅੰਕ;     // +28
    ਪੂਰਨ image_ਵਿੱਥ_2; // +32
    ਪੂਰਨ ਨਕਾਬ_ਵਿੱਥ;  // +36
    ਪੂਰਨ ਬਹੁਲਕ;         // +40
} sprite_ਸਿਰਲੇਖ;

SDL_COMPILE_ਸਮਾਂ_ASSERT(sprite_ਸਿਰਲੇਖ, ਆਕਾਰ(sprite_ਸਿਰਲੇਖ) == 44);

#ਜੇ_ਅੰਤ // SDL_riscosdefs_h_
