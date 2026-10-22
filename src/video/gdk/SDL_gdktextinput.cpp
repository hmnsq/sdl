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

#اگر_تعریف_شدہ SDL_GDK_TEXTINPUT

// GDK headers are weird here
#اگر_غیر_تعریف_شدہ WIN32_LEAN_AND_اوسط
#تعریف_کرو WIN32_LEAN_AND_اوسط
#اگر_ختم
#شامل <Windows.h>
#شامل <XGameUI.h>
#شامل <XUser.h>

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

#شامل "../../events/SDL_keyboard_c.h"
#شامل "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ساکن XTask_قطار_Handle g_متن_Task_قطار = تہی;
// Global because there can be only one text entry shown at once.
ساکن XAsync_بلاک *g_متن_بلاک = تہی;

// Creation parameters
ساکن منطقی g_Did_رجسٹر_Hints = جھوٹ;
ساکن حرف *g_Title_متن = تہی;
ساکن حرف *g_Description_متن = تہی;
ساکن حرف *g_Default_متن = تہی;
ساکن ثابت Sint32 g_Default_متن_داخلہ_Scope = (Sint32)XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
ساکن Sint32 g_متن_داخلہ_Scope = g_Default_متن_داخلہ_Scope;
ساکن ثابت Sint32 g_Default_Max_متن_لمبائی = 1024; // as per doc: maximum allowed amount on consoles
ساکن Sint32 g_Max_متن_لمبائی = g_Default_Max_متن_لمبائی;

ساکن خالی SDLCALL GDK_اندرونی_Hint_Callback(
    خالی *userdata,
    ثابت حرف *name,
    ثابت حرف *old_قدر,
    ثابت حرف *new_قدر)
{
    اگر (!userdata) {
        واپس;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    اگر (userdata == &g_متن_داخلہ_Scope || userdata == &g_Max_متن_لمبائی) {
        // int32 hint
        Sint32 int_قدر = (!new_قدر || new_قدر[0] == '\0') ? 0 : SDL_atoi(new_قدر);
        اگر (userdata == &g_Max_متن_لمبائی && int_قدر <= 0) {
            int_قدر = g_Default_Max_متن_لمبائی;
        } ورنہ اگر (userdata == &g_متن_داخلہ_Scope && int_قدر < 0) {
            int_قدر = g_Default_متن_داخلہ_Scope;
        }

        *(Sint32 *)userdata = int_قدر;
    } ورنہ {
        // string hint
        اگر (!new_قدر || new_قدر[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(حرف **)userdata);
            *(حرف **)userdata = تہی;
        } ورنہ {
            حرف *newString = SDL_strdup(new_قدر);
            اگر (newString) {
                // free previous value and write the new one
                SDL_free(*(حرف **)userdata);
                *(حرف **)userdata = newString;
            }
        }
    }
}

ساکن منطقی GDK_اندرونی_Ensure_Task_قطار(خالی)
{
    اگر (!g_متن_Task_قطار) {
        اگر (!SDL_Get_GDKTask_قطار(&g_متن_Task_قطار)) {
            // SetError will be done for us.
            واپس جھوٹ;
        }
    }
    واپس سچ;
}

ساکن خالی CALLBACK GDK_اندرونی_متن_اندراج_Callback(XAsync_بلاک *async_بلاک)
{
    HRESULT hR = S_OK;
    Uint32 نتیجہ_سائز = 0;
    Uint32 نتیجہ_مستعمل = 0;
    حرف *نتیجہ_بفر = تہی;

    // The keyboard will be already hidden when we reach this code

    اگر (FAILED(hR = XGame_Ui_Show_متن_اندراج_نتیجہ_سائز(
                   async_بلاک,
                   &نتیجہ_سائز))) {
        SDL_سیٹ_Error("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } ورنہ اگر (نتیجہ_سائز > 0) {
        // +1 to be super sure that the buffer will be null terminated
        نتیجہ_بفر = (حرف *)SDL_calloc(1 + (size_t)نتیجہ_سائز, حجم(*نتیجہ_بفر));
        اگر (نتیجہ_بفر) {
            // still pass the original size that we got from ResultSize
            اگر (FAILED(hR = XGame_Ui_Show_متن_اندراج_نتیجہ(
                           async_بلاک,
                           نتیجہ_سائز,
                           نتیجہ_بفر,
                           &نتیجہ_مستعمل))) {
                SDL_سیٹ_Error("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            ورنہ اگر (نتیجہ_مستعمل > 0 && نتیجہ_بفر[0] != '\0') {
                // it's null terminated so it's fine
                SDL_Send_Keyboard_متن(نتیجہ_بفر);
            }
            // we're done with the buffer
            SDL_free(نتیجہ_بفر);
            نتیجہ_بفر = تہی;
        }
    }

    // free the async block after we're done
    SDL_free(async_بلاک);
    async_بلاک = تہی;
    g_متن_بلاک = تہی; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

خالی GDK_EnsureHints(خالی)
{
    اگر (g_Did_رجسٹر_Hints == جھوٹ) {
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
            SDL_HINT_GDK_TEXTINPUT_MAX_لمبائی,
            GDK_اندرونی_Hint_Callback,
            &g_Max_متن_لمبائی);
        g_Did_رجسٹر_Hints = سچ;
    }
}

منطقی GDK_آغاز_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
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
    واپس سچ;
}

منطقی GDK_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // See notice in GDK_StartTextInput
    واپس سچ;
}

منطقی GDK_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
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
    واپس سچ;
}

منطقی GDK_ClearComposition(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // See notice in GDK_StartTextInput
    واپس سچ;
}

منطقی GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    واپس سچ;
}

خالی GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    اگر (g_متن_بلاک) {
        // already showing the keyboard
        واپس;
    }

    اگر (!GDK_اندرونی_Ensure_Task_قطار()) {
        // unable to obtain the SDL GDK queue
        واپس;
    }

    g_متن_بلاک = (XAsync_بلاک *)SDL_calloc(1, حجم(*g_متن_بلاک));
    اگر (!g_متن_بلاک) {
        واپس;
    }

    XGame_Ui_متن_اندراج_داخلہ_Scope scope;
    انتخاب (SDL_Get_متن_داخلہ_Type(props)) {
    طےشدہ:
    حالت SDL_TEXTINPUT_TYPE_متن:
        scope = (XGame_Ui_متن_اندراج_داخلہ_Scope)g_متن_داخلہ_Scope;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_NAME:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_EMAIL:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Email_Smtp_پتہ;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_USERNAME:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Password;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::Default;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::نمبر;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::نمبر;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
        scope = XGame_Ui_متن_اندراج_داخلہ_Scope::نمبر;
        توڑو;
    }

    g_متن_بلاک->قطار = g_متن_Task_قطار;
    g_متن_بلاک->context = _this;
    g_متن_بلاک->callback = GDK_اندرونی_متن_اندراج_Callback;
    اگر (SUCCEEDED(hR = XGame_Ui_Show_متن_اندراج_Async(
                   g_متن_بلاک,
                   g_Title_متن,
                   g_Description_متن,
                   g_Default_متن,
                   scope,
                   (uint32_t)g_Max_متن_لمبائی))) {
        SDL_SendScreenKeyboardShown();
    } ورنہ {
        SDL_free(g_متن_بلاک);
        g_متن_بلاک = تہی;
        SDL_سیٹ_Error("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

خالی GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (g_متن_بلاک) {
        XAsyncCancel(g_متن_بلاک);
        // the completion callback will free the block
    }
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
