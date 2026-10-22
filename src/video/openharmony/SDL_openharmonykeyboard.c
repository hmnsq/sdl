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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_OPENHARMONY

#समावेश "../../events/SDL_events_c.h"

#समावेश "SDL_openharmonykeyboard.h"

#समावेश "../../core/openharmony/SDL_openharmony.h"

bool OPENHARMONY_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    वापस true;
}

व्योम OPENHARMONY_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    पूर्णांक निवेश_type = 0;
    पूर्णांक cap_type = 0;
    अगर (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_संख्या)) {
        निवेश_type = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_OPENHARMONY_INPUTTYPE_संख्या, 0);
    } अन्यथा {
        चयन (SDL_Get_Text_निवेश_Type(props)) {
            #घोषणा INPUTTYPE(sdl,oh) हाल SDL_TEXTINPUT_TYPE_##sdl: निवेश_type = oh; अवरोध
            INPUTTYPE(TEXT, 0);
            INPUTTYPE(TEXT_NAME, 0);
            INPUTTYPE(TEXT_EMAIL, 5);
            INPUTTYPE(TEXT_USERNAME, 10);
            INPUTTYPE(TEXT_PASSWORD_HIDDEN, 7);  // !!! FIXME: this is _also_ PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(TEXT_PASSWORD_VISIBLE, 7);
            INPUTTYPE(संख्या_PASSWORD_HIDDEN, 8); // !!! FIXME: this is _also_ NUMBER_PASSWORD_VISIBLE, but I think this doesn't dictate rendering...?
            INPUTTYPE(संख्या_PASSWORD_VISIBLE, 8);
            #अघोषित INPUTTYPE
            शेष: अवरोध;
        }

        चयन (SDL_Get_Text_निवेश_Capitalization(props)) {
            #घोषणा CAPTYPE(sdl,oh) हाल SDL_CAPITALIZE_##sdl: cap_type = oh; अवरोध
            CAPTYPE(NONE, 0);
            CAPTYPE(LETTERS, 3);
            CAPTYPE(शब्दगण, 2);
            CAPTYPE(SENTENCES, 1);
            #अघोषित CAPTYPE
            शेष: अवरोध;
        }

        #अगर 0  // !!! FIXME
        अगर (SDL_Get_Text_निवेश_Autocorrect(props)) {
            निवेश_type |= (TYPE_TEXT_FLAG_AUTO_CORRECT | TYPE_TEXT_FLAG_AUTO_COMPLETE);
        }
        #पूर्ण_अगर

        अगर (SDL_Get_Text_निवेश_Multiline(props)) {
            निवेश_type = 1;  // sorry, this only works with basic TEXT type.
        }
    }
    SDL_OpenHarmonyShowScreenKeyboard(निवेश_type, cap_type, &window->text_निवेश_rect);
}

व्योम OPENHARMONY_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_OpenHarmonyHideScreenKeyboard();
}

व्योम OPENHARMONY_RestoreScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (_this->screen_keyboard_shown) {
        OPENHARMONY_ShowScreenKeyboard(_this, window, window->text_निवेश_props);
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_OPENHARMONY

