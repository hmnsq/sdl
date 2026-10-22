/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY

#ضمن "../../events/SDL_events_c.h"

#ضمن "SDL_openharmonykeyboard.h"

#ضمن "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    صحيح داخلہ_type = 0;
    صحيح cap_type = 0;
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_نمبر)) {
        داخلہ_type = (صحيح)SDL_Get_نمبر_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_نمبر, 0);
    } وإلا {
        بدل (SDL_Get_متن_داخلہ_Type(props)) {
            #تعریف_کرو INPUTTYPE(sdl,oh) حالة SDL_TEXTINPUT_TYPE_##sdl: داخلہ_type = oh; اكسر
            INPUTTYPE(متن_2, 0);
            INPUTTYPE(متن_NAME, 0);
            INPUTTYPE(متن_EMAIL, 5);
            INPUTTYPE(متن_USERNAME, 10);
            INPUTTYPE(متن_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(متن_PASSWORD_VISIBLE, 7);
            INPUTTYPE(نمبر_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(نمبر_PASSWORD_VISIBLE, 8);
            #تعریف_رد INPUTTYPE
            افتراضي: اكسر;
        }

        بدل (SDL_Get_متن_داخلہ_Capitalization(props)) {
            #تعریف_کرو CAPTYPE(sdl,oh) حالة SDL_CAPITALIZE_##sdl: cap_type = oh; اكسر
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(الفاظ, 2);
            CAPTYPE(SENTENCES, 1);
            #تعریف_رد CAPTYPE
            افتراضي: اكسر;
        }

        #إذا 0  // !!! FIXME
        إذا (SDL_Get_متن_داخلہ_Autocorrect(props)) {
            داخلہ_type |= (TYPE_متن_FLAG_AUTO_CORRECT | TYPE_متن_FLAG_AUTO_COMPLETE);
        }
        #جے_انت

        إذا (SDL_Get_متن_داخلہ_Multiline(props)) {
            داخلہ_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(داخلہ_type, cap_type, &کھڑکی->متن_داخلہ_rect);
}

فراغ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

فراغ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, کھڑکی, کھڑکی->متن_داخلہ_props);
    }
}

#جے_انت // SDL_VIDEO_DRIVER_OPENHARMONY

