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

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#अन्तर्भाव "../../events/SDL_events_c.h"

#अन्तर्भाव "SDL_openharmonykeyboard.h"

#अन्तर्भाव "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    परत true;
}

शून्य OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    पूर्णांक आदान_type = 0;
    पूर्णांक cap_type = 0;
    जर (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_संख्या)) {
        आदान_type = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_संख्या, 0);
    } अन्यथा {
        निवड (SDL_Get_Text_आदान_Type(props)) {
            #define INPUTTYPE(sdl,oh) स्थिती SDL_TEXTINPUT_TYPE_##sdl: आदान_type = oh; थांबा
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(संख्या_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(संख्या_PASSWORD_VISIBLE, 8);
            #undef INPUTTYPE
            पूर्वनिर्धारित: थांबा;
        }

        निवड (SDL_Get_Text_आदान_Capitalization(props)) {
            #define CAPTYPE(sdl,oh) स्थिती SDL_CAPITALIZE_##sdl: cap_type = oh; थांबा
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(शब्द, 2);
            CAPTYPE(SENTENCES, 1);
            #undef CAPTYPE
            पूर्वनिर्धारित: थांबा;
        }

        #जर 0  // !!! FIXME
        जर (SDL_Get_Text_आदान_Autocorrect(props)) {
            आदान_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #endif

        जर (SDL_Get_Text_आदान_Multiline(props)) {
            आदान_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(आदान_type, cap_type, &window->text_आदान_rect);
}

शून्य OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

शून्य OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    जर (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_आदान_props);
    }
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY

