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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_x11settings_h_
#घोषणा SDL_x11settings_h_

#समावेश <X11/Xlib.h>
#समावेश "xsettings-client.h"

#घोषणा SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR "Gdk/WindowScalingFactor"
#घोषणा SDL_XSETTINGS_GDK_UNSCALED_DPI "Gdk/UnscaledDPI"
#घोषणा SDL_XSETTINGS_XFT_DPI "Xft/DPI"

प्रकार काष्ठा X11_Settings_तथ्य {
    XSettingsClient *xsettings;
} SDLX11_Settings_तथ्य;

बाह्य व्योम X11_InitXsettings(SDL_VideoDevice *_this);
बाह्य व्योम X11_QuitXsettings(SDL_VideoDevice *_this);
बाह्य व्योम X11_HandleXsettingsEvent(SDL_VideoDevice *_this, स्थिर XEvent *xevent);
बाह्य पूर्णांक X11_Get_Xsettings_Int_कुंजी(SDL_VideoDevice *_this, स्थिर अक्षर *कुंजी, पूर्णांक fallback_मूल्य);

बाह्य पूर्णांक X11_Get_Xsettings_Client_Int_कुंजी(XSettingsClient *client, स्थिर अक्षर *कुंजी, पूर्णांक fallback_मूल्य);

#पूर्ण_अगर // SDL_x11settings_h_
