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

#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_X11)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11settings.h"

स्थिर शून्य UpdateContentScale(SDL_VideoDevice *_this)
{
    यदि (_this) {
        भिन्न scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        प्रति (पूर्णाङ्क i = 0; i < _this->अंक_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

स्थिर शून्य X11_XsettingsNotify(ध्रुव वर्ण *name, XSettingsAction action, XSettingsSetting *setting, शून्य *data)
{
    SDL_VideoDevice *_this = data;

    यदि (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

शून्य X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, रिक्त, _this);
}

शून्य X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    यदि (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = रिक्त;
    }
}

शून्य X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ध्रुव XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    यदि (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

पूर्णाङ्क X11_Get_Xsettings_Client_Int_कुंजी(XSettingsClient *client, ध्रुव वर्ण *कुंजी, पूर्णाङ्क fallback_मूल्य) {
    XSettingsSetting *setting = रिक्त;
    पूर्णाङ्क res = fallback_मूल्य;

    यदि (client) {
        यदि (xsettings_client_get_setting(client, कुंजी, &setting) != XSETTINGS_SUCCESS) {
            गच्छ no_कुंजी;
        }

        यदि (setting->type != XSETTINGS_TYPE_INT) {
            गच्छ no_कुंजी;
        }

        res = setting->data.v_int;
    }

no_कुंजी:
    यदि (setting) {
        xsettings_setting_free(setting);
    }

    प्रत्यागम res;
}

पूर्णाङ्क X11_Get_Xsettings_Int_कुंजी(SDL_VideoDevice *_this, ध्रुव वर्ण *कुंजी, पूर्णाङ्क fallback_मूल्य) {
    प्रत्यागम X11_Get_Xsettings_Client_Int_कुंजी(_this->internal->xsettings_data.xsettings, कुंजी, fallback_मूल्य);
}

#endif // SDL_VIDEO_DRIVER_X11
