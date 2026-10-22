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
#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "SDL_gdktextinput.h"

#నిర్వచితమైతే SDL_GDK_TEXTINPUT

// GDK headers are weird here
#నిర్వచితం_కాకపోతే WIN32_LEAN_AND_సగటు
#నిర్వచించు WIN32_LEAN_AND_సగటు
#అయితే_ముగింపు
#అన్తర్భావ <Windows.h>
#అన్తర్భావ <XGameUI.h>
#అన్తర్భావ <XUser.h>

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
స్థిర XTask_వరుస_Handle g_పాఠ్యం_Task_వరుస = ఖాళీ;
// Global because there can be only one text entry shown at once.
స్థిర XAsync_ఖండం *g_పాఠ్యం_ఖండం = ఖాళీ;

// Creation parameters
స్థిర తార్కిక g_Did_రిజిస్టరు_Hints = అబద్ధం;
స్థిర అక్షరం *g_Title_పాఠ్యం = ఖాళీ;
స్థిర అక్షరం *g_Description_పాఠ్యం = ఖాళీ;
స్థిర అక్షరం *g_Default_పాఠ్యం = ఖాళీ;
స్థిర స్థిరరాశి Sint32 g_Default_పాఠ్యం_ఆదానం_Scope = (Sint32)XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::Default;
స్థిర Sint32 g_పాఠ్యం_ఆదానం_Scope = g_Default_పాఠ్యం_ఆదానం_Scope;
స్థిర స్థిరరాశి Sint32 g_Default_Max_పాఠ్యం_నిడివి = 1024; // as per doc: maximum allowed amount on consoles
స్థిర Sint32 g_Max_పాఠ్యం_నిడివి = g_Default_Max_పాఠ్యం_నిడివి;

స్థిర శూన్య SDLCALL GDK_అంతర్గత_Hint_Callback(
    శూన్య *userdata,
    స్థిరరాశి అక్షరం *name,
    స్థిరరాశి అక్షరం *old_విలువ,
    స్థిరరాశి అక్షరం *new_విలువ)
{
    ఒకవేళ (!userdata) {
        తిరిగి;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    ఒకవేళ (userdata == &g_పాఠ్యం_ఆదానం_Scope || userdata == &g_Max_పాఠ్యం_నిడివి) {
        // int32 hint
        Sint32 int_విలువ = (!new_విలువ || new_విలువ[0] == '\0') ? 0 : SDL_atoi(new_విలువ);
        ఒకవేళ (userdata == &g_Max_పాఠ్యం_నిడివి && int_విలువ <= 0) {
            int_విలువ = g_Default_Max_పాఠ్యం_నిడివి;
        } లేకపోతే ఒకవేళ (userdata == &g_పాఠ్యం_ఆదానం_Scope && int_విలువ < 0) {
            int_విలువ = g_Default_పాఠ్యం_ఆదానం_Scope;
        }

        *(Sint32 *)userdata = int_విలువ;
    } లేకపోతే {
        // string hint
        ఒకవేళ (!new_విలువ || new_విలువ[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(అక్షరం **)userdata);
            *(అక్షరం **)userdata = ఖాళీ;
        } లేకపోతే {
            అక్షరం *newString = SDL_strdup(new_విలువ);
            ఒకవేళ (newString) {
                // free previous value and write the new one
                SDL_free(*(అక్షరం **)userdata);
                *(అక్షరం **)userdata = newString;
            }
        }
    }
}

స్థిర తార్కిక GDK_అంతర్గత_Ensure_Task_వరుస(శూన్య)
{
    ఒకవేళ (!g_పాఠ్యం_Task_వరుస) {
        ఒకవేళ (!SDL_Get_GDKTask_వరుస(&g_పాఠ్యం_Task_వరుస)) {
            // SetError will be done for us.
            తిరిగి అబద్ధం;
        }
    }
    తిరిగి నిజం;
}

స్థిర శూన్య CALLBACK GDK_అంతర్గత_పాఠ్యం_నమోదు_Callback(XAsync_ఖండం *async_ఖండం)
{
    HRESULT hR = S_OK;
    Uint32 ఫలితం_కొలత = 0;
    Uint32 ఫలితం_వాడిన = 0;
    అక్షరం *ఫలితం_బఫరు = ఖాళీ;

    // The keyboard will be already hidden when we reach this code

    ఒకవేళ (FAILED(hR = XGame_Ui_Show_పాఠ్యం_నమోదు_ఫలితం_కొలత(
                   async_ఖండం,
                   &ఫలితం_కొలత))) {
        SDL_సమితి_Error("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } లేకపోతే ఒకవేళ (ఫలితం_కొలత > 0) {
        // +1 to be super sure that the buffer will be null terminated
        ఫలితం_బఫరు = (అక్షరం *)SDL_calloc(1 + (size_t)ఫలితం_కొలత, పరిమాణం(*ఫలితం_బఫరు));
        ఒకవేళ (ఫలితం_బఫరు) {
            // still pass the original size that we got from ResultSize
            ఒకవేళ (FAILED(hR = XGame_Ui_Show_పాఠ్యం_నమోదు_ఫలితం(
                           async_ఖండం,
                           ఫలితం_కొలత,
                           ఫలితం_బఫరు,
                           &ఫలితం_వాడిన))) {
                SDL_సమితి_Error("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            లేకపోతే ఒకవేళ (ఫలితం_వాడిన > 0 && ఫలితం_బఫరు[0] != '\0') {
                // it's null terminated so it's fine
                SDL_Send_Keyboard_పాఠ్యం(ఫలితం_బఫరు);
            }
            // we're done with the buffer
            SDL_free(ఫలితం_బఫరు);
            ఫలితం_బఫరు = ఖాళీ;
        }
    }

    // free the async block after we're done
    SDL_free(async_ఖండం);
    async_ఖండం = ఖాళీ;
    g_పాఠ్యం_ఖండం = ఖాళీ; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

శూన్య GDK_EnsureHints(శూన్య)
{
    ఒకవేళ (g_Did_రిజిస్టరు_Hints == అబద్ధం) {
        SDL_కూడు_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_TITLE,
            GDK_అంతర్గత_Hint_Callback,
            &g_Title_పాఠ్యం);
        SDL_కూడు_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DESCRIPTION,
            GDK_అంతర్గత_Hint_Callback,
            &g_Description_పాఠ్యం);
        SDL_కూడు_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DEFAULT_పాఠ్యం,
            GDK_అంతర్గత_Hint_Callback,
            &g_Default_పాఠ్యం);
        SDL_కూడు_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_SCOPE,
            GDK_అంతర్గత_Hint_Callback,
            &g_పాఠ్యం_ఆదానం_Scope);
        SDL_కూడు_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_MAX_నిడివి,
            GDK_అంతర్గత_Hint_Callback,
            &g_Max_పాఠ్యం_నిడివి);
        g_Did_రిజిస్టరు_Hints = నిజం;
    }
}

తార్కిక GDK_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
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
    తిరిగి నిజం;
}

తార్కిక GDK_Stop_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // See notice in GDK_StartTextInput
    తిరిగి నిజం;
}

తార్కిక GDK_Update_పాఠ్యం_ఆదానం_Area(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
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
    తిరిగి నిజం;
}

తార్కిక GDK_ClearComposition(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // See notice in GDK_StartTextInput
    తిరిగి నిజం;
}

తార్కిక GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    తిరిగి నిజం;
}

శూన్య GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    ఒకవేళ (g_పాఠ్యం_ఖండం) {
        // already showing the keyboard
        తిరిగి;
    }

    ఒకవేళ (!GDK_అంతర్గత_Ensure_Task_వరుస()) {
        // unable to obtain the SDL GDK queue
        తిరిగి;
    }

    g_పాఠ్యం_ఖండం = (XAsync_ఖండం *)SDL_calloc(1, పరిమాణం(*g_పాఠ్యం_ఖండం));
    ఒకవేళ (!g_పాఠ్యం_ఖండం) {
        తిరిగి;
    }

    XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope scope;
    ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
    అప్రమేయ:
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం:
        scope = (XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope)g_పాఠ్యం_ఆదానం_Scope;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_NAME:
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::Default;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_EMAIL:
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::Email_Smtp_చిరునామా;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_USERNAME:
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::Default;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_HIDDEN:
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::Password;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_VISIBLE:
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::Default;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య:
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::సంఖ్య;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::సంఖ్య;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_VISIBLE:
        scope = XGame_Ui_పాఠ్యం_నమోదు_ఆదానం_Scope::సంఖ్య;
        ఆపు;
    }

    g_పాఠ్యం_ఖండం->వరుస = g_పాఠ్యం_Task_వరుస;
    g_పాఠ్యం_ఖండం->context = _this;
    g_పాఠ్యం_ఖండం->callback = GDK_అంతర్గత_పాఠ్యం_నమోదు_Callback;
    ఒకవేళ (SUCCEEDED(hR = XGame_Ui_Show_పాఠ్యం_నమోదు_Async(
                   g_పాఠ్యం_ఖండం,
                   g_Title_పాఠ్యం,
                   g_Description_పాఠ్యం,
                   g_Default_పాఠ్యం,
                   scope,
                   (uint32_t)g_Max_పాఠ్యం_నిడివి))) {
        SDL_SendScreenKeyboardShown();
    } లేకపోతే {
        SDL_free(g_పాఠ్యం_ఖండం);
        g_పాఠ్యం_ఖండం = ఖాళీ;
        SDL_సమితి_Error("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

శూన్య GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (g_పాఠ్యం_ఖండం) {
        XAsyncCancel(g_పాఠ్యం_ఖండం);
        // the completion callback will free the block
    }
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
