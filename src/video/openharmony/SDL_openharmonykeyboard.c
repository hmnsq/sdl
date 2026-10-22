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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENHARMONY

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonykeyboard.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ਵਾਪਸ true;
}

ਖਾਲੀ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    ਪੂਰਨ ਨਿਵੇਸ਼_type = 0;
    ਪੂਰਨ cap_type = 0;
    ਜੇ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ਸੰਖਿਆ)) {
        ਨਿਵੇਸ਼_type = (ਪੂਰਨ)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ਸੰਖਿਆ, 0);
    } ਨਹੀਂਤਾਂ {
        ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INPUTTYPE(sdl,oh) ਹਾਲਤ SDL_TEXTINPUT_TYPE_##sdl: ਨਿਵੇਸ਼_type = oh; ਰੋਕੋ
            INPUTTYPE(ਪਾਠ_2, 0);
            INPUTTYPE(ਪਾਠ_NAME, 0);
            INPUTTYPE(ਪਾਠ_EMAIL, 5);
            INPUTTYPE(ਪਾਠ_USERNAME, 10);
            INPUTTYPE(ਪਾਠ_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(ਪਾਠ_PASSWORD_VISIBLE, 7);
            INPUTTYPE(ਸੰਖਿਆ_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(ਸੰਖਿਆ_PASSWORD_VISIBLE, 8);
            #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ INPUTTYPE
            ਮੂਲ: ਰੋਕੋ;
        }

        ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Capitalization(props)) {
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CAPTYPE(sdl,oh) ਹਾਲਤ SDL_CAPITALIZE_##sdl: cap_type = oh; ਰੋਕੋ
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(ਸ਼ਬਦ, 2);
            CAPTYPE(SENTENCES, 1);
            #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CAPTYPE
            ਮੂਲ: ਰੋਕੋ;
        }

        #ਜੇ 0  // !!! FIXME
        ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Autocorrect(props)) {
            ਨਿਵੇਸ਼_type |= (TYPE_ਪਾਠ_FLAG_AUTO_CORRECT | TYPE_ਪਾਠ_FLAG_AUTO_COMPLETE);
        }
        #ਜੇ_ਅੰਤ

        ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Multiline(props)) {
            ਨਿਵੇਸ਼_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(ਨਿਵੇਸ਼_type, cap_type, &ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect);
}

ਖਾਲੀ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

ਖਾਲੀ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, ਖਿੜਕੀ, ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OPENHARMONY

