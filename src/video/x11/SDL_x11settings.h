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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_x11settings_h_
#నిర్వచించు SDL_x11settings_h_

#అన్తర్భావ <X11/Xlib.h>
#అన్తర్భావ "xsettings-client.h"

#నిర్వచించు SDL_XSETTINGS_GDK_కిటికీ_SCALING_గుణకం "Gdk/WindowScalingFactor"
#నిర్వచించు SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#నిర్వచించు SDL_XSETTINGS_XFT_DPI "Xft/DPI"

రకనిర్వచనం నిర్మాణం X11_Settings_దత్తాంశం {
    XSettingsClient *xsettings;
} SDLX11_Settings_దత్తాంశం;

బాహ్య శూన్య X11_InitXsettings(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_QuitXsettings(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_HandleXsettingsEvent(SDL_VideoDevice *_this, స్థిరరాశి XEvent *xevent);
బాహ్య పూర్ణాంకం X11_Get_Xsettings_Int_కీలకం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *కీలకం, పూర్ణాంకం fallback_విలువ);

బాహ్య పూర్ణాంకం X11_Get_Xsettings_Client_Int_కీలకం(XSettingsClient *client, స్థిరరాశి అక్షరం *కీలకం, పూర్ణాంకం fallback_విలువ);

#అయితే_ముగింపు // SDL_x11settings_h_
