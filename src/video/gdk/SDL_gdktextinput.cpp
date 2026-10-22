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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_gdktextinput.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_GDK_TEXTINPUT

// GDK headers are weird here
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIN32_LEAN_AND_ਔਸਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WIN32_LEAN_AND_ਔਸਤ
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <Windows.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <XGameUI.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <XUser.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
ਸਥਿਰ XTask_ਕਤਾਰ_Handle g_ਪਾਠ_Task_ਕਤਾਰ = ਨਿਰਾ;
// Global because there can be only one text entry shown at once.
ਸਥਿਰ XAsync_ਖੰਡ *g_ਪਾਠ_ਖੰਡ = ਨਿਰਾ;

// Creation parameters
ਸਥਿਰ ਤਾਰਕਿਕ g_Did_ਰਜਿਸਟਰ_Hints = ਝੂਠ;
ਸਥਿਰ ਅੱਖਰ *g_Title_ਪਾਠ = ਨਿਰਾ;
ਸਥਿਰ ਅੱਖਰ *g_Description_ਪਾਠ = ਨਿਰਾ;
ਸਥਿਰ ਅੱਖਰ *g_Default_ਪਾਠ = ਨਿਰਾ;
ਸਥਿਰ ਅਚਲ Sint32 g_Default_ਪਾਠ_ਨਿਵੇਸ਼_Scope = (Sint32)XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::Default;
ਸਥਿਰ Sint32 g_ਪਾਠ_ਨਿਵੇਸ਼_Scope = g_Default_ਪਾਠ_ਨਿਵੇਸ਼_Scope;
ਸਥਿਰ ਅਚਲ Sint32 g_Default_Max_ਪਾਠ_ਲੰਮਾਈ = 1024; // as per doc: maximum allowed amount on consoles
ਸਥਿਰ Sint32 g_Max_ਪਾਠ_ਲੰਮਾਈ = g_Default_Max_ਪਾਠ_ਲੰਮਾਈ;

