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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#અન્તર્ભાવ "../../events/SDL_events_c.h"

#અન્તર્ભાવ "SDL_openharmonykeyboard.h"

#અન્તર્ભાવ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    પાછા true;
}

શૂન્ય OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    પૂર્ણાંક આગત_type = 0;
    પૂર્ણાંક cap_type = 0;
    જો (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_સંખ્યા)) {
        આગત_type = (પૂર્ણાંક)SDL_Get_સંખ્યા_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_સંખ્યા, 0);
    } નહીંતર {
        પસંદગી (SDL_Get_Text_આગત_Type(props)) {
            #define INPUTTYPE(sdl,oh) સ્થિતિ SDL_TEXTINPUT_TYPE_##sdl: આગત_type = oh; તોડો
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(સંખ્યા_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(સંખ્યા_PASSWORD_VISIBLE, 8);
            #undef INPUTTYPE
            મૂળભૂત: તોડો;
        }

        પસંદગી (SDL_Get_Text_આગત_Capitalization(props)) {
            #define CAPTYPE(sdl,oh) સ્થિતિ SDL_CAPITALIZE_##sdl: cap_type = oh; તોડો
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(શબ્દો, 2);
            CAPTYPE(SENTENCES, 1);
            #undef CAPTYPE
            મૂળભૂત: તોડો;
        }

        #જો 0  // !!! FIXME
        જો (SDL_Get_Text_આગત_Autocorrect(props)) {
            આગત_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #endif

        જો (SDL_Get_Text_આગત_Multiline(props)) {
            આગત_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(આગત_type, cap_type, &window->text_આગત_rect);
}

શૂન્ય OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

શૂન્ય OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    જો (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_આગત_props);
    }
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY

