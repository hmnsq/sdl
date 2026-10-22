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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_x11settings_h_
#define SDL_x11settings_h_

#ଅନ୍ତର୍ଭାଵ <X11/Xlib.h>
#ଅନ୍ତର୍ଭାଵ "xsettings-client.h"

#define SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR "Gdk/WindowScalingFactor"
#define SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#define SDL_XSETTINGS_XFT_DPI "Xft/DPI"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା X11_SettingsData {
    XSettingsClient *xsettings;
} SDLX11_SettingsData;

ବାହ୍ୟ ଶୂନ୍ୟ X11_InitXsettings(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ X11_QuitXsettings(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ଅଚଳ XEvent *xevent);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା X11_Get_Xsettings_Int_ଚାବି(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fallback_ମୂଲ୍ୟ);

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା X11_Get_Xsettings_Client_Int_ଚାବି(XSettingsClient *client, ଅଚଳ ଅକ୍ଷର *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fallback_ମୂଲ୍ୟ);

#endif // SDL_x11settings_h_
