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

#ضمن "SDL_internal.h"

#اگر_تعریف_نشده SDL_x11settings_h_
#تعریف_کن SDL_x11settings_h_

#ضمن <X11/Xlib.h>
#ضمن "xsettings-client.h"

#تعریف_کن SDL_XSETTINGS_GDK_پنجره_SCALING_ضریب "Gdk/WindowScalingFactor"
#تعریف_کن SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#تعریف_کن SDL_XSETTINGS_XFT_DPI "Xft/DPI"

تعريفنوع بنية X11_Settings_داده {
    XSettingsClient *xsettings;
} SDLX11_Settings_داده;

خارجي فراغ X11_InitXsettings(SDL_VideoDevice *_this);
خارجي فراغ X11_QuitXsettings(SDL_VideoDevice *_this);
خارجي فراغ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent);
خارجي صحيح X11_Get_Xsettings_Int_کلید(SDL_VideoDevice *_this, ثابت حرف *کلید, صحيح fallback_مقدار);

خارجي صحيح X11_Get_Xsettings_Client_Int_کلید(XSettingsClient *client, ثابت حرف *کلید, صحيح fallback_مقدار);

#پایان_اگر // SDL_x11settings_h_
