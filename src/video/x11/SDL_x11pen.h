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
#অন্তর্ভাৱ "../../SDL_internal.h"

#ifndef SDL_x11pen_h_
#define SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#অন্তর্ভাৱ "SDL_x11video.h"
#অন্তর্ভাৱ "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
বাহ্য শূন্য X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
বাহ্য শূন্য X11_QuitPen(SDL_VideoDevice *_this);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
সংরচনা SDL_VideoData;

#define SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

প্রকারনির্দেশ সংরচনা X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    পূর্ণাঙ্ক x11_deviceid;
    পূর্ণাঙ্ক valuator_for_axis[SDL_PEN_AXIS_গুনতি];
    ভিন্ন slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    ভিন্ন rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    ভিন্ন axis_min[SDL_PEN_AXIS_গুনতি];
    ভিন্ন axis_max[SDL_PEN_AXIS_গুনতি];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
বাহ্য শূন্য X11_PenAxesFromValuators(ধ্রুৱ X11_PenHandle *pen,
                                     ধ্রুৱ দ্ৱিগুণ *প্ৰবেশ_মানসমূহ, ধ্রুৱ unsigned ৱর্ণ *mask, পূর্ণাঙ্ক mask_len,
                                     ভিন্ন axis_মানসমূহ[SDL_PEN_AXIS_গুনতি]);

// Add a pen (if this function's further checks validate it).
বাহ্য X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, পূর্ণাঙ্ক deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
বাহ্য শূন্য X11_RemovePenByDeviceID(পূর্ণাঙ্ক deviceid);

// Map X11 device ID to pen ID.
বাহ্য X11_PenHandle *X11_FindPenByDeviceID(পূর্ণাঙ্ক deviceid);

// Notify that the pen has entered/left proximity
বাহ্য শূন্য X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক deviceid);

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#endif // SDL_x11pen_h_
