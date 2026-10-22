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
#અન્તર્ભાવ "SDL_internal.h"
#અન્તર્ભાવ "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#અન્તર્ભાવ <Windows.h>
#અન્તર્ભાવ <XGameUI.h>
#અન્તર્ભાવ <XUser.h>

#ifdef __cplusplus
બાહ્ય "C" {
#endif

#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"
#અન્તર્ભાવ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
સ્થિર XTaskQueueHandle g_TextTaskQueue = ખાલી;
// Global because there can be only one text entry shown at once.
સ્થિર XAsyncBlock *g_TextBlock = ખાલી;

// Creation parameters
સ્થિર તાર્કિક g_DidRegisterHints = ખોટું;
સ્થિર અક્ષર *g_TitleText = ખાલી;
સ્થિર અક્ષર *g_DescriptionText = ખાલી;
સ્થિર અક્ષર *g_DefaultText = ખાલી;
સ્થિર અચલ Sint32 g_Default_Text_આગત_Scope = (Sint32)XGame_Ui_Text_Entry_આગત_Scope::Default;
સ્થિર Sint32 g_Text_આગત_Scope = g_Default_Text_આગત_Scope;
સ્થિર અચલ Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
સ્થિર Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

સ્થિર શૂન્ય SDLCALL GDK_InternalHintCallback(
    શૂન્ય *userdata,
    અચલ અક્ષર *name,
    અચલ અક્ષર *old_કિંમત,
    અચલ અક્ષર *new_કિંમત)
{
    જો (!userdata) {
        પાછા;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    જો (userdata == &g_Text_આગત_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_કિંમત = (!new_કિંમત || new_કિંમત[0] == '\0') ? 0 : SDL_atoi(new_કિંમત);
        જો (userdata == &g_MaxTextLength && int_કિંમત <= 0) {
            int_કિંમત = g_DefaultMaxTextLength;
        } નહીંતર જો (userdata == &g_Text_આગત_Scope && int_કિંમત < 0) {
            int_કિંમત = g_Default_Text_આગત_Scope;
        }

        *(Sint32 *)userdata = int_કિંમત;
    } નહીંતર {
        // string hint
        જો (!new_કિંમત || new_કિંમત[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(અક્ષર **)userdata);
            *(અક્ષર **)userdata = ખાલી;
        } નહીંતર {
            અક્ષર *newString = SDL_strdup(new_કિંમત);
            જો (newString) {
                // free previous value and write the new one
                SDL_free(*(અક્ષર **)userdata);
                *(અક્ષર **)userdata = newString;
            }
        }
    }
}

સ્થિર તાર્કિક GDK_InternalEnsureTaskQueue(શૂન્ય)
{
    જો (!g_TextTaskQueue) {
        જો (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            પાછા ખોટું;
        }
    }
    પાછા સાચું;
}

સ્થિર શૂન્ય CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    અક્ષર *resultBuffer = ખાલી;

    // The keyboard will be already hidden when we reach this code

    જો (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } નહીંતર જો (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (અક્ષર *)SDL_calloc(1 + (size_t)resultSize, કદ(*resultBuffer));
        જો (resultBuffer) {
            // still pass the original size that we got from ResultSize
            જો (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            નહીંતર જો (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = ખાલી;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = ખાલી;
    g_TextBlock = ખાલી; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

શૂન્ય GDK_EnsureHints(શૂન્ય)
{
    જો (g_DidRegisterHints == ખોટું) {
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
            &g_Text_આગત_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = સાચું;
    }
}

તાર્કિક GDK_Start_Text_આગત(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    પાછા સાચું;
}

તાર્કિક GDK_Stop_Text_આગત(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    પાછા સાચું;
}

તાર્કિક GDK_Update_Text_આગત_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    પાછા સાચું;
}

તાર્કિક GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    પાછા સાચું;
}

તાર્કિક GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    પાછા સાચું;
}

શૂન્ય GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    જો (g_TextBlock) {
        // already showing the keyboard
        પાછા;
    }

    જો (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        પાછા;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, કદ(*g_TextBlock));
    જો (!g_TextBlock) {
        પાછા;
    }

    XGame_Ui_Text_Entry_આગત_Scope scope;
    પસંદગી (SDL_Get_Text_આગત_Type(props)) {
    મૂળભૂત:
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_આગત_Scope)g_Text_આગત_Scope;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_આગત_Scope::Default;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_આગત_Scope::EmailSmtpAddress;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_આગત_Scope::Default;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_આગત_Scope::Password;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_આગત_Scope::Default;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા:
        scope = XGame_Ui_Text_Entry_આગત_Scope::સંખ્યા;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_આગત_Scope::સંખ્યા;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_આગત_Scope::સંખ્યા;
        તોડો;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    જો (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } નહીંતર {
        SDL_free(g_TextBlock);
        g_TextBlock = ખાલી;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

શૂન્ય GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    જો (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
