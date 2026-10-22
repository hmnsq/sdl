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
ساكن منطقي g_DidRegisterHints = خطأ;
ساكن حرف *g_TitleText = عدم;
ساكن حرف *g_DescriptionText = عدم;
ساكن حرف *g_DefaultText = عدم;
ساكن ثابت Sint32 g_Default_Text_شغرو_Scope = (Sint32)XGame_Ui_Text_Entry_شغرو_Scope::Default;
ساكن Sint32 g_Text_شغرو_Scope = g_Default_Text_شغرو_Scope;
ساكن ثابت Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
ساكن Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

ساكن فراغ SDLCALL GDK_InternalHintCallback(
    فراغ *userdata,
    ثابت حرف *name,
    ثابت حرف *old_درج,
    ثابت حرف *new_درج)
{
    إذا (!userdata) {
        أرجع;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    إذا (userdata == &g_Text_شغرو_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_درج = (!new_درج || new_درج[0] == '\0') ? 0 : SDL_atoi(new_درج);
        إذا (userdata == &g_MaxTextLength && int_درج <= 0) {
            int_درج = g_DefaultMaxTextLength;
        } وإلا إذا (userdata == &g_Text_شغرو_Scope && int_درج < 0) {
            int_درج = g_Default_Text_شغرو_Scope;
        }

        *(Sint32 *)userdata = int_درج;
    } وإلا {
        // string hint
        إذا (!new_درج || new_درج[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(حرف **)userdata);
            *(حرف **)userdata = عدم;
        } وإلا {
            حرف *newString = SDL_strdup(new_درج);
            إذا (newString) {
                // free previous value and write the new one
                SDL_free(*(حرف **)userdata);
                *(حرف **)userdata = newString;
            }
        }
    }
}

ساكن منطقي GDK_InternalEnsureTaskQueue(فراغ)
{
    إذا (!g_TextTaskQueue) {
        إذا (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            أرجع خطأ;
        }
    }
    أرجع true;
}

ساكن فراغ CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    حرف *resultBuffer = عدم;

    // The keyboard will be already hidden when we reach this code

    إذا (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } وإلا إذا (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (حرف *)SDL_calloc(1 + (size_t)resultSize, حجم(*resultBuffer));
        إذا (resultBuffer) {
            // still pass the original size that we got from ResultSize
            إذا (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            وإلا إذا (resultUsed > 0 && resultBuffer[0] != '\0') {
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
    إذا (g_DidRegisterHints == خطأ) {
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
            &g_Text_شغرو_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = true;
    }
}

منطقي GDK_Start_Text_شغرو(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    أرجع true;
}

منطقي GDK_Stop_Text_شغرو(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    أرجع true;
}

منطقي GDK_Update_Text_شغرو_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    أرجع true;
}

منطقي GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    أرجع true;
}

منطقي GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    أرجع true;
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

    إذا (g_TextBlock) {
        // already showing the keyboard
        أرجع;
    }

    إذا (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        أرجع;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, حجم(*g_TextBlock));
    إذا (!g_TextBlock) {
        أرجع;
    }

    XGame_Ui_Text_Entry_شغرو_Scope scope;
    بدل (SDL_Get_Text_شغرو_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_شغرو_Scope)g_Text_شغرو_Scope;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_شغرو_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_شغرو_Scope::EmailSmtpAddress;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_شغرو_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_شغرو_Scope::Password;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_شغرو_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_لمب:
        scope = XGame_Ui_Text_Entry_شغرو_Scope::لمب_2;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_لمب_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_شغرو_Scope::لمب_2;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_لمب_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_شغرو_Scope::لمب_2;
        اكسر;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    إذا (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } وإلا {
        SDL_free(g_TextBlock);
        g_TextBlock = عدم;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

فراغ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    إذا (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
