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

#ಯದಿ defined(SDL_VIDEO_DRIVER_X11)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"

ಸ್ಥಿರ ಶೂನ್ಯ UpdateContentScale(SDL_VideoDevice *_this)
{
    ಯದಿ (_this) {
        ಭಿನ್ನ scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_XsettingsNotify(ಧ್ರುವ ವರ್ಣ *name, XSettingsAction action, XSettingsSetting *setting, ಶೂನ್ಯ *data)
{
    SDL_VideoDevice *_this = data;

    ಯದಿ (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

ಶೂನ್ಯ X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, ರಿಕ್ತ, _this);
}

ಶೂನ್ಯ X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    ಯದಿ (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = ರಿಕ್ತ;
    }
}

ಶೂನ್ಯ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ಧ್ರುವ XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    ಯದಿ (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

ಪೂರ್ಣಾಙ್ಕ X11_Get_Xsettings_Client_Int_ಕೀಲಿ(XSettingsClient *client, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ fallback_ಮೌಲ್ಯ) {
    XSettingsSetting *setting = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ res = fallback_ಮೌಲ್ಯ;

    ಯದಿ (client) {
        ಯದಿ (xsettings_client_get_setting(client, ಕೀಲಿ, &setting) != XSETTINGS_SUCCESS) {
            ಗಚ್ಛ no_ಕೀಲಿ;
        }

        ಯದಿ (setting->type != XSETTINGS_TYPE_INT) {
            ಗಚ್ಛ no_ಕೀಲಿ;
        }

        res = setting->data.v_int;
    }

no_ಕೀಲಿ:
    ಯದಿ (setting) {
        xsettings_setting_free(setting);
    }

    ಪ್ರತ್ಯಾಗಮ res;
}

ಪೂರ್ಣಾಙ್ಕ X11_Get_Xsettings_Int_ಕೀಲಿ(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ fallback_ಮೌಲ್ಯ) {
    ಪ್ರತ್ಯಾಗಮ X11_Get_Xsettings_Client_Int_ಕೀಲಿ(_this->internal->xsettings_data.xsettings, ಕೀಲಿ, fallback_ಮೌಲ್ಯ);
}

#endif // SDL_VIDEO_DRIVER_X11
