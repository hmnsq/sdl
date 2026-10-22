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

#جے_تعریف_شدہ SDL_GDK_TEXTINPUT

// GDK headers are weird here
#جے_بنا_تعریف WIN32_LEAN_AND_اوسط
#تعریف_کرو WIN32_LEAN_AND_اوسط
#جے_انت
#ضمن <Windows.h>
#ضمن <XGameUI.h>
#ضمن <XUser.h>

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ساكن XTask_قطار_Handle g_متن_Task_قطار = عدم;
// Global because there can be only one text entry shown at once.
ساكن XAsync_بلاک *g_متن_بلاک = عدم;

// Creation parameters
ساكن منطقي g_Did_رجسٹر_Hints = خطأ;
ساكن حرف *g_Title_متن = عدم;
ساكن حرف *g_Description_متن = عدم;
ساكن حرف *g_Default_متن = عدم;
ساكن ثابت Sint32 g_Default_متن_داخلہ_Scope = (Sint32)XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
ساكن Sint32 g_متن_داخلہ_Scope = g_Default_متن_داخلہ_Scope;
ساكن ثابت Sint32 g_Default_Max_متن_لمائی = 1024; // as per doc: maximum allowed amount on consoles
ساكن Sint32 g_Max_متن_لمائی = g_Default_Max_متن_لمائی;

ساكن فراغ SDLCALL GDK_اندرونی_Hint_Callback(
    فراغ *userdata,
    ثابت حرف *name,
    ثابت حرف *old_قدر,
    ثابت حرف *new_قدر)
{
    إذا (!userdata) {
        أرجع;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    إذا (userdata == &g_متن_داخلہ_Scope || userdata == &g_Max_متن_لمائی) {
        // int32 hint
        Sint32 int_قدر = (!new_قدر || new_قدر[0] == '\0') ? 0 : SDL_atoi(new_قدر);
        إذا (userdata == &g_Max_متن_لمائی && int_قدر <= 0) {
            int_قدر = g_Default_Max_متن_لمائی;
        } وإلا إذا (userdata == &g_متن_داخلہ_Scope && int_قدر < 0) {
            int_قدر = g_Default_متن_داخلہ_Scope;
        }

        *(Sint32 *)userdata = int_قدر;
    } وإلا {
        // string hint
        إذا (!new_قدر || new_قدر[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(حرف **)userdata);
            *(حرف **)userdata = عدم;
        } وإلا {
            حرف *newString = SDL_strdup(new_قدر);
            إذا (newString) {
                // free previous value and write the new one
                SDL_free(*(حرف **)userdata);
                *(حرف **)userdata = newString;
            }
        }
    }
}

ساكن منطقي GDK_اندرونی_Ensure_Task_قطار(فراغ)
{
    إذا (!g_متن_Task_قطار) {
        إذا (!SDL_Get_GDKTask_قطار(&g_متن_Task_قطار)) {
            // SetError will be done for us.
            أرجع خطأ;
        }
    }
    أرجع سچ;
}

ساكن فراغ CALLBACK GDK_اندرونی_متن_اندراج_Callback(XAsync_بلاک *async_بلاک)
{
    HRESULT hR = S_OK;
    Uint32 نتیجہ_ناپ = 0;
    Uint32 نتیجہ_ورتیا = 0;
    حرف *نتیجہ_بفر = عدم;

    // The keyboard will be already hidden when we reach this code

    إذا (FAILED(hR = XGame_Ui_Show_متن_اندراج_نتیجہ_ناپ(
                   async_بلاک,
                   &نتیجہ_ناپ))) {
        SDL_سیٹ_Error("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } وإلا إذا (نتیجہ_ناپ > 0) {
        // +1 to be super sure that the buffer will be null terminated
        نتیجہ_بفر = (حرف *)SDL_calloc(1 + (size_t)نتیجہ_ناپ, حجم(*نتیجہ_بفر));
        إذا (نتیجہ_بفر) {
            // still pass the original size that we got from ResultSize
            إذا (FAILED(hR = XGame_Ui_Show_متن_اندراج_نتیجہ(
                           async_بلاک,
                           نتیجہ_ناپ,
                           نتیجہ_بفر,
                           &نتیجہ_ورتیا))) {
                SDL_سیٹ_Error("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            وإلا إذا (نتیجہ_ورتیا > 0 && نتیجہ_بفر[0] != '\0') {
                // it's null terminated so it's fine
                SDL_Send_Keyboard_متن(نتیجہ_بفر);
            }
            // we're done with the buffer
            SDL_free(نتیجہ_بفر);
            نتیجہ_بفر = عدم;
        }
    }

    // free the async block after we're done
    SDL_free(async_بلاک);
    async_بلاک = عدم;
    g_متن_بلاک = عدم; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

فراغ GDK_EnsureHints(فراغ)
{
    إذا (g_Did_رجسٹر_Hints == خطأ) {
        SDL_جوڑو_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_TITLE,
            GDK_اندرونی_Hint_Callback,
            &g_Title_متن);
        SDL_جوڑو_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DESCRIPTION,
            GDK_اندرونی_Hint_Callback,
            &g_Description_متن);
        SDL_جوڑو_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DEFAULT_متن,
            GDK_اندرونی_Hint_Callback,
            &g_Default_متن);
        SDL_جوڑو_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_SCOPE,
            GDK_اندرونی_Hint_Callback,
            &g_متن_داخلہ_Scope);
        SDL_جوڑو_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_MAX_لمائی,
            GDK_اندرونی_Hint_Callback,
            &g_Max_متن_لمائی);
        g_Did_رجسٹر_Hints = سچ;
    }
}

