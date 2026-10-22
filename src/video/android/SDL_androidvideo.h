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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_androidvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_androidvideo_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_Screen_Resolution(ಪೂರ್ಣಾಂಕ surface_ಅಗಲ, ಪೂರ್ಣಾಂಕ surface_ಎತ್ತರ, ಪೂರ್ಣಾಂಕ device_ಅಗಲ, ಪೂರ್ಣಾಂಕ device_ಎತ್ತರ, ದಶಮಾಂಶ density, ದಶಮಾಂಶ ದರ);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_Screen_HDRHeadroom(ದಶಮಾಂಶ headroom);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_Format(ಪೂರ್ಣಾಂಕ format_wanted, ಪೂರ್ಣಾಂಕ format_got);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_Orientation(SDL_DisplayOrientation orientation);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SendResize(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_Insets(ಪೂರ್ಣಾಂಕ ಎಡ, ಪೂರ್ಣಾಂಕ ಬಲ, ಪೂರ್ಣಾಂಕ ತುದಿ, ಪೂರ್ಣಾಂಕ bottom);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_Dark_ಬಹುಲಕ(bool enabled);

// Private display data

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ isPaused;
    ಪೂರ್ಣಾಂಕ isPausing;
};

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ Android_Surface_ಅಗಲ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ Android_Surface_ಎತ್ತರ;
ಬಾಹ್ಯ ದಶಮಾಂಶ Android_ScreenDensity;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_ಎಡ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_ಬಲ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_ತುದಿ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_Bottom;

#ಆದರೆ_ಅಂತ್ಯ // SDL_androidvideo_h_
