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
        عائم scale_ضرب_ڪندڙ_2 = X11_GetGlobalContentScaleForDevice(_this);
        لكل (صحيح i = 0; i < _this->انگ_displays; ++i) {
            SDL_سيٽ_Display_Content_Scale(_this->displays[i], scale_ضرب_ڪندڙ_2);
        }
    }
}

ساكن فراغ X11_XsettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *معلومات)
{
    SDL_VideoDevice *_this = معلومات;

    إذا (SDL_strcmp(name, SDL_XSETTINGS_GDK_دري_SCALING_ضرب_ڪندڙ) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

فراغ X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    SDLX11_Settings_معلومات *xsettings_معلومات = &معلومات->xsettings_معلومات;

    xsettings_معلومات->xsettings = xsettings_client_new(معلومات->display,
        DefaultScreen(معلومات->display), X11_XsettingsNotify, عدم, _this);
}

فراغ X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    SDLX11_Settings_معلومات *xsettings_معلومات = &معلومات->xsettings_معلومات;

    إذا (xsettings_معلومات->xsettings) {
        xsettings_client_destroy(xsettings_معلومات->xsettings);
        xsettings_معلومات->xsettings = عدم;
    }
}

فراغ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    SDLX11_Settings_معلومات *xsettings_معلومات = &معلومات->xsettings_معلومات;

    إذا (xsettings_معلومات->xsettings) {
        xsettings_client_process_event(xsettings_معلومات->xsettings, xevent);
    }
}

صحيح X11_Get_Xsettings_Client_Int_ڪنجي(XSettingsClient *client, ثابت حرف *ڪنجي, صحيح fallback_قدر) {
    XSettingsSetting *setting = عدم;
    صحيح res = fallback_قدر;

    إذا (client) {
        إذا (xsettings_client_get_setting(client, ڪنجي, &setting) != XSETTINGS_SUCCESS) {
            اذهب no_ڪنجي;
        }

        إذا (setting->type != XSETTINGS_TYPE_INT) {
            اذهب no_ڪنجي;
        }

        res = setting->معلومات.v_int;
    }

no_ڪنجي:
    إذا (setting) {
        xsettings_setting_free(setting);
    }

    أرجع res;
}

صحيح X11_Get_Xsettings_Int_ڪنجي(SDL_VideoDevice *_this, ثابت حرف *ڪنجي, صحيح fallback_قدر) {
    أرجع X11_Get_Xsettings_Client_Int_ڪنجي(_this->اندروني->xsettings_معلومات.xsettings, ڪنجي, fallback_قدر);
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
