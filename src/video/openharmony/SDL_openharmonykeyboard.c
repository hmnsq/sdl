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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_openharmonykeyboard.h"

#ಅನ್ತರ್ಭಾವ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    ಪೂರ್ಣಾಙ್ಕ ಒಳಹರಿವು_type = 0;
    ಪೂರ್ಣಾಙ್ಕ cap_type = 0;
    ಯದಿ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ಸಂಖ್ಯೆ)) {
        ಒಳಹರಿವು_type = (ಪೂರ್ಣಾಙ್ಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ಸಂಖ್ಯೆ, 0);
    } ಅನ್ಯಥಾ {
        ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
            #define INPUTTYPE(sdl,oh) ಪಕ್ಷ SDL_TEXTINPUT_TYPE_##sdl: ಒಳಹರಿವು_type = oh; ಭಙ್ಗ
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(ಸಂಖ್ಯೆ_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(ಸಂಖ್ಯೆ_PASSWORD_VISIBLE, 8);
            #undef INPUTTYPE
            ಸ್ವಭಾವ: ಭಙ್ಗ;
        }

        ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Capitalization(props)) {
            #define CAPTYPE(sdl,oh) ಪಕ್ಷ SDL_CAPITALIZE_##sdl: cap_type = oh; ಭಙ್ಗ
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(ಪದಗಳು, 2);
            CAPTYPE(SENTENCES, 1);
            #undef CAPTYPE
            ಸ್ವಭಾವ: ಭಙ್ಗ;
        }

        #ಯದಿ 0  // !!! FIXME
        ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Autocorrect(props)) {
            ಒಳಹರಿವು_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #endif

        ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Multiline(props)) {
            ಒಳಹರಿವು_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(ಒಳಹರಿವು_type, cap_type, &window->text_ಒಳಹರಿವು_rect);
}

ಶೂನ್ಯ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

ಶೂನ್ಯ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಯದಿ (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_ಒಳಹರಿವು_props);
    }
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY

