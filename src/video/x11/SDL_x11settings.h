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

#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_x11settings_h_
#تعریف_کرو SDL_x11settings_h_

#شامل <X11/Xlib.h>
#شامل "xsettings-client.h"

#تعریف_کرو SDL_XSETTINGS_GDK_کھڑکی_SCALING_ضربی_عدد "Gdk/WindowScalingFactor"
#تعریف_کرو SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#تعریف_کرو SDL_XSETTINGS_XFT_DPI "Xft/DPI"

قسمتعریف ساخت X11_Settings_ڈیٹا {
    XSettingsClient *xsettings;
} SDLX11_Settings_ڈیٹا;

خارجی خالی X11_InitXsettings(SDL_VideoDevice *_this);
خارجی خالی X11_QuitXsettings(SDL_VideoDevice *_this);
خارجی خالی X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent);
خارجی صحیح X11_Get_Xsettings_Int_کلید(SDL_VideoDevice *_this, ثابت حرف *کلید, صحیح fallback_قدر);

خارجی صحیح X11_Get_Xsettings_Client_Int_کلید(XSettingsClient *client, ثابت حرف *کلید, صحیح fallback_قدر);

#اگر_ختم // SDL_x11settings_h_