ਸਥਿਰ ਖਾਲੀ SDLCALL GDK_ਅੰਦਰੂਨੀ_Hint_Callback(
    ਖਾਲੀ *userdata,
    ਅਚਲ ਅੱਖਰ *name,
    ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ,
    ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    ਜੇ (!userdata) {
        ਵਾਪਸ;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    ਜੇ (userdata == &g_ਪਾਠ_ਨਿਵੇਸ਼_Scope || userdata == &g_Max_ਪਾਠ_ਲੰਮਾਈ) {
        // int32 hint
        Sint32 int_ਮੁੱਲ = (!new_ਮੁੱਲ || new_ਮੁੱਲ[0] == '\0') ? 0 : SDL_atoi(new_ਮੁੱਲ);
        ਜੇ (userdata == &g_Max_ਪਾਠ_ਲੰਮਾਈ && int_ਮੁੱਲ <= 0) {
            int_ਮੁੱਲ = g_Default_Max_ਪਾਠ_ਲੰਮਾਈ;
        } ਨਹੀਂਤਾਂ ਜੇ (userdata == &g_ਪਾਠ_ਨਿਵੇਸ਼_Scope && int_ਮੁੱਲ < 0) {
            int_ਮੁੱਲ = g_Default_ਪਾਠ_ਨਿਵੇਸ਼_Scope;
        }

        *(Sint32 *)userdata = int_ਮੁੱਲ;
    } ਨਹੀਂਤਾਂ {
        // string hint
        ਜੇ (!new_ਮੁੱਲ || new_ਮੁੱਲ[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(ਅੱਖਰ **)userdata);
            *(ਅੱਖਰ **)userdata = ਨਿਰਾ;
        } ਨਹੀਂਤਾਂ {
            ਅੱਖਰ *newString = SDL_strdup(new_ਮੁੱਲ);
            ਜੇ (newString) {
                // free previous value and write the new one
                SDL_free(*(ਅੱਖਰ **)userdata);
                *(ਅੱਖਰ **)userdata = newString;
            }
        }
    }
}

ਸਥਿਰ ਤਾਰਕਿਕ GDK_ਅੰਦਰੂਨੀ_Ensure_Task_ਕਤਾਰ(ਖਾਲੀ)
{
    ਜੇ (!g_ਪਾਠ_Task_ਕਤਾਰ) {
        ਜੇ (!SDL_Get_GDKTask_ਕਤਾਰ(&g_ਪਾਠ_Task_ਕਤਾਰ)) {
            // SetError will be done for us.
            ਵਾਪਸ ਝੂਠ;
        }
    }
    ਵਾਪਸ ਸੱਚ;
}

ਸਥਿਰ ਖਾਲੀ CALLBACK GDK_ਅੰਦਰੂਨੀ_ਪਾਠ_ਇੰਦਰਾਜ_Callback(XAsync_ਖੰਡ *async_ਖੰਡ)
{
    HRESULT hR = S_OK;
    Uint32 ਨਤੀਜਾ_ਮਾਪ = 0;
    Uint32 ਨਤੀਜਾ_ਵਰਤਿਆ = 0;
    ਅੱਖਰ *ਨਤੀਜਾ_ਬਫਰ = ਨਿਰਾ;

    // The keyboard will be already hidden when we reach this code

    ਜੇ (FAILED(hR = XGame_Ui_Show_ਪਾਠ_ਇੰਦਰਾਜ_ਨਤੀਜਾ_ਮਾਪ(
                   async_ਖੰਡ,
                   &ਨਤੀਜਾ_ਮਾਪ))) {
        SDL_ਸੈੱਟ_Error("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } ਨਹੀਂਤਾਂ ਜੇ (ਨਤੀਜਾ_ਮਾਪ > 0) {
        // +1 to be super sure that the buffer will be null terminated
        ਨਤੀਜਾ_ਬਫਰ = (ਅੱਖਰ *)SDL_calloc(1 + (size_t)ਨਤੀਜਾ_ਮਾਪ, ਆਕਾਰ(*ਨਤੀਜਾ_ਬਫਰ));
        ਜੇ (ਨਤੀਜਾ_ਬਫਰ) {
            // still pass the original size that we got from ResultSize
            ਜੇ (FAILED(hR = XGame_Ui_Show_ਪਾਠ_ਇੰਦਰਾਜ_ਨਤੀਜਾ(
                           async_ਖੰਡ,
                           ਨਤੀਜਾ_ਮਾਪ,
                           ਨਤੀਜਾ_ਬਫਰ,
                           &ਨਤੀਜਾ_ਵਰਤਿਆ))) {
                SDL_ਸੈੱਟ_Error("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            ਨਹੀਂਤਾਂ ਜੇ (ਨਤੀਜਾ_ਵਰਤਿਆ > 0 && ਨਤੀਜਾ_ਬਫਰ[0] != '\0') {
                // it's null terminated so it's fine
                SDL_Send_Keyboard_ਪਾਠ(ਨਤੀਜਾ_ਬਫਰ);
            }
            // we're done with the buffer
            SDL_free(ਨਤੀਜਾ_ਬਫਰ);
            ਨਤੀਜਾ_ਬਫਰ = ਨਿਰਾ;
        }
    }

    // free the async block after we're done
    SDL_free(async_ਖੰਡ);
    async_ਖੰਡ = ਨਿਰਾ;
    g_ਪਾਠ_ਖੰਡ = ਨਿਰਾ; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

ਖਾਲੀ GDK_EnsureHints(ਖਾਲੀ)
{
    ਜੇ (g_Did_ਰਜਿਸਟਰ_Hints == ਝੂਠ) {
        SDL_ਜੋੜੋ_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_TITLE,
            GDK_ਅੰਦਰੂਨੀ_Hint_Callback,
            &g_Title_ਪਾਠ);
        SDL_ਜੋੜੋ_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DESCRIPTION,
            GDK_ਅੰਦਰੂਨੀ_Hint_Callback,
            &g_Description_ਪਾਠ);
        SDL_ਜੋੜੋ_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DEFAULT_ਪਾਠ,
            GDK_ਅੰਦਰੂਨੀ_Hint_Callback,
            &g_Default_ਪਾਠ);
        SDL_ਜੋੜੋ_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_SCOPE,
            GDK_ਅੰਦਰੂਨੀ_Hint_Callback,
            &g_ਪਾਠ_ਨਿਵੇਸ਼_Scope);
        SDL_ਜੋੜੋ_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_MAX_ਲੰਮਾਈ,
            GDK_ਅੰਦਰੂਨੀ_Hint_Callback,
            &g_Max_ਪਾਠ_ਲੰਮਾਈ);
        g_Did_ਰਜਿਸਟਰ_Hints = ਸੱਚ;
    }
}

