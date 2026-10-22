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

#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_X11)

#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11settings.h"

સ્થિર શૂન્ય UpdateContentScale(SDL_VideoDevice *_this)
{
    જો (_this) {
        દશાંશ scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        માટે (પૂર્ણાંક i = 0; i < _this->અંક_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

સ્થિર શૂન્ય X11_XsettingsNotify(અચલ અક્ષર *name, XSettingsAction action, XSettingsSetting *setting, શૂન્ય *data)
{
    SDL_VideoDevice *_this = data;

    જો (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

શૂન્ય X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, ખાલી, _this);
}

શૂન્ય X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    જો (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = ખાલી;
    }
}

શૂન્ય X11_HandleXsettingsEvent(SDL_VideoDevice *_this, અચલ XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    જો (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

પૂર્ણાંક X11_Get_Xsettings_Client_Int_ચાવી(XSettingsClient *client, અચલ અક્ષર *ચાવી, પૂર્ણાંક fallback_કિંમત) {
    XSettingsSetting *setting = ખાલી;
    પૂર્ણાંક res = fallback_કિંમત;

    જો (client) {
        જો (xsettings_client_get_setting(client, ચાવી, &setting) != XSETTINGS_SUCCESS) {
            જાઓ no_ચાવી;
        }

        જો (setting->type != XSETTINGS_TYPE_INT) {
            જાઓ no_ચાવી;
        }

        res = setting->data.v_int;
    }

no_ચાવી:
    જો (setting) {
        xsettings_setting_free(setting);
    }

    પાછા res;
}

પૂર્ણાંક X11_Get_Xsettings_Int_ચાવી(SDL_VideoDevice *_this, અચલ અક્ષર *ચાવી, પૂર્ણાંક fallback_કિંમત) {
    પાછા X11_Get_Xsettings_Client_Int_ચાવી(_this->internal->xsettings_data.xsettings, ચાવી, fallback_કિંમત);
}

#endif // SDL_VIDEO_DRIVER_X11
