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
#അന്തര്ഭാവ "SDL_internal.h"
#അന്തര്ഭാവ "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#അന്തര്ഭാവ <Windows.h>
#അന്തര്ഭാവ <XGameUI.h>
#അന്തര്ഭാവ <XUser.h>

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
സ്ഥിതം XTaskQueueHandle g_TextTaskQueue = ശൂന്യ;
// Global because there can be only one text entry shown at once.
സ്ഥിതം XAsyncBlock *g_TextBlock = ശൂന്യ;

// Creation parameters
സ്ഥിതം തർക്കം g_DidRegisterHints = അസത്യം;
സ്ഥിതം അക്ഷരം *g_TitleText = ശൂന്യ;
സ്ഥിതം അക്ഷരം *g_DescriptionText = ശൂന്യ;
സ്ഥിതം അക്ഷരം *g_DefaultText = ശൂന്യ;
സ്ഥിതം സ്ഥിരം Sint32 g_Default_Text_നിവേശം_Scope = (Sint32)XGame_Ui_Text_Entry_നിവേശം_Scope::Default;
സ്ഥിതം Sint32 g_Text_നിവേശം_Scope = g_Default_Text_നിവേശം_Scope;
സ്ഥിതം സ്ഥിരം Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
സ്ഥിതം Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

സ്ഥിതം ശൂന്യം SDLCALL GDK_InternalHintCallback(
    ശൂന്യം *userdata,
    സ്ഥിരം അക്ഷരം *name,
    സ്ഥിരം അക്ഷരം *old_മൂല്യം,
    സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    എങ്കിൽ (!userdata) {
        തിരികെ;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    എങ്കിൽ (userdata == &g_Text_നിവേശം_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_മൂല്യം = (!new_മൂല്യം || new_മൂല്യം[0] == '\0') ? 0 : SDL_atoi(new_മൂല്യം);
        എങ്കിൽ (userdata == &g_MaxTextLength && int_മൂല്യം <= 0) {
            int_മൂല്യം = g_DefaultMaxTextLength;
        } അല്ലെങ്കിൽ എങ്കിൽ (userdata == &g_Text_നിവേശം_Scope && int_മൂല്യം < 0) {
            int_മൂല്യം = g_Default_Text_നിവേശം_Scope;
        }

        *(Sint32 *)userdata = int_മൂല്യം;
    } അല്ലെങ്കിൽ {
        // string hint
        എങ്കിൽ (!new_മൂല്യം || new_മൂല്യം[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(അക്ഷരം **)userdata);
            *(അക്ഷരം **)userdata = ശൂന്യ;
        } അല്ലെങ്കിൽ {
            അക്ഷരം *newString = SDL_strdup(new_മൂല്യം);
            എങ്കിൽ (newString) {
                // free previous value and write the new one
                SDL_free(*(അക്ഷരം **)userdata);
                *(അക്ഷരം **)userdata = newString;
            }
        }
    }
}

സ്ഥിതം തർക്കം GDK_InternalEnsureTaskQueue(ശൂന്യം)
{
    എങ്കിൽ (!g_TextTaskQueue) {
        എങ്കിൽ (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            തിരികെ അസത്യം;
        }
    }
    തിരികെ സത്യം;
}

സ്ഥിതം ശൂന്യം CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    അക്ഷരം *resultBuffer = ശൂന്യ;

    // The keyboard will be already hidden when we reach this code

    എങ്കിൽ (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } അല്ലെങ്കിൽ എങ്കിൽ (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (അക്ഷരം *)SDL_calloc(1 + (size_t)resultSize, വലുപ്പം(*resultBuffer));
        എങ്കിൽ (resultBuffer) {
            // still pass the original size that we got from ResultSize
            എങ്കിൽ (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            അല്ലെങ്കിൽ എങ്കിൽ (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = ശൂന്യ;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = ശൂന്യ;
    g_TextBlock = ശൂന്യ; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

ശൂന്യം GDK_EnsureHints(ശൂന്യം)
{
    എങ്കിൽ (g_DidRegisterHints == അസത്യം) {
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
            &g_Text_നിവേശം_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = സത്യം;
    }
}

തർക്കം GDK_Start_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    തിരികെ സത്യം;
}

തർക്കം GDK_Stop_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    തിരികെ സത്യം;
}

തർക്കം GDK_Update_Text_നിവേശം_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    തിരികെ സത്യം;
}

തർക്കം GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    തിരികെ സത്യം;
}

തർക്കം GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    തിരികെ സത്യം;
}

ശൂന്യം GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    എങ്കിൽ (g_TextBlock) {
        // already showing the keyboard
        തിരികെ;
    }

    എങ്കിൽ (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        തിരികെ;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, വലുപ്പം(*g_TextBlock));
    എങ്കിൽ (!g_TextBlock) {
        തിരികെ;
    }

    XGame_Ui_Text_Entry_നിവേശം_Scope scope;
    തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Type(props)) {
    സ്ഥിരസ്ഥിതി:
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_നിവേശം_Scope)g_Text_നിവേശം_Scope;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::Default;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::EmailSmtpAddress;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::Default;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::Password;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::Default;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ:
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::സംഖ്യ;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::സംഖ്യ;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_നിവേശം_Scope::സംഖ്യ;
        നിർത്തുക;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    എങ്കിൽ (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } അല്ലെങ്കിൽ {
        SDL_free(g_TextBlock);
        g_TextBlock = ശൂന്യ;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

ശൂന്യം GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
