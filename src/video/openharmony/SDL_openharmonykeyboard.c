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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OPENHARMONY

#ضمن "../../events/SDL_events_c.h"

#ضمن "SDL_openharmonykeyboard.h"

#ضمن "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props)
{
    صحيح داخلا_type = 0;
    صحيح cap_type = 0;
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_عدد)) {
        داخلا_type = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_عدد, 0);
    } وإلا {
        بدل (SDL_Get_متن_داخلا_Type(props)) {
            #وصف_ڪريو INPUTTYPE(sdl,oh) حالة SDL_TEXTINPUT_TYPE_##sdl: داخلا_type = oh; اكسر
            INPUTTYPE(متن_2, 0);
            INPUTTYPE(متن_NAME, 0);
            INPUTTYPE(متن_EMAIL, 5);
            INPUTTYPE(متن_USERNAME, 10);
            INPUTTYPE(متن_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(متن_PASSWORD_VISIBLE, 7);
            INPUTTYPE(عدد_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(عدد_PASSWORD_VISIBLE, 8);
            #وصف_رد INPUTTYPE
            افتراضي: اكسر;
        }

        بدل (SDL_Get_متن_داخلا_Capitalization(props)) {
            #وصف_ڪريو CAPTYPE(sdl,oh) حالة SDL_CAPITALIZE_##sdl: cap_type = oh; اكسر
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(لفظ, 2);
            CAPTYPE(SENTENCES, 1);
            #وصف_رد CAPTYPE
            افتراضي: اكسر;
        }

        #إذا 0  // !!! FIXME
        إذا (SDL_Get_متن_داخلا_Autocorrect(props)) {
            داخلا_type |= (TYPE_متن_FLAG_AUTO_CORRECT | TYPE_متن_FLAG_AUTO_COMPLETE);
        }
        #جيڪڏهن_پورو

        إذا (SDL_Get_متن_داخلا_Multiline(props)) {
            داخلا_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(داخلا_type, cap_type, &دري->متن_داخلا_rect);
}

فراغ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

فراغ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, دري, دري->متن_داخلا_props);
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_OPENHARMONY

