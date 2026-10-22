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
#شامل "../../SDL_internal.h"

#ifndef SDL_x11pen_h_
#define SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#شامل "SDL_x11video.h"
#شامل "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
بیرونی تهی X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
بیرونی تهی X11_QuitPen(SDL_VideoDevice *_this);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
ساختار SDL_VideoData;

#define SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

تعریفنوع ساختار X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    صحیح x11_deviceid;
    صحیح valuator_for_axis[SDL_PEN_AXIS_شمار];
    اعشاری slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    اعشاری rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    اعشاری axis_min[SDL_PEN_AXIS_شمار];
    اعشاری axis_max[SDL_PEN_AXIS_شمار];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
بیرونی تهی X11_PenAxesFromValuators(ثابت X11_PenHandle *pen,
                                     ثابت دوگانه *درون_داد_مقادیر, ثابت unsigned نویسه *mask, صحیح mask_len,
                                     اعشاری axis_مقادیر[SDL_PEN_AXIS_شمار]);

// Add a pen (if this function's further checks validate it).
بیرونی X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, صحیح deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
بیرونی تهی X11_RemovePenByDeviceID(صحیح deviceid);

// Map X11 device ID to pen ID.
بیرونی X11_PenHandle *X11_FindPenByDeviceID(صحیح deviceid);

// Notify that the pen has entered/left proximity
بیرونی تهی X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, صحیح deviceid);

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#endif // SDL_x11pen_h_