منطقي GDK_شروع_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
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
    أرجع سچ;
}

منطقي GDK_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // See notice in GDK_StartTextInput
    أرجع سچ;
}

منطقي GDK_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
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
    أرجع سچ;
}

منطقي GDK_ClearComposition(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // See notice in GDK_StartTextInput
    أرجع سچ;
}

منطقي GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    أرجع سچ;
}

فراغ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    إذا (g_متن_بلاک) {
        // already showing the keyboard
        أرجع;
    }

    إذا (!GDK_اندرونی_Ensure_Task_قطار()) {
        // unable to obtain the SDL GDK queue
        أرجع;
    }

    g_متن_بلاک = (XAsync_بلاک *)SDL_calloc(1, حجم(*g_متن_بلاک));
    إذا (!g_متن_بلاک) {
        أرجع;
    }

    XGame_Ui_متن_اندراج_داخلہ_Scope scope;
    بدل (SDL_Get_متن_داخلہ_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_متن:
        scope = (XGame_Ui_متن_اندراج_داخلہ_Scope)g_متن_داخلہ_Scope;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Email_Smtp_پتہ;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_USERNAME:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Password;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::نمبر;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::نمبر;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::نمبر;
        اكسر;
    }

    g_متن_بلاک->قطار = g_متن_Task_قطار;
    g_متن_بلاک->context = _this;
    g_متن_بلاک->callback = GDK_اندرونی_متن_اندراج_Callback;
    إذا (SUCCEEDED(hR = XGame_Ui_Show_متن_اندراج_Async(
                   g_متن_بلاک,
                   g_Title_متن,
                   g_Description_متن,
                   g_Default_متن,
                   scope,
                   (uint32_t)g_Max_متن_لمائی))) {
        SDL_SendScreenKeyboardShown();
    } وإلا {
        SDL_free(g_متن_بلاک);
        g_متن_بلاک = عدم;
        SDL_سیٹ_Error("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

فراغ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (g_متن_بلاک) {
        XAsyncCancel(g_متن_بلاک);
        // the completion callback will free the block
    }
}

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
