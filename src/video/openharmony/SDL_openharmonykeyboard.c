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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENHARMONY

#అన్తర్భావ "../../events/SDL_events_c.h"

#అన్తర్భావ "SDL_openharmonykeyboard.h"

#అన్తర్భావ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    తిరిగి true;
}

శూన్య OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    పూర్ణాంకం ఆదానం_type = 0;
    పూర్ణాంకం cap_type = 0;
    ఒకవేళ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_సంఖ్య)) {
        ఆదానం_type = (పూర్ణాంకం)SDL_Get_సంఖ్య_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_సంఖ్య, 0);
    } లేకపోతే {
        ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
            #నిర్వచించు INPUTTYPE(sdl,oh) స్థితి SDL_TEXTINPUT_TYPE_##sdl: ఆదానం_type = oh; ఆపు
            INPUTTYPE(పాఠ్యం_2, 0);
            INPUTTYPE(పాఠ్యం_NAME, 0);
            INPUTTYPE(పాఠ్యం_EMAIL, 5);
            INPUTTYPE(పాఠ్యం_USERNAME, 10);
            INPUTTYPE(పాఠ్యం_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(పాఠ్యం_PASSWORD_VISIBLE, 7);
            INPUTTYPE(సంఖ్య_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(సంఖ్య_PASSWORD_VISIBLE, 8);
            #నిర్వచనం_రద్దు INPUTTYPE
            అప్రమేయ: ఆపు;
        }

        ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Capitalization(props)) {
            #నిర్వచించు CAPTYPE(sdl,oh) స్థితి SDL_CAPITALIZE_##sdl: cap_type = oh; ఆపు
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(పదాలు, 2);
            CAPTYPE(SENTENCES, 1);
            #నిర్వచనం_రద్దు CAPTYPE
            అప్రమేయ: ఆపు;
        }

        #ఒకవేళ 0  // !!! FIXME
        ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Autocorrect(props)) {
            ఆదానం_type |= (TYPE_పాఠ్యం_FLAG_AUTO_CORRECT | TYPE_పాఠ్యం_FLAG_AUTO_COMPLETE);
        }
        #అయితే_ముగింపు

        ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Multiline(props)) {
            ఆదానం_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(ఆదానం_type, cap_type, &కిటికీ->పాఠ్యం_ఆదానం_rect);
}

శూన్య OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

శూన్య OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, కిటికీ, కిటికీ->పాఠ్యం_ఆదానం_props);
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OPENHARMONY

