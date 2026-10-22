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
/*
  Screen keyboard and text input backend
  for GDK platforms.
*/
#समावेश "SDL_internal.h"
#समावेश "SDL_gdktextinput.h"

#अगर_घोषित SDL_GDK_TEXTINPUT

// GDK headers are weird here
#अगर_अघोषित WIN32_LEAN_AND_MEAN
#घोषणा WIN32_LEAN_AND_MEAN
#पूर्ण_अगर
#समावेश <Windows.h>
#समावेश <XGameUI.h>
#समावेश <XUser.h>

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
अटल XTaskQueueHandle g_TextTaskQueue = शून्य;
// Global because there can be only one text entry shown at once.
अटल XAsyncBlock *g_TextBlock = शून्य;

// Creation parameters
अटल bool g_DidRegisterHints = false;
अटल अक्षर *g_TitleText = शून्य;
अटल अक्षर *g_DescriptionText = शून्य;
अटल अक्षर *g_DefaultText = शून्य;
अटल स्थिर Sint32 g_Default_Text_निवेश_Scope = (Sint32)XGame_Ui_Text_Entry_निवेश_Scope::Default;
अटल Sint32 g_Text_निवेश_Scope = g_Default_Text_निवेश_Scope;
अटल स्थिर Sint32 g_Default_Max_Text_लंबाई = 1024; // as per doc: maximum allowed amount on consoles
अटल Sint32 g_Max_Text_लंबाई = g_Default_Max_Text_लंबाई;

अटल व्योम SDLCALL GDK_InternalHintCallback(
    व्योम *userdata,
    स्थिर अक्षर *name,
    स्थिर अक्षर *old_मूल्य,
    स्थिर अक्षर *new_मूल्य)
{
    अगर (!userdata) {
        वापस;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    अगर (userdata == &g_Text_निवेश_Scope || userdata == &g_Max_Text_लंबाई) {
        // int32 hint
        Sint32 int_मूल्य = (!new_मूल्य || new_मूल्य[0] == '\0') ? 0 : SDL_atoi(new_मूल्य);
        अगर (userdata == &g_Max_Text_लंबाई && int_मूल्य <= 0) {
            int_मूल्य = g_Default_Max_Text_लंबाई;
        } अन्यथा अगर (userdata == &g_Text_निवेश_Scope && int_मूल्य < 0) {
            int_मूल्य = g_Default_Text_निवेश_Scope;
        }

        *(Sint32 *)userdata = int_मूल्य;
    } अन्यथा {
        // string hint
        अगर (!new_मूल्य || new_मूल्य[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(अक्षर **)userdata);
            *(अक्षर **)userdata = शून्य;
        } अन्यथा {
            अक्षर *newString = SDL_strdup(new_मूल्य);
            अगर (newString) {
                // free previous value and write the new one
                SDL_free(*(अक्षर **)userdata);
                *(अक्षर **)userdata = newString;
            }
        }
    }
}

अटल bool GDK_InternalEnsureTaskQueue(व्योम)
{
    अगर (!g_TextTaskQueue) {
        अगर (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            वापस false;
        }
    }
    वापस true;
}

अटल व्योम CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 परिणाम_आकार = 0;
    Uint32 परिणाम_Used = 0;
    अक्षर *परिणाम_बफर = शून्य;

    // The keyboard will be already hidden when we reach this code

    अगर (FAILED(hR = XGame_Ui_Show_Text_Entry_परिणाम_आकार(
                   asyncBlock,
                   &परिणाम_आकार))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } अन्यथा अगर (परिणाम_आकार > 0) {
        // +1 to be super sure that the buffer will be null terminated
        परिणाम_बफर = (अक्षर *)SDL_calloc(1 + (माप_प्रकार)परिणाम_आकार, माप(*परिणाम_बफर));
        अगर (परिणाम_बफर) {
            // still pass the original size that we got from ResultSize
            अगर (FAILED(hR = XGame_Ui_Show_Text_Entry_परिणाम(
                           asyncBlock,
                           परिणाम_आकार,
                           परिणाम_बफर,
                           &परिणाम_Used))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            अन्यथा अगर (परिणाम_Used > 0 && परिणाम_बफर[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(परिणाम_बफर);
            }
            // we're done with the buffer
            SDL_free(परिणाम_बफर);
            परिणाम_बफर = शून्य;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = शून्य;
    g_TextBlock = शून्य; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

व्योम GDK_EnsureHints(व्योम)
{
    अगर (g_DidRegisterHints == false) {
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_TITLE,
            GDK_InternalHintCallback,
            &g_TitleText);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_DESCRIPTION,
            GDK_InternalHintCallback,
            &g_DescriptionText);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_DEFAULT_TEXT,
            GDK_InternalHintCallback,
            &g_DefaultText);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_SCOPE,
            GDK_InternalHintCallback,
            &g_Text_निवेश_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_लंबाई,
            GDK_InternalHintCallback,
            &g_Max_Text_लंबाई);
        g_DidRegisterHints = true;
    }
}

bool GDK_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * Currently a stub, since all input is handled by the virtual keyboard,
     * but perhaps when implementing XGameUiTextEntryOpen in the future
     * you will need this.
     *
     * Also XGameUiTextEntryOpen docs say that it is
     * "not implemented on desktop" so... no thanks.
     *
     * Right now this function isn't implemented on Desktop
     * and seems to be present only in the docs? So I didn't bother.
     */
    वापस true;
}

bool GDK_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    वापस true;
}

bool GDK_Update_Text_निवेश_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    /*
     * XGameUiShowTextEntryAsync does not allow you to set
     * the position of the virtual keyboard window.
     *
     * However, XGameUiTextEntryOpen seems to allow that,
     * but again, see notice in GDK_StartTextInput.
     *
     * Right now it's a stub which may be useful later.
     */
    वापस true;
}

bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    वापस true;
}

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    वापस true;
}

व्योम GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    अगर (g_TextBlock) {
        // already showing the keyboard
        वापस;
    }

    अगर (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        वापस;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, माप(*g_TextBlock));
    अगर (!g_TextBlock) {
        वापस;
    }

    XGame_Ui_Text_Entry_निवेश_Scope scope;
    चयन (SDL_Get_Text_निवेश_Type(props)) {
    शेष:
    हाल SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_निवेश_Scope)g_Text_निवेश_Scope;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_निवेश_Scope::Default;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_निवेश_Scope::EmailSmtpAddress;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_निवेश_Scope::Default;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_निवेश_Scope::Password;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_निवेश_Scope::Default;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या:
        scope = XGame_Ui_Text_Entry_निवेश_Scope::संख्या;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_निवेश_Scope::संख्या;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_निवेश_Scope::संख्या;
        अवरोध;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    अगर (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_Max_Text_लंबाई))) {
        SDL_SendScreenKeyboardShown();
    } अन्यथा {
        SDL_free(g_TextBlock);
        g_TextBlock = शून्य;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

व्योम GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
