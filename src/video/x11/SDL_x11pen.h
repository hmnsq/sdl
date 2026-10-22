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
#అన్తర్భావ "../../SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_x11pen_h_
#నిర్వచించు SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
బాహ్య శూన్య X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
బాహ్య శూన్య X11_QuitPen(SDL_VideoDevice *_this);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
నిర్మాణం SDL_Video_దత్తాంశం;

#నిర్వచించు SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

రకనిర్వచనం నిర్మాణం X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    పూర్ణాంకం x11_deviceid;
    పూర్ణాంకం valuator_for_axis[SDL_PEN_AXIS_లెక్క];
    దశాంశం slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    దశాంశం rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    దశాంశం axis_min[SDL_PEN_AXIS_లెక్క];
    దశాంశం axis_max[SDL_PEN_AXIS_లెక్క];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
బాహ్య శూన్య X11_PenAxesFromValuators(స్థిరరాశి X11_PenHandle *pen,
                                     స్థిరరాశి ద్విగుణ *ఆదానం_విలువలు, స్థిరరాశి గుర్తులేని అక్షరం *ముసుగు, పూర్ణాంకం ముసుగు_len,
                                     దశాంశం axis_విలువలు[SDL_PEN_AXIS_లెక్క]);

// Add a pen (if this function's further checks validate it).
బాహ్య X11_PenHandle *X11_Maybe_కూడు_Pen_By_Device_ID(SDL_VideoDevice *_this, పూర్ణాంకం deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
బాహ్య శూన్య X11_RemovePenByDeviceID(పూర్ణాంకం deviceid);

// Map X11 device ID to pen ID.
బాహ్య X11_PenHandle *X11_కనుగొను_Pen_By_Device_ID(పూర్ణాంకం deviceid);

// Notify that the pen has entered/left proximity
బాహ్య శూన్య X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం deviceid);

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2

#అయితే_ముగింపు // SDL_x11pen_h_
