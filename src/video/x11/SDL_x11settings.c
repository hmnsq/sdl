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

#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_X11)

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11settings.h"

স্থির শূন্য UpdateContentScale(SDL_VideoDevice *_this)
{
    যদি (_this) {
        দশমিক scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        জন্য (পূর্ণসংখ্যা i = 0; i < _this->অঙ্ক_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

স্থির শূন্য X11_XsettingsNotify(ধ্রুবক অক্ষর *name, XSettingsAction action, XSettingsSetting *setting, শূন্য *তথ্য)
{
    SDL_VideoDevice *_this = তথ্য;

    যদি (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

শূন্য X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    SDLX11_Settings_তথ্য *xsettings_তথ্য = &তথ্য->xsettings_তথ্য;

    xsettings_তথ্য->xsettings = xsettings_client_new(তথ্য->display,
        DefaultScreen(তথ্য->display), X11_XsettingsNotify, ফাঁকা, _this);
}

শূন্য X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    SDLX11_Settings_তথ্য *xsettings_তথ্য = &তথ্য->xsettings_তথ্য;

    যদি (xsettings_তথ্য->xsettings) {
        xsettings_client_destroy(xsettings_তথ্য->xsettings);
        xsettings_তথ্য->xsettings = ফাঁকা;
    }
}

শূন্য X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ধ্রুবক XEvent *xevent)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    SDLX11_Settings_তথ্য *xsettings_তথ্য = &তথ্য->xsettings_তথ্য;

    যদি (xsettings_তথ্য->xsettings) {
        xsettings_client_process_event(xsettings_তথ্য->xsettings, xevent);
    }
}

পূর্ণসংখ্যা X11_Get_Xsettings_Client_Int_চাবি(XSettingsClient *client, ধ্রুবক অক্ষর *চাবি, পূর্ণসংখ্যা fallback_মান) {
    XSettingsSetting *setting = ফাঁকা;
    পূর্ণসংখ্যা res = fallback_মান;

    যদি (client) {
        যদি (xsettings_client_get_setting(client, চাবি, &setting) != XSETTINGS_SUCCESS) {
            যাও no_চাবি;
        }

        যদি (setting->type != XSETTINGS_TYPE_INT) {
            যাও no_চাবি;
        }

        res = setting->তথ্য.v_int;
    }

no_চাবি:
    যদি (setting) {
        xsettings_setting_free(setting);
    }

    ফেরত res;
}

পূর্ণসংখ্যা X11_Get_Xsettings_Int_চাবি(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *চাবি, পূর্ণসংখ্যা fallback_মান) {
    ফেরত X11_Get_Xsettings_Client_Int_চাবি(_this->internal->xsettings_তথ্য.xsettings, চাবি, fallback_মান);
}

#endif // SDL_VIDEO_DRIVER_X11
