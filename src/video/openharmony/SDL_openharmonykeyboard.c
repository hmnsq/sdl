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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_openharmonykeyboard.h"

#ଅନ୍ତର୍ଭାଵ "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ନିବେଶ_type = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cap_type = 0;
    ଯଦି (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ସଂଖ୍ୟା)) {
        ନିବେଶ_type = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_ସଂଖ୍ୟା, 0);
    } ଅନ୍ୟଥା {
        ବାଛ (SDL_Get_Text_ନିବେଶ_Type(props)) {
            #define INPUTTYPE(sdl,oh) ସ୍ଥିତି SDL_TEXTINPUT_TYPE_##sdl: ନିବେଶ_type = oh; ଭାଙ୍ଗ
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(ସଂଖ୍ୟା_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(ସଂଖ୍ୟା_PASSWORD_VISIBLE, 8);
            #undef INPUTTYPE
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ: ଭାଙ୍ଗ;
        }

        ବାଛ (SDL_Get_Text_ନିବେଶ_Capitalization(props)) {
            #define CAPTYPE(sdl,oh) ସ୍ଥିତି SDL_CAPITALIZE_##sdl: cap_type = oh; ଭାଙ୍ଗ
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(ଶବ୍ଦଗୁଡ଼ିକ, 2);
            CAPTYPE(SENTENCES, 1);
            #undef CAPTYPE
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ: ଭାଙ୍ଗ;
        }

        #ଯଦି 0  // !!! FIXME
        ଯଦି (SDL_Get_Text_ନିବେଶ_Autocorrect(props)) {
            ନିବେଶ_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #endif

        ଯଦି (SDL_Get_Text_ନିବେଶ_Multiline(props)) {
            ନିବେଶ_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(ନିବେଶ_type, cap_type, &window->text_ନିବେଶ_rect);
}

ଶୂନ୍ୟ OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

ଶୂନ୍ୟ OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    ଯଦି (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_ନିବେଶ_props);
    }
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY

