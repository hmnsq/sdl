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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY

#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_openharmonykeyboard.h"

#ಅನ್ತರ್ಭಾವ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    ಪೂರ್ಣಾಂಕ ಒಳಹರಿವು_type = 0;
    ಪೂರ್ಣಾಂಕ cap_type = 0;
    ಆದರೆ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ಸಂಖ್ಯೆ)) {
        ಒಳಹರಿವು_type = (ಪೂರ್ಣಾಂಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ಸಂಖ್ಯೆ, 0);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(props)) {
            #ವ್ಯಾಖ್ಯಾನಿಸು INPUTTYPE(sdl,oh) ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_##sdl: ಒಳಹರಿವು_type = oh; ನಿಲ್ಲಿಸು
            INPUTTYPE(ಪಠ್ಯ_2, 0);
            INPUTTYPE(ಪಠ್ಯ_NAME, 0);
            INPUTTYPE(ಪಠ್ಯ_EMAIL, 5);
            INPUTTYPE(ಪಠ್ಯ_USERNAME, 10);
            INPUTTYPE(ಪಠ್ಯ_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(ಪಠ್ಯ_PASSWORD_VISIBLE, 7);
            INPUTTYPE(ಸಂಖ್ಯೆ_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(ಸಂಖ್ಯೆ_PASSWORD_VISIBLE, 8);
            #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು INPUTTYPE
            ಪೂರ್ವನಿಯೋಜಿತ: ನಿಲ್ಲಿಸು;
        }

        ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Capitalization(props)) {
            #ವ್ಯಾಖ್ಯಾನಿಸು CAPTYPE(sdl,oh) ಸ್ಥಿತಿ SDL_CAPITALIZE_##sdl: cap_type = oh; ನಿಲ್ಲಿಸು
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(ಪದಗಳು, 2);
            CAPTYPE(SENTENCES, 1);
            #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CAPTYPE
            ಪೂರ್ವನಿಯೋಜಿತ: ನಿಲ್ಲಿಸು;
        }

        #ಆದರೆ 0  // !!! FIXME
        ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Autocorrect(props)) {
            ಒಳಹರಿವು_type |= (TYPE_ಪಠ್ಯ_FLAG_AUTO_CORRECT | TYPE_ಪಠ್ಯ_FLAG_AUTO_COMPLETE);
        }
        #ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Multiline(props)) {
            ಒಳಹರಿವು_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(ಒಳಹರಿವು_type, cap_type, &ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect);
}

ಶೂನ್ಯ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

ಶೂನ್ಯ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, ಕಿಟಕಿ, ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OPENHARMONY

