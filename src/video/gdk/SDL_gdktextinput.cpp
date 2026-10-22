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

#اگر_تعریف_شده SDL_GDK_TEXTINPUT

// GDK headers are weird here
#اگر_تعریف_نشده WIN32_LEAN_AND_میانگین
#تعریف_کن WIN32_LEAN_AND_میانگین
#پایان_اگر
#ضمن <Windows.h>
#ضمن <XGameUI.h>
#ضمن <XUser.h>

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ساكن XTask_صف_Handle g_متن_Task_صف = عدم;
// Global because there can be only one text entry shown at once.
ساكن XAsync_بلوک *g_متن_بلوک = عدم;

// Creation parameters
ساكن منطقي g_Did_ثبات_Hints = خطأ;
ساكن حرف *g_Title_متن = عدم;
ساكن حرف *g_Description_متن = عدم;
ساكن حرف *g_Default_متن = عدم;
ساكن ثابت Sint32 g_Default_متن_درون_داد_Scope = (Sint32)XGame_Ui_متن_مدخل_درون_داد_Scope::Default;
ساكن Sint32 g_متن_درون_داد_Scope = g_Default_متن_درون_داد_Scope;
ساكن ثابت Sint32 g_Default_Max_متن_درازی = 1024; // as per doc: maximum allowed amount on consoles
ساكن Sint32 g_Max_متن_درازی = g_Default_Max_متن_درازی;

ساكن فراغ SDLCALL GDK_داخلی_Hint_Callback(
    فراغ *userdata,
    ثابت حرف *name,
    ثابت حرف *old_مقدار,
    ثابت حرف *new_مقدار)
{
    إذا (!userdata) {
        أرجع;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    إذا (userdata == &g_متن_درون_داد_Scope || userdata == &g_Max_متن_درازی) {
        // int32 hint
        Sint32 int_مقدار = (!new_مقدار || new_مقدار[0] == '\0') ? 0 : SDL_atoi(new_مقدار);
        إذا (userdata == &g_Max_متن_درازی && int_مقدار <= 0) {
            int_مقدار = g_Default_Max_متن_درازی;
        } وإلا إذا (userdata == &g_متن_درون_داد_Scope && int_مقدار < 0) {
            int_مقدار = g_Default_متن_درون_داد_Scope;
        }

        *(Sint32 *)userdata = int_مقدار;
    } وإلا {
        // string hint
        إذا (!new_مقدار || new_مقدار[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(حرف **)userdata);
            *(حرف **)userdata = عدم;
        } وإلا {
            حرف *newString = SDL_strdup(new_مقدار);
            إذا (newString) {
                // free previous value and write the new one
                SDL_free(*(حرف **)userdata);
                *(حرف **)userdata = newString;
            }
        }
    }
}

ساكن منطقي GDK_داخلی_Ensure_Task_صف(فراغ)
{
    إذا (!g_متن_Task_صف) {
        إذا (!SDL_Get_GDKTask_صف(&g_متن_Task_صف)) {
            // SetError will be done for us.
            أرجع خطأ;
        }
    }
    أرجع درست;
}

ساكن فراغ CALLBACK GDK_داخلی_متن_مدخل_Callback(XAsync_بلوک *async_بلوک)
{
    HRESULT hR = S_OK;
    Uint32 نتیجه_اندازه = 0;
    Uint32 نتیجه_استفاده_شده = 0;
    حرف *نتیجه_میانگیر = عدم;

    // The keyboard will be already hidden when we reach this code

    إذا (FAILED(hR = XGame_Ui_Show_متن_مدخل_نتیجه_اندازه(
                   async_بلوک,
                   &نتیجه_اندازه))) {
        SDL_مجموعه_Error("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } وإلا إذا (نتیجه_اندازه > 0) {
        // +1 to be super sure that the buffer will be null terminated
        نتیجه_میانگیر = (حرف *)SDL_calloc(1 + (size_t)نتیجه_اندازه, حجم(*نتیجه_میانگیر));
        إذا (نتیجه_میانگیر) {
            // still pass the original size that we got from ResultSize
            إذا (FAILED(hR = XGame_Ui_Show_متن_مدخل_نتیجه(
                           async_بلوک,
                           نتیجه_اندازه,
                           نتیجه_میانگیر,
                           &نتیجه_استفاده_شده))) {
                SDL_مجموعه_Error("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            وإلا إذا (نتیجه_استفاده_شده > 0 && نتیجه_میانگیر[0] != '\0') {
                // it's null terminated so it's fine
                SDL_Send_Keyboard_متن(نتیجه_میانگیر);
            }
            // we're done with the buffer
            SDL_free(نتیجه_میانگیر);
            نتیجه_میانگیر = عدم;
        }
    }

    // free the async block after we're done
    SDL_free(async_بلوک);
    async_بلوک = عدم;
    g_متن_بلوک = عدم; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

فراغ GDK_EnsureHints(فراغ)
{
    إذا (g_Did_ثبات_Hints == خطأ) {
        SDL_جمع_کن_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_TITLE,
            GDK_داخلی_Hint_Callback,
            &g_Title_متن);
        SDL_جمع_کن_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DESCRIPTION,
            GDK_داخلی_Hint_Callback,
            &g_Description_متن);
        SDL_جمع_کن_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DEFAULT_متن,
            GDK_داخلی_Hint_Callback,
            &g_Default_متن);
        SDL_جمع_کن_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_SCOPE,
            GDK_داخلی_Hint_Callback,
            &g_متن_درون_داد_Scope);
        SDL_جمع_کن_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_MAX_درازی,
            GDK_داخلی_Hint_Callback,
            &g_Max_متن_درازی);
        g_Did_ثبات_Hints = درست;
    }
}

منطقي GDK_شروع_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
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
    أرجع درست;
}

منطقي GDK_Stop_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // See notice in GDK_StartTextInput
    أرجع درست;
}

منطقي GDK_Update_متن_درون_داد_Area(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
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
    أرجع درست;
}

منطقي GDK_ClearComposition(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // See notice in GDK_StartTextInput
    أرجع درست;
}

منطقي GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    أرجع درست;
}

فراغ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    إذا (g_متن_بلوک) {
        // already showing the keyboard
        أرجع;
    }

    إذا (!GDK_داخلی_Ensure_Task_صف()) {
        // unable to obtain the SDL GDK queue
        أرجع;
    }

    g_متن_بلوک = (XAsync_بلوک *)SDL_calloc(1, حجم(*g_متن_بلوک));
    إذا (!g_متن_بلوک) {
        أرجع;
    }

    XGame_Ui_متن_مدخل_درون_داد_Scope scope;
    بدل (SDL_Get_متن_درون_داد_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_متن:
        scope = (XGame_Ui_متن_مدخل_درون_داد_Scope)g_متن_درون_داد_Scope;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::Email_Smtp_آدرس;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_USERNAME:
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::Password;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::Default;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد:
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::عدد;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::عدد;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
        scope = XGame_Ui_متن_مدخل_درون_داد_Scope::عدد;
        اكسر;
    }

    g_متن_بلوک->صف = g_متن_Task_صف;
    g_متن_بلوک->context = _this;
    g_متن_بلوک->callback = GDK_داخلی_متن_مدخل_Callback;
    إذا (SUCCEEDED(hR = XGame_Ui_Show_متن_مدخل_Async(
                   g_متن_بلوک,
                   g_Title_متن,
                   g_Description_متن,
                   g_Default_متن,
                   scope,
                   (uint32_t)g_Max_متن_درازی))) {
        SDL_SendScreenKeyboardShown();
    } وإلا {
        SDL_free(g_متن_بلوک);
        g_متن_بلوک = عدم;
        SDL_مجموعه_Error("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

فراغ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (g_متن_بلوک) {
        XAsyncCancel(g_متن_بلوک);
        // the completion callback will free the block
    }
}

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
