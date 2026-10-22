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

#إذا defined(SDL_VIDEO_DRIVER_X11)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11settings.h"

ساكن فراغ UpdateContentScale(SDL_VideoDevice *_this)
{
    إذا (_this) {
        عائم scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        لكل (صحيح i = 0; i < _this->اڠک_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

ساكن فراغ X11_XsettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *data)
{
    SDL_VideoDevice *_this = data;

    إذا (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

فراغ X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, عدم, _this);
}

فراغ X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    إذا (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = عدم;
    }
}

فراغ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    إذا (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

صحيح X11_Get_Xsettings_Client_Int_کونچي(XSettingsClient *client, ثابت حرف *کونچي, صحيح fallback_نيلاي) {
    XSettingsSetting *setting = عدم;
    صحيح res = fallback_نيلاي;

    إذا (client) {
        إذا (xsettings_client_get_setting(client, کونچي, &setting) != XSETTINGS_SUCCESS) {
            اذهب no_کونچي;
        }

        إذا (setting->type != XSETTINGS_TYPE_INT) {
            اذهب no_کونچي;
        }

        res = setting->data.v_int;
    }

no_کونچي:
    إذا (setting) {
        xsettings_setting_free(setting);
    }

    أرجع res;
}

صحيح X11_Get_Xsettings_Int_کونچي(SDL_VideoDevice *_this, ثابت حرف *کونچي, صحيح fallback_نيلاي) {
    أرجع X11_Get_Xsettings_Client_Int_کونچي(_this->internal->xsettings_data.xsettings, کونچي, fallback_نيلاي);
}

#endif // SDL_VIDEO_DRIVER_X11
