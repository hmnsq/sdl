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
#அந்தர்பாவ "../../SDL_internal.h"

#ifndef SDL_x11pen_h_
#define SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
வெளி வெறுமை X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
வெளி வெறுமை X11_QuitPen(SDL_VideoDevice *_this);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
கட்டமைப்பு SDL_VideoData;

#define SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

வகைவரை கட்டமைப்பு X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    முழு x11_deviceid;
    முழு valuator_for_axis[SDL_PEN_AXIS_மொத்தம்];
    தசம slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    தசம rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    தசம axis_min[SDL_PEN_AXIS_மொத்தம்];
    தசம axis_max[SDL_PEN_AXIS_மொத்தம்];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
வெளி வெறுமை X11_PenAxesFromValuators(மாறிலி X11_PenHandle *pen,
                                     மாறிலி இரட்டை *உள்ளீடு_மதிப்புகள், மாறிலி unsigned எழுத்து *mask, முழு mask_len,
                                     தசம axis_மதிப்புகள்[SDL_PEN_AXIS_மொத்தம்]);

// Add a pen (if this function's further checks validate it).
வெளி X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, முழு deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
வெளி வெறுமை X11_RemovePenByDeviceID(முழு deviceid);

// Map X11 device ID to pen ID.
வெளி X11_PenHandle *X11_FindPenByDeviceID(முழு deviceid);

// Notify that the pen has entered/left proximity
வெளி வெறுமை X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, முழு deviceid);

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#endif // SDL_x11pen_h_
