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

#include "SDL_internal.h"

#ако defined(SDL_VIDEO_DRIVER_X11)

#include "SDL_x11video.h"
#include "SDL_x11settings.h"

static void UpdateContentScale(SDL_VideoDevice *_this)
{
    ако (_this) {
        float scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        за (цео i = 0; i < _this->num_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

static void X11_XsettingsNotify(const char *name, XSettingsAction action, XSettingsSetting *setting, void *data)
{
    SDL_VideoDevice *_this = data;

    ако (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

void X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, NULL, _this);
}

void X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    ако (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = NULL;
    }
}

void X11_HandleXsettingsEvent(SDL_VideoDevice *_this, const XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    ако (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

цео X11_GetXsettingsClientIntKey(XSettingsClient *client, const char *key, цео fallback_value) {
    XSettingsSetting *setting = NULL;
    цео res = fallback_value;

    ако (client) {
        ако (xsettings_client_get_setting(client, key, &setting) != XSETTINGS_SUCCESS) {
            goto no_key;
        }

        ако (setting->type != XSETTINGS_TYPE_INT) {
            goto no_key;
        }

        res = setting->data.v_int;
    }

no_key:
    ако (setting) {
        xsettings_setting_free(setting);
    }

    врати res;
}

цео X11_GetXsettingsIntKey(SDL_VideoDevice *_this, const char *key, цео fallback_value) {
    врати X11_GetXsettingsClientIntKey(_this->internal->xsettings_data.xsettings, key, fallback_value);
}

#endif // SDL_VIDEO_DRIVER_X11
