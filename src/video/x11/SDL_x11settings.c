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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_X11)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11settings.h"

ਸਥਿਰ ਖਾਲੀ UpdateContentScale(SDL_VideoDevice *_this)
{
    ਜੇ (_this) {
        ਦਸ਼ਮਲਵ scale_ਗੁਣਕ_2 = X11_GetGlobalContentScaleForDevice(_this);
        ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
            SDL_ਸੈੱਟ_Display_Content_Scale(_this->displays[i], scale_ਗੁਣਕ_2);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ X11_XsettingsNotify(ਅਚਲ ਅੱਖਰ *name, XSettingsAction action, XSettingsSetting *setting, ਖਾਲੀ *ਅੰਕੜੇ)
{
    SDL_VideoDevice *_this = ਅੰਕੜੇ;

    ਜੇ (SDL_strcmp(name, SDL_XSETTINGS_GDK_ਖਿੜਕੀ_SCALING_ਗੁਣਕ) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

ਖਾਲੀ X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDLX11_Settings_ਅੰਕੜੇ *xsettings_ਅੰਕੜੇ = &ਅੰਕੜੇ->xsettings_ਅੰਕੜੇ;

    xsettings_ਅੰਕੜੇ->xsettings = xsettings_client_new(ਅੰਕੜੇ->display,
        DefaultScreen(ਅੰਕੜੇ->display), X11_XsettingsNotify, ਨਿਰਾ, _this);
}

ਖਾਲੀ X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDLX11_Settings_ਅੰਕੜੇ *xsettings_ਅੰਕੜੇ = &ਅੰਕੜੇ->xsettings_ਅੰਕੜੇ;

    ਜੇ (xsettings_ਅੰਕੜੇ->xsettings) {
        xsettings_client_destroy(xsettings_ਅੰਕੜੇ->xsettings);
        xsettings_ਅੰਕੜੇ->xsettings = ਨਿਰਾ;
    }
}

ਖਾਲੀ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ਅਚਲ XEvent *xevent)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDLX11_Settings_ਅੰਕੜੇ *xsettings_ਅੰਕੜੇ = &ਅੰਕੜੇ->xsettings_ਅੰਕੜੇ;

    ਜੇ (xsettings_ਅੰਕੜੇ->xsettings) {
        xsettings_client_process_event(xsettings_ਅੰਕੜੇ->xsettings, xevent);
    }
}

ਪੂਰਨ X11_Get_Xsettings_Client_Int_ਕੁੰਜੀ(XSettingsClient *client, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ fallback_ਮੁੱਲ) {
    XSettingsSetting *setting = ਨਿਰਾ;
    ਪੂਰਨ res = fallback_ਮੁੱਲ;

    ਜੇ (client) {
        ਜੇ (xsettings_client_get_setting(client, ਕੁੰਜੀ, &setting) != XSETTINGS_SUCCESS) {
            ਜਾਓ no_ਕੁੰਜੀ;
        }

        ਜੇ (setting->type != XSETTINGS_TYPE_INT) {
            ਜਾਓ no_ਕੁੰਜੀ;
        }

        res = setting->ਅੰਕੜੇ.v_int;
    }

no_ਕੁੰਜੀ:
    ਜੇ (setting) {
        xsettings_setting_free(setting);
    }

    ਵਾਪਸ res;
}

ਪੂਰਨ X11_Get_Xsettings_Int_ਕੁੰਜੀ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ fallback_ਮੁੱਲ) {
    ਵਾਪਸ X11_Get_Xsettings_Client_Int_ਕੁੰਜੀ(_this->ਅੰਦਰੂਨੀ->xsettings_ਅੰਕੜੇ.xsettings, ਕੁੰਜੀ, fallback_ਮੁੱਲ);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
