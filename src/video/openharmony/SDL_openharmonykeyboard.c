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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#അന്തര്ഭാവ "../../events/SDL_events_c.h"

#അന്തര്ഭാവ "SDL_openharmonykeyboard.h"

#അന്തര്ഭാവ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    തിരികെ true;
}

ശൂന്യം OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    പൂർണ്ണസംഖ്യ നിവേശം_type = 0;
    പൂർണ്ണസംഖ്യ cap_type = 0;
    എങ്കിൽ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_സംഖ്യ)) {
        നിവേശം_type = (പൂർണ്ണസംഖ്യ)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_സംഖ്യ, 0);
    } അല്ലെങ്കിൽ {
        തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Type(props)) {
            #define INPUTTYPE(sdl,oh) അവസ്ഥ SDL_TEXTINPUT_TYPE_##sdl: നിവേശം_type = oh; നിർത്തുക
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(സംഖ്യ_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(സംഖ്യ_PASSWORD_VISIBLE, 8);
            #undef INPUTTYPE
            സ്ഥിരസ്ഥിതി: നിർത്തുക;
        }

        തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Capitalization(props)) {
            #define CAPTYPE(sdl,oh) അവസ്ഥ SDL_CAPITALIZE_##sdl: cap_type = oh; നിർത്തുക
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(വാക്കുകൾ, 2);
            CAPTYPE(SENTENCES, 1);
            #undef CAPTYPE
            സ്ഥിരസ്ഥിതി: നിർത്തുക;
        }

        #എങ്കിൽ 0  // !!! FIXME
        എങ്കിൽ (SDL_Get_Text_നിവേശം_Autocorrect(props)) {
            നിവേശം_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #endif

        എങ്കിൽ (SDL_Get_Text_നിവേശം_Multiline(props)) {
            നിവേശം_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(നിവേശം_type, cap_type, &window->text_നിവേശം_rect);
}

ശൂന്യം OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

ശൂന്യം OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_നിവേശം_props);
    }
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY

