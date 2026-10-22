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

ساکن خالی UpdateContentScale(SDL_VideoDevice *_this)
{
    اگر (_this) {
        اعشاری scale_ضربی_عدد_2 = X11_GetGlobalContentScaleForDevice(_this);
        برائے (صحیح i = 0; i < _this->عدد_displays; ++i) {
            SDL_سیٹ_Display_Content_Scale(_this->displays[i], scale_ضربی_عدد_2);
        }
    }
}

ساکن خالی X11_XsettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, خالی *ڈیٹا)
{
    SDL_VideoDevice *_this = ڈیٹا;

    اگر (SDL_strcmp(name, SDL_XSETTINGS_GDK_کھڑکی_SCALING_ضربی_عدد) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

خالی X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDLX11_Settings_ڈیٹا *xsettings_ڈیٹا = &ڈیٹا->xsettings_ڈیٹا;

    xsettings_ڈیٹا->xsettings = xsettings_client_new(ڈیٹا->display,
        DefaultScreen(ڈیٹا->display), X11_XsettingsNotify, تہی, _this);
}

خالی X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDLX11_Settings_ڈیٹا *xsettings_ڈیٹا = &ڈیٹا->xsettings_ڈیٹا;

    اگر (xsettings_ڈیٹا->xsettings) {
        xsettings_client_destroy(xsettings_ڈیٹا->xsettings);
        xsettings_ڈیٹا->xsettings = تہی;
    }
}

خالی X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDLX11_Settings_ڈیٹا *xsettings_ڈیٹا = &ڈیٹا->xsettings_ڈیٹا;

    اگر (xsettings_ڈیٹا->xsettings) {
        xsettings_client_process_event(xsettings_ڈیٹا->xsettings, xevent);
    }
}

صحیح X11_Get_Xsettings_Client_Int_کلید(XSettingsClient *client, ثابت حرف *کلید, صحیح fallback_قدر) {
    XSettingsSetting *setting = تہی;
    صحیح res = fallback_قدر;

    اگر (client) {
        اگر (xsettings_client_get_setting(client, کلید, &setting) != XSETTINGS_SUCCESS) {
            جاؤ no_کلید;
        }

        اگر (setting->type != XSETTINGS_TYPE_INT) {
            جاؤ no_کلید;
        }

        res = setting->ڈیٹا.v_int;
    }

no_کلید:
    اگر (setting) {
        xsettings_setting_free(setting);
    }

    واپس res;
}

صحیح X11_Get_Xsettings_Int_کلید(SDL_VideoDevice *_this, ثابت حرف *کلید, صحیح fallback_قدر) {
    واپس X11_Get_Xsettings_Client_Int_کلید(_this->اندرونی_2->xsettings_ڈیٹا.xsettings, کلید, fallback_قدر);
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
