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
#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "SDL_gdktextinput.h"

#यदि_परिभाषितम् SDL_GDK_TEXTINPUT

// GDK headers are weird here
#यदि_अपरिभाषितम् WIN32_LEAN_AND_माध्यम्
#परिभाषय WIN32_LEAN_AND_माध्यम्
#यदि_अन्तः
#अन्तर्भाव <Windows.h>
#अन्तर्भाव <XGameUI.h>
#अन्तर्भाव <XUser.h>

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../windows/SDL_windowsvideo.h"

// TODO: Have a separate task queue for text input perhaps?
स्थिर XTaskQueueHandle g_TextTaskQueue = रिक्त;
// Global because there can be only one text entry shown at once.
स्थिर XAsync_खण्डम् *g_Text_खण्डम् = रिक्त;

// Creation parameters
स्थिर तार्किक g_Did_पञ्जिकाकोशः_Hints = असत्य;
स्थिर वर्ण *g_TitleText = रिक्त;
स्थिर वर्ण *g_DescriptionText = रिक्त;
स्थिर वर्ण *g_DefaultText = रिक्त;
स्थिर ध्रुव Sint32 g_Default_Text_निवेशः_Scope = (Sint32)XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::Default;
स्थिर Sint32 g_Text_निवेशः_Scope = g_Default_Text_निवेशः_Scope;
स्थिर ध्रुव Sint32 g_Default_Max_Text_दीर्घता = 1024; // as per doc: maximum allowed amount on consoles
स्थिर Sint32 g_Max_Text_दीर्घता = g_Default_Max_Text_दीर्घता;

स्थिर शून्य SDLCALL GDK_आन्तरिकम्_Hint_Callback(
    शून्य *userdata,
    ध्रुव वर्ण *name,
    ध्रुव वर्ण *old_मानम्,
    ध्रुव वर्ण *new_मानम्)
{
    यदि (!userdata) {
        प्रत्यागम;
    }

    // oldValue is ignored because we store it ourselves.
    // name is ignored because we deduce it from userdata

    यदि (userdata == &g_Text_निवेशः_Scope || userdata == &g_Max_Text_दीर्घता) {
        // int32 hint
        Sint32 int_मानम् = (!new_मानम् || new_मानम्[0] == '\0') ? 0 : SDL_atoi(new_मानम्);
        यदि (userdata == &g_Max_Text_दीर्घता && int_मानम् <= 0) {
            int_मानम् = g_Default_Max_Text_दीर्घता;
        } अन्यथा यदि (userdata == &g_Text_निवेशः_Scope && int_मानम् < 0) {
            int_मानम् = g_Default_Text_निवेशः_Scope;
        }

        *(Sint32 *)userdata = int_मानम्;
    } अन्यथा {
        // string hint
        यदि (!new_मानम् || new_मानम्[0] == '\0') {
            // treat empty or NULL strings as just NULL for this impl
            SDL_free(*(वर्ण **)userdata);
            *(वर्ण **)userdata = रिक्त;
        } अन्यथा {
            वर्ण *newString = SDL_strdup(new_मानम्);
            यदि (newString) {
                // free previous value and write the new one
                SDL_free(*(वर्ण **)userdata);
                *(वर्ण **)userdata = newString;
            }
        }
    }
}

स्थिर तार्किक GDK_आन्तरिकम्_Ensure_Task_Queue(शून्य)
{
    यदि (!g_TextTaskQueue) {
        यदि (!SDL_GetGDKTaskQueue(&g_TextTaskQueue)) {
            // SetError will be done for us.
            प्रत्यागम असत्य;
        }
    }
    प्रत्यागम सत्य;
}

स्थिर शून्य CALLBACK GDK_आन्तरिकम्_Text_प्रविष्टिः_Callback(XAsync_खण्डम् *async_खण्डम्)
{
    HRESULT hR = S_OK;
    Uint32 परिणाम_आकार = 0;
    Uint32 परिणाम_प्रयुक्तम् = 0;
    वर्ण *परिणाम_बफर = रिक्त;

    // The keyboard will be already hidden when we reach this code

    यदि (FAILED(hR = XGame_Ui_Show_Text_प्रविष्टिः_परिणाम_आकार(
                   async_खण्डम्,
                   &परिणाम_आकार))) {
        SDL_समुच्चयः_Error("XGameUiShowTextEntryResultSize failure with HRESULT of %08X", hR);
    } अन्यथा यदि (परिणाम_आकार > 0) {
        // +1 to be super sure that the buffer will be null terminated
        परिणाम_बफर = (वर्ण *)SDL_calloc(1 + (size_t)परिणाम_आकार, परिमाण(*परिणाम_बफर));
        यदि (परिणाम_बफर) {
            // still pass the original size that we got from ResultSize
            यदि (FAILED(hR = XGame_Ui_Show_Text_प्रविष्टिः_परिणाम(
                           async_खण्डम्,
                           परिणाम_आकार,
                           परिणाम_बफर,
                           &परिणाम_प्रयुक्तम्))) {
                SDL_समुच्चयः_Error("XGameUiShowTextEntryResult failure with HRESULT of %08X", hR);
            }
            // check that we have some text and that we weren't cancelled
            अन्यथा यदि (परिणाम_प्रयुक्तम् > 0 && परिणाम_बफर[0] != '\0') {
                // it's null terminated so it's fine
                SDL_SendKeyboardText(परिणाम_बफर);
            }
            // we're done with the buffer
            SDL_free(परिणाम_बफर);
            परिणाम_बफर = रिक्त;
        }
    }

    // free the async block after we're done
    SDL_free(async_खण्डम्);
    async_खण्डम् = रिक्त;
    g_Text_खण्डम् = रिक्त; // once we do this we're fully done with the keyboard

    SDL_SendScreenKeyboardHidden();
}

