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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11settings_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11settings_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "xsettings-client.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_XSETTINGS_GDK_ਖਿੜਕੀ_SCALING_ਗੁਣਕ "Gdk/WindowScalingFactor"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_XSETTINGS_XFT_DPI "Xft/DPI"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ X11_Settings_ਅੰਕੜੇ {
    XSettingsClient *xsettings;
} SDLX11_Settings_ਅੰਕੜੇ;

ਬਾਹਰੀ ਖਾਲੀ X11_InitXsettings(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ X11_QuitXsettings(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ਅਚਲ XEvent *xevent);
ਬਾਹਰੀ ਪੂਰਨ X11_Get_Xsettings_Int_ਕੁੰਜੀ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ fallback_ਮੁੱਲ);

ਬਾਹਰੀ ਪੂਰਨ X11_Get_Xsettings_Client_Int_ਕੁੰਜੀ(XSettingsClient *client, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ fallback_ਮੁੱਲ);

#ਜੇ_ਅੰਤ // SDL_x11settings_h_
