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
स्थिर तार्किक g_DidRegisterHints = मिच्छा;
स्थिर वर्ण *g_TitleText = रिक्त;
स्थिर वर्ण *g_DescriptionText = रिक्त;
स्थिर वर्ण *g_DefaultText = रिक्त;
स्थिर ध्रुव Sint32 g_Default_Text_निवेशः_Scope = (Sint32)XGame_Ui_Text_Entry_निवेशः_Scope::Default;
स्थिर Sint32 g_Text_निवेशः_Scope = g_Default_Text_निवेशः_Scope;
स्थिर ध्रुव Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
स्थिर Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

स्थिर शून्य SDLCALL GDK_InternalHintCallback(
    शून्य *userdata,
    ध्रुव वर्ण *name,
    ध्रुव वर्ण *old_मानम्,
    ध्रुव वर्ण *new_मानम्)
{
    सचे (!userdata) {
        पटिनिवत्त;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    सचे (userdata == &g_Text_निवेशः_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_मानम् = (!new_मानम् || new_मानम्[0] == '\0') ? 0 : SDL_atoi(new_मानम्);
        सचे (userdata == &g_MaxTextLength && int_मानम् <= 0) {
            int_मानम् = g_DefaultMaxTextLength;
        } अञ्ञथा सचे (userdata == &g_Text_निवेशः_Scope && int_मानम् < 0) {
            int_मानम् = g_Default_Text_निवेशः_Scope;
        }

        *(Sint32 *)userdata = int_मानम्;
    } अञ्ञथा {
        // string hint
        सचे (!new_मानम् || new_मानम्[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(वर्ण **)userdata);
            *(वर्ण **)userdata = रिक्त;
        } अञ्ञथा {
            वर्ण *newString = SDL_strdup(new_मानम्);
            सचे (newString) {
                // free previous value and write the new one
                SDL_free(*(वर्ण **)userdata);
                *(वर्ण **)userdata = newString;
            }
        }
    }
}

स्थिर तार्किक GDK_InternalEnsureTaskQueue(शून्य)
{
    सचे (!g_TextTaskQueue) {
        सचे (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            पटिनिवत्त मिच्छा;
        }
    }
    पटिनिवत्त सच्च;
}

स्थिर शून्य CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    वर्ण *resultBuffer = रिक्त;

    // The keyboard will be already hidden when we reach this code

    सचे (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } अञ्ञथा सचे (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (वर्ण *)SDL_calloc(1 + (size_t)resultSize, परिमाण(*resultBuffer));
        सचे (resultBuffer) {
            // still pass the original size that we got from ResultSize
            सचे (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            अञ्ञथा सचे (resultUsed > 0 && resultBuffer[0] != '\0') {
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
    सचे (g_DidRegisterHints == मिच्छा) {
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
            &g_Text_निवेशः_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = सच्च;
    }
}

तार्किक GDK_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    पटिनिवत्त सच्च;
}

तार्किक GDK_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    पटिनिवत्त सच्च;
}

तार्किक GDK_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    पटिनिवत्त सच्च;
}

तार्किक GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    पटिनिवत्त सच्च;
}

तार्किक GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    पटिनिवत्त सच्च;
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

    सचे (g_TextBlock) {
        // already showing the keyboard
        पटिनिवत्त;
    }

    सचे (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        पटिनिवत्त;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, परिमाण(*g_TextBlock));
    सचे (!g_TextBlock) {
        पटिनिवत्त;
    }

    XGame_Ui_Text_Entry_निवेशः_Scope scope;
    विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
    स्वभाव:
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_निवेशः_Scope)g_Text_निवेशः_Scope;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::EmailSmtpAddress;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::Password;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या:
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::सङ्ख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::सङ्ख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_निवेशः_Scope::सङ्ख्या;
        भङ्ग;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    सचे (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } अञ्ञथा {
        SDL_free(g_TextBlock);
        g_TextBlock = रिक्त;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

शून्य GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    सचे (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
