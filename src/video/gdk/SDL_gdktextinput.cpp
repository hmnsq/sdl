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
#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "SDL_gdktextinput.h"

#ifdef SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#অন্তর্ভাব <Windows.h>
#অন্তর্ভাব <XGameUI.h>
#অন্তর্ভাব <XUser.h>

#ifdef __cplusplus
বাহ্যিক "C" {
#endif

#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
স্থির XTaskQueueHandle g_TextTaskQueue = ফাঁকা;
// Global because there can be only one text entry shown at once.
স্থির XAsyncBlock *g_TextBlock = ফাঁকা;

// Creation parameters
স্থির যৌক্তিক g_DidRegisterHints = মিথ্যা;
স্থির অক্ষর *g_TitleText = ফাঁকা;
স্থির অক্ষর *g_DescriptionText = ফাঁকা;
স্থির অক্ষর *g_DefaultText = ফাঁকা;
স্থির ধ্রুবক Sint32 g_Default_Text_প্রবেশ_Scope = (Sint32)XGame_Ui_Text_Entry_প্রবেশ_Scope::Default;
স্থির Sint32 g_Text_প্রবেশ_Scope = g_Default_Text_প্রবেশ_Scope;
স্থির ধ্রুবক Sint32 g_Default_Max_Text_দৈর্ঘ্য = 1024; // as per doc: maximum allowed amount on consoles
স্থির Sint32 g_Max_Text_দৈর্ঘ্য = g_Default_Max_Text_দৈর্ঘ্য;

স্থির শূন্য SDLCALL GDK_InternalHintCallback(
    শূন্য *userdata,
    ধ্রুবক অক্ষর *name,
    ধ্রুবক অক্ষর *old_মান,
    ধ্রুবক অক্ষর *new_মান)
{
    যদি (!userdata) {
        ফেরত;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    যদি (userdata == &g_Text_প্রবেশ_Scope || userdata == &g_Max_Text_দৈর্ঘ্য) {
        // int32 hint
        Sint32 int_মান = (!new_মান || new_মান[0] == '\0') ? 0 : SDL_atoi(new_মান);
        যদি (userdata == &g_Max_Text_দৈর্ঘ্য && int_মান <= 0) {
            int_মান = g_Default_Max_Text_দৈর্ঘ্য;
        } অন্যথা যদি (userdata == &g_Text_প্রবেশ_Scope && int_মান < 0) {
            int_মান = g_Default_Text_প্রবেশ_Scope;
        }

        *(Sint32 *)userdata = int_মান;
    } অন্যথা {
        // string hint
        যদি (!new_মান || new_মান[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(অক্ষর **)userdata);
            *(অক্ষর **)userdata = ফাঁকা;
        } অন্যথা {
            অক্ষর *newString = SDL_strdup(new_মান);
            যদি (newString) {
                // free previous value and write the new one
                SDL_free(*(অক্ষর **)userdata);
                *(অক্ষর **)userdata = newString;
            }
        }
    }
}

স্থির যৌক্তিক GDK_InternalEnsureTaskQueue(শূন্য)
{
    যদি (!g_TextTaskQueue) {
        যদি (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            ফেরত মিথ্যা;
        }
    }
    ফেরত সত্য;
}

স্থির শূন্য CALLBACK GDK_InternalTextEntryCallback(XAsyncBlock *asyncBlock)
{
    HRESULT hR = S_OK;
    Uint32 ফলাফল_আকার = 0;
    Uint32 ফলাফল_Used = 0;
    অক্ষর *ফলাফল_বাফার = ফাঁকা;

    // The keyboard will be already hidden when we reach this code

    যদি (FAILED(hR = XGame_Ui_Show_Text_Entry_ফলাফল_আকার(
                   asyncBlock,
                   &ফলাফল_আকার))) {
        SDL_SetError("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } অন্যথা যদি (ফলাফল_আকার > 0) {
        // +1 to be super sure that the buffer will be null terminated
        ফলাফল_বাফার = (অক্ষর *)SDL_calloc(1 + (size_t)ফলাফল_আকার, আকার(*ফলাফল_বাফার));
        যদি (ফলাফল_বাফার) {
            // still pass the original size that we got from ResultSize
            যদি (FAILED(hR = XGame_Ui_Show_Text_Entry_ফলাফল(
                           asyncBlock,
                           ফলাফল_আকার,
                           ফলাফল_বাফার,
                           &ফলাফল_Used))) {
                SDL_SetError("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            অন্যথা যদি (ফলাফল_Used > 0 && ফলাফল_বাফার[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(ফলাফল_বাফার);
            }
            // we're done with the buffer
            SDL_free(ফলাফল_বাফার);
            ফলাফল_বাফার = ফাঁকা;
        }
    }

    // free the async block after we're done
    SDL_free(asyncBlock);
    asyncBlock = ফাঁকা;
    g_TextBlock = ফাঁকা; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

শূন্য GDK_EnsureHints(শূন্য)
{
    যদি (g_DidRegisterHints == মিথ্যা) {
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
            &g_Text_প্রবেশ_Scope);
        SDL_AddHintCallback(
            SDL_HINT_GDK_TEXTINPUT_MAX_দৈর্ঘ্য,
            GDK_InternalHintCallback,
            &g_Max_Text_দৈর্ঘ্য);
        g_DidRegisterHints = সত্য;
    }
}

যৌক্তিক GDK_Start_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
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
    ফেরত সত্য;
}

যৌক্তিক GDK_Stop_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ফেরত সত্য;
}

যৌক্তিক GDK_Update_Text_প্রবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window)
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
    ফেরত সত্য;
}

যৌক্তিক GDK_ClearComposition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // See notice in GDK_StartTextInput
    ফেরত সত্য;
}

যৌক্তিক GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    ফেরত সত্য;
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
        ফেরত;
    }

    যদি (!GDK_InternalEnsureTaskQueue()) {
        // unable to obtain the SDL GDK queue
        ফেরত;
    }

    g_TextBlock = (XAsyncBlock *)SDL_calloc(1, আকার(*g_TextBlock));
    যদি (!g_TextBlock) {
        ফেরত;
    }

    XGame_Ui_Text_Entry_প্রবেশ_Scope scope;
    নির্বাচন (SDL_Get_Text_প্রবেশ_Type(props)) {
    পূর্বনির্ধারিত:
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_Entry_প্রবেশ_Scope)g_Text_প্রবেশ_Scope;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::Default;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::EmailSmtpAddress;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::Default;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::Password;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::Default;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা:
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::সংখ্যা;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::সংখ্যা;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_Entry_প্রবেশ_Scope::সংখ্যা;
        বিরতি;
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
                   (uint32_t)g_Max_Text_দৈর্ঘ্য))) {
        SDL_SendScreenKeyboardShown();
    } অন্যথা {
        SDL_free(g_TextBlock);
        g_TextBlock = ফাঁকা;
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
