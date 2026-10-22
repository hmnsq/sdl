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
#অন্তর্ভাৱ "SDL_internal.h"
#অন্তর্ভাৱ "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#অন্তর্ভাৱ <Windows.h>
#অন্তর্ভাৱ <XGameUI.h>
#অন্তর্ভাৱ <XUser.h>

#ifdef __cplusplus
বাহ্য "C" {
#endif

#অন্তর্ভাৱ "../../events/SDL_keyboard_c.h"
#অন্তর্ভাৱ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
স্থির XTaskQueueHandle g_TextTaskQueue = রিক্ত;
// Global because there can be only one text entry shown at once.
স্থির XAsyncBlock *g_TextBlock = রিক্ত;

// Creation parameters
স্থির তার্কিক g_DidRegisterHints = মিছা;
স্থির ৱর্ণ *g_TitleText = রিক্ত;
স্থির ৱর্ণ *g_DescriptionText = রিক্ত;
স্থির ৱর্ণ *g_DefaultText = রিক্ত;
স্থির ধ্রুৱ Sint32 g_Default_Text_প্ৰবেশ_Scope = (Sint32)XGame_Ui_Text_Entry_প্ৰবেশ_Scope::Default;
স্থির Sint32 g_Text_প্ৰবেশ_Scope = g_Default_Text_প্ৰবেশ_Scope;
স্থির ধ্রুৱ Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
স্থির Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

স্থির শূন্য SDLCALL GDK_InternalHintCallback(
    শূন্য *userdata,
    ধ্রুৱ ৱর্ণ *name,
    ধ্রুৱ ৱর্ণ *old_মান,
    ধ্রুৱ ৱর্ণ *new_মান)
{
    যদি (!userdata) {
        ঘূৰাই;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    যদি (userdata == &g_Text_প্ৰবেশ_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_মান = (!new_মান || new_মান[0] == '\0') ? 0 : SDL_atoi(new_মান);
        যদি (userdata == &g_MaxTextLength && int_মান <= 0) {
            int_মান = g_DefaultMaxTextLength;
        } অন্যথা যদি (userdata == &g_Text_প্ৰবেশ_Scope && int_মান < 0) {
            int_মান = g_Default_Text_প্ৰবেশ_Scope;
        }

        *(Sint32 *)userdata = int_মান;
    } অন্যথা {
        // string hint
        যদি (!new_মান || new_মান[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(ৱর্ণ **)userdata);
            *(ৱর্ণ **)userdata = রিক্ত;
        } অন্যথা {
            ৱর্ণ *newString = SDL_strdup(new_মান);
            যদি (newString) {
                // free previous value and write the new one
                SDL_free(*(ৱর্ণ **)userdata);
                *(ৱর্ণ **)userdata = newString;
            }
        }
    }
}

স্থির তার্কিক GDK_InternalEnsureTaskQueue(শূন্য)
{
    যদি (!g_TextTaskQueue) {
        যদি (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            ঘূৰাই মিছা;
        }
    }
    ঘূৰাই সঁচা;
}

স্থির শূন্য CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    ৱর্ণ *resultBuffer = রিক্ত;

    // The keyboard will be already hidden when we reach this code

    যদি (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } অন্যথা যদি (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (ৱর্ণ *)SDL_calloc(1 + (size_t)resultSize, পরিমাণ(*resultBuffer));
        যদি (resultBuffer) {
            // still pass the original size that we got from ResultSize
            যদি (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            অন্যথা যদি (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = রিক্ত;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = রিক্ত;
    g_TextBlock = রিক্ত; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

শূন্য GDK_EnsureHints(শূন্য)
{
    যদি (g_DidRegisterHints == মিছা) {
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
            &g_Text_প্ৰবেশ_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = সঁচা;
    }
}

তার্কিক GDK_Start_Text_প্ৰবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    ঘূৰাই সঁচা;
}

তার্কিক GDK_Stop_Text_প্ৰবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ঘূৰাই সঁচা;
}

তার্কিক GDK_Update_Text_প্ৰবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    ঘূৰাই সঁচা;
}

তার্কিক GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ঘূৰাই সঁচা;
}

তার্কিক GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    ঘূৰাই সঁচা;
}

শূন্য GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    যদি (g_TextBlock) {
        // already showing the keyboard
        ঘূৰাই;
    }

    যদি (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        ঘূৰাই;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, পরিমাণ(*g_TextBlock));
    যদি (!g_TextBlock) {
        ঘূৰাই;
    }

    XGame_Ui_Text_Entry_প্ৰবেশ_Scope scope;
    ৱিকল্প (SDL_Get_Text_প্ৰবেশ_Type(props)) {
    স্ৱভাৱ:
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_প্ৰবেশ_Scope)g_Text_প্ৰবেশ_Scope;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::Default;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::EmailSmtpAddress;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::Default;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::Password;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::Default;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা:
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::সংখ্যা;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::সংখ্যা;
        ভঙ্গ;
    পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_প্ৰবেশ_Scope::সংখ্যা;
        ভঙ্গ;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    যদি (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } অন্যথা {
        SDL_free(g_TextBlock);
        g_TextBlock = রিক্ত;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

শূন্য GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
