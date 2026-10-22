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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OPENHARMONY

#अन्तर्भाव "../../events/SDL_events_c.h"

#अन्तर्भाव "SDL_openharmonykeyboard.h"

#अन्तर्भाव "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    प्रत्यागम true;
}

शून्य OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    पूर्णाङ्क निवेशः_type = 0;
    पूर्णाङ्क cap_type = 0;
    यदि (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_सङ्ख्या)) {
        निवेशः_type = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_सङ्ख्या, 0);
    } अन्यथा {
        विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
            #परिभाषय INPUTTYPE(sdl,oh) पक्ष SDL_TEXTINPUT_TYPE_##sdl: निवेशः_type = oh; भङ्ग
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(सङ्ख्या_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(सङ्ख्या_PASSWORD_VISIBLE, 8);
            #अपरिभाषय INPUTTYPE
            स्वभाव: भङ्ग;
        }

        विकल्प (SDL_Get_Text_निवेशः_Capitalization(props)) {
            #परिभाषय CAPTYPE(sdl,oh) पक्ष SDL_CAPITALIZE_##sdl: cap_type = oh; भङ्ग
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(शब्दाः, 2);
            CAPTYPE(SENTENCES, 1);
            #अपरिभाषय CAPTYPE
            स्वभाव: भङ्ग;
        }

        #यदि 0  // !!! FIXME
        यदि (SDL_Get_Text_निवेशः_Autocorrect(props)) {
            निवेशः_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #यदि_अन्तः

        यदि (SDL_Get_Text_निवेशः_Multiline(props)) {
            निवेशः_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(निवेशः_type, cap_type, &गवाक्षः->text_निवेशः_rect);
}

शून्य OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

शून्य OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, गवाक्षः, गवाक्षः->text_निवेशः_props);
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_OPENHARMONY

