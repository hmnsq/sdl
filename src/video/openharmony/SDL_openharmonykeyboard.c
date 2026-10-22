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

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ضمن "../../events/SDL_events_c.h"

#ضمن "SDL_openharmonykeyboard.h"

#ضمن "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    صحيح مدخل_type = 0;
    صحيح cap_type = 0;
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_رقم)) {
        مدخل_type = (صحيح)SDL_Get_رقم_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_رقم, 0);
    } وإلا {
        بدل (SDL_Get_Text_مدخل_Type(props)) {
            #define INPUTTYPE(sdl,oh) حالة SDL_TEXTINPUT_TYPE_##sdl: مدخل_type = oh; اكسر
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(رقم_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(رقم_PASSWORD_VISIBLE, 8);
            #undef INPUTTYPE
            افتراضي: اكسر;
        }

        بدل (SDL_Get_Text_مدخل_Capitalization(props)) {
            #define CAPTYPE(sdl,oh) حالة SDL_CAPITALIZE_##sdl: cap_type = oh; اكسر
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(كلمات, 2);
            CAPTYPE(SENTENCES, 1);
            #undef CAPTYPE
            افتراضي: اكسر;
        }

        #إذا 0  // !!! FIXME
        إذا (SDL_Get_Text_مدخل_Autocorrect(props)) {
            مدخل_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #endif

        إذا (SDL_Get_Text_مدخل_Multiline(props)) {
            مدخل_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(مدخل_type, cap_type, &window->text_مدخل_rect);
}

فراغ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

فراغ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    إذا (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_مدخل_props);
    }
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY

