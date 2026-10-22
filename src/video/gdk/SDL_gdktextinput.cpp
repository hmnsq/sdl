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
#شامل "SDL_internal.h"
#شامل "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#شامل <Windows.h>
#شامل <XGameUI.h>
#شامل <XUser.h>

#ifdef __cplusplus
بیرونی "C" {
#endif

#شامل "../../events/SDL_keyboard_c.h"
#شامل "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ایستا XTaskQueueHandle g_TextTaskQueue = پوچ;
// Global because there can be only one text entry shown at once.
ایستا XAsyncBlock *g_TextBlock = پوچ;

// Creation parameters
ایستا منطقی g_DidRegisterHints = نادرست;
ایستا نویسه *g_TitleText = پوچ;
ایستا نویسه *g_DescriptionText = پوچ;
ایستا نویسه *g_DefaultText = پوچ;
ایستا ثابت Sint32 g_Default_Text_درون_داد_Scope = (Sint32)XGame_Ui_Text_Entry_درون_داد_Scope::Default;
ایستا Sint32 g_Text_درون_داد_Scope = g_Default_Text_درون_داد_Scope;
ایستا ثابت Sint32 g_DefaultMaxTextLength = 1024; // as per doc: maximum allowed amount on consoles
ایستا Sint32 g_MaxTextLength = g_DefaultMaxTextLength;

ایستا تهی SDLCALL GDK_InternalHintCallback(
    تهی *userdata,
    ثابت نویسه *name,
    ثابت نویسه *old_مقدار,
    ثابت نویسه *new_مقدار)
{
    اگر (!userdata) {
        بازگشت;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    اگر (userdata == &g_Text_درون_داد_Scope || userdata == &g_MaxTextLength) {
        // int32 hint
        Sint32 int_مقدار = (!new_مقدار || new_مقدار[0] == '\0') ? 0 : SDL_atoi(new_مقدار);
        اگر (userdata == &g_MaxTextLength && int_مقدار <= 0) {
            int_مقدار = g_DefaultMaxTextLength;
        } وگرنه اگر (userdata == &g_Text_درون_داد_Scope && int_مقدار < 0) {
            int_مقدار = g_Default_Text_درون_داد_Scope;
        }

        *(Sint32 *)userdata = int_مقدار;
    } وگرنه {
        // string hint
        اگر (!new_مقدار || new_مقدار[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(نویسه **)userdata);
            *(نویسه **)userdata = پوچ;
        } وگرنه {
            نویسه *newString = SDL_strdup(new_مقدار);
            اگر (newString) {
                // free previous value and write the new one
                SDL_free(*(نویسه **)userdata);
                *(نویسه **)userdata = newString;
            }
        }
    }
}

ایستا منطقی GDK_InternalEnsureTaskQueue(تهی)
{
    اگر (!g_TextTaskQueue) {
        اگر (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            بازگشت نادرست;
        }
    }
    بازگشت درست;
}

ایستا تهی CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 resultSize = 0;
    Uint32 resultUsed = 0;
    نویسه *resultBuffer = پوچ;

    // The keyboard will be already hidden when we reach this code

    اگر (FAILED(hR = XGameUiShowTextEntryResultSize(
                   asyncBlock,
                   &resultSize))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } وگرنه اگر (resultSize > 0) {
        // +1 to be super sure that the buffer will be null terminated
        resultBuffer = (نویسه *)SDL_calloc(1 + (size_t)resultSize, اندازه(*resultBuffer));
        اگر (resultBuffer) {
            // still pass the original size that we got from ResultSize
            اگر (FAILED(hR = XGameUiShowTextEntryResult(
                           asyncBlock,
                           resultSize,
                           resultBuffer,
                           &resultUsed))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            وگرنه اگر (resultUsed > 0 && resultBuffer[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(resultBuffer);
            }
            // we're done with the buffer
            SDL_free(resultBuffer);
            resultBuffer = پوچ;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = پوچ;
    g_TextBlock = پوچ; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

تهی GDK_EnsureHints(تهی)
{
    اگر (g_DidRegisterHints == نادرست) {
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
            &g_Text_درون_داد_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH,
            GDK_InternalHintCallback,
            &g_MaxTextLength);
        g_DidRegisterHints = درست;
    }
}

منطقی GDK_Start_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    بازگشت درست;
}

منطقی GDK_Stop_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    بازگشت درست;
}

منطقی GDK_Update_Text_درون_داد_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    بازگشت درست;
}

منطقی GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    بازگشت درست;
}

منطقی GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    بازگشت درست;
}

تهی GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    اگر (g_TextBlock) {
        // already showing the keyboard
        بازگشت;
    }

    اگر (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        بازگشت;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, اندازه(*g_TextBlock));
    اگر (!g_TextBlock) {
        بازگشت;
    }

    XGame_Ui_Text_Entry_درون_داد_Scope scope;
    انتخاب (SDL_Get_Text_درون_داد_Type(props)) {
    پیشفرض:
    حالت SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_درون_داد_Scope)g_Text_درون_داد_Scope;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::Default;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::EmailSmtpAddress;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::Default;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::Password;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::Default;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_عدد:
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::عدد;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::عدد;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_درون_داد_Scope::عدد;
        بشکن;
    }

    g_TextBlock->queue = g_TextTaskQueue;
    g_TextBlock->context = _this;
    g_TextBlock->callback = GDK_InternalTextEntryCallback;
    اگر (SUCCEEDED(hR = XGameUiShowTextEntryAsync(
                   g_TextBlock,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_MaxTextLength))) {
        SDL_SendScreenKeyboardShown();
    } وگرنه {
        SDL_free(g_TextBlock);
        g_TextBlock = پوچ;
        SDL_SetError("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

تهی GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    اگر (g_TextBlock) {
        XAsyncCancel(g_TextBlock);
        // the completion callback will free the block
    }
}

#ifdef __cplusplus
}
#endif

#endif
