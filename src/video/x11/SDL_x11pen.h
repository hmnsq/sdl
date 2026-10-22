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
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11pen_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
ਬਾਹਰੀ ਖਾਲੀ X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
ਬਾਹਰੀ ਖਾਲੀ X11_QuitPen(SDL_VideoDevice *_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
ਬਣਤਰ SDL_Video_ਅੰਕੜੇ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    ਪੂਰਨ x11_deviceid;
    ਪੂਰਨ valuator_for_axis[SDL_PEN_AXIS_ਗਿਣਤੀ];
    ਦਸ਼ਮਲਵ slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    ਦਸ਼ਮਲਵ rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    ਦਸ਼ਮਲਵ axis_min[SDL_PEN_AXIS_ਗਿਣਤੀ];
    ਦਸ਼ਮਲਵ axis_max[SDL_PEN_AXIS_ਗਿਣਤੀ];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
ਬਾਹਰੀ ਖਾਲੀ X11_PenAxesFromValuators(ਅਚਲ X11_PenHandle *pen,
                                     ਅਚਲ ਦੁੱਗਣਾ *ਨਿਵੇਸ਼_ਮੁੱਲਾਂ, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਨਕਾਬ, ਪੂਰਨ ਨਕਾਬ_len,
                                     ਦਸ਼ਮਲਵ axis_ਮੁੱਲਾਂ[SDL_PEN_AXIS_ਗਿਣਤੀ]);

// Add a pen (if this function's further checks validate it).
ਬਾਹਰੀ X11_PenHandle *X11_Maybe_ਜੋੜੋ_Pen_By_Device_ID(SDL_VideoDevice *_this, ਪੂਰਨ deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
ਬਾਹਰੀ ਖਾਲੀ X11_RemovePenByDeviceID(ਪੂਰਨ deviceid);

// Map X11 device ID to pen ID.
ਬਾਹਰੀ X11_PenHandle *X11_ਲੱਭੋ_Pen_By_Device_ID(ਪੂਰਨ deviceid);

// Notify that the pen has entered/left proximity
ਬਾਹਰੀ ਖਾਲੀ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ deviceid);

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2

#ਜੇ_ਅੰਤ // SDL_x11pen_h_
