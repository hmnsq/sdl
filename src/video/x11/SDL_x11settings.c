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

#ܐܢ defined(SDL_VIDEO_DRIVER_X11)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11settings.h"

ساكن فراغ UpdateContentScale(SDL_VideoDevice *_this)
{
    ܐܢ (_this) {
        عائم scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        لكل (صحيح i = 0; i < _this->num_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

ساكن فراغ X11_XsettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *data)
{
    SDL_VideoDevice *_this = data;

    ܐܢ (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
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

    ܐܢ (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = عدم;
    }
}

فراغ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    ܐܢ (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

صحيح X11_GetXsettingsClientIntKey(XSettingsClient *client, ثابت حرف *key, صحيح fallback_value) {
    XSettingsSetting *setting = عدم;
    صحيح res = fallback_value;

    ܐܢ (client) {
        ܐܢ (xsettings_client_get_setting(client, key, &setting) != XSETTINGS_SUCCESS) {
            اذهب no_key;
        }

        ܐܢ (setting->type != XSETTINGS_TYPE_INT) {
            اذهب no_key;
        }

        res = setting->data.v_int;
    }

no_key:
    ܐܢ (setting) {
        xsettings_setting_free(setting);
    }

    ܦܢܐ res;
}

صحيح X11_GetXsettingsIntKey(SDL_VideoDevice *_this, ثابت حرف *key, صحيح fallback_value) {
    ܦܢܐ X11_GetXsettingsClientIntKey(_this->internal->xsettings_data.xsettings, key, fallback_value);
}

#endif // SDL_VIDEO_DRIVER_X11
