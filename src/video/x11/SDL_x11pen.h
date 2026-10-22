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
#ಅನ್ತರ್ಭಾವ "../../SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11pen_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
ಬಾಹ್ಯ ಶೂನ್ಯ X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
ಬಾಹ್ಯ ಶೂನ್ಯ X11_QuitPen(SDL_VideoDevice *_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
ರಚನೆ SDL_Video_ದತ್ತಾಂಶ;

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    ಪೂರ್ಣಾಂಕ x11_deviceid;
    ಪೂರ್ಣಾಂಕ valuator_for_axis[SDL_PEN_AXIS_ಎಣಿಕೆ];
    ದಶಮಾಂಶ slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    ದಶಮಾಂಶ rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    ದಶಮಾಂಶ axis_min[SDL_PEN_AXIS_ಎಣಿಕೆ];
    ದಶಮಾಂಶ axis_max[SDL_PEN_AXIS_ಎಣಿಕೆ];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
ಬಾಹ್ಯ ಶೂನ್ಯ X11_PenAxesFromValuators(ಸ್ಥಿರಾಂಕ X11_PenHandle *pen,
                                     ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *ಒಳಹರಿವು_ಮೌಲ್ಯಗಳು, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ಮುಖವಾಡ, ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ_len,
                                     ದಶಮಾಂಶ axis_ಮೌಲ್ಯಗಳು[SDL_PEN_AXIS_ಎಣಿಕೆ]);

// Add a pen (if this function's further checks validate it).
ಬಾಹ್ಯ X11_PenHandle *X11_Maybe_ಕೂಡಿಸು_Pen_By_Device_ID(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
ಬಾಹ್ಯ ಶೂನ್ಯ X11_RemovePenByDeviceID(ಪೂರ್ಣಾಂಕ deviceid);

// Map X11 device ID to pen ID.
ಬಾಹ್ಯ X11_PenHandle *X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(ಪೂರ್ಣಾಂಕ deviceid);

// Notify that the pen has entered/left proximity
ಬಾಹ್ಯ ಶೂನ್ಯ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ deviceid);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11pen_h_
