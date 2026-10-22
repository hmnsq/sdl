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

#اگر_غیر_تعریف_شدہ SDL_x11pen_h_
#تعریف_کرو SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#شامل "SDL_x11video.h"
#شامل "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
خارجی خالی X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
خارجی خالی X11_QuitPen(SDL_VideoDevice *_this);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
ساخت SDL_Video_ڈیٹا;

#تعریف_کرو SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

قسمتعریف ساخت X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    صحیح x11_deviceid;
    صحیح valuator_for_axis[SDL_PEN_AXIS_گنتی];
    اعشاری slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    اعشاری rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    اعشاری axis_min[SDL_PEN_AXIS_گنتی];
    اعشاری axis_max[SDL_PEN_AXIS_گنتی];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
خارجی خالی X11_PenAxesFromValuators(ثابت X11_PenHandle *pen,
                                     ثابت دوہرا *داخلہ_اقدار, ثابت غیرعلامتی حرف *نقاب, صحیح نقاب_len,
                                     اعشاری axis_اقدار[SDL_PEN_AXIS_گنتی]);

// Add a pen (if this function's further checks validate it).
خارجی X11_PenHandle *X11_Maybe_جوڑو_Pen_By_Device_ID(SDL_VideoDevice *_this, صحیح deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
خارجی خالی X11_RemovePenByDeviceID(صحیح deviceid);

// Map X11 device ID to pen ID.
خارجی X11_PenHandle *X11_ڈھونڈو_Pen_By_Device_ID(صحیح deviceid);

// Notify that the pen has entered/left proximity
خارجی خالی X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح deviceid);

#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2

#اگر_ختم // SDL_x11pen_h_
