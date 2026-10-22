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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#شامل "../../events/SDL_events_c.h"

#شامل "SDL_openharmonykeyboard.h"

#شامل "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    بازگشت true;
}

تهی OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    صحیح درون_داد_type = 0;
    صحیح cap_type = 0;
    اگر (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_عدد)) {
        درون_داد_type = (صحیح)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_عدد, 0);
    } وگرنه {
        انتخاب (SDL_Get_Text_درون_داد_Type(props)) {
            #define INPUTTYPE(sdl,oh) حالت SDL_TEXTINPUT_TYPE_##sdl: درون_داد_type = oh; بشکن
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(عدد_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(عدد_PASSWORD_VISIBLE, 8);
            #undef INPUTTYPE
            پیشفرض: بشکن;
        }

        انتخاب (SDL_Get_Text_درون_داد_Capitalization(props)) {
            #define CAPTYPE(sdl,oh) حالت SDL_CAPITALIZE_##sdl: cap_type = oh; بشکن
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(واژگان, 2);
            CAPTYPE(SENTENCES, 1);
            #undef CAPTYPE
            پیشفرض: بشکن;
        }

        #اگر 0  // !!! FIXME
        اگر (SDL_Get_Text_درون_داد_Autocorrect(props)) {
            درون_داد_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #endif

        اگر (SDL_Get_Text_درون_داد_Multiline(props)) {
            درون_داد_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(درون_داد_type, cap_type, &window->text_درون_داد_rect);
}

تهی OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

تهی OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    اگر (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_درون_داد_props);
    }
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY

