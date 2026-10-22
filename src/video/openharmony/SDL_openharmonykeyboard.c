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

#که_تعریف_شوی SDL_VIDEO_DRIVER_OPENHARMONY

#ضمن "../../events/SDL_events_c.h"

#ضمن "SDL_openharmonykeyboard.h"

#ضمن "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    صحيح ننوت_type = 0;
    صحيح cap_type = 0;
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_شمېره)) {
        ننوت_type = (صحيح)SDL_Get_شمېره_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_شمېره, 0);
    } وإلا {
        بدل (SDL_Get_متن_ننوت_Type(props)) {
            #تعریف_کړه INPUTTYPE(sdl,oh) حالة SDL_TEXTINPUT_TYPE_##sdl: ننوت_type = oh; اكسر
            INPUTTYPE(متن_2, 0);
            INPUTTYPE(متن_NAME, 0);
            INPUTTYPE(متن_EMAIL, 5);
            INPUTTYPE(متن_USERNAME, 10);
            INPUTTYPE(متن_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(متن_PASSWORD_VISIBLE, 7);
            INPUTTYPE(شمېره_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(شمېره_PASSWORD_VISIBLE, 8);
            #تعریف_لغوه INPUTTYPE
            افتراضي: اكسر;
        }

        بدل (SDL_Get_متن_ننوت_Capitalization(props)) {
            #تعریف_کړه CAPTYPE(sdl,oh) حالة SDL_CAPITALIZE_##sdl: cap_type = oh; اكسر
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(ټکي, 2);
            CAPTYPE(SENTENCES, 1);
            #تعریف_لغوه CAPTYPE
            افتراضي: اكسر;
        }

        #إذا 0  // !!! FIXME
        إذا (SDL_Get_متن_ننوت_Autocorrect(props)) {
            ننوت_type |= (TYPE_متن_FLAG_AUTO_CORRECT | TYPE_متن_FLAG_AUTO_COMPLETE);
        }
        #د_که_پای

        إذا (SDL_Get_متن_ننوت_Multiline(props)) {
            ننوت_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(ننوت_type, cap_type, &کړکۍ->متن_ننوت_rect);
}

فراغ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

فراغ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, کړکۍ, کړکۍ->متن_ننوت_props);
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_OPENHARMONY

