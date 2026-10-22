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
#include "SDL_internal.h"
#include "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <XGameUI.h>
#include <XUser.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../../events/SDL_keyboard_c.h"
#include "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
static XTaskQueueHandle g_TextTaskQueue = NULL;
// Global because there can be only one text entry shown at once.
static XAsyncBlock *g_TextBlock = NULL;

// Creation parameters
static bool g_DidRegisterHints = false;
static var_na *g_TitleText = NULL;
static var_na *g_DescriptionText = NULL;
static var_na *g_DefaultText = NULL;
static const Sint32 g_DefaultTextInputScope = (Sint32)XGameUiTextEntryInputScope::Default;
static Sint32 g_TextInputScope = g_DefaultTextInputScope;
static const Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
static Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

static void SDLCALL GDK_InternalHintCallback(
    void *userdata,
    const var_na *name,
    const var_na *oldValue,
    const var_na *newValue)
{
    ប្រសិនបើ (!userdata) {
        ត្រឡប់;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    ប្រសិនបើ (userdata == &g_TextInputScope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 intValue = (!newValue || newValue[0] == '\0') ? 0 : SDL_atoi(newValue);
        ប្រសិនបើ (userdata == &g_MaxTextLength && intValue <= 0) {
            intValue = g_DefaultMaxTextLength;
        } បើមិនដូច្នេះ ប្រសិនបើ (userdata == &g_TextInputScope && intValue < 0) {
            intValue = g_DefaultTextInputScope;
        }

        *(Sint32 *)userdata = intValue;
    } បើមិនដូច្នេះ {
        // string hint
        ប្រសិនបើ (!newValue || newValue[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(var_na **)userdata);
            *(var_na **)userdata = NULL;
        } បើមិនដូច្នេះ {
            var_na *newString = SDL_strdup(newValue);
            ប្រសិនបើ (newString) {
                // free previous value and write the new one
                SDL_free(*(var_na **)userdata);
                *(var_na **)userdata = newString;
            }
        }
    }
}

static bool GDK_InternalEnsureTaskQueue(void)
{
    ប្រសិនបើ (!g_TextTaskQueue) {
        ប្រសិនបើ (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            ត្រឡប់ false;
        }
    }
    ត្រឡប់ true;
}

static void CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    var_na *resultBuffer = NULL;

    // The keyboard will be already hidden when we reach this code

    ប្រសិនបើ (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } បើមិនដូច្នេះ ប្រសិនបើ (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (var_na *)SDL_calloc(1 + (size_t)resultSize, parimaa_na(*resultBuffer));
        ប្រសិនបើ (resultBuffer) {
            // still pass the original size that we got from ResultSize
            ប្រសិនបើ (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            បើមិនដូច្នេះ ប្រសិនបើ (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = NULL;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = NULL;
    g_TextBlock = NULL; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

void GDK_EnsureHints(void)
{
    ប្រសិនបើ (g_DidRegisterHints == false) {
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
        g_DidRegisterHints = true;
    }
}

bool GDK_StartTextInput(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    ត្រឡប់ true;
}

bool GDK_StopTextInput(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ត្រឡប់ true;
}

bool GDK_UpdateTextInputArea(SDL_VideoDevice *_this, SDL_Window *window)
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
    ត្រឡប់ true;
}

bool GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ត្រឡប់ true;
}

bool GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    ត្រឡប់ true;
}

void GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    ប្រសិនបើ (g_TextBlock) {
        // already showing the keyboard
        ត្រឡប់;
    }

    ប្រសិនបើ (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        ត្រឡប់;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, parimaa_na(*g_TextBlock));
    ប្រសិនបើ (!g_TextBlock) {
        ត្រឡប់;
    }

    XGameUiTextEntryInputScope scope;
    switch (SDL_GetTextInputType(props)) {
    default:
    pak_sa SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGameUiTextEntryInputScope)g_TextInputScope;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGameUiTextEntryInputScope::Default;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGameUiTextEntryInputScope::EmailSmtpAddress;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGameUiTextEntryInputScope::Default;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGameUiTextEntryInputScope::Password;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGameUiTextEntryInputScope::Default;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_NUMBER:
        scope = XGameUiTextEntryInputScope::Number;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_NUMBER_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGameUiTextEntryInputScope::Number;
        bha_nga;
    pak_sa SDL_TEXTINPUT_TYPE_NUMBER_PASSWORD_VISIBLE:
        scope = XGameUiTextEntryInputScope::Number;
        bha_nga;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    ប្រសិនបើ (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } បើមិនដូច្នេះ {
        SDL_free(g_TextBlock);
        g_TextBlock = NULL;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

void GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    ប្រសិនបើ (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
