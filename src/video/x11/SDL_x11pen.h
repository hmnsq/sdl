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
#समावेश "../../SDL_internal.h"

#अगर_अघोषित SDL_x11pen_h_
#घोषणा SDL_x11pen_h_

// Pressure-sensitive pen support for X11.

#समावेश "SDL_x11video.h"
#समावेश "../../events/SDL_pen_c.h"

// Prep pen support (never fails; pens simply won't be added if there's a problem).
बाह्य व्योम X11_InitPen(SDL_VideoDevice *_this);

// Clean up pen support.
बाह्य व्योम X11_QuitPen(SDL_VideoDevice *_this);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2

// Forward definition for SDL_x11video.h
काष्ठा SDL_Video_तथ्य;

#घोषणा SDL_X11_PEN_AXIS_VALUATOR_MISSING -1

प्रकार काष्ठा X11_PenHandle
{
    SDL_PenID pen;
    bool is_eraser;
    पूर्णांक x11_deviceid;
    पूर्णांक valuator_for_axis[SDL_PEN_AXIS_गिनती];
    भग्न slider_bias;      // shift value to add to PEN_AXIS_SLIDER (before normalisation)
    भग्न rotation_bias;    // rotation to add to PEN_AXIS_ROTATION  (after normalisation)
    भग्न axis_min[SDL_PEN_AXIS_गिनती];
    भग्न axis_max[SDL_PEN_AXIS_गिनती];
} X11_PenHandle;

// Converts XINPUT2 valuators into pen axis information, including normalisation.
बाह्य व्योम X11_PenAxesFromValuators(स्थिर X11_PenHandle *pen,
                                     स्थिर द्विगुन *निवेश_मूल्यावली, स्थिर अचिन्हित अक्षर *mask, पूर्णांक mask_len,
                                     भग्न axis_मूल्यावली[SDL_PEN_AXIS_गिनती]);

// Add a pen (if this function's further checks validate it).
बाह्य X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, पूर्णांक deviceid);

// Remove a pen. It's okay if deviceid is bogus or not a pen, we'll check it.
बाह्य व्योम X11_RemovePenByDeviceID(पूर्णांक deviceid);

// Map X11 device ID to pen ID.
बाह्य X11_PenHandle *X11_FindPenByDeviceID(पूर्णांक deviceid);

// Notify that the pen has entered/left proximity
बाह्य व्योम X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक deviceid);

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2

#पूर्ण_अगर // SDL_x11pen_h_