ਤਾਰਕਿਕ GDK_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
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
    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ GDK_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // See notice in GDK_StartTextInput
    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ GDK_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
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
    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ GDK_ClearComposition(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // See notice in GDK_StartTextInput
    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    ਜੇ (g_ਪਾਠ_ਖੰਡ) {
        // already showing the keyboard
        ਵਾਪਸ;
    }

    ਜੇ (!GDK_ਅੰਦਰੂਨੀ_Ensure_Task_ਕਤਾਰ()) {
        // unable to obtain the SDL GDK queue
        ਵਾਪਸ;
    }

    g_ਪਾਠ_ਖੰਡ = (XAsync_ਖੰਡ *)SDL_calloc(1, ਆਕਾਰ(*g_ਪਾਠ_ਖੰਡ));
    ਜੇ (!g_ਪਾਠ_ਖੰਡ) {
        ਵਾਪਸ;
    }

    XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope scope;
    ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
    ਮੂਲ:
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ:
        scope = (XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope)g_ਪਾਠ_ਨਿਵੇਸ਼_Scope;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_NAME:
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::Default;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_EMAIL:
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::Email_Smtp_ਪਤਾ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_USERNAME:
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::Default;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_HIDDEN:
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::Password;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_VISIBLE:
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::Default;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ:
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::ਸੰਖਿਆ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::ਸੰਖਿਆ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_VISIBLE:
        scope = XGame_Ui_ਪਾਠ_ਇੰਦਰਾਜ_ਨਿਵੇਸ਼_Scope::ਸੰਖਿਆ;
        ਰੋਕੋ;
    }

    g_ਪਾਠ_ਖੰਡ->ਕਤਾਰ = g_ਪਾਠ_Task_ਕਤਾਰ;
    g_ਪਾਠ_ਖੰਡ->context = _this;
    g_ਪਾਠ_ਖੰਡ->callback = GDK_ਅੰਦਰੂਨੀ_ਪਾਠ_ਇੰਦਰਾਜ_Callback;
    ਜੇ (SUCCEEDED(hR = XGame_Ui_Show_ਪਾਠ_ਇੰਦਰਾਜ_Async(
                   g_ਪਾਠ_ਖੰਡ,
                   g_Title_ਪਾਠ,
                   g_Description_ਪਾਠ,
                   g_Default_ਪਾਠ,
                   scope,
                   (uint32_t)g_Max_ਪਾਠ_ਲੰਮਾਈ))) {
        SDL_SendScreenKeyboardShown();
    } ਨਹੀਂਤਾਂ {
        SDL_free(g_ਪਾਠ_ਖੰਡ);
        g_ਪਾਠ_ਖੰਡ = ਨਿਰਾ;
        SDL_ਸੈੱਟ_Error("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

ਖਾਲੀ GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (g_ਪਾਠ_ਖੰਡ) {
        XAsyncCancel(g_ਪਾਠ_ਖੰਡ);
        // the completion callback will free the block
    }
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
