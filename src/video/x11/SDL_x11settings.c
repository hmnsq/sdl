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

#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11)

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11settings.h"

స్థిర శూన్య UpdateContentScale(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this) {
        దశాంశం scale_గుణకం_2 = X11_GetGlobalContentScaleForDevice(_this);
        కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
            SDL_సమితి_Display_Content_Scale(_this->displays[i], scale_గుణకం_2);
        }
    }
}

స్థిర శూన్య X11_XsettingsNotify(స్థిరరాశి అక్షరం *name, XSettingsAction action, XSettingsSetting *setting, శూన్య *దత్తాంశం)
{
    SDL_VideoDevice *_this = దత్తాంశం;

    ఒకవేళ (SDL_strcmp(name, SDL_XSETTINGS_GDK_కిటికీ_SCALING_గుణకం) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

శూన్య X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDLX11_Settings_దత్తాంశం *xsettings_దత్తాంశం = &దత్తాంశం->xsettings_దత్తాంశం;

    xsettings_దత్తాంశం->xsettings = xsettings_client_new(దత్తాంశం->display,
        DefaultScreen(దత్తాంశం->display), X11_XsettingsNotify, ఖాళీ, _this);
}

శూన్య X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDLX11_Settings_దత్తాంశం *xsettings_దత్తాంశం = &దత్తాంశం->xsettings_దత్తాంశం;

    ఒకవేళ (xsettings_దత్తాంశం->xsettings) {
        xsettings_client_destroy(xsettings_దత్తాంశం->xsettings);
        xsettings_దత్తాంశం->xsettings = ఖాళీ;
    }
}

శూన్య X11_HandleXsettingsEvent(SDL_VideoDevice *_this, స్థిరరాశి XEvent *xevent)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDLX11_Settings_దత్తాంశం *xsettings_దత్తాంశం = &దత్తాంశం->xsettings_దత్తాంశం;

    ఒకవేళ (xsettings_దత్తాంశం->xsettings) {
        xsettings_client_process_event(xsettings_దత్తాంశం->xsettings, xevent);
    }
}

పూర్ణాంకం X11_Get_Xsettings_Client_Int_కీలకం(XSettingsClient *client, స్థిరరాశి అక్షరం *కీలకం, పూర్ణాంకం fallback_విలువ) {
    XSettingsSetting *setting = ఖాళీ;
    పూర్ణాంకం res = fallback_విలువ;

    ఒకవేళ (client) {
        ఒకవేళ (xsettings_client_get_setting(client, కీలకం, &setting) != XSETTINGS_SUCCESS) {
            వెళ్ళు no_కీలకం;
        }

        ఒకవేళ (setting->type != XSETTINGS_TYPE_INT) {
            వెళ్ళు no_కీలకం;
        }

        res = setting->దత్తాంశం.v_int;
    }

no_కీలకం:
    ఒకవేళ (setting) {
        xsettings_setting_free(setting);
    }

    తిరిగి res;
}

పూర్ణాంకం X11_Get_Xsettings_Int_కీలకం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *కీలకం, పూర్ణాంకం fallback_విలువ) {
    తిరిగి X11_Get_Xsettings_Client_Int_కీలకం(_this->అంతర్గత->xsettings_దత్తాంశం.xsettings, కీలకం, fallback_విలువ);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
