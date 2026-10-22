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
#ଅନ୍ତର୍ଭାଵ "../../SDL_internal.h"

#ifndef SDL_x11pen_h_
#define SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
ବାହ୍ୟ ଶୂନ୍ୟ X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
ବାହ୍ୟ ଶୂନ୍ୟ X11_QuitPen(SDL_VideoDevice *_this);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
ସଂରଚନା SDL_VideoData;

#define SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x11_deviceid;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା valuator_for_axis[SDL_PEN_AXIS_ଗଣନା];
    ଦଶମିକ slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    ଦଶମିକ rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    ଦଶମିକ axis_min[SDL_PEN_AXIS_ଗଣନା];
    ଦଶମିକ axis_max[SDL_PEN_AXIS_ଗଣନା];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
ବାହ୍ୟ ଶୂନ୍ୟ X11_PenAxesFromValuators(ଅଚଳ X11_PenHandle *pen,
                                     ଅଚଳ ଦ୍ୱିଗୁଣ *ନିବେଶ_ମୂଲ୍ୟଗୁଡ଼ିକ, ଅଚଳ unsigned ଅକ୍ଷର *mask, ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask_len,
                                     ଦଶମିକ axis_ମୂଲ୍ୟଗୁଡ଼ିକ[SDL_PEN_AXIS_ଗଣନା]);

// Add a pen (if this function's further checks validate it).
ବାହ୍ୟ X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
ବାହ୍ୟ ଶୂନ୍ୟ X11_RemovePenByDeviceID(ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid);

// Map X11 device ID to pen ID.
ବାହ୍ୟ X11_PenHandle *X11_FindPenByDeviceID(ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid);

// Notify that the pen has entered/left proximity
ବାହ୍ୟ ଶୂନ୍ୟ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid);

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#endif // SDL_x11pen_h_
