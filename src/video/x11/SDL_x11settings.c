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
        عائم scale_ضارب_2 = X11_GetGlobalContentScaleForDevice(_this);
        لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
            SDL_سیٹ_Display_Content_Scale(_this->displays[i], scale_ضارب_2);
        }
    }
}

ساكن فراغ X11_XsettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *انکڑے)
{
    SDL_VideoDevice *_this = انکڑے;

    إذا (SDL_strcmp(name, SDL_XSETTINGS_GDK_کھڑکی_SCALING_ضارب) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

فراغ X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDLX11_Settings_انکڑے *xsettings_انکڑے = &انکڑے->xsettings_انکڑے;

    xsettings_انکڑے->xsettings = xsettings_client_new(انکڑے->display,
        DefaultScreen(انکڑے->display), X11_XsettingsNotify, عدم, _this);
}

فراغ X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDLX11_Settings_انکڑے *xsettings_انکڑے = &انکڑے->xsettings_انکڑے;

    إذا (xsettings_انکڑے->xsettings) {
        xsettings_client_destroy(xsettings_انکڑے->xsettings);
        xsettings_انکڑے->xsettings = عدم;
    }
}

فراغ X11_HandleXsettingsEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDLX11_Settings_انکڑے *xsettings_انکڑے = &انکڑے->xsettings_انکڑے;

    إذا (xsettings_انکڑے->xsettings) {
        xsettings_client_process_event(xsettings_انکڑے->xsettings, xevent);
    }
}

صحيح X11_Get_Xsettings_Client_Int_کلید(XSettingsClient *client, ثابت حرف *کلید, صحيح fallback_قدر) {
    XSettingsSetting *setting = عدم;
    صحيح res = fallback_قدر;

    إذا (client) {
        إذا (xsettings_client_get_setting(client, کلید, &setting) != XSETTINGS_SUCCESS) {
            اذهب no_کلید;
        }

        إذا (setting->type != XSETTINGS_TYPE_INT) {
            اذهب no_کلید;
        }

        res = setting->انکڑے.v_int;
    }

no_کلید:
    إذا (setting) {
        xsettings_setting_free(setting);
    }

    أرجع res;
}

صحيح X11_Get_Xsettings_Int_کلید(SDL_VideoDevice *_this, ثابت حرف *کلید, صحيح fallback_قدر) {
    أرجع X11_Get_Xsettings_Client_Int_کلید(_this->اندرونی->xsettings_انکڑے.xsettings, کلید, fallback_قدر);
}

#جے_انت // SDL_VIDEO_DRIVER_X11
