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
#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#अन्तर्भाव <Windows.h>
#अन्तर्भाव <XGameUI.h>
#अन्तर्भाव <XUser.h>

#ifdef __cplusplus
बाह्य "C" {
#endif

#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
स्थिर XTaskQueueHandle g_TextTaskQueue = रिक्त;
// Global because there can be only one text entry shown at once.
स्थिर XAsyncBlock *g_TextBlock = रिक्त;

// Creation parameters
स्थिर तार्किक g_DidRegisterHints = असत्य;
स्थिर वर्ण *g_TitleText = रिक्त;
स्थिर वर्ण *g_DescriptionText = रिक्त;
स्थिर वर्ण *g_DefaultText = रिक्त;
स्थिर ध्रुव Sint32 g_Default_Text_आदान_Scope = (Sint32)XGame_Ui_Text_Entry_आदान_Scope::Default;
स्थिर Sint32 g_Text_आदान_Scope = g_Default_Text_आदान_Scope;
स्थिर ध्रुव Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
स्थिर Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

स्थिर शून्य SDLCALL GDK_InternalHintCallback(
    शून्य *userdata,
    ध्रुव वर्ण *name,
    ध्रुव वर्ण *old_मूल्य,
    ध्रुव वर्ण *new_मूल्य)
{
    यदि (!userdata) {
        प्रत्यागम;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    यदि (userdata == &g_Text_आदान_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_मूल्य = (!new_मूल्य || new_मूल्य[0] == '\0') ? 0 : SDL_atoi(new_मूल्य);
        यदि (userdata == &g_MaxTextLength && int_मूल्य <= 0) {
            int_मूल्य = g_DefaultMaxTextLength;
        } अन्यथा यदि (userdata == &g_Text_आदान_Scope && int_मूल्य < 0) {
            int_मूल्य = g_Default_Text_आदान_Scope;
        }

        *(Sint32 *)userdata = int_मूल्य;
    } अन्यथा {
        // string hint
        यदि (!new_मूल्य || new_मूल्य[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(वर्ण **)userdata);
            *(वर्ण **)userdata = रिक्त;
        } अन्यथा {
            वर्ण *newString = SDL_strdup(new_मूल्य);
            यदि (newString) {
                // free previous value and write the new one
                SDL_free(*(वर्ण **)userdata);
                *(वर्ण **)userdata = newString;
            }
        }
    }
}

स्थिर तार्किक GDK_InternalEnsureTaskQueue(शून्य)
{
    यदि (!g_TextTaskQueue) {
        यदि (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            प्रत्यागम असत्य;
        }
    }
    प्रत्यागम सत्य;
}

स्थिर शून्य CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    वर्ण *resultBuffer = रिक्त;

    // The keyboard will be already hidden when we reach this code

    यदि (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } अन्यथा यदि (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (वर्ण *)SDL_calloc(1 + (size_t)resultSize, परिमाण(*resultBuffer));
        यदि (resultBuffer) {
            // still pass the original size that we got from ResultSize
            यदि (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            अन्यथा यदि (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = रिक्त;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = रिक्त;
    g_TextBlock = रिक्त; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

शून्य GDK_EnsureHints(शून्य)
{
    यदि (g_DidRegisterHints == असत्य) {
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
            &g_Text_आदान_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = सत्य;
    }
}

तार्किक GDK_Start_Text_आदान(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    प्रत्यागम सत्य;
}

तार्किक GDK_Stop_Text_आदान(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    प्रत्यागम सत्य;
}

तार्किक GDK_Update_Text_आदान_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    प्रत्यागम सत्य;
}

तार्किक GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    प्रत्यागम सत्य;
}

तार्किक GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    प्रत्यागम सत्य;
}

शून्य GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    यदि (g_TextBlock) {
        // already showing the keyboard
        प्रत्यागम;
    }

    यदि (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        प्रत्यागम;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, परिमाण(*g_TextBlock));
    यदि (!g_TextBlock) {
        प्रत्यागम;
    }

    XGame_Ui_Text_Entry_आदान_Scope scope;
    विकल्प (SDL_Get_Text_आदान_Type(props)) {
    स्वभाव:
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_आदान_Scope)g_Text_आदान_Scope;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_आदान_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_आदान_Scope::EmailSmtpAddress;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_आदान_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_आदान_Scope::Password;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_आदान_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_संख्या:
        scope = XGame_Ui_Text_Entry_आदान_Scope::संख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_आदान_Scope::संख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_आदान_Scope::संख्या;
        भङ्ग;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    यदि (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } अन्यथा {
        SDL_free(g_TextBlock);
        g_TextBlock = रिक्त;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

शून्य GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    यदि (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
