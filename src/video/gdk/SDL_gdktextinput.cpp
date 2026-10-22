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
#ضمن "SDL_internal.h"
#ضمن "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ضمن <Windows.h>
#ضمن <XGameUI.h>
#ضمن <XUser.h>

#ifdef __cplusplus
خارجي "C" {
#endif

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ساكن XTaskQueueHandle g_TextTaskQueue = عدم;
// Global because there can be only one text entry shown at once.
ساكن XAsyncBlock *g_TextBlock = عدم;

// Creation parameters
ساكن منطقي g_DidRegisterHints = ܕܓܠܐ;
ساكن حرف *g_TitleText = عدم;
ساكن حرف *g_DescriptionText = عدم;
ساكن حرف *g_DefaultText = عدم;
ساكن ثابت Sint32 g_DefaultTextInputScope = (Sint32)XGameUiTextEntryInputScope::Default;
ساكن Sint32 g_TextInputScope = g_DefaultTextInputScope;
ساكن ثابت Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
ساكن Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

ساكن فراغ SDLCALL GDK_InternalHintCallback(
    فراغ *userdata,
    ثابت حرف *name,
    ثابت حرف *oldValue,
    ثابت حرف *newValue)
{
    ܐܢ (!userdata) {
        ܦܢܐ;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    ܐܢ (userdata == &g_TextInputScope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 intValue = (!newValue || newValue[0] == '\0') ? 0 : SDL_atoi(newValue);
        ܐܢ (userdata == &g_MaxTextLength && intValue <= 0) {
            intValue = g_DefaultMaxTextLength;
        } ܐܚܪܢܐ ܐܢ (userdata == &g_TextInputScope && intValue < 0) {
            intValue = g_DefaultTextInputScope;
        }

        *(Sint32 *)userdata = intValue;
    } ܐܚܪܢܐ {
        // string hint
        ܐܢ (!newValue || newValue[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(حرف **)userdata);
            *(حرف **)userdata = عدم;
        } ܐܚܪܢܐ {
            حرف *newString = SDL_strdup(newValue);
            ܐܢ (newString) {
                // free previous value and write the new one
                SDL_free(*(حرف **)userdata);
                *(حرف **)userdata = newString;
            }
        }
    }
}

ساكن منطقي GDK_InternalEnsureTaskQueue(فراغ)
{
    ܐܢ (!g_TextTaskQueue) {
        ܐܢ (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            ܦܢܐ ܕܓܠܐ;
        }
    }
    ܦܢܐ ܫܪܪܐ;
}

ساكن فراغ CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    حرف *resultBuffer = عدم;

    // The keyboard will be already hidden when we reach this code

    ܐܢ (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } ܐܚܪܢܐ ܐܢ (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (حرف *)SDL_calloc(1 + (size_t)resultSize, حجم(*resultBuffer));
        ܐܢ (resultBuffer) {
            // still pass the original size that we got from ResultSize
            ܐܢ (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            ܐܚܪܢܐ ܐܢ (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = عدم;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = عدم;
    g_TextBlock = عدم; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

فراغ GDK_EnsureHints(فراغ)
{
    ܐܢ (g_DidRegisterHints == ܕܓܠܐ) {
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
            &g_TextInputScope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = ܫܪܪܐ;
    }
}

منطقي GDK_StartTextInput(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    ܦܢܐ ܫܪܪܐ;
}

منطقي GDK_StopTextInput(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ܦܢܐ ܫܪܪܐ;
}

منطقي GDK_UpdateTextInputArea(SDL_VideoDevice *_this, SDL_Window *window)
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
    ܦܢܐ ܫܪܪܐ;
}

منطقي GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ܦܢܐ ܫܪܪܐ;
}

منطقي GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    ܦܢܐ ܫܪܪܐ;
}

فراغ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    ܐܢ (g_TextBlock) {
        // already showing the keyboard
        ܦܢܐ;
    }

    ܐܢ (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        ܦܢܐ;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, حجم(*g_TextBlock));
    ܐܢ (!g_TextBlock) {
        ܦܢܐ;
    }

    XGameUiTextEntryInputScope scope;
    بدل (SDL_GetTextInputType(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGameUiTextEntryInputScope)g_TextInputScope;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGameUiTextEntryInputScope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGameUiTextEntryInputScope::EmailSmtpAddress;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGameUiTextEntryInputScope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGameUiTextEntryInputScope::Password;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGameUiTextEntryInputScope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_NUMBER:
        scope = XGameUiTextEntryInputScope::Number;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_NUMBER_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGameUiTextEntryInputScope::Number;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_NUMBER_PASSWORD_VISIBLE:
        scope = XGameUiTextEntryInputScope::Number;
        اكسر;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    ܐܢ (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } ܐܚܪܢܐ {
        SDL_free(g_TextBlock);
        g_TextBlock = عدم;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

فراغ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    ܐܢ (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
