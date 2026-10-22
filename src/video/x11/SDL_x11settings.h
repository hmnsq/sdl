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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11settings_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11settings_h_

#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
#ಅನ್ತರ್ಭಾವ "xsettings-client.h"

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_XSETTINGS_GDK_ಕಿಟಕಿ_SCALING_ಗುಣಕ "Gdk/WindowScalingFactor"
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_XSETTINGS_XFT_DPI "Xft/DPI"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ X11_Settings_ದತ್ತಾಂಶ {
    XSettingsClient *xsettings;
} SDLX11_Settings_ದತ್ತಾಂಶ;

ಬಾಹ್ಯ ಶೂನ್ಯ X11_InitXsettings(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_QuitXsettings(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XEvent *xevent);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ X11_Get_Xsettings_Int_ಕೀಲಿ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ fallback_ಮೌಲ್ಯ);

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ X11_Get_Xsettings_Client_Int_ಕೀಲಿ(XSettingsClient *client, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ fallback_ಮೌಲ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11settings_h_
