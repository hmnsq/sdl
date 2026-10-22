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
#ضمن "../../SDL_internal.h"

#که_نه_تعریف_شوی SDL_x11pen_h_
#تعریف_کړه SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#ضمن "SDL_x11video.h"
#ضمن "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
خارجي فراغ X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
خارجي فراغ X11_QuitPen(SDL_VideoDevice *_this);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
بنية SDL_Video_معلومات;

#تعریف_کړه SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

تعريفنوع بنية X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    صحيح x11_deviceid;
    صحيح valuator_for_axis[SDL_PEN_AXIS_شمېر];
    عائم slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    عائم rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    عائم axis_min[SDL_PEN_AXIS_شمېر];
    عائم axis_max[SDL_PEN_AXIS_شمېر];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
خارجي فراغ X11_PenAxesFromValuators(ثابت X11_PenHandle *pen,
                                     ثابت مزدوج *ننوت_ارزښتونه, ثابت بینښه حرف *ماسک, صحيح ماسک_len,
                                     عائم axis_ارزښتونه[SDL_PEN_AXIS_شمېر]);

// Add a pen (if this function's further checks validate it).
خارجي X11_PenHandle *X11_Maybe_جمع_کړه_Pen_By_Device_ID(SDL_VideoDevice *_this, صحيح deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
خارجي فراغ X11_RemovePenByDeviceID(صحيح deviceid);

// Map X11 device ID to pen ID.
خارجي X11_PenHandle *X11_پیدا_کړه_Pen_By_Device_ID(صحيح deviceid);

// Notify that the pen has entered/left proximity
خارجي فراغ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح deviceid);

#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2

#د_که_پای // SDL_x11pen_h_
