/*
  Simple DirectMedia Layer
  Copyright 2024 Igalia S.L.

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

#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_x11settings_h_
#define SDL_x11settings_h_

#அந்தர்பாவ <X11/Xlib.h>
#அந்தர்பாவ "xsettings-client.h"

#define SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR "Gdk/WindowScalingFactor"
#define SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#define SDL_XSETTINGS_XFT_DPI "Xft/DPI"

வகைவரை கட்டமைப்பு X11_SettingsData {
    XSettingsClient *xsettings;
} SDLX11_SettingsData;

வெளி வெறுமை X11_InitXsettings(SDL_VideoDevice *_this);
வெளி வெறுமை X11_QuitXsettings(SDL_VideoDevice *_this);
வெளி வெறுமை X11_HandleXsettingsEvent(SDL_VideoDevice *_this, மாறிலி XEvent *xevent);
வெளி முழு X11_Get_Xsettings_Int_சாவி(SDL_VideoDevice *_this, மாறிலி எழுத்து *சாவி, முழு fallback_மதிப்பு);

வெளி முழு X11_Get_Xsettings_Client_Int_சாவி(XSettingsClient *client, மாறிலி எழுத்து *சாவி, முழு fallback_மதிப்பு);

#endif // SDL_x11settings_h_