शून्य GDK_EnsureHints(शून्य)
{
    यदि (g_Did_पञ्जिकाकोशः_Hints == असत्य) {
        SDL_सङ्कलय_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_TITLE,
            GDK_आन्तरिकम्_Hint_Callback,
            &g_TitleText);
        SDL_सङ्कलय_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DESCRIPTION,
            GDK_आन्तरिकम्_Hint_Callback,
            &g_DescriptionText);
        SDL_सङ्कलय_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_DEFAULT_TEXT,
            GDK_आन्तरिकम्_Hint_Callback,
            &g_DefaultText);
        SDL_सङ्कलय_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_SCOPE,
            GDK_आन्तरिकम्_Hint_Callback,
            &g_Text_निवेशः_Scope);
        SDL_सङ्कलय_Hint_Callback(
            SDL_HINT_GDK_TEXTINPUT_MAX_दीर्घता,
            GDK_आन्तरिकम्_Hint_Callback,
            &g_Max_Text_दीर्घता);
        g_Did_पञ्जिकाकोशः_Hints = सत्य;
    }
}

तार्किक GDK_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
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
    प्रत्यागम सत्य;
}

तार्किक GDK_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // See notice in GDK_StartTextInput
    प्रत्यागम सत्य;
}

तार्किक GDK_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
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
    प्रत्यागम सत्य;
}

तार्किक GDK_ClearComposition(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // See notice in GDK_StartTextInput
    प्रत्यागम सत्य;
}

तार्किक GDK_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    // Currently always true for this input method
    प्रत्यागम सत्य;
}

शून्य GDK_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    /*
     * There is XGameUiTextEntryOpen but it's only in online docs,
     * My October Update 1 GDKX installation does not have this function defined
     * and as such I decided not to use it at all, since some folks might use even older GDKs.
     *
     * That means the only text input option for us is a simple virtual keyboard widget.
     */

    HRESULT hR = S_OK;

    यदि (g_Text_खण्डम्) {
        // already showing the keyboard
        प्रत्यागम;
    }

    यदि (!GDK_आन्तरिकम्_Ensure_Task_Queue()) {
        // unable to obtain the SDL GDK queue
        प्रत्यागम;
    }

    g_Text_खण्डम् = (XAsync_खण्डम् *)SDL_calloc(1, परिमाण(*g_Text_खण्डम्));
    यदि (!g_Text_खण्डम्) {
        प्रत्यागम;
    }

    XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope scope;
    विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
    स्वभाव:
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        scope = (XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope)g_Text_निवेशः_Scope;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::Email_Smtp_स्थानाङ्कः;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::Password;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::Default;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या:
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::सङ्ख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_HIDDEN:
        // FIXME: Password or number scope?
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::सङ्ख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_VISIBLE:
        scope = XGame_Ui_Text_प्रविष्टिः_निवेशः_Scope::सङ्ख्या;
        भङ्ग;
    }

    g_Text_खण्डम्->queue = g_TextTaskQueue;
    g_Text_खण्डम्->context = _this;
    g_Text_खण्डम्->callback = GDK_आन्तरिकम्_Text_प्रविष्टिः_Callback;
    यदि (SUCCEEDED(hR = XGame_Ui_Show_Text_प्रविष्टिः_Async(
                   g_Text_खण्डम्,
                   g_TitleText,
                   g_DescriptionText,
                   g_DefaultText,
                   scope,
                   (uint32_t)g_Max_Text_दीर्घता))) {
        SDL_SendScreenKeyboardShown();
    } अन्यथा {
        SDL_free(g_Text_खण्डम्);
        g_Text_खण्डम् = रिक्त;
        SDL_समुच्चयः_Error("XGameUiShowTextEntryAsync failure with HRESULT of %08X", hR);
    }
}

शून्य GDK_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (g_Text_खण्डम्) {
        XAsyncCancel(g_Text_खण्डम्);
        // the completion callback will free the block
    }
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
