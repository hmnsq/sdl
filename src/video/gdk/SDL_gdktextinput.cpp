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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"
#ଅନ୍ତର୍ଭାଵ "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ଅନ୍ତର୍ଭାଵ <Windows.h>
#ଅନ୍ତର୍ଭାଵ <XGameUI.h>
#ଅନ୍ତର୍ଭାଵ <XUser.h>

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ସ୍ଥିର XTaskQueueHandle g_TextTaskQueue = ଖାଲି;
// Global because there can be only one text entry shown at once.
ସ୍ଥିର XAsyncBlock *g_TextBlock = ଖାଲି;

// Creation parameters
ସ୍ଥିର ତାର୍କିକ g_DidRegisterHints = ମିଥ୍ୟା;
ସ୍ଥିର ଅକ୍ଷର *g_TitleText = ଖାଲି;
ସ୍ଥିର ଅକ୍ଷର *g_DescriptionText = ଖାଲି;
ସ୍ଥିର ଅକ୍ଷର *g_DefaultText = ଖାଲି;
ସ୍ଥିର ଅଚଳ Sint32 g_Default_Text_ନିବେଶ_Scope = (Sint32)XGame_Ui_Text_Entry_ନିବେଶ_Scope::Default;
ସ୍ଥିର Sint32 g_Text_ନିବେଶ_Scope = g_Default_Text_ନିବେଶ_Scope;
ସ୍ଥିର ଅଚଳ Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
ସ୍ଥିର Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

ସ୍ଥିର ଶୂନ୍ୟ SDLCALL GDK_InternalHintCallback(
    ଶୂନ୍ୟ *userdata,
    ଅଚଳ ଅକ୍ଷର *name,
    ଅଚଳ ଅକ୍ଷର *old_ମୂଲ୍ୟ,
    ଅଚଳ ଅକ୍ଷର *new_ମୂଲ୍ୟ)
{
    ଯଦି (!userdata) {
        ଫେରନ୍ତୁ;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    ଯଦି (userdata == &g_Text_ନିବେଶ_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_ମୂଲ୍ୟ = (!new_ମୂଲ୍ୟ || new_ମୂଲ୍ୟ[0] == '\0') ? 0 : SDL_atoi(new_ମୂଲ୍ୟ);
        ଯଦି (userdata == &g_MaxTextLength && int_ମୂଲ୍ୟ <= 0) {
            int_ମୂଲ୍ୟ = g_DefaultMaxTextLength;
        } ଅନ୍ୟଥା ଯଦି (userdata == &g_Text_ନିବେଶ_Scope && int_ମୂଲ୍ୟ < 0) {
            int_ମୂଲ୍ୟ = g_Default_Text_ନିବେଶ_Scope;
        }

        *(Sint32 *)userdata = int_ମୂଲ୍ୟ;
    } ଅନ୍ୟଥା {
        // string hint
        ଯଦି (!new_ମୂଲ୍ୟ || new_ମୂଲ୍ୟ[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(ଅକ୍ଷର **)userdata);
            *(ଅକ୍ଷର **)userdata = ଖାଲି;
        } ଅନ୍ୟଥା {
            ଅକ୍ଷର *newString = SDL_strdup(new_ମୂଲ୍ୟ);
            ଯଦି (newString) {
                // free previous value and write the new one
                SDL_free(*(ଅକ୍ଷର **)userdata);
                *(ଅକ୍ଷର **)userdata = newString;
            }
        }
    }
}

ସ୍ଥିର ତାର୍କିକ GDK_InternalEnsureTaskQueue(ଶୂନ୍ୟ)
{
    ଯଦି (!g_TextTaskQueue) {
        ଯଦି (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            ଫେରନ୍ତୁ ମିଥ୍ୟା;
        }
    }
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ସ୍ଥିର ଶୂନ୍ୟ CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    ଅକ୍ଷର *resultBuffer = ଖାଲି;

    // The keyboard will be already hidden when we reach this code

    ଯଦି (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } ଅନ୍ୟଥା ଯଦି (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (ଅକ୍ଷର *)SDL_calloc(1 + (size_t)resultSize, ଆକାର(*resultBuffer));
        ଯଦି (resultBuffer) {
            // still pass the original size that we got from ResultSize
            ଯଦି (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            ଅନ୍ୟଥା ଯଦି (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = ଖାଲି;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = ଖାଲି;
    g_TextBlock = ଖାଲି; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

ଶୂନ୍ୟ GDK_EnsureHints(ଶୂନ୍ୟ)
{
    ଯଦି (g_DidRegisterHints == ମିଥ୍ୟା) {
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
            &g_Text_ନିବେଶ_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = ସତ୍ୟ;
    }
}

ତାର୍କିକ GDK_Start_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ GDK_Stop_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ GDK_Update_Text_ନିବେଶ_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଶୂନ୍ୟ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    ଯଦି (g_TextBlock) {
        // already showing the keyboard
        ଫେରନ୍ତୁ;
    }

    ଯଦି (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        ଫେରନ୍ତୁ;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, ଆକାର(*g_TextBlock));
    ଯଦି (!g_TextBlock) {
        ଫେରନ୍ତୁ;
    }

    XGame_Ui_Text_Entry_ନିବେଶ_Scope scope;
    ବାଛ (SDL_Get_Text_ନିବେଶ_Type(props)) {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_ନିବେଶ_Scope)g_Text_ନିବେଶ_Scope;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::Default;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::EmailSmtpAddress;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::Default;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::Password;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::Default;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା:
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::ସଂଖ୍ୟା;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::ସଂଖ୍ୟା;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_ନିବେଶ_Scope::ସଂଖ୍ୟା;
        ଭାଙ୍ଗ;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    ଯଦି (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } ଅନ୍ୟଥା {
        SDL_free(g_TextBlock);
        g_TextBlock = ଖାଲି;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

ଶୂନ୍ୟ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    ଯଦି (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
