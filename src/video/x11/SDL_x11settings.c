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

#ଯଦି defined(SDL_VIDEO_DRIVER_X11)

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11settings.h"

ସ୍ଥିର ଶୂନ୍ୟ UpdateContentScale(SDL_VideoDevice *_this)
{
    ଯଦି (_this) {
        ଦଶମିକ scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ X11_XsettingsNotify(ଅଚଳ ଅକ୍ଷର *name, XSettingsAction action, XSettingsSetting *setting, ଶୂନ୍ୟ *data)
{
    SDL_VideoDevice *_this = data;

    ଯଦି (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

ଶୂନ୍ୟ X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, ଖାଲି, _this);
}

ଶୂନ୍ୟ X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    ଯଦି (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = ଖାଲି;
    }
}

ଶୂନ୍ୟ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ଅଚଳ XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    ଯଦି (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା X11_Get_Xsettings_Client_Int_ଚାବି(XSettingsClient *client, ଅଚଳ ଅକ୍ଷର *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fallback_ମୂଲ୍ୟ) {
    XSettingsSetting *setting = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା res = fallback_ମୂଲ୍ୟ;

    ଯଦି (client) {
        ଯଦି (xsettings_client_get_setting(client, ଚାବି, &setting) != XSETTINGS_SUCCESS) {
            ଯାଅ no_ଚାବି;
        }

        ଯଦି (setting->type != XSETTINGS_TYPE_INT) {
            ଯାଅ no_ଚାବି;
        }

        res = setting->data.v_int;
    }

no_ଚାବି:
    ଯଦି (setting) {
        xsettings_setting_free(setting);
    }

    ଫେରନ୍ତୁ res;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା X11_Get_Xsettings_Int_ଚାବି(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fallback_ମୂଲ୍ୟ) {
    ଫେରନ୍ତୁ X11_Get_Xsettings_Client_Int_ଚାବି(_this->internal->xsettings_data.xsettings, ଚାବି, fallback_ମୂଲ୍ୟ);
}

#endif // SDL_VIDEO_DRIVER_X11
