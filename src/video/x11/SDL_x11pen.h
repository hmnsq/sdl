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
#അന്തര്ഭാവ "../../SDL_internal.h"

#ifndef SDL_x11pen_h_
#define SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
ബാഹ്യ ശൂന്യം X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
ബാഹ്യ ശൂന്യം X11_QuitPen(SDL_VideoDevice *_this);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
ഘടന SDL_VideoData;

#define SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

തരനിർവചനം ഘടന X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    പൂർണ്ണസംഖ്യ x11_deviceid;
    പൂർണ്ണസംഖ്യ valuator_for_axis[SDL_PEN_AXIS_എണ്ണം];
    ദശാംശം slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    ദശാംശം rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    ദശാംശം axis_min[SDL_PEN_AXIS_എണ്ണം];
    ദശാംശം axis_max[SDL_PEN_AXIS_എണ്ണം];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
ബാഹ്യ ശൂന്യം X11_PenAxesFromValuators(സ്ഥിരം X11_PenHandle *pen,
                                     സ്ഥിരം ഇരട്ട *നിവേശം_മൂല്യങ്ങൾ, സ്ഥിരം unsigned അക്ഷരം *mask, പൂർണ്ണസംഖ്യ mask_len,
                                     ദശാംശം axis_മൂല്യങ്ങൾ[SDL_PEN_AXIS_എണ്ണം]);

// Add a pen (if this function's further checks validate it).
ബാഹ്യ X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
ബാഹ്യ ശൂന്യം X11_RemovePenByDeviceID(പൂർണ്ണസംഖ്യ deviceid);

// Map X11 device ID to pen ID.
ബാഹ്യ X11_PenHandle *X11_FindPenByDeviceID(പൂർണ്ണസംഖ്യ deviceid);

// Notify that the pen has entered/left proximity
ബാഹ്യ ശൂന്യം X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ deviceid);

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#endif // SDL_x11pen_h_
