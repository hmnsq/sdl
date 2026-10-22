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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_x11settings_h_
#define SDL_x11settings_h_

#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
#ಅನ್ತರ್ಭಾವ "xsettings-client.h"

#define SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR "Gdk/WindowScalingFactor"
#define SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#define SDL_XSETTINGS_XFT_DPI "Xft/DPI"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ X11_SettingsData {
    XSettingsClient *xsettings;
} SDLX11_SettingsData;

ಬಾಹ್ಯ ಶೂನ್ಯ X11_InitXsettings(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_QuitXsettings(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ಧ್ರುವ XEvent *xevent);
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ X11_Get_Xsettings_Int_ಕೀಲಿ(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ fallback_ಮೌಲ್ಯ);

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ X11_Get_Xsettings_Client_Int_ಕೀಲಿ(XSettingsClient *client, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ fallback_ಮೌಲ್ಯ);

#endif // SDL_x11settings_h_
