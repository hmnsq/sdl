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

#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_X11)

#समावेश "SDL_x11video.h"
#समावेश "SDL_x11settings.h"

अटल व्योम UpdateContentScale(SDL_VideoDevice *_this)
{
    अगर (_this) {
        भग्न scale_factor = X11_GetGlobalContentScaleForDevice(_this);
        क्रम (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
            SDL_SetDisplayContentScale(_this->displays[i], scale_factor);
        }
    }
}

अटल व्योम X11_XsettingsNotify(स्थिर अक्षर *name, XSettingsAction action, XSettingsSetting *setting, व्योम *तथ्य)
{
    SDL_VideoDevice *_this = तथ्य;

    अगर (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        UpdateContentScale(_this);
    }
}

व्योम X11_InitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDLX11_Settings_तथ्य *xsettings_तथ्य = &तथ्य->xsettings_तथ्य;

    xsettings_तथ्य->xsettings = xsettings_client_new(तथ्य->display,
        DefaultScreen(तथ्य->display), X11_XsettingsNotify, शून्य, _this);
}

व्योम X11_QuitXsettings(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDLX11_Settings_तथ्य *xsettings_तथ्य = &तथ्य->xsettings_तथ्य;

    अगर (xsettings_तथ्य->xsettings) {
        xsettings_client_destroy(xsettings_तथ्य->xsettings);
        xsettings_तथ्य->xsettings = शून्य;
    }
}

व्योम X11_HandleXsettingsEvent(SDL_VideoDevice *_this, स्थिर XEvent *xevent)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDLX11_Settings_तथ्य *xsettings_तथ्य = &तथ्य->xsettings_तथ्य;

    अगर (xsettings_तथ्य->xsettings) {
        xsettings_client_process_event(xsettings_तथ्य->xsettings, xevent);
    }
}

पूर्णांक X11_Get_Xsettings_Client_Int_कुंजी(XSettingsClient *client, स्थिर अक्षर *कुंजी, पूर्णांक fallback_मूल्य) {
    XSettingsSetting *setting = शून्य;
    पूर्णांक res = fallback_मूल्य;

    अगर (client) {
        अगर (xsettings_client_get_setting(client, कुंजी, &setting) != XSETTINGS_SUCCESS) {
            जाओ no_कुंजी;
        }

        अगर (setting->type != XSETTINGS_TYPE_INT) {
            जाओ no_कुंजी;
        }

        res = setting->तथ्य.v_int;
    }

no_कुंजी:
    अगर (setting) {
        xsettings_setting_free(setting);
    }

    वापस res;
}

पूर्णांक X11_Get_Xsettings_Int_कुंजी(SDL_VideoDevice *_this, स्थिर अक्षर *कुंजी, पूर्णांक fallback_मूल्य) {
    वापस X11_Get_Xsettings_Client_Int_कुंजी(_this->internal->xsettings_तथ्य.xsettings, कुंजी, fallback_मूल्य);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
