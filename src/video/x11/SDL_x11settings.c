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

#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11)

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11settings.h"

സ്ഥിതം ശൂന്യം UpdateContentScale(SDL_VideoDevice *_this)
{
    എങ്കിൽ (_this) {
        ദശാംശം scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

സ്ഥിതം ശൂന്യം X11_XsettingsNotify(സ്ഥിരം അക്ഷരം *name, XSettingsAction action, XSettingsSetting *setting, ശൂന്യം *data)
{
    SDL_VideoDevice *_this = data;

    എങ്കിൽ (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

ശൂന്യം X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    xsettings_data->xsettings = xsettings_client_new(data->display,
        DefaultScreen(data->display), X11_XsettingsNotify, ശൂന്യ, _this);
}

ശൂന്യം X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    എങ്കിൽ (xsettings_data->xsettings) {
        xsettings_client_destroy(xsettings_data->xsettings);
        xsettings_data->xsettings = ശൂന്യ;
    }
}

ശൂന്യം X11_HandleXsettingsEvent(SDL_VideoDevice *_this, സ്ഥിരം XEvent *xevent)
{
    SDL_VideoData *data = _this->internal;
    SDLX11_SettingsData *xsettings_data = &data->xsettings_data;

    എങ്കിൽ (xsettings_data->xsettings) {
        xsettings_client_process_event(xsettings_data->xsettings, xevent);
    }
}

പൂർണ്ണസംഖ്യ X11_Get_Xsettings_Client_Int_താക്കോൽ(XSettingsClient *client, സ്ഥിരം അക്ഷരം *താക്കോൽ, പൂർണ്ണസംഖ്യ fallback_മൂല്യം) {
    XSettingsSetting *setting = ശൂന്യ;
    പൂർണ്ണസംഖ്യ res = fallback_മൂല്യം;

    എങ്കിൽ (client) {
        എങ്കിൽ (xsettings_client_get_setting(client, താക്കോൽ, &setting) != XSETTINGS_SUCCESS) {
            പോകുക no_താക്കോൽ;
        }

        എങ്കിൽ (setting->type != XSETTINGS_TYPE_INT) {
            പോകുക no_താക്കോൽ;
        }

        res = setting->data.v_int;
    }

no_താക്കോൽ:
    എങ്കിൽ (setting) {
        xsettings_setting_free(setting);
    }

    തിരികെ res;
}

പൂർണ്ണസംഖ്യ X11_Get_Xsettings_Int_താക്കോൽ(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *താക്കോൽ, പൂർണ്ണസംഖ്യ fallback_മൂല്യം) {
    തിരികെ X11_Get_Xsettings_Client_Int_താക്കോൽ(_this->internal->xsettings_data.xsettings, താക്കോൽ, fallback_മൂല്യം);
}

#endif // SDL_VIDEO_DRIVER_X11
