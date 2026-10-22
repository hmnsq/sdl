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

#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_X11)

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11settings.h"

நிலையான வெறுமை UpdateContentScale(SDL_VideoDevice *_this)
{
    எனில் (_this) {
        தசம scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

நிலையான வெறுமை X11_XsettingsNotify(மாறிலி எழுத்து *name, XSettingsAction action, XSettingsSetting *setting, வெறுமை *data)
{
    SDL_VideoDevice *_this = data;

    எனில் (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

வெறுமை X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, வெற்று, _this);
}

வெறுமை X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    எனில் (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = வெற்று;
    }
}

வெறுமை X11_HandleXsettingsEvent(SDL_VideoDevice *_this, மாறிலி XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    எனில் (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

முழு X11_Get_Xsettings_Client_Int_சாவி(XSettingsClient *client, மாறிலி எழுத்து *சாவி, முழு fallback_மதிப்பு) {
    XSettingsSetting *setting = வெற்று;
    முழு res = fallback_மதிப்பு;

    எனில் (client) {
        எனில் (xsettings_client_get_setting(client, சாவி, &setting) != XSETTINGS_SUCCESS) {
            செல் no_சாவி;
        }

        எனில் (setting->type != XSETTINGS_TYPE_INT) {
            செல் no_சாவி;
        }

        res = setting->data.v_int;
    }

no_சாவி:
    எனில் (setting) {
        xsettings_setting_free(setting);
    }

    திரும்பு res;
}

முழு X11_Get_Xsettings_Int_சாவி(SDL_VideoDevice *_this, மாறிலி எழுத்து *சாவி, முழு fallback_மதிப்பு) {
    திரும்பு X11_Get_Xsettings_Client_Int_சாவி(_this->internal->xsettings_data.xsettings, சாவி, fallback_மதிப்பு);
}

#endif // SDL_VIDEO_DRIVER_X11
