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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"

ಸ್ಥಿರ ಶೂನ್ಯ UpdateContentScale(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this) {
        ದಶಮಾಂಶ scale_ಗುಣಕ_2 = X11_GetGlobalContentScaleForDevice(_this);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_ಗಣ_Display_Content_Scale(_this->displays[i], scale_ಗುಣಕ_2);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_XsettingsNotify(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, XSettingsAction action, XSettingsSetting *setting, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    SDL_VideoDevice *_this = ದತ್ತಾಂಶ;

    ಆದರೆ (SDL_strcmp(name, SDL_XSETTINGS_GDK_ಕಿಟಕಿ_SCALING_ಗುಣಕ) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

ಶೂನ್ಯ X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDLX11_Settings_ದತ್ತಾಂಶ *xsettings_ದತ್ತಾಂಶ = &ದತ್ತಾಂಶ->xsettings_ದತ್ತಾಂಶ;

    xsettings_ದತ್ತಾಂಶ->xsettings = xsettings_client_new(ದತ್ತಾಂಶ->display,
        DefaultScreen(ದತ್ತಾಂಶ->display), X11_XsettingsNotify, ಖಾಲಿ, _this);
}

ಶೂನ್ಯ X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDLX11_Settings_ದತ್ತಾಂಶ *xsettings_ದತ್ತಾಂಶ = &ದತ್ತಾಂಶ->xsettings_ದತ್ತಾಂಶ;

    ಆದರೆ (xsettings_ದತ್ತಾಂಶ->xsettings) {
        xsettings_client_destroy(xsettings_ದತ್ತಾಂಶ->xsettings);
        xsettings_ದತ್ತಾಂಶ->xsettings = ಖಾಲಿ;
    }
}

ಶೂನ್ಯ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XEvent *xevent)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDLX11_Settings_ದತ್ತಾಂಶ *xsettings_ದತ್ತಾಂಶ = &ದತ್ತಾಂಶ->xsettings_ದತ್ತಾಂಶ;

    ಆದರೆ (xsettings_ದತ್ತಾಂಶ->xsettings) {
        xsettings_client_process_event(xsettings_ದತ್ತಾಂಶ->xsettings, xevent);
    }
}

ಪೂರ್ಣಾಂಕ X11_Get_Xsettings_Client_Int_ಕೀಲಿ(XSettingsClient *client, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ fallback_ಮೌಲ್ಯ) {
    XSettingsSetting *setting = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ res = fallback_ಮೌಲ್ಯ;

    ಆದರೆ (client) {
        ಆದರೆ (xsettings_client_get_setting(client, ಕೀಲಿ, &setting) != XSETTINGS_SUCCESS) {
            ಹೋಗು no_ಕೀಲಿ;
        }

        ಆದರೆ (setting->type != XSETTINGS_TYPE_INT) {
            ಹೋಗು no_ಕೀಲಿ;
        }

        res = setting->ದತ್ತಾಂಶ.v_int;
    }

no_ಕೀಲಿ:
    ಆದರೆ (setting) {
        xsettings_setting_free(setting);
    }

    ಹಿಂತಿರುಗಿ res;
}

ಪೂರ್ಣಾಂಕ X11_Get_Xsettings_Int_ಕೀಲಿ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ fallback_ಮೌಲ್ಯ) {
    ಹಿಂತಿರುಗಿ X11_Get_Xsettings_Client_Int_ಕೀಲಿ(_this->ಆಂತರಿಕ->xsettings_ದತ್ತಾಂಶ.xsettings, ಕೀಲಿ, fallback_ಮೌಲ್ಯ);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
