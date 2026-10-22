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
#अन्तर्भाव "../../SDL_internal.h"

#यदि_अपरिभाषितम् SDL_x11pen_h_
#परिभाषय SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
बाह्य शून्य X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
बाह्य शून्य X11_QuitPen(SDL_VideoDevice *_this);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
संरचना SDL_Video_दत्त;

#परिभाषय SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

प्रकारनिर्देश संरचना X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    पूर्णाङ्क x11_deviceid;
    पूर्णाङ्क valuator_for_axis[SDL_PEN_AXIS_गणनम्];
    भिन्न slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    भिन्न rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    भिन्न axis_min[SDL_PEN_AXIS_गणनम्];
    भिन्न axis_max[SDL_PEN_AXIS_गणनम्];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
बाह्य शून्य X11_PenAxesFromValuators(ध्रुव X11_PenHandle *pen,
                                     ध्रुव द्विगुण *निवेशः_मानानि, ध्रुव अचिह्नित वर्ण *आवरणम्, पूर्णाङ्क आवरणम्_len,
                                     भिन्न axis_मानानि[SDL_PEN_AXIS_गणनम्]);

// Add a pen (if this function's further checks validate it).
बाह्य X11_PenHandle *X11_Maybe_सङ्कलय_Pen_By_Device_ID(SDL_VideoDevice *_this, पूर्णाङ्क deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
बाह्य शून्य X11_RemovePenByDeviceID(पूर्णाङ्क deviceid);

// Map X11 device ID to pen ID.
बाह्य X11_PenHandle *X11_FindPenByDeviceID(पूर्णाङ्क deviceid);

// Notify that the pen has entered/left proximity
बाह्य शून्य X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क deviceid);

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2

#यदि_अन्तः // SDL_x11pen_h_
