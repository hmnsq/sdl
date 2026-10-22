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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ಅನ್ತರ್ಭಾವ <Windows.h>
#ಅನ್ತರ್ಭಾವ <XGameUI.h>
#ಅನ್ತರ್ಭಾವ <XUser.h>

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ಸ್ಥಿರ XTaskQueueHandle g_TextTaskQueue = ರಿಕ್ತ;
// Global because there can be only one text entry shown at once.
ಸ್ಥಿರ XAsyncBlock *g_TextBlock = ರಿಕ್ತ;

// Creation parameters
ಸ್ಥಿರ ತಾರ್ಕಿಕ g_DidRegisterHints = ಅಸತ್ಯ;
ಸ್ಥಿರ ವರ್ಣ *g_TitleText = ರಿಕ್ತ;
ಸ್ಥಿರ ವರ್ಣ *g_DescriptionText = ರಿಕ್ತ;
ಸ್ಥಿರ ವರ್ಣ *g_DefaultText = ರಿಕ್ತ;
ಸ್ಥಿರ ಧ್ರುವ Sint32 g_Default_Text_ಒಳಹರಿವು_Scope = (Sint32)XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::Default;
ಸ್ಥಿರ Sint32 g_Text_ಒಳಹರಿವು_Scope = g_Default_Text_ಒಳಹರಿವು_Scope;
ಸ್ಥಿರ ಧ್ರುವ Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
ಸ್ಥಿರ Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL GDK_InternalHintCallback(
    ಶೂನ್ಯ *userdata,
    ಧ್ರುವ ವರ್ಣ *name,
    ಧ್ರುವ ವರ್ಣ *old_ಮೌಲ್ಯ,
    ಧ್ರುವ ವರ್ಣ *new_ಮೌಲ್ಯ)
{
    ಯದಿ (!userdata) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    ಯದಿ (userdata == &g_Text_ಒಳಹರಿವು_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_ಮೌಲ್ಯ = (!new_ಮೌಲ್ಯ || new_ಮೌಲ್ಯ[0] == '\0') ? 0 : SDL_atoi(new_ಮೌಲ್ಯ);
        ಯದಿ (userdata == &g_MaxTextLength && int_ಮೌಲ್ಯ <= 0) {
            int_ಮೌಲ್ಯ = g_DefaultMaxTextLength;
        } ಅನ್ಯಥಾ ಯದಿ (userdata == &g_Text_ಒಳಹರಿವು_Scope && int_ಮೌಲ್ಯ < 0) {
            int_ಮೌಲ್ಯ = g_Default_Text_ಒಳಹರಿವು_Scope;
        }

        *(Sint32 *)userdata = int_ಮೌಲ್ಯ;
    } ಅನ್ಯಥಾ {
        // string hint
        ಯದಿ (!new_ಮೌಲ್ಯ || new_ಮೌಲ್ಯ[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(ವರ್ಣ **)userdata);
            *(ವರ್ಣ **)userdata = ರಿಕ್ತ;
        } ಅನ್ಯಥಾ {
            ವರ್ಣ *newString = SDL_strdup(new_ಮೌಲ್ಯ);
            ಯದಿ (newString) {
                // free previous value and write the new one
                SDL_free(*(ವರ್ಣ **)userdata);
                *(ವರ್ಣ **)userdata = newString;
            }
        }
    }
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ GDK_InternalEnsureTaskQueue(ಶೂನ್ಯ)
{
    ಯದಿ (!g_TextTaskQueue) {
        ಯದಿ (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
        }
    }
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಸ್ಥಿರ ಶೂನ್ಯ CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    ವರ್ಣ *resultBuffer = ರಿಕ್ತ;

    // The keyboard will be already hidden when we reach this code

    ಯದಿ (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } ಅನ್ಯಥಾ ಯದಿ (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (ವರ್ಣ *)SDL_calloc(1 + (size_t)resultSize, ಪರಿಮಾಣ(*resultBuffer));
        ಯದಿ (resultBuffer) {
            // still pass the original size that we got from ResultSize
            ಯದಿ (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            ಅನ್ಯಥಾ ಯದಿ (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = ರಿಕ್ತ;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = ರಿಕ್ತ;
    g_TextBlock = ರಿಕ್ತ; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

ಶೂನ್ಯ GDK_EnsureHints(ಶೂನ್ಯ)
{
    ಯದಿ (g_DidRegisterHints == ಅಸತ್ಯ) {
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
            &g_Text_ಒಳಹರಿವು_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = ಸತ್ಯ;
    }
}

ತಾರ್ಕಿಕ GDK_Start_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ GDK_Stop_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ GDK_Update_Text_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    ಯದಿ (g_TextBlock) {
        // already showing the keyboard
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        ಪ್ರತ್ಯಾಗಮ;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, ಪರಿಮಾಣ(*g_TextBlock));
    ಯದಿ (!g_TextBlock) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope scope;
    ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
    ಸ್ವಭಾವ:
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope)g_Text_ಒಳಹರಿವು_Scope;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::Default;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::EmailSmtpAddress;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::Default;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::Password;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::Default;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::ಸಂಖ್ಯೆ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::ಸಂಖ್ಯೆ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_ಒಳಹರಿವು_Scope::ಸಂಖ್ಯೆ;
        ಭಙ್ಗ;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    ಯದಿ (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } ಅನ್ಯಥಾ {
        SDL_free(g_TextBlock);
        g_TextBlock = ರಿಕ್ತ;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

ಶೂನ್ಯ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಯದಿ (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
