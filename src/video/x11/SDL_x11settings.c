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

#اگر defined(SDL_VIDEO_DRIVER_X11)

#شامل "SDL_x11video.h"
#شامل "SDL_x11settings.h"

ایستا تهی UpdateContentScale(SDL_VideoDevice *_this)
{
    اگر (_this) {
        اعشاری scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        برای (صحیح i = 0; i < _this->رقم_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

ایستا تهی X11_XsettingsNotify(ثابت نویسه *name, XSettingsAction action, XSettingsSetting *setting, تهی *data)
{
    SDL_VideoDevice *_this = data;

    اگر (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

تهی X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, پوچ, _this);
}

تهی X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    اگر (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = پوچ;
    }
}

تهی X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    اگر (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

صحیح X11_Get_Xsettings_Client_Int_کلید(XSettingsClient *client, ثابت نویسه *کلید, صحیح fallback_مقدار) {
    XSettingsSetting *setting = پوچ;
    صحیح res = fallback_مقدار;

    اگر (client) {
        اگر (xsettings_client_get_setting(client, کلید, &setting) != XSETTINGS_SUCCESS) {
            برو no_کلید;
        }

        اگر (setting->type != XSETTINGS_TYPE_INT) {
            برو no_کلید;
        }

        res = setting->data.v_int;
    }

no_کلید:
    اگر (setting) {
        xsettings_setting_free(setting);
    }

    بازگشت res;
}

صحیح X11_Get_Xsettings_Int_کلید(SDL_VideoDevice *_this, ثابت نویسه *کلید, صحیح fallback_مقدار) {
    بازگشت X11_Get_Xsettings_Client_Int_کلید(_this->internal->xsettings_data.xsettings, کلید, fallback_مقدار);
}

#endif // SDL_VIDEO_DRIVER_X11
