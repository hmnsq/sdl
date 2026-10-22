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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_riscosdefs_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_riscosdefs_h_

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ sprite_area
{
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;  // +0
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2; // +4
    ಪೂರ್ಣಾಂಕ ಆರಂಭ; // +8
    ಪೂರ್ಣಾಂಕ ಕೊನೆ;   // +12
} sprite_area;

SDL_COMPILE_ಸಮಯ_ASSERT(sprite_area, ಗಾತ್ರ(sprite_area) == 16);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ sprite_ಶೀರ್ಷಿಕೆ
{
    ಪೂರ್ಣಾಂಕ ಮುಂದಿನ;         // +0
    ಅಕ್ಷರ name[12];    // +4
    ಪೂರ್ಣಾಂಕ ಅಗಲ;        // +16
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ;       // +20
    ಪೂರ್ಣಾಂಕ ಮೊದಲ_ಬಿಟ್;    // +24
    ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_ಬಿಟ್;     // +28
    ಪೂರ್ಣಾಂಕ image_ಸ್ಥಾನಾಂತರ_2; // +32
    ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ_ಸ್ಥಾನಾಂತರ;  // +36
    ಪೂರ್ಣಾಂಕ ಬಹುಲಕ;         // +40
} sprite_ಶೀರ್ಷಿಕೆ;

SDL_COMPILE_ಸಮಯ_ASSERT(sprite_ಶೀರ್ಷಿಕೆ, ಗಾತ್ರ(sprite_ಶೀರ್ಷಿಕೆ) == 44);

#ಆದರೆ_ಅಂತ್ಯ // SDL_riscosdefs_h_
